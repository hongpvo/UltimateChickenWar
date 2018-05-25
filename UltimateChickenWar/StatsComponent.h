#pragma once
#include "UCW.h"
#include"Player_system.h"
//#include "Component.h"

class StatsComponent : public Component {
public:
	int hp, atk, def;
	int player_num; // health point, attack, defend, accuracy
	bool isAlive, choosing, myturn;
	int  range;
	//bool isActive;
	StatsComponent(int index, int healthPoint, int attack, int defend, int rangePoint) {
		hp = healthPoint;
		atk = attack;
		def = defend;
		player_num = index;
		isAlive = 1;
		choosing = 0;
		myturn = false;
		range = rangePoint;
	}
};