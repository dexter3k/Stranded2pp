#pragma once

#include <string>

class RingBuffer;

class Modification
{
public:
	struct Controls
	{
		uint16_t inputKeys[21];

		struct
		{
			float sensitivity;
			bool invertVertically;
			bool smooth;
		} mouse;
	};

	struct ScriptControls
	{
		uint16_t inputKeys[21];
	};

	struct Settings
	{
		struct
		{
			uint32_t width;
			uint32_t height;
			uint32_t bitsPerPixel;
		} screen;

		uint32_t viewRange;
		uint32_t terrain;
		uint32_t water;
		uint32_t sky;
		uint32_t effects;

		float musicVolume;
		float sfxVolume;

		uint32_t grass;
		uint32_t fx2d;
		uint32_t fxlight;
		uint32_t windsway;

		std::string playerName;
		uint16_t serverPort;

		uint32_t fog;
		uint32_t hwmultitex;
		uint32_t motionBlur;
		float motionBlurAplha;
	};
public:
	Modification();
	Modification(const std::string& modificationName);

	std::string getName() const;

	std::string getPath() const;

	Controls& getControls();
	const Controls& getControls() const;

	ScriptControls& getScriptControls();
	const ScriptControls& getScriptControls() const;

	Settings& getSettings();
	const Settings& getSettings() const;
private:
	static const std::string defaultModificationPath;

	static const size_t configurationBufferSize;
	static const std::string controlsConfigPath;
	static const std::string scriptControlsConfigPath;
	static const std::string settingsConfigPath;
private:
	bool init();

	bool loadConfiguration();
	bool loadControls();
	bool loadScriptControls();
	bool loadSettings();
private:
	std::string modificationName;

	Controls controls;
	ScriptControls scriptControls;
	Settings settings;
};
