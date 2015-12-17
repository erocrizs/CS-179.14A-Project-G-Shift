#include <SFML/Graphics.hpp>
#include <iostream>
#include "State.h"
#include "StateManager.h"
#include "Splash.h"
#include "MenuScreen.h"
#include "HostState.h"
#include "GameState.h"
#include "JoinState.h"
#include "GameServer.h"

float fps = 30;
float spf = 1.0/fps;
std::string text;
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "G-Shift", sf::Style::Close);
    StateManager sm;

    Splash splash_screen;
    sm.addScreen(&splash_screen); //0
    MenuScreen menu_screen;
    sm.addScreen(&menu_screen); //1
    HostState host_screen;
    sm.addScreen(&host_screen); //2
    GameState game_screen;
    sm.addScreen(&game_screen); //3
    JoinState join_screen;
    sm.addScreen(&join_screen); //4

    sm.push(0);
    GameServer* gs = game_screen.getServer();
    sf::Clock clock;
    while (window.isOpen())
    {
        clock.restart();

        sf::Event event;
        float u = sf::Mouse::getPosition(window).x;
        float v = sf::Mouse::getPosition(window).y;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
                gs->timeFinish();
                system("pause");
            }
            if(event.type == sf::Event::MouseButtonPressed)
                sm.onClick(u, v);
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b')
                {
                    if(text.size() == 0){}
                    else{text.erase(text.size() - 1, 1);}

                }
                else if (event.text.unicode < 128)
                {
                    text += static_cast<char>(event.text.unicode);
                }
                sm.getText(text);
            }
            if(event.type == sf::Event::KeyReleased)
            {
                sm.onKeyReleased(event);
            }
        }
        sm.update(spf, u, v);
        //std::cout << "("<< u << ", " << v << ")" << std::endl;
        window.clear();
        sm.draw(window);
        window.display();

        sf::Time t = clock.getElapsedTime();
        float tInSec = t.asSeconds();
        float rem = spf-tInSec;
        if(rem>0) {
            sf::sleep(sf::seconds(rem));
            //std::cout << "rem: " << rem << std::endl;
        }
        t = clock.getElapsedTime();
        tInSec = t.asSeconds();
        //std::cout<< "frameRate: " << tInSec << std::endl;
    }


    return 0;
}
