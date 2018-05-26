#pragma once
#include<iostream>
#include "UCW.h"
#include "Popup.h"
#include "UI.h"

using namespace std;
class Component;
class Chicken;

class Component {

public:
	Chicken * chicken;
	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};

	

};

class Chicken {
private:
	bool active = true;
	int index = 0;
	
	Component* components[3];
	
public:
	void update()
	{
		for (int i = 0; i < 3; i++ ) {
			components[i]->update();
		}

	}
	void draw() {
		for (int i = 0; i < 3; i++) {
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
		c->chicken = this;
		components[index] = static_cast<Component*>(c);
		getComponentTypeID<T>();
		
		
		index++;
		c->init();
		return *c;
	}

	template<typename T> T* getComponent() {
		Component* ptr = components[getComponentTypeID<T>()];
		return dynamic_cast<T*>(ptr);
	}

	template <typename T> int getComponentTypeID() {
		static int typeID = index;
		return typeID;
	}

};

class Player {
private:
	Chicken ** chickens;
	int index = 0;
	Chicken* e;
public:
	static Chicken* allChickens[6];
	~Player() {
		delete[] chickens;
	}
	static void initialiser() {
		for (int i = 0; i < 6; i++) {
			Player::allChickens[i] = NULL;
		}
	}
	friend void UCW::init(const char* , int, int , int , int , bool);
	void update() {
		for (int i = 0; i < returnlength(); i++) {
			if (chickens[i]!=NULL) chickens[i]->update();
		}
	}
	void draw() {
		for (int i = 0; i < returnlength(); i++) {
			if (chickens[i] != NULL) chickens[i]->draw();
		}
	}
	void refresh() {
		
		for (int i = 0; i < returnlength(); i++) {
			if (chickens[i] != NULL) {
				if (!(chickens[i]->isActive())) chickens[i] = NULL;
			}
		}
	}

	Chicken* addChicken(int i) {
		e = new Chicken();
		index++;
		Chicken** entities_temp = new Chicken*[index];
		for (int i = 0; i < index - 1; i++) {
			entities_temp[i] = chickens[i];
		}
		entities_temp[index - 1] = e;
		delete[] chickens;
		chickens = new Chicken*[index];
		chickens = entities_temp;
	
		allChickens[i] = e;
		return e;

	}

	Chicken** getChickenList() {
		return chickens;
	}
	int returnlength() {
		int numChickens=0;
		for (int i = 0; i <= index-1; i++) {
			if (chickens[i] != NULL) numChickens++;
		}
		return numChickens;
	}

	
};
//Entity* Manager::allEntities[6];

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