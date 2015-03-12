#pragma once

#include "ClientGui.h"
#include <Windows.h>

class ClientConnect : public ClientGui
{
	private:
		sf::TcpListener listenerTcp;
		sf::TcpSocket socketTcp;
		sf::UdpSocket socketUdp;
		sf::IpAddress serverAddress;
		sf::Socket::Status connectStatusTcp;
		sf::Packet pakiet;
		sf::Music musicMessage;

		bool bConnected;

		const int PORT_SERVER_TCP;
		const int PORT_SERVER_UDP;
		const int PORT_CLIENT_UDP;

		const string IP_SERVER;

	public:
		static enum status{
			CLIENT_UNLOGGED = 0,
			CLIENT_LOGGED
		};

	private: status statusClient;

	public: 
		ClientConnect();
		~ClientConnect();

		void logIn();
		void logOut();
		void loopConnect();

		bool getStatusClient();
		bool setStatusClient( status statusClient );
		string setLoginClient( string szLogin );
		string getLoginClient();
		bool getConnectTcp();
		bool getDataUdp();
		bool getDataTcp();
		bool sendDataUdp( string szText );
		bool sendDataTcp( string szText );
		bool sendDataUdp123();
		bool sendDataTcp123();
};

void ClientConnect::loopConnect(){
	getDataUdp();
	getDataTcp();
}

bool ClientConnect::sendDataUdp123(){
	pakiet.clear();
	pakiet << "login" << "Muzzik" << "moje_haslo_123";
	socketUdp.send( pakiet, IP_SERVER, PORT_SERVER_UDP );
	return true;
}

bool ClientConnect::sendDataTcp123(){
	pakiet.clear();	connectStatusTcp = socketTcp.connect( serverAddress, PORT_SERVER_TCP );

	if( connectStatusTcp == sf::Socket::Done )
		bConnected = true;
	else
		return false;

	pakiet.clear();
	pakiet << "login" << "admin" << "admin";
	socketTcp.send( pakiet );
	socketTcp.disconnect();
	return true;
}

ClientConnect::ClientConnect(): PORT_SERVER_TCP( 12345 ), PORT_SERVER_UDP( 54321 ), PORT_CLIENT_UDP( 11111 ), IP_SERVER( "25.60.93.242" ){
	bConnected = false;
	statusClient = CLIENT_UNLOGGED;
	serverAddress = IP_SERVER;
	listenerTcp.setBlocking( false );
	socketUdp.setBlocking( false );
	listenerTcp.listen( 12121 );
	socketUdp.bind( PORT_CLIENT_UDP );

	musicMessage.openFromFile( "message.ogg" );
}

ClientConnect::~ClientConnect(){
	bConnected = false;
}

bool ClientConnect::sendDataTcp( string szText ){
	connectStatusTcp = socketTcp.connect( serverAddress, PORT_SERVER_TCP );

	if( connectStatusTcp == sf::Socket::Done )
		bConnected = true;
	else
		return false;

	pakiet.clear();
	pakiet << szLogin << szText;
	socketTcp.send( pakiet );
	socketTcp.disconnect();
	return true;
}

bool ClientConnect::getStatusClient(){
	return statusClient;
}

bool ClientConnect::setStatusClient( status statusClient ){
	return this->statusClient = statusClient;
}

string ClientConnect::getLoginClient(){
	return szLogin;
}

string ClientConnect::setLoginClient( string szLogin ){
	return this->szLogin = szLogin;
}

bool ClientConnect::getConnectTcp(){
	return bConnected;
}

bool ClientConnect::sendDataUdp( string szText ){
	pakiet.clear();
	pakiet << szText;
	socketUdp.send( pakiet, IP_SERVER, PORT_SERVER_UDP );
	return true;
}

bool ClientConnect::getDataUdp(){
	sf::IpAddress senderAddress;
	unsigned short senderPort;
	string szText, szText2;

	pakiet.clear();
	if( !socketUdp.receive( pakiet, senderAddress, senderPort ) ){
		pakiet >> szText >> szText2;
		cout << "Odebrano od " << szText << ": " << szText2 << endl;
		musicMessage.play();
	}
	return true;
}

bool ClientConnect::getDataTcp(){
	int iTest;
	if( listenerTcp.accept( socketTcp ) == sf::Socket::Done ){
		cout << "Odebranie polaczenia tcp od: " << socketTcp.getRemoteAddress().toString() << endl;
		socketTcp.receive( pakiet );
		pakiet >> iTest; 
		cout << " -> " << iTest << endl;
	}
	return true;
}

void ClientConnect::logIn(){
	sendDataTcp( "dolacz" );
}

void ClientConnect::logOut(){
	sendDataTcp( "rozlacz" );
}
