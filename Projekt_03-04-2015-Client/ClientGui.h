#pragma once


class ClientGui : public sf::Drawable
{
	private:
		sf::RectangleShape rectangleLogin, rectangleOk;
		sf::Text tLogin, tOk;
		sf::Font fontGui;

	public:
		ClientGui(void){
			fontGui.loadFromFile( "arial.ttf" );

			tLogin.setFont( fontGui );
			tLogin.setPosition( 250, 150 );
			tLogin.setString( "Testowy_Login" );

			rectangleLogin.setSize( sf::Vector2f( 200, 25 ) );
			rectangleLogin.setOutlineColor( sf::Color::Black );
			rectangleLogin.setOutlineThickness( 1 );
			rectangleLogin.setPosition( 250, 150 );

			/*rectangleOk.setSize(sf::Vector2f(100, 50));
			rectangleOk.setOutlineColor(sf::Color::Red);
			rectangleOk.setOutlineThickness(5);
			rectangleOk.setPosition(10, 20);*/
		}

		~ClientGui(void)
		{

		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
			target.draw( rectangleLogin );
			target.draw( tLogin );
		}
};

