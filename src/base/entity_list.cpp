#include "entity_list.hpp"

void EntityList::flush() {
	// Add entities from spawn_buffer to list
	for (auto& [id, entity] : spawn_buffer) {
		list[id] = std::move(entity);
	}
	spawn_buffer.clear();
	// Remove entities in destroy_buffer from list
	for (int id : destroy_buffer) {
		list.erase(id);
	}
	destroy_buffer.clear();
}

void EntityList::update(float dt) {
	for (auto& [id, entity] : list) {
		if (entity->update_enabled) {
			entity->update(dt);
		}
	}
}

void EntityList::clear() {
	list.clear();
	spawn_buffer.clear();
	destroy_buffer.clear();
}

void EntityList::spawn(std::unique_ptr<Entity> entity) {
	spawn_buffer[entity->id] = std::move(entity);
}

void EntityList::spawn(std::string name, std::unique_ptr<Entity> entity) {
	entity->name = name;
	spawn_buffer[entity->id] = std::move(entity);
}

void EntityList::destroy(int id) {
	destroy_buffer.push_back(id);
}