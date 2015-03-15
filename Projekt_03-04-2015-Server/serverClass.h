#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include "serverGui.h"
#include <fstream>

using namespace std;

class serverClass: public serverGui
{
	/// STALE PORTOW NA KTORYCH DZIALAMY DEFINIOWANE W KONSTRUKTORZE
	const int SERVER_PORT_TCP;
	const int CLIENT_PORT_TCP;
	const int SERVER_PORT_UDP;
	const int CLIENT_PORT_UDP;

	struct s_message{							/// struktura przechowywana w kolejce packetsQueue
		sf::Packet packet;
		sf::IpAddress address;
		s_message( sf::Packet p, sf::IpAddress i ): packet(p), address(i){};
	};

	struct s_address{
		sf::IpAddress ip;
		string login;
		s_address( sf::IpAddress p, string l ): ip(p), login(l){};
	};

	sf::TcpListener listener;					/// listener do tcp
	sf::TcpSocket socketTcp;					/// socket sluzacy do odbierania i wysylania pakietow przez tcp 
	sf::UdpSocket socketUdp;					/// socket sluzacy do odbierania i wysylania pakietow przez udp 
	sf::Packet receivePacket, senderPacket;		/// pakiety do odbierania i do wyslyania 
	sf::IpAddress senderAdres;					/// zapisany adres do kogo ostatnio wyslalismy pakiet udp 
	unsigned short senderPort;					/// zapisany port do kogo ostatnio wyslalismy pakiet udp 
	vector<s_address> activeClient;				/// lista polaczonych klientow 
	std::queue<s_message> packetsQueue;			/// kolejka pakietow do wyslania
	
public:

	serverClass(void);															/// binduje odpowiednie porty 
	void checkConnection();														/// funkcja odbierajaca udp i tcp oraz wykonywujacca odpowiednie akcje
	void checkUdp();															/// odbieranie na udp
	void checkTcp();															/// odbieranie na tcp
	void checkAction( sf::Packet packet );										/// obsluga polecenia z tcp
	void addClient( s_address address );										/// dodanie nowego adresu do listy klientow podlaczonych 
	void deleteClient( sf::IpAddress login );											/// usuniecie adresu z listy klientow podlaczonych 
	void sendDataToAll();														/// wyslanie danego pakietu od nadawcy do reszty podlaczonych klientow 
	void checkLogin( string login, string password, sf::IpAddress address );	/// sprawdza czy podany login haslo znajduje sie w bazie
	~serverClass(void);	
};

	serverClass::serverClass(void): SERVER_PORT_TCP( 12345 ), SERVER_PORT_UDP( 54321 ), CLIENT_PORT_UDP( 11111 ), CLIENT_PORT_TCP( 12121 )
	{
		listener.setBlocking(false);
		socketUdp.setBlocking(false);

		try {
			cout <<"Bindowanie portow" << endl;
			socketUdp.bind( SERVER_PORT_UDP );
			listener.listen( SERVER_PORT_TCP );
		}
		catch( sf::UdpSocket &l ){
			cout << "Blad przy bindowaniu portu udp: " << SERVER_PORT_UDP << endl;
		}
		catch( sf::TcpListener &l ){
			cout << "Blad przy bindowaniu portu tcp: " << SERVER_PORT_TCP << endl;
		}
		
	}

	void serverClass::checkConnection()
	{
		checkUdp();
		checkTcp();
	}

	void serverClass::checkUdp()		
	{
		if( !socketUdp.receive( receivePacket, senderAdres, senderPort ) )
			packetsQueue.push( s_message( receivePacket, senderAdres ) );
		else if( packetsQueue.size() > 0 )
			sendDataToAll();
		
	}

	void serverClass::checkTcp()		
	{
		if ( listener.accept(socketTcp) == sf::Socket::Done ){
			cout << "Odebranie polaczenia tcp od: " << socketTcp.getRemoteAddress().toString() << endl;
			while( !socketTcp.receive( receivePacket ) )
				checkAction( receivePacket );
		}
	}

	void serverClass::checkAction( sf::Packet packet )
	{
		string message, login;
		packet >> message >> login;

		cout << "message: " << message << endl;
		if( message == "rozlacz" ){
			deleteClient( socketTcp.getRemoteAddress() );
		}
		else if( message == "login" )
		{
			string password;
			packet >> password;
			checkLogin( login, password, socketTcp.getRemoteAddress() );
		}
	}

	void serverClass::checkLogin( string login, string password, sf::IpAddress address )
	{
		cout << "check login: " << address.toString() << endl;
		fstream file;
		file.open( "baza.txt" );

		socketTcp.setBlocking( true );
	
		socketTcp.disconnect();
		string str;

		if ( socketTcp.connect( address, CLIENT_PORT_TCP, sf::Time( sf::seconds(10) )) == sf::Socket::Done )
			cout << "polaczony" << endl;

		bool isGoodLogin = false;
		senderPacket.clear();

		while( file.is_open() && !file.eof() )
		{
			file >> str;
			if( str == login )
			{
				file >> str;
				if( str == password )
				{
					isGoodLogin = true; 
					addClient( s_address( address, login ) );
					break;
				}
			}
			else file >> str;
		}

		senderPacket << isGoodLogin;
		socketTcp.send( senderPacket );
		socketTcp.setBlocking( false );
	}

	void serverClass::addClient( s_address address )
	{
		for( int i=0; i<activeClient.size(); i++ )
			if( activeClient[i].ip == address.ip )
				return;

		activeClient.push_back( address );
		addIpClient( activeClient.back().ip.toString(), activeClient.back().login );
		cout << "Dodano: " << activeClient.back().ip.toString() << " login : " << address.login << endl;
	}

	void serverClass::deleteClient( sf::IpAddress login )
	{

		cout << "size: " << activeClient.size() << endl;
		for( int i=0; i<activeClient.size(); i++ )
		{
			
			if( activeClient[i].ip == login ){
				cout << "Usunieto: " << activeClient[i].login << endl;
				deleteIpClient( activeClient[i].ip.toString(), activeClient[i].login );
				activeClient.erase( activeClient.begin() + i );	
				return;
			}
		}
	}

	void serverClass::sendDataToAll()
	{
		senderPacket.clear();

		for( int i=0; i<activeClient.size(); i++ ){
			if( packetsQueue.front().address != activeClient[i].ip ) {			/// pomija przy wysylaniu adres nadawcy 
				string ss;
				packetsQueue.front().packet >> ss;
				senderPacket << packetsQueue.front().address.toString() << ss;
				socketUdp.send( senderPacket, activeClient[i].ip, CLIENT_PORT_UDP );	
			}
		}	

		packetsQueue.pop();

		
	}

	serverClass::~serverClass(void)
	{
		listener.close();
		socketTcp.disconnect();
	}
