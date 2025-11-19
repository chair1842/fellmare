#include "collision_entity.hpp"

bool CollisionEntity::checkCollision(const CollisionEntity& other) const{
	return !(position.x + rect_size.x < other.position.x ||
		position.x > other.position.x + other.rect_size.x ||
		position.y + rect_size.y < other.position.y ||
		position.y > other.position.y + other.rect_size.y);
}

CollisionEntity::CollisionEntity(Vector2f position, Vector2f rect_size)
	: Entity2D(position, rect_size) {
}