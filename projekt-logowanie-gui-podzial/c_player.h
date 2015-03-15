#pragma once
#include "AnimationClass.h"
#include "c_gamePhysics.h"

class c_player
{
	sf::Vector2f lastGoodPosition;
	std::string playerName;
	AnimationClass anim;
	float speed;
	float jump;
	float gravity;
	tile map[60][16];
	b2Body *playerBody;

public:
	c_player( std::string name );
	sf::Vector2f getPosition();
	void checkEvent( sf::Event &event );
	void update();
	void draw();
	void setMap( tile map[60][16] );
	void setWorld( c_gamePhysics &world );

};

c_player::c_player( std::string name )
{
	playerName = name;
	anim.addAnim("walk_left","anim.png",sf::IntRect(0,184,432,82),sf::Vector2i(48,92),0.1,true);
	anim.addAnim("walk_right","anim.png",sf::IntRect(0,552,432,82),sf::Vector2i(48,92),0.1,true);
	anim.addAnim("stop","anim.png",sf::IntRect(0,0,54,82),sf::Vector2i(48,92),0.01,false);
	anim.sprite.setPosition( sf::Vector2f( 400, 300 ) );
	anim.sprite.setOrigin( anim.sprite.getGlobalBounds().width/2.0f, anim.sprite.getGlobalBounds().height/2.0f );
}

void c_player::setWorld( c_gamePhysics &world )
{
	playerBody = world.addObject( sf::Vector2f(anim.sprite.getPosition().x, anim.sprite.getPosition().y ), sf::Vector2f(30,90), true );
}

void c_player::setMap( tile map[60][16] )
{
	for( int x=0 ; x<60; x++ )
		for( int y=0 ; y<16; y++ )
			this->map[x][y] = map[x][y];
}

sf::Vector2f c_player::getPosition()
{
	return anim.sprite.getPosition();
}

void c_player::checkEvent( sf::Event &event )
{
	if( event.type == event.KeyPressed && event.key.code == sf::Keyboard::Space && jump == 0 )
	{
		playerBody->ApplyForceToCenter( b2Vec2( 0,-350 ), true );
		jump = 1;
	}
}

void c_player::update()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
	{ 
		anim.play("walk_left");
		speed = -20;
	}
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
	{
		anim.play("walk_right");
		speed = 20;
	}
	else
	{
		anim.play("stop");
		speed = 0;
	}
	playerBody->ApplyForceToCenter( b2Vec2( speed,0 ), true );

	sf::Vector2f positionUpdate;
	positionUpdate.x = playerBody->GetPosition().x*50 - anim.sprite.getPosition().x;
	positionUpdate.y = playerBody->GetPosition().y*50 - anim.sprite.getPosition().y;

	if( positionUpdate.y == 0 ) jump = 0;

	anim.sprite.setPosition( sf::Vector2f( playerBody->GetPosition().x*50, playerBody->GetPosition().y*50) );
}

void c_player::draw()
{
	anim.draw( window );
}


