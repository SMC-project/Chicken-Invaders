#pragma once
#include <SFML/Network.hpp>

class Networking
{
public:
	void ServerConnection();
	bool ClientConnection();

	void SendData();
	bool ReceiveData();
public:
	sf::Packet packet;

private:
	sf::IpAddress ip = "192.168.1.142";
	sf::TcpListener listener;
	sf::TcpSocket socket;
};

