#pragma once

#include "ClientGui.h"

class ClientConnect : public ClientGui
{
	private:
		sf::TcpSocket socketTcp;
		sf::UdpSocket socketUdp;
		sf::IpAddress serverAddress;
		sf::Socket::Status connectStatusTcp;
		sf::Packet pakiet;

		bool bConnected;

		const int PORT_SERVER_TCP;
		const int PORT_SERVER_UDP;
		const int PORT_CLIENT_UDP;

		const string IP_SERVER;

		enum status{
			CLIENT_UNLOGGED = 0,
			CLIENT_LOGGED
		};

		status statusClient;
		string szLoginClient;

		ClientGui clientGui;

	public:
		ClientConnect();
		~ClientConnect();

		void logIn();
		void logOut();
		bool getStatusClient();
		bool setStatusClient( status statusClient );
		string setLoginClient( string szLoginClient );
		string getLoginClient();
		bool getConnectTcp();
		bool getDataUdp();
		bool getDataTcp();
		bool sendDataUdp( string szText );
		bool sendDataTcp( string szText );
};

ClientConnect::ClientConnect(): PORT_SERVER_TCP( 12345 ), PORT_SERVER_UDP( 54321 ), PORT_CLIENT_UDP( 11111 ), IP_SERVER( "192.168.0.102" ){
	bConnected = false;
	statusClient = CLIENT_UNLOGGED;
	serverAddress = IP_SERVER;
	socketUdp.setBlocking( false );
	socketUdp.bind( PORT_CLIENT_UDP );
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
	pakiet << szLoginClient << szText;
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
	return szLoginClient;
}

string ClientConnect::setLoginClient( string szLoginClient ){
	return this->szLoginClient = szLoginClient;
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
	string szText;

	pakiet.clear();
	if( !socketUdp.receive( pakiet, senderAddress, senderPort ) ){
		pakiet >> szText;
		cout << "Odebrano: " << szText << endl;
	}
	return true;
}

void ClientConnect::logIn(){
	sendDataTcp( "dolacz" );
}

void ClientConnect::logOut(){
	sendDataTcp( "rozlacz" );
}
