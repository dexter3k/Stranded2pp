#include "SaveGameUtils.h"

#include <iostream>

#include "Engine.h"

#include "common/ByteBuffer.h"
#include "common/FileSystem.h"
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "graphics/Image.h"
#include "graphics/Color.h"
#include "utils/StringUtils.h"

namespace
{

struct MainHeader
{
	std::string identificationString = "";
	std::string gameVersion = "";
	std::string date = "";
	std::string time = "";
	std::string format = "";
	std::string mode = "";
};

struct ColorMapData
{
	uint32_t size;

	std::vector<gfx::Color> colorMap;
};

bool readMainHeader(ByteBuffer & buffer, MainHeader & mainHeader)
{
	mainHeader.identificationString = buffer.readLine();
	if (!string::startsWith(
			mainHeader.identificationString,
			"### Stranded II"))
	{
		std::cout << "Wrong (corrupted?) header" << std::endl;

		return false;
	}

	mainHeader.gameVersion = buffer.readLine();
	mainHeader.date = buffer.readLine();
	mainHeader.time = buffer.readLine();
	mainHeader.format = buffer.readLine();
	mainHeader.mode = buffer.readLine();

	return true;
}

bool readPreviewImage(ByteBuffer & buffer, gfx::Image & image)
{
	image.create(math::Vector2u(96, 72), gfx::Color(255, 255, 255));

	for (unsigned x = 0; x < 96; ++x) {
		for (unsigned y = 0; y < 72; ++y) {
			uint8_t red = buffer.readUint8();
			uint8_t green = buffer.readUint8();
			uint8_t blue = buffer.readUint8();

			image.setPixel(x, y, gfx::Color(red, green, blue));
		}
	}

	return true;
}

bool readColorMap(ByteBuffer & buffer, ColorMapData & data)
{
	data.size = buffer.readUint32();

	data.colorMap.resize(data.size * data.size, gfx::Color(255, 255, 255));

	gfx::Image debugImage;
	debugImage.create(math::Vector2u(data.size, data.size), gfx::Color(255, 255, 255));

	for (unsigned x = 0; x < data.size; ++x) {
		for (unsigned y = 0; y < data.size; ++y) {
			uint8_t red = buffer.readUint8();
			uint8_t green = buffer.readUint8();
			uint8_t blue = buffer.readUint8();

			data.colorMap[x + y * data.size] = gfx::Color(red, green, blue);
			debugImage.setPixel(x, y, gfx::Color(red, green, blue));
		}
	}

	debugImage.saveToFile("colorMapDebug.png");

	return true;
}

} // anonymous namespace

