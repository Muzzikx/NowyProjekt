#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

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

const float TIME_STEP = 1.0f/60.0f;
const float MAX_ACCUMULATED_TIME = 1.0f;

const int PORT_SERVER_TCP = 12345;
const int PORT_SERVER_UDP = 54321;
const int PORT_CLIENT_UDP = 11111;
const int PORT_CLIENT_TCP = 12121;

const string IP_SERVER = "25.60.93.242";


/// --------------------------------------------------WYLICZENIOWE TYPY UZYWANE W PROGRAMIE
enum gameState{
	E_LOGIN_MENU,
	E_GAME_MENU
};

enum status{
	CLIENT_UNLOGGED = 0,
	CLIENT_LOGGED
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

struct s_anim{
	std::string name;
	sf::Texture *texture;
	sf::Vector2i frameSize;
	sf::IntRect intRect;
	double frameTime;
	bool isRepeat;
	int maxFrame;
	s_anim(  std::string animName, std::string path, sf::IntRect intRect, sf::Vector2i frameSize, double frameTime, bool isRepeat ){
		this->name = 	animName;
		this->texture = new sf::Texture();
		if (!this->texture->loadFromFile( path ))
			std::cout << "blad wczytywania textury: " << path << std::endl;
		this->frameSize = frameSize;
		this->intRect = intRect;
		this->frameTime = frameTime;
		this->isRepeat = isRepeat;
		this->maxFrame = intRect.width / frameSize.x;
	}
};

struct tile
{
	sf::Sprite sprite;
	bool isVisible;

};
