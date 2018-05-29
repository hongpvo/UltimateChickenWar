#pragma once
#include "UCW.h"
#include"Player_system.h"

//this class stores the information of the chicken
class StatsComponent : public Component {
public:
	int hp, atk, def;	// health point, attack, defend, accuracy
	int player_num;		//the number index of the chicken
	bool isAlive, choosing, myturn;	//alive status, choosing status,turn status
	int  range;	//the moving and attacking range

	//constructor, initialize the class member as specified by the parameters
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