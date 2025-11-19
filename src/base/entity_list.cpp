#include "entity_list.hpp"

bool EntityList::spawn(string name, unique_ptr<Entity> entity) {
	if (exists(name) || in_spawn_buff(name)) {
		return false;
	}
	entity->name = name;
	spawn_buffer[name] = move(entity);
	return true;
}

bool EntityList::destroy(string name) {
	// if in spawn buffer, remove from there
	if (in_spawn_buff(name)) {
		spawn_buffer.erase(name);
		return true;
	}
	// if not exists or already in destroy buffer, return false
	if (!exists(name) || in_destroy_buff(name)) {
		return false;
	}
	destroy_buffer.push_back(name);
	return true;
}

bool EntityList::exists(string name) {
	return list.find(name) != list.end();
}

bool EntityList::in_spawn_buff(string name) {
	return spawn_buffer.find(name) != spawn_buffer.end();
}

bool EntityList::in_destroy_buff(string name) {
	return find(destroy_buffer.begin(), destroy_buffer.end(), name) != destroy_buffer.end();
}

Entity* EntityList::get(const std::string& name) {
	auto it = list.find(name);
	if (it != list.end())
		return it->second.get();

	return nullptr;
}

void EntityList::update(float dt) {
	// update all entities
	for (auto& pair : list) {
		pair.second->update(dt, *this);
	}
}

void EntityList::flush() {
	// spawn entities from spawn buffer
	for (auto& pair : spawn_buffer) {
		pair.second->enter();
		list[pair.first] = move(pair.second);
	}
	spawn_buffer.clear();

	// destroy entities in destroy buffer
	for (const auto& name : destroy_buffer) {
		auto it = list.find(name);
		if (it != list.end()) {
			it->second->exit();
			list.erase(it);
		}
	}
	destroy_buffer.clear();
}

void EntityList::for_each(const std::function<void(Entity&)>& fn) {
	for (auto& [name, entityPtr] : list) {
		fn(*entityPtr);
	}
}
