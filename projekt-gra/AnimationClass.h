#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

class AnimationClass
{
protected:

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
	void play( std::string name );							/// Rozpoczyna animacje o danej nazwie 
	void stop( );											/// Zatrzymuje sie na danej klatce danej animacji
	void setFrameTime( std::string name, double time );	/// Ustawia czas pomiedzy klatkami animacji
	void update();
	void draw( sf::RenderWindow &window );					/// Rysuje odpowiednia klatke animacji
	
	~AnimationClass(void);
};

