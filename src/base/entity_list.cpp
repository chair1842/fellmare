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
			entity->update(dt, *this);
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

Entity* EntityList::get(int id) {
	if (list.find(id) != list.end()) {
		return list[id].get();
	}
	return nullptr;
}

Entity* EntityList::get(const std::string& name) {
	for (auto& [id, entity] : list) {
		if (entity->name == name) {
			return entity.get();
		}
	}
	return nullptr;
}

int EntityList::name_to_id(const std::string& name) {
	for (auto& [id, entity] : list) {
		if (entity->name == name) {
			return id;
		}
	}
	return -1; // Not found
}

std::string EntityList::id_to_name(int id) {
	if (list.find(id) != list.end()) {
		return list[id]->name;
	}
	return ""; // Not found
}

bool EntityList::exists(int id) {
	return list.find(id) != list.end();
}

bool EntityList::exists(const std::string& name) {
	for (auto& [id, entity] : list) {
		if (entity->name == name) {
			return true;
		}
	}
	return false;
}

bool EntityList::in_spawn_buffer(int id) {
	return spawn_buffer.find(id) != spawn_buffer.end();
}

bool EntityList::in_spawn_buffer(const std::string& name) {
	for (auto& [id, entity] : spawn_buffer) {
		if (entity->name == name) {
			return true;
		}
	}
	return false;
}

bool EntityList::in_destroy_buffer(int id) {
	for (int destroy_id : destroy_buffer) {
		if (destroy_id == id) {
			return true;
		}
	}
	return false;
}

bool EntityList::in_destroy_buffer(const std::string& name) {
	for (int destroy_id : destroy_buffer) {
		if (list.find(destroy_id) != list.end() && list[destroy_id]->name == name) {
			return true;
		}
	}
	return false;
}