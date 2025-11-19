#pragma once
#include <SFML/Graphics.hpp>
#include "entity_list.hpp"
#include <memory>
using namespace sf;
using namespace std;

// Base class for all entities

class Entity {
public:
    string name;

    virtual void update(float dt, EntityList& entity_list) {}
    virtual void exit() {}
    virtual void enter() {}
};
