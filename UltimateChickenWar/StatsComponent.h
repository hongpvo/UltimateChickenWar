#pragma once
#include "UCW.h"
#include "ECS.h"
#include "Component.h"

class StatsComponent : public Component {
public:
	double hp, atk, def, acc;
	int player_num; // health point, attack, defend, accuracy
	StatsComponent(int index) {
		hp = 100;
		atk = 20;
		def = 20;
		acc = 0.9;
		player_num = index;
	}
};