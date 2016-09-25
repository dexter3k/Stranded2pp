#pragma once

namespace gfx
{

namespace gui
{

class Gui;

class Screen
{
public:
	enum Screens
	{
		Intro,
		MainMenu,
		Inventory
	};
public:
	Screen(Gui& gui);
	virtual ~Screen();

	virtual void create();
	virtual void destroy();

	virtual void update(float deltaTime);
protected:
	Gui& gui;

	bool isCreated;
};

} // namespace gui

} // namespace gfx
