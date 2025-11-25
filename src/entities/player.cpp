#include "player.hpp"

void Player::update(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
		velocity.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
		velocity.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
		velocity.x -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
		velocity.x += 1;
	}

	velocity = (velocity == sf::Vector2f(0, 0)) ? sf::Vector2f(0,0) : velocity.normalized();
	position += velocity * dt * 100.f * speed;
	velocity = { 0.f, 0.f };
}