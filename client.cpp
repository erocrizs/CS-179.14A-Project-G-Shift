#include <SFML/Network.hpp>
#include <iostream>

int main()
{
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("172.20.10.3", 53000);
    if (status != sf::Socket::Done)
    {
        std::cout<< "AHA NOT CONNECTED!" <<std::endl;
    }
}
