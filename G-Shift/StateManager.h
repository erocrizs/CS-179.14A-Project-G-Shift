#ifndef STATEMANAGER_H_INCLUDED
#define STATEMANAGER_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>

class State;
class StateManager {
private:
    std::vector<State*> m_states;
public:
    StateManager();
    void push(State*);
    void pop(unsigned int);
    void update(float dt);
    void draw(sf::RenderWindow&);
};

#endif // STATEMANAGER_H_INCLUDED
