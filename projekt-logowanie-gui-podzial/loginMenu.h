#pragma once
#include "guiMenager.h"
#include "ClientConnect.h"

class loginMenu
{
	sf::Texture textureWallpapper;
	sf::Sprite spriteWallpapper;					/// sprite odpowiedzialny za tlo w menu
	guiMenager gui;									/// reprezentant klasy guiMenager zazadza calym gui w programie 
	ClientConnect *connect;

public:
	loginMenu( ClientConnect &connect );									/// utworzenie komponentow gui i wczytanie tekstur 
	void checkEvent( );								/// obsluga eventow 
	void update( gameState &currentState  );		/// oblsuga dzialan 
	void draw()  ;									/// wyswietlanie menu
};

loginMenu::loginMenu( ClientConnect &connect )
{
	this->connect = &connect;
	textureWallpapper.loadFromFile("data/loginMenu/wallpapper.jpg");
	spriteWallpapper.setTexture( textureWallpapper );

	/// typ / pozycja srodka / rozmiar / nazwa

	gui.add( "button", sf::Vector2f( 420, 550 ), sf::Vector2f( 150, 40 ), "LOGIN" );
	gui.add( "button", sf::Vector2f( 604, 550 ), sf::Vector2f( 150, 40 ), "EXIT" );
	gui.add( "inputText", sf::Vector2f( 540, 450 ), sf::Vector2f( 250, 40 ), "" );
	gui.add( "label", sf::Vector2f(380,450),sf::Vector2f(0,0),"LOGIN:" );
	gui.add( "inputText", sf::Vector2f( 540, 500 ), sf::Vector2f( 250, 40 ), "*" );
	gui.add( "label", sf::Vector2f(380,500),sf::Vector2f(0,0),"PASS :" );
}

void loginMenu::update( gameState &currentState )
{
	switch(gui.getClickedButton())
	{
	case 0:		/// przycik login
		if( connect->loginOnServer( gui.getInputText(0), gui.getInputText(1) ) )
			currentState = gameState::E_GAME_MENU;
		break;
	case 1:		/// przycik exit
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


