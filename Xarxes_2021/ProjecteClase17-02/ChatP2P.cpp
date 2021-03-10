#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

bool Servidor(sf::TcpSocket* sock)
{
	sf::Socket::Status status;
	//Listener escoltant el port.
	sf::TcpListener listener;
	status = listener.listen(50000);
	if (status != sf::Socket::Done)
	{
		std::cout << "Error en el listener\n";
		return false;
	}

	//Print de IP:port per el que s'escolta
	sf::IpAddress ip = sf::IpAddress::LocalHost;
	std::cout << ip.getLocalAddress() << ":" << std::to_string(50000) << std::endl;
	//Quedar-se esperant en accept per el Socket nou
	status = listener.accept(*sock);
	listener.close();
	if (status != sf::Socket::Done)
	{
		std::cout << "Error en el accept\n";
		return false;
	}
	return true;
}

bool Client(sf::TcpSocket* sock, sf::IpAddress ip, unsigned short port)
{
	//Connect a IP:port indicats.
	sf::Socket::Status status;
	status = sock->connect(ip, port);
	if (status != sf::Socket::Done)
	{
		std::cout << "Error en el connect\n";
		return false;
	}
	return true;
}

void Rebre(sf::TcpSocket* sock)
{
	//Fer receive en bucle
	while (true)
	{
		
		//sock->receive(sf::Packet pack);
	}
}
int main()
{
	//Decidir si som client o server
	std::cout << "Vols ser el client (c) o el servidor(s) del xat? " << std::endl;
	char c;
	std::cin >> c;
	sf::TcpSocket* sock = new sf::TcpSocket();
	bool okConexio = false;

	if (c == 's')
	{
		okConexio = Servidor(sock);
	}
	else if(c == 'c')
	{
		//Demanar IP:port i passar per parametre.
		std::cout << "IP a la que et vols conectar? " << std::endl;
		std::string ip;
		std::cin >> ip;
		unsigned short port;
		std::cout << "A quin port et vols conectar? " << std::endl;
		std::cin >> port;
		okConexio = Client(sock, ip, port);
	}
	if (okConexio)
	{
		//Si la conexió es bona, ens quedem amb els thread de rebre i enviar.
		std::thread t(Rebre, sock);
		t.detach();
		//enviar packets 
		//getline
		//send
	}

	//TCPSocket -> a partir del que es pot fer send i receive


	return 0;
}