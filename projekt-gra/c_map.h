#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "c_gamePhysics.h"
using namespace std;

class c_map
{
	sf::Texture textureOn;
	sf::Texture textureOff;
	c_gamePhysics *world;

public:
	tile tiles[60][16];

	c_map( c_gamePhysics &world );
	void draw();
	void setActive( int x, int y );
	tile** getMap();
	void checkEvent( sf::Event &event );
};

c_map::c_map( c_gamePhysics &world )
{
	this->world = &world;
	textureOn.loadFromFile( "brickOn.png" );
	textureOff.loadFromFile( "brickOff.png" );
	for( int x=0 ; x<60; x++ )
	{
		for( int y=0 ; y<16; y++ )
		{
			tiles[x][y].sprite.setTexture( textureOff );
			tiles[x][y].sprite.setPosition( y*64.0f, x*64.0f );
			if( x == 59 || y == 0 || y == 15 ||( x == 57 && y != 5) ) tiles[x][y].isVisible = true;
			else tiles[x][y].isVisible = false;
			if( tiles[x][y].isVisible )
			this->world->addObject( sf::Vector2f( (tiles[x][y].sprite.getPosition().x+32), (tiles[x][y].sprite.getPosition().y+32) ), sf::Vector2f( 65, 65 ) ) ;
		}
	}
}

void c_map::checkEvent( sf::Event &event )
{
	if( event.type == event.MouseButtonPressed && event.key.code == sf::Mouse::Button::Left )
	{
		sf::Vector2f pos = sf::Vector2f( sf::Mouse::getPosition( window ).x, (window.getView().getCenter().y-384) + sf::Mouse::getPosition( window ).y);
		setActive( pos.x/64, pos.y/64 );

	}
}

void c_map::setActive( int x, int y )
{
	if( x > 1 && x < 16 && y > 1 && y <= 60 ){
		tiles[y][x].isVisible = true;
		world->addObject( sf::Vector2f( (tiles[y][x].sprite.getPosition().x+32), (tiles[y][x].sprite.getPosition().y+32) ), sf::Vector2f( 65, 65 ) ) ;
	}
}

void c_map::draw()
{
	float actualYmin = (window.getView().getCenter().y - 448);
	float actualYmax = (window.getView().getCenter().y + 384);

	for( int x=0 ; x<60; x++ )
		for( int y=0 ; y<16; y++ )
			if( tiles[x][y].sprite.getPosition().y >= actualYmin && tiles[x][y].sprite.getPosition().y <= actualYmax )
			{
				if( tiles[x][y].isVisible ) tiles[x][y].sprite.setTexture( textureOn );
				else tiles[x][y].sprite.setTexture( textureOff );
				
				window.draw( tiles[x][y].sprite );
			}
}

