#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include "serverClass.h"

using namespace std;

int main()
{
	sf::Event event;
	sf::RenderWindow window(sf::VideoMode( 800, 600 ), "SERVER--ON", sf::Style::Titlebar );
	serverClass server;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ) window.close();
        }

		server.checkConnection();

        window.clear();
		window.draw(server);
        window.display();
    }

    return 0;
}