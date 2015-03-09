#pragma once
using namespace std;

class serverGui: public sf::Drawable
{
	sf::Font font;						/// czcionka
	sf::Text tServerIp;					/// text zawierajacy ip servera 
	vector<sf::Text> clientIp;			/// text zawierajcy ip podlaczonych klientow
public:

	serverGui(void);																/// ladowanie czcionek i konfiguracja ip servera	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;		/// wypisanie podlaczonych klientow i ip servera
	void addIpClient( string address, string login );												/// dodawanie klienta do wyswietlenia 
	void deleteIpClient( string address , string login);											/// usuniecie klienta z wyswietlania

};

	serverGui::serverGui(void)
	{
		font.loadFromFile( "font.ttf" );
		tServerIp.setFont( font );
		tServerIp.setColor( sf::Color(255,120,0,255) );
		tServerIp.setPosition( 0, 0 );
		tServerIp.setString( "		SERVER IP --> " + sf::IpAddress::getLocalAddress().toString() );
	}

	void serverGui::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw( tServerIp );
		for( int i=0; i<clientIp.size(); i++ )
			target.draw( clientIp[i] );	
	}

	void serverGui::addIpClient( string address , string login  )
	{
		clientIp.push_back( sf::Text() );
		clientIp.back().setFont( font );
		clientIp.back().setString( login + " --> " + address );
		clientIp.back().setColor( sf::Color::White );
		clientIp.back().setPosition( 0, clientIp.size()*30 );

	}

	void serverGui::deleteIpClient( string address, string login )
	{
		for( int i=0; i<clientIp.size(); i++ )			
			if( clientIp[i].getString() == ( login+" --> " +address) ){
				clientIp.erase( clientIp.begin() + i );
				return;
			}
	}
