#include "bullet.hpp"

void Bullet::update(float dt, EntityList& entity_list) {
	// move the bullet according to rotation and speed
	// then delete it if it goes out of bounds
	const float rad = rotation * (3.14159265f / 180.0f);
	Vector2f direction = Vector2f(cosf(rad), sinf(rad));
	position += direction * static_cast<float>(speed) * dt;

	Player* player = entity_list.get_as<Player>("player");

	// check for player, if hit, enable is_hit
	if (entity_list.exists("player")) {
		if (checkCollision(*player)) { 
			player->is_hit = true; 
		}
	} 
	else {
		entity_list.destroy(name);
	}

	if (position.x < -rect_size.x || position.x > 480 || position.y < -rect_size.y || position.y > 480) {
		entity_list.destroy(name);
	}
}

Bullet::Bullet(float angle, Vector2f pos)
	: CollisionEntity(pos, { 8, 8 }) {
	auto r = make_unique<RectangleShape>(Vector2f{ 8, 8 });
	r->setFillColor(Color(255, 255, 0));
	drawable = move(r);
	rotation = angle;
}