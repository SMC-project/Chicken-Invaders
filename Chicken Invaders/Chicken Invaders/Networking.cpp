#include "Networking.h"
#include <iostream>

void Networking::ServerConnection()
{
	listener.listen(49200);
	listener.accept(socket);
	std::string text = "Connected to server.";
	packet << text;
	socket.send(packet);

	packet.clear();
	socket.receive(packet);
	packet >> text;
	std::cout << text << std::endl;

	socket.setBlocking(false);
}

bool Networking::ClientConnection()
{
	if (socket.connect(ip, 49200) != sf::Socket::Done)
		return false;

	socket.receive(packet);
	std::string text;
	packet >> text;
	std::cout << text << std::endl;

	text = "Client has connected.";
	packet.clear();
	packet << text;
	socket.send(packet);

	socket.setBlocking(false);
	return true;
}

void Networking::SendData()
{
	socket.send(packet);
}

bool Networking::ReceiveData()
{
	if (socket.receive(packet) == socket.Done)
		return true;
	return false;
}



