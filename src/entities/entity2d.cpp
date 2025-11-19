#include "entity2d.hpp"

Entity2D::Entity2D(Vector2f position, Vector2f rect_size)
	: position(position), rect_size(rect_size) {
}

void Entity2D::draw(RenderTarget& target) {
	if (!drawable) return;

	if (auto t = dynamic_cast<Transformable*>(drawable.get())) {
		t->setPosition(position);
		t->setRotation(sf::degrees(rotation));
	}
	target.draw(*drawable);
}