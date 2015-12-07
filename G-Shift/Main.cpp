#include <SFML/Graphics.hpp>
#include <iostream>
#include "State.h"
#include "StateManager.h"
#include "Splash.h"

float fps = 30;
float spf = 1.0/fps;
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "G-Shift");
    StateManager sm;
    Splash splash;
    sm.push(&splash);
    sf::Clock clock;
    while (window.isOpen())
    {
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sm.update(spf);

        window.clear();
        sm.draw(window);
        window.display();

        sf::Time t = clock.getElapsedTime();
        float tInSec = t.asSeconds();
        float rem = spf-tInSec;
        if(rem>0) {
            sf::sleep(sf::seconds(rem));
        }
        tInSec = clock.getElapsedTime().asSeconds();
    }

    return 0;
}
