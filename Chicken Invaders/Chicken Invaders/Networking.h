#pragma once
#include <SFML/Network.hpp>

class Networking
{
public:
	void ServerConnection();
	void ClientConnection();

	void SendData();
	bool ReceiveData();
public:
	sf::Packet packet;

private:
	sf::IpAddress ip = "172.27.1.119";
	sf::TcpListener listener;
	sf::TcpSocket socket;
};

