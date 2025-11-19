#pragma once
#include "collision_entity.hpp"
#include "player.hpp"

class Bullet : public CollisionEntity {
public:
	const int speed = 750;
	Bullet(float angle, Vector2f pos);
	
	void update(float dt, EntityList& entity_list) override;
};
