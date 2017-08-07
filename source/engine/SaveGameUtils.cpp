#include "SaveGameUtils.h"

#include <iostream>

#include "Engine.h"

#include "common/FileSystem.h"
#include "common/RingBuffer.h"
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "graphics/Image.h"
#include "graphics/Color.h"

namespace save
{
	namespace impl
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

		bool readMainHeader(RingBuffer& buffer, MainHeader& mainHeader)
		{
			if (!buffer.readNewlineTerminatedString(
				mainHeader.identificationString)) return false;

			if (mainHeader.identificationString.substr(0, 15) !=
				"### Stranded II")
			{
				std::cout << "Wrong (corrupted?) header" << std::endl;

				return false;
			}

			return (
				buffer.readNewlineTerminatedString(mainHeader.gameVersion) &&
				buffer.readNewlineTerminatedString(mainHeader.date) &&
				buffer.readNewlineTerminatedString(mainHeader.time) &&
				buffer.readNewlineTerminatedString(mainHeader.format) &&
				buffer.readNewlineTerminatedString(mainHeader.mode));
		}

		bool readPreviewImage(RingBuffer& buffer, gfx::Image& image)
		{
			image.create(math::Vector2u(96, 72), gfx::Color(255, 255, 255));

			for (unsigned x = 0; x < 96; ++x)
			{
				for (unsigned y = 0; y < 72; ++y)
				{
					uint8_t red, green, blue;
					red = green = blue = 0;

					if (!buffer.readUint8(red)) return false;
					if (!buffer.readUint8(green)) return false;
					if (!buffer.readUint8(blue)) return false;

					image.setPixel(x, y, gfx::Color(red, green, blue));
				}
			}

			return true;
		}

