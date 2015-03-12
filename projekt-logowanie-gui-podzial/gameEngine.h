#pragma once
#include "definitions.h"
#include "loginMenu.h"

class gameEngine
{
	gameState currentState;					/// aktualny stan gry 
	loginMenu loginsMenu;					/// klasa odpowiedzialna za menu logowania 

public:

	gameEngine( );							/// tworzenie okna 
	void checkEvent();						/// sprawdzanie klikniec itp 
	void mainLoop();						/// glowna petla gry 
	void update();							/// obsluga zdarzen 
	void draw();							/// rysowanie 
};

gameEngine::gameEngine( )
{
	window.create( sf::VideoMode(1024, 768), "Game", sf::Style::Titlebar );
	window.setFramerateLimit( 60 );
	currentState = gameState::E_LOGIN_MENU;
}

void gameEngine::checkEvent()
{
	while (window.pollEvent(event)){
		if ( event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape ) window.close();

		if( currentState == gameState::E_LOGIN_MENU ) loginsMenu.checkEvent( );
    }
}

void gameEngine::update()
{
	loginsMenu.update( currentState );
}

void gameEngine::mainLoop()
{
	while( window.isOpen() ){
		checkEvent();
		update();
		draw();
	}
}

void gameEngine::draw()
{
	window.clear();
	if( currentState == gameState::E_LOGIN_MENU ) loginsMenu.draw();
	window.display();
}