namespace save
{

bool loadFromFile(std::string const & filename, Engine & engine)
{
	if (!fs::checkFileExists(filename)) {
		std::cout << "Unable to load map '" << filename
			<< "': file not found" << std::endl;

		return false;
	}

	ByteBuffer buffer(fs::getFileSize(filename));
	if (!fs::loadFile(filename, buffer))
	{
		std::cout << "Unable to load '" << filename << "'" << std::endl;

		return false;
	}

	// Main header data
	MainHeader mainHeader;
	if (!readMainHeader(buffer, mainHeader))
	{
		std::cout << "Unable to read main header in '" << filename << "'!"
			<< std::endl;

		return false;
	}

	std::cout << "Loading map: " << "[" << mainHeader.gameVersion << "] "
		<< mainHeader.date << " " << mainHeader.time << " " <<
		mainHeader.format << " " << mainHeader.mode << std::endl;

	// Header OK

	struct
	{
		int object = 0;
		int unit = 0;
		int item = 0;
	} dataFormat;

	std::string const dataFormatString = buffer.readLine();

	if (dataFormatString != "") {
		dataFormat.object = std::stoi(dataFormatString.substr(1, 1));
		dataFormat.unit = std::stoi(dataFormatString.substr(2, 1));
		dataFormat.item = std::stoi(dataFormatString.substr(3, 1));
	}

	// Skip reserved space
	for (unsigned i = 0; i < 5; ++i) {
		buffer.readLine();
	}

	// Load 96 x 72 R8G8B8 raw image
	gfx::Image previewImage;
	if (!readPreviewImage(buffer, previewImage)) {
		return false;
	}

	// Password is not checked during normal play
	buffer.readBool();
	buffer.readLine();

	uint32_t day = buffer.readUint32();
	uint8_t hour = buffer.readUint8();
	uint8_t minute = buffer.readUint8();
	uint8_t freezeTime = buffer.readUint8(); // might be bool
	std::string skybox = buffer.readString(buffer.readUint32());
	uint8_t multiplayer = buffer.readUint8(); // also might be bool
	uint8_t climate = buffer.readUint8();
	std::string music = buffer.readString(buffer.readUint32());
	std::string brief = buffer.readString(buffer.readUint32());
	/* uint8_t fog0 = */ buffer.readUint8();
	/* uint8_t fog1 = */ buffer.readUint8();
	/* uint8_t fog2 = */ buffer.readUint8();
	/* uint8_t fog3 = */ buffer.readUint8();
	buffer.readUint8(); // reserved

	engine.setupGame(day, hour, minute, freezeTime, skybox, multiplayer,
		climate, music, brief);

	// Quickslots
	std::vector<std::string> quickslots(10, "");
	for (unsigned i = 0; i < 10; ++i) {
		quickslots[i] = buffer.readString(buffer.readUint32());
	}
	engine.setupQuickslots(quickslots);

	// Color map
	ColorMapData colorMapData;
	if (!readColorMap(buffer, colorMapData)) {
		std::cout << "Unable to load color map" << std::endl;

		return false;
	}

	uint32_t mapSize = buffer.readUint32();

	std::cout << "Colormap size: " << colorMapData.size << std::endl;
	std::cout << "Map size: " << mapSize << std::endl;

	uint32_t heightMapSize = mapSize + 1;

	std::vector<float> heightMap(heightMapSize * heightMapSize, 0.0f);
	for (unsigned x = 0; x < heightMapSize; ++x) {
		for (unsigned y = 0; y < heightMapSize; ++y) {
			heightMap[x + y * heightMapSize] = buffer.readFloat();
		}
	}

	uint32_t grassMapSize = colorMapData.size + 1;

	std::vector<uint8_t> grassMap(grassMapSize * grassMapSize, 0);
	for (unsigned x = 0; x < grassMapSize; ++x) {
		for (unsigned y = 0; y < grassMapSize; ++y) {
			grassMap[x + y * grassMapSize] = buffer.readUint8();
		}
	}

	if (!engine.setupTerrain(mapSize, heightMap, colorMapData.size,
		colorMapData.colorMap, grassMap))
	{
		return false;
	}

	engine.onPreload();

	// Now all terrain info, game script, etc is loaded. We can start adding units

	// "Stuff"

	// Objects
	uint32_t objectCount = buffer.readUint32();
	std::cout << "Object count: " << objectCount << std::endl;
	for (unsigned i = 0; i < objectCount; ++i) {
		uint32_t objectId = buffer.readUint32();

		uint16_t objectType = 0;
		if (dataFormat.object != 0) {
			objectType = buffer.readUint16();
		} else {
			objectType = buffer.readUint8();
		}
		
		float posX = buffer.readFloat();
		float posZ = buffer.readFloat();
		float yaw = buffer.readFloat();
		float health = buffer.readFloat();
		float maxHealth = buffer.readFloat();
		uint32_t dayTimer = buffer.readUint32();

		engine.placeObject(objectId, objectType, posX, posZ, yaw, health, maxHealth, dayTimer);
	}

	// Units
	uint32_t unitCount = buffer.readUint32();
	std::cout << "Unit count: " << unitCount << std::endl;
	for (unsigned i = 0; i < unitCount; ++i) {
		uint32_t unitId = buffer.readUint32();

		uint16_t unitType = 0;
		if (dataFormat.unit != 0) {
			unitType = buffer.readUint16();
		} else {
			unitType = buffer.readUint8();
		}

		float posX = buffer.readFloat();
		float posY = buffer.readFloat();
		float posZ = buffer.readFloat();
		float yaw = buffer.readFloat();
		float health = buffer.readFloat();
		float maxHealth = buffer.readFloat();
		float hunger = buffer.readFloat();
		float thirst = buffer.readFloat();
		float exhaustion = buffer.readFloat();
		float aiX = buffer.readFloat();
		float aiZ = buffer.readFloat();

		engine.placeUnit(unitId, unitType, posX, posY, posZ, yaw, health,
			maxHealth, hunger, thirst, exhaustion, aiX, aiZ);
	}

	// Items
	uint32_t itemCount = buffer.readUint32();
	std::cout << "Item count: " << itemCount << std::endl;
	for (unsigned i = 0; i < itemCount; ++i) {
		uint32_t itemId = buffer.readUint32();

		uint16_t itemType = 0;
		if (dataFormat.item != 0) {
			itemType = buffer.readUint16();
		} else {
			itemType = buffer.readUint8();
		}

		float posX = buffer.readFloat();
		float posY = buffer.readFloat();
		float posZ = buffer.readFloat();
		float yaw = buffer.readFloat();
		float health = buffer.readFloat();
		uint32_t count = buffer.readUint32();
		uint8_t parentClass = buffer.readUint8();
		uint8_t parentMode = buffer.readUint8();
		uint32_t parentId = buffer.readUint32();

		engine.placeItem(itemId, itemType, posX, posY, posZ, yaw, health,
			count, parentClass, parentMode, parentId);
	}


	// Infos
	uint32_t infoCount = buffer.readUint32();
	std::cout << "Info count: " << infoCount << std::endl;
	for (unsigned i = 0; i < infoCount; ++i) {
		uint32_t infoId = buffer.readUint32();

		uint8_t infoType = buffer.readUint8();

		float posX = buffer.readFloat();
		float posY = buffer.readFloat();
		float posZ = buffer.readFloat();
		float pitch = buffer.readFloat();
		float yaw = buffer.readFloat();
		std::string vars = buffer.readString(buffer.readUint32());

		engine.placeInfo(infoId, infoType, posX, posY, posZ, pitch, yaw, vars);
	}

	// States
	uint32_t stateCount = buffer.readUint32();
	std::cout << "State count: " << stateCount << std::endl;
	for (unsigned i = 0; i < stateCount; ++i) {
		uint8_t type = buffer.readUint8();

		uint8_t parentClass = buffer.readUint8();
		uint32_t parentId = buffer.readUint32();

		float posX = buffer.readFloat();
		float posY = buffer.readFloat();
		float posZ = buffer.readFloat();
		float fposX = buffer.readFloat();
		float fposY = buffer.readFloat();
		float fposZ = buffer.readFloat();

		uint32_t value = buffer.readUint32();
		float fvalue = buffer.readFloat();
		std::string strvalue = buffer.readString(buffer.readUint32());

		engine.placeState(type, parentClass, parentId,
			posX, posY, posZ, fposX, fposY, fposZ, value, fvalue, strvalue);
	}

	// Extensions and vars

	uint32_t extCount = buffer.readUint32();
	std::cout << "Ext count: " << extCount << std::endl;
	for (unsigned i = 0; i < extCount; ++i) {
		uint8_t type = buffer.readUint8();

		uint8_t parentClass = buffer.readUint8();
		uint32_t parentId = buffer.readUint32();
		uint32_t mode = buffer.readUint32();

		std::string key = buffer.readString(buffer.readUint32());
		std::string value = buffer.readString(buffer.readUint32());
		std::string stuff = buffer.readString(buffer.readUint32());

		engine.addExtension(type, parentClass, parentId, mode, key, value, stuff);
	}

	if (mainHeader.mode == "sav") {
		float cameraPitch = buffer.readFloat();
		float cameraYaw = buffer.readFloat();

		engine.setCameraRotation(cameraPitch, cameraYaw);
	}

	// Skip reserved space
	buffer.readLine();
	buffer.readLine();

	std::string endMark = buffer.readLine();
	if (endMark != "www.unrealsoftware.de") {
		std::cout << "Unable to load map '" << filename << "' completely." <<
			"Errors might occur!" << std::endl;
	} else {
		// Load attachments

		if (mainHeader.mode == "map") {
			while (buffer.bytesLeftForReading() > 0) {
				/* std::string atfile = */ buffer.readLine();
				/* uint32_t atsize = */ buffer.readUint32();

				std::cout << "An attachment is skipped!" << std::endl;
			}
		}
	}

	std::cout << "Data remaining: " << buffer.bytesLeftForReading() << std::endl;

	return true;
}

} // namespace save
