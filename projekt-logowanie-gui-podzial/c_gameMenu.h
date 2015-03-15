#pragma once
#include "c_map.h"
#include "c_player.h"
#include "definitions.h"
#include "c_gamePhysics.h"

class c_gameMenu
{
	c_map *map;
	std::vector<c_player> players;
	sf::View mainCamera;
	c_gamePhysics world;

public:
	c_gameMenu();
	void checkEvent();
	void update( gameState &state );
	void draw();
};

c_gameMenu::c_gameMenu()
{
	map = new c_map( world );
	mainCamera = window.getView();
	players.push_back( c_player("login_tutaj") );
	players[0].setWorld( world );
}

void c_gameMenu::checkEvent( )
{
	players[0].checkEvent( event );
	players[0].setMap( map->tiles );
	map->checkEvent( event );
}

void c_gameMenu::update( gameState &state )
{
	world.update();
	players[0].update();
	mainCamera.setCenter( sf::Vector2f( mainCamera.getCenter().x , players[0].getPosition().y+384 > 3840 ? 3456 : (int)players[0].getPosition().y ) );
	window.setView( mainCamera );
}

void c_gameMenu::draw()
{
	map->draw();
	for(int i=0;i<players.size(); i++)
		players[i].draw();
	world.draw( window );
}

