#pragma once

#include <memory>
#include <vector>
#include <type_traits>


class Component {
public:
    virtual void start() = 0; // Pure virtual function
    virtual void update() = 0; // Pure virtual function
    virtual ~Component() {} // Virtual destructor for proper cleanup
};


class Entity {
private:
    std::vector<std::unique_ptr<Component>> components;

public:
    template<typename T, typename... Args>
    T* addComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component");
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        T* compPtr = comp.get();
        components.push_back(std::move(comp));
        return compPtr;
    }

    template<typename T>
    T* get_component() const {
        for (const auto& comp : components) {
            if (auto casted = dynamic_cast<T*>(comp.get())) {
                return casted;
            }
        }
        return nullptr;
    }

    void start() {
        for (auto& comp : components) {
            comp->start();
        }
    }

    void update() {
        for (auto& comp : components) {
            comp->update();
        }
    }
};


class World {
private:
    std::vector<std::shared_ptr<Entity>> entities;

public:
    Entity* add_entity() {
        auto entity = std::make_unique<Entity>();
        Entity* entityPtr = entity.get();
        entities.push_back(std::move(entity));
        return entityPtr;
    }

    void update() {
        for (auto& entity : entities) {
            entity->update();
        }
    }
};
