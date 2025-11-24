#pragma once
#include "../base/entity2d.hpp"
#include <print>

class Player : public Entity2D {
public:
	sf::Vector2f velocity{ 0.f, 0.f };
	const float speed = 3;

	void update(float dt) override;
	Player() : Entity2D("Player", 1) {
		// set drawable to a square
		bounding_box = { 32.f, 32.f };
		position = { 234.f, 234.f };
		drawable = std::make_unique<sf::RectangleShape>(bounding_box);
	}
};