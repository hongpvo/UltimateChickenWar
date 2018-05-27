#pragma once
#include"UCW.h"
#include "LoadTextureFromText.h"
#include <string>
#include "TextureManager.h"
#include "Popup.h"
#include "UI.h"
#include "Player_system.h"
//This class is used to display 2 Name Input box after you pressed Start/Restart
//Derived from UI
class NameInput: public UI{
public:
	//get the default name from UCW
	NameInput(std::string str);
	~NameInput();
	//Override from base class and return name to player 
	int draw(Player* manager);

	//Override from the base class to destroy all texture in Input name section
	void clean();

private:
	// Declare name of player input, default_name of player
	std::string name, player;
	std::string default_name;
	// Get event from keyboard
	SDL_Event event;
	// instances to render the instruction and the word that you have typed from keyboard
	LoadTextureFromText gInput, title;
	// boolean variable to check if there's any rendered text and if you have done the input name section  
	bool renderText = false;
	bool end = false;
	
};