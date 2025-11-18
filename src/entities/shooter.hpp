#pragma once
#include "../base/entity.hpp"
#include "bullet.hpp"
#include "player.hpp"
#include <SFML/Audio.hpp>
#include <print>
#include <stdexcept>

class Shooter : public Entity {
public:
	int cooldown = 50; // centiseconds
	int tsls = 0; // time since last shot in centiseconds
	SoundBuffer shtsbuff;
	Sound shoots;

	Shooter(Vector2f position, int cooldown = 50);
	void update(float dt, vector<unique_ptr<Entity>>& entity_list, vector<unique_ptr<Entity>>& to_spawn) override;
	void shoot(vector<unique_ptr<Entity>>& entity_list, vector<unique_ptr<Entity>>& to_spawn, bool& to_delete);
};