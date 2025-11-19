#pragma once
#include "entity2d.hpp"
#include "bullet.hpp"
#include "player.hpp"
#include <SFML/Audio.hpp>
#include <print>
#include <stdexcept>

class Shooter : public Entity2D {
public:
	int cooldown = 50; // centiseconds
	int tsls = 0; // time since last shot in centiseconds
	SoundBuffer shtsbuff;
	Sound shoots;

	Shooter(Vector2f position, int cooldown = 50);
	void update(float dt, EntityList& entity_list) override;
	void shoot(EntityList& entity_list, Player* player);
};