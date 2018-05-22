#pragma once
#include "UCW.h"
#include "ECS.h"
//#include "Component.h"

class StatsComponent : public Component {
public:
	int hp, atk, def;
	double acc;
	int player_num; // health point, attack, defend, accuracy
	bool attacking, isAlive, choosing, myturn;
	int  range;
	//bool isActive;
	StatsComponent(int index) {
		hp = 0;
		atk = 1;
		def = 0;
		acc = 0.9;
		player_num = index;
		attacking = 0;
		isAlive = 1;
		choosing = 0;
		myturn = false;
		range = 2;
	}
};