#pragma once
#include "definitions.h"
#include "loginMenu.h"
#include "c_gameMenu.h"
#include "ClientConnect.h"


class gameEngine
{
	gameState currentState;					/// aktualny stan gry 
	loginMenu *loginsMenu;					/// klasa odpowiedzialna za menu logowania 
	c_gameMenu *gameMenu;					/// klasa odpowiedzialna za gre 

	ClientConnect connect;					/// klient sieciowy

	/// do petli stalokrokowej
	float dt;								/// uplyw czasu 
	sf::Time lastUpdateTime;				/// czas ostatniego update
	float accumulator;						/// akumuluje ilosc updatow do wykonania

public:

	gameEngine( );							/// tworzenie okna 
	void checkEvent();						/// sprawdzanie klikniec itp 
	void mainLoop();						/// glowna petla gry 
	void update();							/// obsluga zdarzen 
	void draw();							/// rysowanie 
};

gameEngine::gameEngine( )
{
	window.create( sf::VideoMode( 1024, 768 ), "Game", sf::Style::Titlebar );
	currentState = gameState::E_LOGIN_MENU;

	loginsMenu = new loginMenu( connect );
	gameMenu = new c_gameMenu();

	dt = 0.0f;
	accumulator = 0.0f;
}

void gameEngine::checkEvent()
{
	while (window.pollEvent(event)){
		if ( event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape ) window.close();
		if( currentState == gameState::E_LOGIN_MENU ) loginsMenu->checkEvent( );
		if( currentState == gameState::E_GAME_MENU ) gameMenu->checkEvent( );
    }
}

void gameEngine::update()
{
	if( currentState == gameState::E_LOGIN_MENU ) loginsMenu->update( currentState );
	if( currentState == gameState::E_GAME_MENU ) gameMenu->update( currentState );

	loginsMenu->update( currentState );
	connect.loopConnect();
}

void gameEngine::mainLoop()
{
	while( window.isOpen() ){
		/// dzialania do petli stalokrokowej
		dt = clocks.getElapsedTime().asSeconds() - lastUpdateTime.asSeconds();
		lastUpdateTime = clocks.getElapsedTime();
		dt = dt < 0 ? dt*-1 : dt;
		accumulator += dt;
		accumulator = accumulator > MAX_ACCUMULATED_TIME ? MAX_ACCUMULATED_TIME : accumulator ;
       
		checkEvent();
		while( accumulator > TIME_STEP )
		{
			update();
			accumulator -= TIME_STEP;
		}
		draw();
	}
}

void gameEngine::draw()
{
	window.clear();
	if( currentState == gameState::E_LOGIN_MENU ) loginsMenu->draw();
	if( currentState == gameState::E_GAME_MENU ) gameMenu->draw();
	window.display();
}