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
}

void Networking::ClientConnection()
{
	socket.connect(ip, 49200);
	socket.receive(packet);
	std::string text;
	packet >> text;
	std::cout << text << std::endl;

	text = "Client has connected.";
	packet.clear();
	packet << text;
	socket.send(packet);
}

void Networking::SendData()
{
	socket.send(packet);
}

bool Networking::ReceiveData()
{
	if(socket.receive(packet) == socket.Done)
		return true;
	return false;
}
