#pragma once
#include "UCW.h"
#include "ECS.h"
#include "Component.h"

class StatsComponent : public Component {
public:
	double hp, atk, def, acc;
	int player_num; // health point, attack, defend, accuracy
	bool attacking, isAlive, choosing, myturn;
	int side;
	//bool isActive;
	StatsComponent(int index, int a) {
		hp = 3;
		atk = 20;
		def = 20;
		acc = 0.9;
		player_num = index;
		attacking = 0;
		isAlive = 1;
		choosing = 0;
		side = a;
		myturn = false;
	}
};