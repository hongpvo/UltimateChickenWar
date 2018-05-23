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

