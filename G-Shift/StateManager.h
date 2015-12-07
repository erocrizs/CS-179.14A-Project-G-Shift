#ifndef STATEMANAGER_H_INCLUDED
#define STATEMANAGER_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>

class State;
class Splash;

class StateManager {
private:
    std::vector<State*> game_states;
    std::vector<State*> m_states;
public:
    StateManager();
    void push(int id);
    void pop(unsigned int);
    void update(float dt);
    void draw(sf::RenderWindow&);
    void addScreen(State*);
};

#endif // STATEMANAGER_H_INCLUDED
