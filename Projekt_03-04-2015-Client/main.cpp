#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

using namespace std;

#include "ClientConnect.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode( 640, 480 ), "Projekt 04.03.2015r", sf::Style::Titlebar );
	ClientConnect connect;

	sf::Event event;
	while( window.isOpen() )
	{
		while( window.pollEvent( event ) )
		{
			if( event.type == sf::Event::Closed )
				window.close();

			if( ( event.type == sf::Event::KeyPressed ) && ( event.key.code == sf::Keyboard::Escape ) )
				window.close();

			if( connect.bSetText ){
				connect.getLoginFromKeyboard( event, window );
			}
			else if( !connect.getStatusClient() ){
				connect.sendDataTcp( "dolacz" );
				connect.setStatusClient( ClientConnect::CLIENT_LOGGED );
			}
			else{
				connect.sendDataUdp123();
			}
		}
		window.clear();

		window.draw( connect );

		connect.getDataUdp();

		window.display();
	}
	connect.logOut();
    return 0;
}