#pragma once
#include "entity.hpp"
#include <SFML/Graphics.hpp>

class Entity2D : public Entity {
public:
	sf::Vector2f position{ 0.f, 0.f };
	float rotation = 0.f; // In degrees
	sf::Vector2f bounding_box{ 0.f, 0.f }; // Width and height

	std::unique_ptr<sf::Drawable> drawable;
	bool visible = true;

	void draw(sf::RenderTarget& target) const;

	Entity2D(const std::string& name, int id) : Entity(name, id) {}
	Entity2D(const Entity2D& other)
		: Entity(other),
		position(other.position),
		rotation(other.rotation) {
	}
};