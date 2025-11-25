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

	Entity* get(int id);
	Entity* get(const std::string& name);
	int name_to_id(const std::string& name);
	std::string id_to_name(int id);

	bool exists(int id);
	bool exists(const std::string& name);
	bool in_spawn_buffer(int id);
	bool in_spawn_buffer(const std::string& name);
	bool in_destroy_buffer(int id);
	bool in_destroy_buffer(const std::string& name);
};