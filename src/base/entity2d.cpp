#include "entity2d.hpp"

void Entity2D::draw(sf::RenderTarget& target) const {
	// use drawable with position and rotation if visible
	if (visible && drawable) {
		sf::RenderStates states;
		states.transform.translate(position);
		states.transform.rotate(sf::degrees(rotation));
		target.draw(*drawable, states);
	}
}