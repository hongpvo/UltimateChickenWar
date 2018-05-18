#pragma once
#include<iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
using namespace std;
class Component;
class Entity;

class Component {

public:
	Entity * entity;
	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};

	virtual ~Component() {};

};

class Entity {
private:
	bool active = true;
	int index = 0;
	
	Component* components[4];
	
public:
	void update()
	{
		for (int i = 0; i < 4; i++ ) {
			components[i]->update();
		}

	}
	void draw() {
		for (int i = 0; i < 4; i++) {
			components[i]->draw();
		}
	}

	bool isActive() { return active; }
	void destroy() {
		active = false;
	}

	

	template <typename T, typename... TArgs>
	T& addComponent(TArgs... mArgs) {
		T*c = new T(mArgs...);
		c->entity = this;
		Component* uPtr = c;
		components[index] = uPtr;
		getComponentTypeID<T>();
		
		
		index++;
		c->init();
		return *c;
	}

	template<typename T> T& getComponent() {
		auto ptr = components[getComponentTypeID<T>()];
		return *static_cast<T*>(ptr);
	}

	template <typename T> int getComponentTypeID() {
		//static int typeID = getComponentTypeID();
		static int typeID = index;
		return typeID;
	}

};

class Manager {
private:
	Entity ** entities;
	int index = 0;
public:
	friend void UCW::init(const char* , int, int , int , int , bool);
	void update() {
		for (int i = 0; i < returnlength(); i++) {
			if (entities[i]!=NULL) entities[i]->update();
		}
	}
	void draw() {
		for (int i = 0; i < returnlength(); i++) {
			if (entities[i] != NULL) entities[i]->draw();
		}
	}
	void refresh() {
		
		for (int i = 0; i < returnlength(); i++) {
			if (entities[i] != NULL) {
				if (!(entities[i]->isActive())) entities[i] = NULL;
			}
		}
	}

	Entity& addEntity() {
		Entity* e = new Entity();
		Entity* uPtr{ e };
		index++;
		Entity** entities_temp = new Entity*[index];
		for (int i = 0; i < index - 1; i++) {
			entities_temp[i] = entities[i];
		}
		entities_temp[index - 1] = uPtr;
		delete[] entities;
		entities = new Entity*[index];
		entities = entities_temp;
		return *e;

	}

	Entity** getEntityList() {
		return entities;
	}
	int returnlength() {
		int numEntities=0;
		for (int i = 0; i <= index-1; i++) {
			if (entities[i] != NULL) numEntities++;
		}
		return numEntities;
	}

	
};

/*
#pragma once
#include<iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {

public:
	Entity* entity;

	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};

	virtual ~Component() {};
};

class Entity {
private:
	bool active = true;
	//std::vector<std::unique_ptr<Component>> components;
	std::vector<Component*> components;
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
public:
	void update()
	{
		for (auto& c : components) c->update();
	}

	void draw() {
		for (auto& c : components) c->draw();
	};

	bool isActive() { return active; }
	void destroy() {
		active = false;
	}

	template <typename T> bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T*c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		//std::unique_ptr<Component> uPtr{ c };
		Component* uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}


};

class Manager {
private:
	//std::vector<std::unique_ptr<Entity>> entities;
	std::vector<Entity*> entities;
public:
	void update() {
		for (auto& e : entities) e->update();
	}
	void draw() {
		for (auto& e : entities) e->draw();
	}
	void refresh() {
		//entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity) {
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](Entity* &mEntity) {
			return !mEntity->isActive(); }), std::end(entities));
	}

	Entity& addEntity() {
		Entity* e = new Entity();
		//std::unique_ptr<Entity> uPtr{ e };
		Entity* uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;

	}

	std::vector<Entity*> getEntityList() {
		return entities;
	}
	int returnlength() {
		return size(entities);
	}
};
*/