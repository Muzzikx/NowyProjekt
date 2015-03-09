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
	//connect.logIn();

	string szTextGetLogin = "Podaj swoj login: ";
	string szLogin;
	sf::Event event;
	sf::Text textGetLogin, textMessageLogin;
	sf::Font fontText;

	fontText.loadFromFile( "font.ttf" );

	textGetLogin.setPosition( 5.0, 50.0 );
	textGetLogin.setFont( fontText );
	textGetLogin.setColor( sf::Color::White );
	textGetLogin.setCharacterSize( 40 );
	textGetLogin.setString( szTextGetLogin );

	textMessageLogin.setPosition( 250.0, 50.0 );
	textMessageLogin.setFont( fontText );
	textMessageLogin.setColor( sf::Color::White );
	textMessageLogin.setCharacterSize( 40 );

	while( window.isOpen() )
	{
		while( window.pollEvent( event ) )
		{
			if( event.type == sf::Event::Closed )
				window.close();

			if( ( event.type == sf::Event::KeyPressed ) && ( event.key.code == sf::Keyboard::Escape ) )
				window.close();

			if( connect.bSetText ){
				connect.getLoginFromKeyboard( event );
				cout << "#1" << endl;
			}
			else if( !connect.getStatusClient() ){
				connect.sendDataTcp( "dolacz" );
				connect.setStatusClient( ClientConnect::CLIENT_LOGGED );
				cout << "#2" << endl;
			}
			else{
				connect.sendDataUdp123();
				cout << "#3" << endl;
			}

			/*if( ( event.type == sf::Event::KeyPressed ) && ( event.key.code == sf::Keyboard::Q ) ){
				cin >> szText;
				textMessage.setString( szText );
			}*/
		}
		window.clear();

		textMessageLogin.setString( szLogin );

		window.draw( textGetLogin );
		window.draw( textMessageLogin );
		window.draw( connect );

		connect.getDataUdp();

		window.display();
	}
	connect.logOut();
    return 0;
}