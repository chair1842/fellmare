#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../base/entity.hpp"
using namespace sf;
using namespace std;

class Entity2D : public Entity {
public:
    Vector2f position;
    Vector2f scale;
    float rotation; // in degrees
    Vector2f rect_size;
    unique_ptr<Drawable> drawable; // points to actual shape or sprite

    Entity2D(Vector2f position = { 0,0 }, Vector2f rect_size = { 0,0 });

    virtual void draw(RenderTarget& target);
};
