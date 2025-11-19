#include "shooter.hpp"

Shooter::Shooter(Vector2f position, int cldwn)
	: Entity2D(position, { 32, 32 }), shoots(shtsbuff) {
	if (!shtsbuff.loadFromFile("shoot.wav")) {
		println("I know you deleted shoot.wav");
		println("I need it back to play a sound yk");
		throw runtime_error("Failed to load shoot.wav");
	}
	shoots.setBuffer(shtsbuff);

	cooldown = cldwn;
	auto r = make_unique<RectangleShape>(Vector2f{ 32, 32 });
	r->setFillColor(Color(255, 128, 128));
	r->setOrigin({ 16,16 });
	drawable = move(r);
}

void Shooter::update(float dt, EntityList& entity_list) {
	tsls += static_cast<int>(dt * 100); // convert to centiseconds

	Player* player = entity_list.get_as<Player>("player");
	if (!player) { 
		shoots.stop();
		entity_list.destroy(name);
		return; 
	} // no player found

	Vector2f direction = player->position - position;
	rotation = atan2f(direction.y, direction.x) * 180.0f / 3.14159265f;

	// simple AI: shoot towards the player if cooldown is over
	if (tsls >= cooldown) {
		shoot(entity_list, player);
		tsls = 0;
	}
}

void Shooter::shoot(EntityList& entity_list, Player* player) {
	if (!player) return; // no player found

	shoots.play();

	// calculate angle towards player
	Vector2f direction = player->position - position;
	float angle = atan2f(direction.y, direction.x) * 180.0f / 3.14159265f; // Pie dont get it ;P
	entity_list.spawn<Bullet>("bullet_" + (rand() % 101), angle, position + rect_size / 4.0f);
}