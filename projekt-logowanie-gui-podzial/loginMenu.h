#pragma once
#include "guiMenager.h"

class loginMenu
{
	sf::Texture textureWallpapper;
	sf::Sprite spriteWallpapper;
	guiMenager gui;

public:
	loginMenu();
	void checkEvent( );
	void update( gameState &currentState  );
	void draw()  ;

};

loginMenu::loginMenu()
{
	textureWallpapper.loadFromFile("data/loginMenu/wallpapper.jpg");
	spriteWallpapper.setTexture( textureWallpapper );

	/// typ / pozycja srodka / rozmiar / nazwa

	gui.add( "button", sf::Vector2f( 420, 550 ), sf::Vector2f( 150, 40 ), "LOGIN" );
	gui.add( "button", sf::Vector2f( 604, 550 ), sf::Vector2f( 150, 40 ), "EXIT" );
	gui.add( "inputText", sf::Vector2f( 512, 500 ), sf::Vector2f( 335, 40 ), "" );
}

void loginMenu::update( gameState &currentState )
{
	switch(gui.getClickedButton())
	{
	case 0:
		currentState = gameState::E_GAME_MENU;
		break;
	case 1:
		window.close();
		break;
	}
}

void loginMenu::checkEvent( )
{
	gui.checkEvent( );
}

void loginMenu::draw() 
{
	window.draw( spriteWallpapper );
	gui.draw();
}


