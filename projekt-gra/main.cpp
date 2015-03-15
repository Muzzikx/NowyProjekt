#include <SFML/Graphics.hpp>

sf::RenderWindow window;

#include "c_gameMenu.h"


int main()
{
    window.create(sf::VideoMode( 1024, 768 ), "SFML works!", sf::Style::Default );
	c_gameMenu gameMenu;
	sf::Clock clock;

	float dt = 0.0f;
	sf::Time lastUpdate = clock.getElapsedTime();
	float accumulator = 0.0f;
	const float TIME_STEP = 1.0f/60.0f;
	const float MAX_ACCUMULATED_TIME = 1.0f;

	sf::Event event;
    while (window.isOpen())
    {
		dt = clock.getElapsedTime().asSeconds() - lastUpdate.asSeconds();
		lastUpdate = clock.getElapsedTime();
		dt = dt < 0 ? dt*-1 : dt;
		accumulator += dt;
		accumulator = accumulator > MAX_ACCUMULATED_TIME ? MAX_ACCUMULATED_TIME : accumulator ;
       
		while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
			gameMenu.checkEvent( event );
        }

		while( accumulator > TIME_STEP )
		{
			gameMenu.update();
			accumulator -= TIME_STEP;
		}
		
        window.clear();
		gameMenu.draw();
        window.display();
    }

    return 0;
}