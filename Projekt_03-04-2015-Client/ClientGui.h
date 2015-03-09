#pragma once

class ClientGui : public sf::Drawable
{
	private:
		sf::RectangleShape rectangleLogin, rectangleOk;
		sf::Text textLogin, tLogin, tOk;
		sf::Font fontGui;
		

	public:
		bool bSetText;	
		string szLogin;
		ClientGui(void){
			fontGui.loadFromFile( "arial.ttf" );

			tLogin.setFont( fontGui );
			tLogin.setColor( sf::Color::Black );
			tLogin.setPosition( 250, 346 );
			tLogin.setCharacterSize( 25 );
			tLogin.setString( "" );

			tOk.setFont( fontGui );
			tOk.setColor( sf::Color::Black );
			tOk.setPosition( 300, 403 );
			tOk.setCharacterSize( 20 );
			tOk.setString( "Zaloguj" );

			textLogin.setFont( fontGui );
			textLogin.setColor( sf::Color::White );
			textLogin.setPosition( 150, 346 );
			textLogin.setCharacterSize( 25 );
			textLogin.setString( "LOGIN " );

			rectangleLogin.setSize( sf::Vector2f( 200, 25 ) );
			rectangleLogin.setOutlineColor( sf::Color::Black );
			rectangleLogin.setOutlineThickness( 1 );
			rectangleLogin.setPosition( 250, 350 );

			rectangleOk.setSize( sf::Vector2f( 70, 35 ) );
			rectangleOk.setFillColor( sf::Color::Red );
			rectangleOk.setPosition( 300, 400 );

			bSetText = true;

		}

		~ClientGui(void)
		{

		}

		void getLoginFromKeyboard( sf::Event &event, sf::RenderWindow &window );
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

void ClientGui::draw( sf::RenderTarget& target, sf::RenderStates states ) const{
	target.draw( rectangleLogin );
	target.draw( rectangleOk );
	target.draw( tLogin );
	target.draw( tOk );
	target.draw( textLogin );
}

void ClientGui::getLoginFromKeyboard( sf::Event &event, sf::RenderWindow &window ){
	sf::Mouse mouse;
	sf::Vector2i position = mouse.getPosition( window );

	if( event.type == sf::Event::TextEntered ){
		switch( event.text.unicode ){
			case 8:
				if( szLogin.size() > 0 )
					szLogin.erase( szLogin.size()-1,1 );
			break;

			case 13:
					bSetText = false;
			break;

			default:
				szLogin += static_cast< char >( event.text.unicode );
			break;
		}
		tLogin.setString( szLogin );
	}

	if( rectangleOk.getGlobalBounds().contains( sf::Vector2f( position ) ) ){
		
	}
}