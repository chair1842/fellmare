#pragma once
#include "../base/entity.hpp"
// a entity class for collision detection

class CollisionEntity : public Entity {
public:
	CollisionEntity(Vector2f position, Vector2f rect_size);

	// AABB collision detection
	// The dark magic of copilot
	bool checkCollision(const CollisionEntity& other) const;
};
