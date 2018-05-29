#pragma once
#include<iostream>
#include "UCW.h"
#include "Popup.h"
#include "UI.h"

using namespace std;
//class foward declaration
class Component;
class Chicken;

//represents each component of the chicken
class Component {
public:
	Chicken * chicken;	//represent the chicken that is owning this component
	//these are functions to be overidden in the derived classes
	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};

	

};

//this class represents each chicken
class Chicken {
private:
	bool active = true;
	//the index of each component
	int index = 0;
	//array of the components 
	Component* components[3];
	
public:
	//update each component in the components array
	void update()
	{
		for (int i = 0; i < 3; i++ ) {
			components[i]->update();
		}
	}
	//draw each component in the components array
	void draw() {
		for (int i = 0; i < 3; i++) {
			components[i]->draw();
		}
	}
	
	bool isActive() { return active; }
	//used to remove the chicken when end game 
	void destroy() {
		active = false;
	}
	//add the component to the component list
	template <typename T, typename... TArgs> //T is the type of the component, TArgs are the types of arguments to pass into component's construtor
	T& addComponent(TArgs... Args) {
		T*c = new T(Args...); //create a new instance of T by passing Args into the constructor and make the pointer "c" points to it
		c->chicken = this; //assign the chicken that is possessing this component to be "this"
		components[index] = static_cast<Component*>(c); //upcast the c pointer (from "T*" type to "Component*" type)
		getComponentTypeID<T>();	//assign a new id to T component
		index++;	
		c->init();	//initialize the component
		return *c;
	}
	//get the pointer that points to the component of type T*
	template<typename T> T* getComponent() {
		Component* ptr = components[getComponentTypeID<T>()]; //Get the id of the component, then take it out from the components array
		return dynamic_cast<T*>(ptr); //downcast it back to pointer of type T*
	}

	//return the id of each component
	template <typename T> int getComponentTypeID() {
		static int typeID = index;	//this is only run once at the beginning and remain the same in the subsequent calls
		return typeID;
	}

};
//represent the player
class Player {
private:
	//list of pointers to chickens of each player. We don't define a size for flexibility in increasing the size of the array.
	Chicken ** chickens;
	//index of each chicken in the list
	int index = 0;
	//the pointer to a chicken
	Chicken* e;
public:
	//name of the chicken
	std::string name="";
	//the shared list of pointers to all 6 chickens
	static Chicken* allChickens[6];
	//destrucor : deleter the dynamic memory pointed to by chickens array
	~Player() {
		delete[] chickens;
	}
	//static function to be called outside the class to initialize allChickens pointer array
	static void initialiser() {
		for (int i = 0; i < 6; i++) {
			Player::allChickens[i] = NULL;
		}
	}
	//UCW::init() need to access to private members of Player class
	friend void UCW::init(const char* , int, int , int , int , bool);
	//update all the chickens
	void update() {
		for (int i = 0; i < returnlength(); i++) {
			//chicken's pointer must not be null before updating, else it will return a memory error
			if (chickens[i]!=NULL) chickens[i]->update();
		}
	}
	//draw all the chicken
	void draw() {
		for (int i = 0; i < returnlength(); i++) {
			//chicken's pointer must not be null before updating, else it will return a memory error
			if (chickens[i] != NULL) chickens[i]->draw();
		}
	}
	//check the chickens list
	void refresh() {
		for (int i = 0; i < returnlength(); i++) {
			if (chickens[i] != NULL) {
				//if chicken is no longer active, then remove it from the list. (used to reboot the game when pressing start and restart)
				if (!(chickens[i]->isActive())) chickens[i] = NULL;
			}
		}
	}
	//add new chickens to the list
	Chicken* addChicken(int i) {
		//create a new instance of chicken
		e = new Chicken();
		//increas the index
		index++;
		//create a temporary array of size bigger than previous one 
		Chicken** chickens_temp = new Chicken*[index];
		//copy old array into new temporary array
		for (int i = 0; i < index - 1; i++) {
			chickens_temp[i] = chickens[i];
		}
		//assign the last index to the pointer of chicken
		chickens_temp[index - 1] = e;
		//delete the old array
		delete[] chickens;
		//now create the array chickens with the enough size to store all chickens
		chickens = new Chicken*[index];
		//copy from the temporary array into the true array
		for (int i = 0; i < index; i++) {
			chickens[i] = chickens_temp[i];
		}
		//delete temporary array
		delete[]chickens_temp;
		//assign the newly created pointer to chicken instance to the last index of allChicken list
		allChickens[i] = e;
		//return the pointer to the chicken
		return e;

	}
	//return the pointer to 3 chickens that each player has
	Chicken** getChickenList() {
		return chickens;
	}
	//count the number of chicken in the chicken list of each player
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