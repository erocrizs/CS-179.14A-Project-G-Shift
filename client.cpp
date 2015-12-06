#include <SFML/Network.hpp>
#include <iostream>

int main()
{
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("172.20.10.3", 53000);
    if (status != sf::Socket::Done){
        std::cout<< "AHA NOT CONNECTED!" <<std::endl;
    }
    else{ //should be in a while loop too to continuously get messages
        std::cout << "Connected to server" <<std::endl;
        sf::Packet packet2;
        if(socket.receive(packet2) == sf::Socket::Done){
            std::string as;
            packet2 >> as;
            std::cout << as << std::endl;
        }
        system("PAUSE");
    }
}
