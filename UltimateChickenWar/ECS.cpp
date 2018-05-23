#include "ECS.h"
#include<iostream>
#include "UCW.h"
#include "Popup.h"
#include "UI.h"
//DON'T remove this - this is correct
Entity* Manager::allEntities[6];
void Manager::initialiser() {
	for (int i = 0; i < 6; i++) {
		Manager::allEntities[i] = NULL;
	}
}






//problem from down here:
void Entity:: update()
	{
		for (int i = 0; i < 3; i++) {
			components[i]->update();
		}

	}
	void Entity:: draw() {
		for (int i = 0; i < 3; i++) {
			components[i]->draw();
		}
	}

	bool Entity::isActive() { return active; }
	void Entity::destroy() {
		active = false;
	}



	template <typename T, typename... TArgs>
	T& Entity::addComponent(TArgs... mArgs) {
		T*c = new T(mArgs...);
		c->entity = this;
		Component* uPtr = c;
		components[index] = uPtr;
		getComponentTypeID<T>();


		index++;
		c->init();
		return *c;
	}

	template<typename T> T& Entity::getComponent() {
		Component* ptr = components[getComponentTypeID<T>()];
		return *dynamic_cast<T*>(ptr);
	}

	template <typename T> int Entity::getComponentTypeID() {

		static int typeID = index;
		return typeID;
	}
	



	void Manager::update() {
		for (int i = 0; i < returnlength(); i++) {
			if (entities[i] != NULL) entities[i]->update();
		}
	}
	void Manager:: draw() {
		for (int i = 0; i < returnlength(); i++) {
			if (entities[i] != NULL) entities[i]->draw();
		}
	}
	void Manager:: refresh() {

		for (int i = 0; i < returnlength(); i++) {
			if (entities[i] != NULL) {
				if (!(entities[i]->isActive())) entities[i] = NULL;
			}
		}
	}

	Entity& Manager::addEntity(int shared_index) {
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
		allEntities[shared_index] = e;
		//delete e;
		return *e;
	}

	Entity** Manager::getEntityList() {
		return entities;
	}
	int Manager::returnlength() {
		int numEntities = 0;
		for (int i = 0; i <= index - 1; i++) {
			if (entities[i] != NULL) numEntities++;
		}
		return numEntities;
	}