		bool readColorMap(RingBuffer& buffer, ColorMapData& data)
		{
			unsigned colorMapSize = 0;
			if (!buffer.readUint32(colorMapSize))
			{
				return false;
			}
			data.size = colorMapSize;

			data.colorMap.resize(colorMapSize * colorMapSize,
				gfx::Color(255, 255, 255));

			gfx::Image debugImage;
			debugImage.create(math::Vector2u(colorMapSize, colorMapSize),
				gfx::Color(255, 255, 255));

			for (unsigned x = 0; x < colorMapSize; ++x)
			{
				for (unsigned y = 0; y < colorMapSize; ++y)
				{
					uint8_t red, green, blue;
					red = green = blue = 0;

					if (!buffer.readUint8(red)) return false;
					if (!buffer.readUint8(green)) return false;
					if (!buffer.readUint8(blue)) return false;

					data.colorMap[x + y * colorMapSize] = gfx::Color(red, green,
						blue);

					debugImage.setPixel(x, y, gfx::Color(red, green, blue));
				}
			}

			debugImage.saveToFile("colorMapDebug.png");

			return true;
		}
	}

	bool loadFromFile(const std::string& filename, Engine& engine)
	{
		if (!fs::checkFileExists(filename))
		{
			std::cout << "Unable to load map '" << filename << "' - file not found"
				<< std::endl;

			return false;
		}

		size_t fileSize = fs::getFileSize(filename);
		if (fileSize == 0)
		{
			std::cout << "Corrupted map '" << filename << "'" << std::endl;

			return false;
		}

		RingBuffer buffer(fileSize);
		if (!fs::loadFile(filename, buffer))
		{
			std::cout << "Unable to load '" << filename << "'" << std::endl;

			return false;
		}

		// Main header data
		impl::MainHeader mainHeader;
		if (!impl::readMainHeader(buffer, mainHeader))
		{
			std::cout << "Unable to read main header in '" << filename << "'!"
				<< std::endl;

			return false;
		}

		std::cout << "Loading map:\n" << "[" << mainHeader.gameVersion << "] "
			<< mainHeader.date << " " << mainHeader.time << " " <<
			mainHeader.format << " " << mainHeader.mode << std::endl;

		// Header OK

		struct
		{
			int object = 0;
			int unit = 0;
			int item = 0;
		} dataFormat;

		std::string dataFormatString = "";
		if (!buffer.readNewlineTerminatedString(dataFormatString)) return false;

		if (dataFormatString != "")
		{
			dataFormat.object = std::stoi(dataFormatString.substr(1, 1));
			dataFormat.unit = std::stoi(dataFormatString.substr(2, 1));
			dataFormat.item = std::stoi(dataFormatString.substr(3, 1));
		}

		// Skip reserved space
		for (unsigned i = 0; i < 5; ++i)
		{
			std::string temporary;
			if (!buffer.readNewlineTerminatedString(temporary)) return false;
		}

		// Load 96 x 72 R8G8B8 raw image
		gfx::Image previewImage;
		if (!impl::readPreviewImage(buffer, previewImage))
		{
			return false;
		}

		uint8_t passKey = 0;
		std::string password = "";

		if (!buffer.readUint8(passKey)) return false;
		if (!buffer.readNewlineTerminatedString(password)) return false;

		uint32_t day = 0;
		uint8_t hour = 0;
		uint8_t minute = 0;
		uint8_t freezeTime = 0; // bool?
		std::string skybox = "";
		uint8_t multiplayer = 0; // bool?
		uint8_t climate = 0;
		std::string music = "";
		std::string brief = "";
		uint8_t fog[4] = {0, 0, 0, 0};
		uint8_t reservedByte = 0;

		if (!buffer.readUint32(day)) return false;
		if (!buffer.readUint8(hour)) return false;
		if (!buffer.readUint8(minute)) return false;
		if (!buffer.readUint8(freezeTime)) return false;
		if (!buffer.readLengthPrefixedString(skybox)) return false;
		if (!buffer.readUint8(multiplayer)) return false;
		if (!buffer.readUint8(climate)) return false;
		if (!buffer.readLengthPrefixedString(music)) return false;
		if (!buffer.readLengthPrefixedString(brief)) return false;
		if (!buffer.readUint8(fog[0])) return false;
		if (!buffer.readUint8(fog[1])) return false;
		if (!buffer.readUint8(fog[2])) return false;
		if (!buffer.readUint8(fog[3])) return false;
		if (!buffer.readUint8(reservedByte)) return false;

		engine.resetGame();
		engine.setupGame(day, hour, minute, freezeTime, skybox, multiplayer,
			climate, music, brief);

		// Quickslots
		std::vector<std::string> quickslots(10, "");
		for (unsigned i = 0; i < 10; ++i)
		{
			if (!buffer.readLengthPrefixedString(quickslots[i])) return false;
		}

		engine.setupQuickslots(quickslots);

		// Color map
		impl::ColorMapData colorMapData;
		if (!impl::readColorMap(buffer, colorMapData))
		{
			std::cout << "Unable to load color map" << std::endl;

			return false;
		}

		uint32_t mapSize = 0;
		if (!buffer.readUint32(mapSize)) return false;

		std::cout << "Colormap size: " << colorMapData.size << std::endl;
		std::cout << "Map size: " << mapSize << std::endl;

		uint32_t heightMapSize = mapSize + 1;

		std::vector<float> heightMap(heightMapSize * heightMapSize, 0.0f);
		for (unsigned x = 0; x < heightMapSize; ++x)
		{
			for (unsigned y = 0; y < heightMapSize; ++y)
			{
				if (!buffer.readFloat(heightMap[x + y * heightMapSize]))
					return false;
			}
		}

		uint32_t grassMapSize = colorMapData.size + 1;

		std::vector<uint8_t> grassMap(grassMapSize * grassMapSize, 0);
		for (unsigned x = 0; x < grassMapSize; ++x)
		{
			for (unsigned y = 0; y < grassMapSize; ++y)
			{
				if (!buffer.readUint8(grassMap[x + y * grassMapSize])) return false;
			}
		}

		if (!engine.setupTerrain(mapSize, heightMap, colorMapData.size,
			colorMapData.colorMap, grassMap))
		{
			return false;
		}

		// "Stuff"

		// Objects
		uint32_t objectCount = 0;
		if (!buffer.readUint32(objectCount)) return false;

		std::cout << "Object count: " << objectCount << std::endl;

		for (unsigned i = 0; i < objectCount; ++i)
		{
			uint32_t objectId = 0;
			if (!buffer.readUint32(objectId)) return false;

			uint16_t objectType = 0;
			if (dataFormat.object != 0)
			{
				if (!buffer.readUint16(objectType)) return false;
			}
			else
			{
				uint8_t type = 0;
				if (!buffer.readUint8(type)) return false;

				objectType = type & 0x00ff;
			}

			struct
			{
				float x = 0.0f;
				float z = 0.0f;
			} position;

			float yaw = 0.0f;
			float health = 0.0f;
			float maxHealth = 0.0f;
			uint32_t dayTimer = 0.0f;

			if (!buffer.readFloat(position.x)) return false;
			if (!buffer.readFloat(position.z)) return false;
			if (!buffer.readFloat(yaw)) return false;
			if (!buffer.readFloat(health)) return false;
			if (!buffer.readFloat(maxHealth)) return false;
			if (!buffer.readUint32(dayTimer)) return false;

			//std::cout << "Object " << i << " [" << objectId << "] t: " << objectType
			//	<< " x: " << position.x << " z: " << position.z << " yaw: " << yaw
			//	<< " h: " << health << " mH: " << maxHealth << " age: " << dayTimer
			//	<< std::endl;
		}

		// Units
		uint32_t unitCount = 0;
		if (!buffer.readUint32(unitCount)) return false;

		std::cout << "Unit count: " << unitCount << std::endl;

		for (unsigned i = 0; i < unitCount; ++i)
		{
			uint32_t unitId = 0;
			if (!buffer.readUint32(unitId)) return false;

			uint16_t unitType = 0;
			if (dataFormat.unit != 0)
			{
				if (!buffer.readUint16(unitType)) return false;
			}
			else
			{
				uint8_t type = 0;
				if (!buffer.readUint8(type)) return false;

				unitType = type & 0x00ff;
			}

			math::Vector3f position(0.0f, 0.0f, 0.0f);

			float yaw = 0.0f;
			float health = 0.0f;
			float maxHealth = 0.0f;
			float hunger = 0.0f;
			float thirst = 0.0f;
			float exhaustion = 0.0f;
			struct
			{
				float x = 0.0f;
				float z = 0.0f;
			} aiCenter;

			if (!buffer.readFloat(position.x)) return false;
			if (!buffer.readFloat(position.y)) return false;
			if (!buffer.readFloat(position.z)) return false;
			if (!buffer.readFloat(yaw)) return false;
			if (!buffer.readFloat(health)) return false;
			if (!buffer.readFloat(maxHealth)) return false;
			if (!buffer.readFloat(hunger)) return false;
			if (!buffer.readFloat(thirst)) return false;
			if (!buffer.readFloat(exhaustion)) return false;
			if (!buffer.readFloat(aiCenter.x)) return false;
			if (!buffer.readFloat(aiCenter.z)) return false;

			//std::cout << "Unit " << i << " [" << unitId << "] t: " << unitType
			//	<< " x: " << position.x << " y: " << position.y << " z: " <<
			//	position.z << " yaw: " << yaw << " h: " << health << " mH: " <<
			//	maxHealth << std::endl;
		}

		// Items
		uint32_t itemCount = 0;
		if (!buffer.readUint32(itemCount)) return false;

		std::cout << "Item count: " << itemCount << std::endl;

		for (unsigned i = 0; i < itemCount; ++i)
		{
			uint32_t itemId = 0;
			if (!buffer.readUint32(itemId)) return false;

			uint16_t itemType = 0;
			if (dataFormat.item != 0)
			{
				if (!buffer.readUint16(itemType)) return false;
			}
			else
			{
				uint8_t type = 0;
				if (!buffer.readUint8(type)) return false;

				itemType = type & 0x00ff;
			}

			math::Vector3f position(0.0f, 0.0f, 0.0f);

			float yaw = 0.0f;
			float health = 0.0f;
			uint32_t count = 0;
			uint8_t parentClass = 0;
			uint8_t parentMode = 0;
			uint32_t parentId = 0;

			if (!buffer.readFloat(position.x)) return false;
			if (!buffer.readFloat(position.y)) return false;
			if (!buffer.readFloat(position.z)) return false;
			if (!buffer.readFloat(yaw)) return false;
			if (!buffer.readFloat(health)) return false;
			if (!buffer.readUint32(count)) return false;
			if (!buffer.readUint8(parentClass)) return false;
			if (!buffer.readUint8(parentMode)) return false;
			if (!buffer.readUint32(parentId)) return false;

			//std::cout << "Item " << i << " [" << itemId << "] t: " << itemType
			//	<< " x: " << position.x << " y: " << position.y << " z: " <<
			//	position.z << " yaw: " << yaw << " h: " << health << " c: " << count
			//	<< " pC: " << static_cast<uint16_t>(parentClass) << " pM: " <<
			//	static_cast<uint16_t>(parentMode) << " pId: " << parentId <<
			//	std::endl;
		}


		// Infos
		uint32_t infoCount = 0;
		if (!buffer.readUint32(infoCount)) return false;

		std::cout << "Info count: " << infoCount << std::endl;

		for (unsigned i = 0; i < infoCount; ++i)
		{
			uint32_t infoId = 0;
			if (!buffer.readUint32(infoId)) return false;

			uint8_t infoType = 0;
			if (!buffer.readUint8(infoType)) return false;

			math::Vector3f position(0.0f, 0.0f, 0.0f);

			float pitch = 0.0f;
			float yaw = 0.0f;
			std::string vars = "";

			if (!buffer.readFloat(position.x)) return false;
			if (!buffer.readFloat(position.y)) return false;
			if (!buffer.readFloat(position.z)) return false;
			if (!buffer.readFloat(pitch)) return false;
			if (!buffer.readFloat(yaw)) return false;
			if (!buffer.readLengthPrefixedString(vars)) return false;

			//std::cout << "Info " << i << " [" << infoId << "] t: " <<
			//	static_cast<uint16_t>(infoType) << " x: " << position.x <<
			//	" y: " << position.y << " z: " << position.z << " pitch: " <<
			//	pitch << " yaw: " << yaw << " vars: " << vars << std::endl;
		}

		// States

		uint32_t stateCount = 0;
		if (!buffer.readUint32(stateCount)) return false;

		std::cout << "State count: " << stateCount << std::endl;
		for (unsigned i = 0; i < stateCount; ++i)
		{
			uint8_t type = 0;
			if (!buffer.readUint8(type)) return false;

			uint8_t parentClass = 0;
			if (!buffer.readUint8(parentClass)) return false;
			uint32_t parentId = 0;
			if (!buffer.readUint32(parentId)) return false;

			math::Vector3f position(0.0f, 0.0f, 0.0f);
			math::Vector3f fposition(0.0f, 0.0f, 0.0f);

			if (!buffer.readFloat(position.x)) return false;
			if (!buffer.readFloat(position.y)) return false;
			if (!buffer.readFloat(position.z)) return false;
			if (!buffer.readFloat(fposition.x)) return false;
			if (!buffer.readFloat(fposition.y)) return false;
			if (!buffer.readFloat(fposition.z)) return false;

			uint32_t value = 0;
			float fvalue = 0.0f;
			std::string strvalue = "";

			if (!buffer.readUint32(value)) return false;
			if (!buffer.readFloat(fvalue)) return false;
			if (!buffer.readLengthPrefixedString(strvalue)) return false;

			//std::cout << "State " << i << std::endl;
		}

		// Extensions and vars

		uint32_t extCount = 0;
		if (!buffer.readUint32(extCount)) return false;

		std::cout << "Ext count: " << extCount << std::endl;
		for (unsigned i = 0; i < extCount; ++i)
		{
			uint8_t type = 0;
			if (!buffer.readUint8(type)) return false;

			uint8_t parentClass = 0;
			if (!buffer.readUint8(parentClass)) return false;
			uint32_t parentId = 0;
			if (!buffer.readUint32(parentId)) return false;

			uint32_t mode = 0;
			if (!buffer.readUint32(mode)) return false;

			std::string key = "";
			std::string value = "";
			std::string stuff = "";

			if (!buffer.readLengthPrefixedString(key)) return false;
			if (!buffer.readLengthPrefixedString(value)) return false;
			if (!buffer.readLengthPrefixedString(stuff)) return false;
		}

		if (mainHeader.mode == "sav")
		{
			float cameraPitch = 0.0f;
			float cameraYaw = 0.0f;

			if (!buffer.readFloat(cameraPitch)) return false;
			if (!buffer.readFloat(cameraYaw)) return false;
		}

		std::string reservedAtEnd[2] = {"", ""};
		for (unsigned i = 0; i < 2; ++i)
		{
			if (!buffer.readNewlineTerminatedString(reservedAtEnd[i])) return false;
		}

		std::string endMark = "";
		if (!buffer.readNewlineTerminatedString(endMark)) return false;
		if (endMark != "www.unrealsoftware.de")
		{
			std::cout << "Unable to load map '" << filename << "' completely." <<
				"Errors might occur!" << std::endl;
		}
		else
		{
			// Load attachments

			if (mainHeader.mode == "map")
			{
				while (buffer.getDataSize() > 0)
				{
					std::string atfile = "";
					if (!buffer.readNewlineTerminatedString(atfile)) return false;
					uint32_t atsize = 0;
					if (!buffer.readUint32(atsize)) return false;

					std::cout << "Attachment is skipped!" << std::endl;
				}
			}
		}

		std::cout << "Data remaining: " << buffer.getDataSize() << std::endl;

		return true;
	}
} // namespace save
