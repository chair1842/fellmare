#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
using namespace sf;
using namespace std;

class Entity {
public:
    Vector2f position;
    float rotation = 0; // in degrees
    Vector2f rect_size;
    unique_ptr<Drawable> drawable; // points to actual shape or sprite
    bool to_delete = false;

    Entity(Vector2f position = { 0,0 }, Vector2f rect_size = { 0,0 });

    virtual void draw(RenderTarget& target);

    virtual void update(float dt, vector<unique_ptr<Entity>>& entity_list, vector<unique_ptr<Entity>>& to_spawn) {}
    virtual void exit() {}
    virtual void enter() {}
};
