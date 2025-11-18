#include "entity.hpp"

Entity::Entity(Vector2f position, Vector2f rect_size)
	: position(position), rect_size(rect_size) { }

void Entity::draw(RenderTarget& target) {
	if (!drawable) return;

	if (auto t = dynamic_cast<Transformable*>(drawable.get())) {
		t->setPosition(position);
		t->setRotation(sf::degrees(rotation));
	}
	target.draw(*drawable);
}