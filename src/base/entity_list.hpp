#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include "entity.hpp"
using namespace std;

class EntityList {
public:
    unordered_map<string, unique_ptr<Entity>> list;
    unordered_map<string, unique_ptr<Entity>> spawn_buffer;
    vector<string> destroy_buffer;

    bool spawn(string name, unique_ptr<Entity> entity);
    template <typename T, typename... Args>
    bool spawn(const std::string& name, Args&&... args) {
        static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity");
        if (exists(name) || in_spawn_buff(name)) return false;
        spawn_buffer[name] = std::make_unique<T>(std::forward<Args>(args)...);
        return true;
    }
    bool destroy(string name);

    bool exists(string name); // checks if entity is in main list
    bool in_spawn_buff(string name);
    bool in_destroy_buff(string name);

    template <typename T>
    bool is_type(string name) {
        auto it = list.find(name);
        if (it == list.end()) {
            return false;
        }
        return dynamic_cast<T*>(it->second.get()) != nullptr;
    }

    Entity* get(const std::string& name);
    template <typename T>
    T* get_as(const std::string& name) {
        Entity* e = get(name);
        return dynamic_cast<T*>(e);
    }

    void update(float dt);
    void flush();

    void for_each(const function<void(Entity&)>& fn);
};