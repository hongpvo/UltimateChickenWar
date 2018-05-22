#pragma once
#include<iostream>
#include "UCW.h"
#include "Popup.h"
#include "UI.h"

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

	Component* components[3];

public:
	void update();
	void draw();

	bool isActive();
	void destroy();



	template <typename T, typename... TArgs>
	T& addComponent(TArgs... mArgs);

	template<typename T> T& getComponent();

	template <typename T> int getComponentTypeID();

};

class Manager {
private:
	Entity * * entities;
	int index = 0;

public:
	static Entity* allEntities[6];
	friend void UCW::init(const char*, int, int, int, int, bool);
	friend void Mouse_Controller(Manager*, int[9][16], int[9][16], Popup*);
	friend class stats_table;
	friend void UCW::render();
	//friend int stats_table::draw(Manager*);
	static void initialiser();
	void update();
	void draw();
	void refresh();
	Entity& addEntity(int shared_index);
	Entity** getEntityList();
	int returnlength();

};



