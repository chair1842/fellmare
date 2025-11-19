#include "player.hpp"

void Player::update(float dt, EntityList& entity_list) {
	if (is_hit && lives == 1) {
		pains.play();
	}
	if (is_hit && (lives > 0)) {
		hits.play();
		lives--;
		is_hit = false;
	}
	else if (lives <= 0) {
		hits.stop();
		pains.stop();
		entity_list.destroy(name);
		return;
	}

	Vector2f velocity;

	if (Keyboard::isKeyPressed(Keyboard::Scan::W) || Keyboard::isKeyPressed(Keyboard::Scan::Up)) {
		velocity.y -= 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Scan::D) || Keyboard::isKeyPressed(Keyboard::Scan::Down)) {
		velocity.y += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Scan::A) || Keyboard::isKeyPressed(Keyboard::Scan::Left)) {
		velocity.x -= 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Scan::D) || Keyboard::isKeyPressed(Keyboard::Scan::Right)) {
		velocity.x += 1;
	}

	velocity = (velocity == Vector2f(0, 0)) 
		? velocity 
		: velocity.normalized() * static_cast<float>(speed) * dt; // The way has been found
	position += velocity;

	// clamp the position to bounds
	position = Vector2f(clamp<float>(position.x, 0, 480 - rect_size.x), clamp<float>(position.y, 0, 480 - rect_size.y)); // rect.y isnt nessecary, but anyways
}

Player::Player(float size, Vector2f pos) 
	: CollisionEntity(pos, { size, size }), hits(hitsbuff), pains(painbuff) {
	if (!hitsbuff.loadFromFile("hit.wav")) {
		println("You deleted your audible pain");
		println("But I DEMAND it");
		throw runtime_error("Failed to load hit.wav");
	}
	hits.setBuffer(hitsbuff);
	if (!painbuff.loadFromFile("pain.wav")) {
		println("Your groans of suffering are gone");
		println("But what?");
		throw runtime_error("Failed to load pain.wav");
	}
	pains.setBuffer(painbuff);

	auto r = make_unique<CircleShape>(size / 2);
	r->setFillColor(Color(128, 128, 255));
	drawable = move(r);
}