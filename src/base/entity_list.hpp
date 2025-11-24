#pragma once
#include "entity.hpp"
#include <unordered_map>
#include <vector>
#include <memory>

class EntityList {
public:
	std::unordered_map<int, std::unique_ptr<Entity>> list; // Main list
	std::unordered_map<int, std::unique_ptr<Entity>> spawn_buffer; // Entities to add
	std::vector<int> destroy_buffer; // Entities to destroy

	void flush();
	void update(float dt);
	void clear();

	void spawn(std::unique_ptr<Entity> entity);
	void spawn(std::string name, std::unique_ptr<Entity> entity);
	void destroy(int id);
};