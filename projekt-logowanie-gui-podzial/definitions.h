#pragma once

sf::RenderWindow window;				/// podstawowe komponenty okna
sf::Event event;
sf::Mouse mouse;
sf::Clock clocks;


const std::string DEFAULT_FONT_PATH = "data/font.ttf";
const std::string ARIAL_FONT_PATH = "data/arial.ttf";

const sf::Color COLOR_TRANSPARENT = sf::Color(0,0,0,0);
const sf::Color COLOR_BUTTON_IN = sf::Color(30,30,30,255);
const sf::Color COLOR_BUTTON_OUT = sf::Color(255,120,0,255);

const sf::Color COLOR_TEXTINPUT_IN = sf::Color(15,15,15,255);
const sf::Color COLOR_TEXTINPUT_OUT = sf::Color(255,120,0,255);

enum gameState{
	E_LOGIN_MENU,
	E_GAME_MENU
};

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
	sf::RectangleShape shape;
	bool isActived;
};
