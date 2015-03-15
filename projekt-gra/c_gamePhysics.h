#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
#include <vector>
#include <iostream>

using namespace std;

class c_gamePhysics
{
	b2World *world;
	vector<b2BodyDef> bodyDef;
	vector<b2Body*> body;
	vector<b2PolygonShape> polygonShape;
	vector<b2FixtureDef> fixtureDef;
	vector<sf::RectangleShape> shape;

public:
	c_gamePhysics();
	b2Body* addObject( sf::Vector2f position, sf::Vector2f size, bool isDynamic );
	void update( double dt );
	void draw( sf::RenderWindow &window );

};

c_gamePhysics::c_gamePhysics()
{
	world = new b2World( b2Vec2( 0.0f , 9.7f ) ); 
}

b2Body* c_gamePhysics::addObject( sf::Vector2f position, sf::Vector2f size, bool isDynamic=false )
{
	shape.push_back( sf::RectangleShape() );
	shape.back().setOrigin( size.x/2.0f, size.y/2.0f );
	shape.back().setPosition( position );
	shape.back().setSize( size );
	shape.back().setOutlineThickness( 1 );
	if( isDynamic ) shape.back().setOutlineColor( sf::Color::Cyan ); 
	else shape.back().setOutlineColor( sf::Color::White );
	shape.back().setFillColor( sf::Color( 255, 255, 255, 10 ) );
	cout << "push: " << shape.size() << " position: " << shape.back().getPosition().x << " " <<  shape.back().getPosition().y << endl;

	bodyDef.push_back( b2BodyDef() );
	if( isDynamic ) bodyDef.back().type = b2_dynamicBody;
	bodyDef.back().position.Set( position.x*0.02f, position.y*0.02f );

	polygonShape.push_back( b2PolygonShape() );
	polygonShape.back().SetAsBox( (size.x/2)*0.02f, (size.y/2)*0.02f ); 

	if( isDynamic ){
		fixtureDef.push_back( b2FixtureDef() );
		fixtureDef.back().shape = &polygonShape.back();
		fixtureDef.back().density = 1.0f;
		fixtureDef.back().friction = 4.0f;
		fixtureDef.back().restitution = 0.1f;
	}

	body.push_back( world->CreateBody( &bodyDef.back() ) );
	body.back()->SetFixedRotation( true );
	if( isDynamic ) body.back()->CreateFixture( &fixtureDef.back() );
	else body.back()->CreateFixture( &polygonShape.back(), 1.0f );

	return body.back();
}

void c_gamePhysics::update( double dt )
{
	world->Step( dt, 10, 5 );
	for( int i=0; i<body.size(); i++ ){
		shape[i].setPosition( body[i]->GetPosition().x*50, body[i]->GetPosition().y*50 );
		shape[i].setRotation( (180*  body[i]->GetAngle()) / 3.14159 );
	}
}

void c_gamePhysics::draw( sf::RenderWindow &window )
{
	for( int i=0; i<shape.size(); i++ )
		window.draw( shape[i] );
}





