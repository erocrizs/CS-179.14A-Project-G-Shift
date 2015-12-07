#include "State.h"
#include "StateManager.h"
#include <cassert>
#include <iostream>

StateManager::StateManager()
{
    std::vector<State*> temp;
    m_states = temp;
}

void StateManager::push(State* s)
{
    assert(s->manager==nullptr && "Only one manager per state allowed");
    State* prev = nullptr;

    if(!m_states.empty())
    {
        prev = m_states.back();
    }

    s->manager = this;
    s->m_isActive = true;
    m_states.push_back(s);
    s->onActivate();

    if(prev!=nullptr)
    {
        prev->m_isActive = false;
        prev->onDeactivate();
    }
}

void StateManager::pop(unsigned int level)
{
    while(level-- > 0 && !m_states.empty())
    {
        auto s = m_states.back();
        m_states.pop_back();
        s->manager = nullptr;
        s->m_isActive = false;
        s->onDeactivate();
    }

    if(!m_states.empty() && m_states.back()->m_isActive==false)
    {
        m_states.back()->m_isActive = true;
        m_states.back()->onActivate();
    }
}

void StateManager::update(float dt)
{
    if(m_states.empty()) return;
    m_states.back()->update(dt);
}

void StateManager::draw(sf::RenderWindow& window)
{
    if(m_states.empty()) return;
    m_states.back()->draw(window);
}
