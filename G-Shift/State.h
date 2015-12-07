#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <SFML/Graphics.hpp>

class StateManager;
class State
{
protected:
    friend class StateManager;
    StateManager *manager;
    bool m_isActive;

    void popSelf(unsigned int);
    bool isActive() const {
        return m_isActive;
    }
    bool isOnStack() const {
        return manager != nullptr;
    }
public:
    State();
    virtual void update(float) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void onActivate() {}
    virtual void onDeactivate() {}
};

#endif // STATE_H_INCLUDED
