#pragma once
#include "definitions.h"

class AnimationClass
{
protected:
	std::vector< s_anim* > animationsList;

	sf::Clock clock;
	sf::Time lastUpdate;

	std::string currentName;
	int currentId;
	int currentFrame;
	bool isPlay;
	bool isVisible;

public:
	AnimationClass(void);
	
	/// Obsluga pelna sprita
	sf::Sprite sprite;

	/// Dodawanie nowej animacji 
	void addAnim( std::string animName, std::string path, sf::IntRect intRect, sf::Vector2i frameSize, double frameTime, bool isRepeat );
	void play( std::string name );												/// Rozpoczyna animacje o danej nazwie 
	void stop( );																/// Zatrzymuje sie na danej klatce danej animacji
	void setFrameTime( std::string name, double time );							/// Ustawia czas pomiedzy klatkami animacji
	void update();
	void draw( sf::RenderWindow &window );										/// Rysuje odpowiednia klatke animacji
};

AnimationClass::AnimationClass(void)
{
	isPlay = false;
	isVisible = false;
	currentFrame = -1;
	currentId = -1;
	currentName = "null";
	sprite.setTextureRect( sf::IntRect(0,0,1,1));
}

void AnimationClass::addAnim( std::string animName, std::string path, sf::IntRect intRect, sf::Vector2i frameSize, double frameTime, bool isRepeat )
{
	for( int i=0; i<animationsList.size(); i++ )
		if( animationsList[i]->name == animName ){
			std::cout << "Animacja o nazwie: "<< animName << " juz istnieje" << std::endl;
			return;
		}

	animationsList.push_back( new s_anim( animName, path, intRect, frameSize, frameTime, isRepeat  ) );
}

void AnimationClass::play( std::string name )
{
	if ( currentName != name )
		for( int i=0; i<animationsList.size(); i++ )
			if( animationsList[i]->name == name ){
				currentFrame = 0;
				currentId = i;
				currentName = name;
				isPlay = true;
				isVisible = true;
				sprite.setTexture( *animationsList[currentId]->texture );
				
				sprite.setOrigin( animationsList[currentId]->frameSize.x/2, animationsList[currentId]->frameSize.y/2);
				return;
			}
}

void AnimationClass::update()
{
	if( isPlay && ( clock.getElapsedTime().asSeconds() - lastUpdate.asSeconds() >= animationsList[currentId]->frameTime ) )
	{
		lastUpdate = clock.getElapsedTime();

		if( currentFrame < animationsList[currentId]->maxFrame-1 )
			currentFrame++;
		else if( animationsList[currentId]->isRepeat )
			currentFrame = 0;
		else
			isPlay = false;

		sprite.setTextureRect( sf::IntRect( animationsList[currentId]->intRect.left+ animationsList[currentId]->frameSize.x * currentFrame,
			animationsList[currentId]->intRect.top, animationsList[currentId]->frameSize.x, animationsList[currentId]->frameSize.y)  );
	}
}

void AnimationClass::setFrameTime( std::string name, double time )
{
	for( int i=0; i<animationsList.size(); i++ )
		if( animationsList[i]->name == name ){
			animationsList[i]->frameTime = time;
			return;
		}
}

void AnimationClass::stop()
{
	isPlay = false;
	isVisible = false;
}

void AnimationClass::draw( sf::RenderWindow &window )
{
	update();
	if( isVisible )
		window.draw( sprite );
}

