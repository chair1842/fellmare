#pragma once
#include <string>

// Base class for all entities, a mere id and name
class Entity {
public:
	const int id;
	std::string name;
	bool update_enabled = true; // Whether update() should be called

	virtual void update(float dt) {}

	// Constructor
	Entity(const std::string& name, int id) : name(name), id(id) {}

	// Copy constructor (id stays the same)
	Entity(const Entity& other) : name(other.name), id(other.id) {}

	// Copy assignment operator deleted because id is const
	Entity& operator=(const Entity&) = delete;

	// Move constructor and assignment operator
	Entity(Entity&& other) noexcept : name(std::move(other.name)), id(other.id) {}
	Entity& operator=(Entity&&) = delete;

};
