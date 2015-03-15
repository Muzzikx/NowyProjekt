#pragma once

/// ------------------------------------------------- PODSTAWOWE KOMPONENTY
sf::RenderWindow window;				
sf::Event event;
sf::Mouse mouse;
sf::Clock clocks;

/// ------------------------------------------------- STALE UZYWANE W PROGRAMIE
const std::string DEFAULT_FONT_PATH = "data/font.ttf";
const std::string ARIAL_FONT_PATH = "data/arial.ttf";

const sf::Color COLOR_TRANSPARENT = sf::Color(0,0,0,0);
const sf::Color COLOR_BUTTON_IN = sf::Color(30,30,30,255);
const sf::Color COLOR_BUTTON_OUT = sf::Color(255,120,0,255);

const sf::Color COLOR_TEXTINPUT_IN = sf::Color(15,15,15,255);
const sf::Color COLOR_TEXTINPUT_OUT = sf::Color(255,120,0,255);

/// --------------------------------------------------WYLICZENIOWE TYPY UZYWANE W PROGRAMIE
enum gameState{
	E_LOGIN_MENU,
	E_GAME_MENU
};

/// ---------------------------------------------------STRUKTURY UZYWANE W PROGRAMIE
struct s_button
{
	sf::Text name;
	sf::RectangleShape shape;
	bool isClicked;
	bool isActived;
};

struct s_inputText
{
	sf::Text name;
	std::string text;
	sf::RectangleShape shape;
	bool isActived;
	bool isPass;
};

struct s_label
{
	sf::Text name;
};
