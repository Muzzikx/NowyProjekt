#pragma once
#include <SFML/Network.hpp>
#include <Windows.h>

using namespace std;

class ClientConnect 
{
	sf::TcpListener listenerTcp;
	sf::TcpSocket socketTcp;
	sf::UdpSocket socketUdp;
	sf::Packet packet;

public: 
	ClientConnect();			/// ustawienie danych 
	~ClientConnect();			/// rozlaczeni z serverem

	void loopConnect();										/// wywolywane do pobrania danych z servera jesli wysyla
	bool getDataUdp();										/// pobiera dane na udp
	bool sendDataUdp( string szText );						/// wysyla podana wiadomosc do servera za pomocac udp
	bool sendDataTcp( string szText );						/// wysyla podana wiadomosc do servera za pomocac tcp
	bool loginOnServer( string login, string password );	/// odpowiada za wyslanie do servera loginu i haslo oraz uruchomienei getLoginTcp aby dostac odpowiedz
	bool getLoginTcp();										/// zwraca true or false jesli dobrze sie zalogowalismy na server
};

ClientConnect::ClientConnect(){
	listenerTcp.setBlocking( false );
	socketUdp.setBlocking( false );
	listenerTcp.listen( PORT_CLIENT_TCP );
	socketUdp.bind( PORT_CLIENT_UDP );
}

ClientConnect::~ClientConnect(){
	sendDataTcp( "rozlacz" );
}

void ClientConnect::loopConnect(){
	getDataUdp();
}

bool ClientConnect::loginOnServer( string login, string password ){
	packet.clear();	
	socketTcp.disconnect();

	if( socketTcp.connect( IP_SERVER, PORT_SERVER_TCP ) == sf::Socket::Done )
	{
		packet.clear();
		packet << "login" << login << password;
		socketTcp.send( packet );
		return getLoginTcp();
	}
	return false;
}

bool ClientConnect::getLoginTcp()
{
	bool ret = false;
	listenerTcp.setBlocking( true );
	
	if( listenerTcp.accept( socketTcp ) == sf::Socket::Done ){
		socketTcp.receive( packet );
		packet >> ret; 
	}

	listenerTcp.setBlocking( false );

	return ret;
}

bool ClientConnect::sendDataTcp( string szText ){
	packet.clear();	
	socketTcp.disconnect();

	if( socketTcp.connect( IP_SERVER, PORT_SERVER_TCP ) == sf::Socket::Done )
	{
		packet << szText;
		socketTcp.send( packet );
		return true;
	}
	return false;
}

bool ClientConnect::sendDataUdp( string szText ){
	packet.clear();
	packet << szText;
	socketUdp.send( packet, IP_SERVER, PORT_SERVER_UDP );
	return true;
}

bool ClientConnect::getDataUdp(){
	sf::IpAddress senderAddress;
	unsigned short senderPort;
	string szText, szText2;

	packet.clear();
	if( !socketUdp.receive( packet, senderAddress, senderPort ) ){
		packet >> szText >> szText2;
		cout << "Odebrano od " << szText << ": " << szText2 << endl;
	}
	return true;
}
