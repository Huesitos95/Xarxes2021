//#include <SFML/Network.hpp>
#include <thread>
#include <vector>
#include <iostream>
#include <mutex>
#include <chrono>

std::mutex mtxJugadores;

void TratarTodosClientes(std::vector<std::string>* jugadores)
{
	while (true)
	{
		mtxJugadores.lock();
		for (size_t i = 0; i < jugadores->size(); i++)
		{
			std::cout << jugadores->at(i) << std::endl;
		}
		mtxJugadores.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

void TratarCliente(std::string nick, std::vector<std::string>* jugadores)
{
	for (size_t i = 0; i < 10; i++)
	{
		std::cout << "El jugador " << nick << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	mtxJugadores.lock();
	for (size_t i = 0; i < jugadores->size(); i++)
	{
		if (jugadores->at(i) == nick)
		{
			jugadores->erase(jugadores->begin() + i);
			break;
		}
	}
	mtxJugadores.unlock();

}

/*
int main()
{
	std::string nick;
	std::vector<std::string> jugadores;
	std::thread tAll(TratarTodosClientes, &jugadores);
	tAll.detach();
	do
	{
		//std::cout << "Introdueix nom del jugador: ";
		std::cin >> nick;
		if (nick == "exit") break;
		mtxJugadores.lock();
		jugadores.push_back(nick);
		mtxJugadores.unlock();
		std::thread t(TratarCliente, nick,&jugadores);
		t.detach();
	} while (true);


	return 0;
}
*/