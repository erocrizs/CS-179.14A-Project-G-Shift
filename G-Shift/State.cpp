#include "State.h"
#include "StateManager.h"

State::State()
{
    manager = nullptr;
    m_isActive = false;
}

void State::popSelf(unsigned int level)
{
    manager->pop(level);
}
