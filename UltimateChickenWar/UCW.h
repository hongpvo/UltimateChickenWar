#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <vector>

//This class represents the game controller unit
class UCW
{
public:
	//This function initialize the window and basic element
	void init(const char* title, int xpos, int ypos, int width, int height);
	//This function react to any event happen (like keypress or mouse motion)
	void handleEvents(); 
	//This function will iteratively refresh update both player info
	void update();
	//This function will load and render the image based on many condition
	void render();
	//THis function clean all process and quit the game
	void clean();

	//Globally used font
	static TTF_Font *gFont;

	//Create globally renderer 
	static SDL_Renderer* renderer;
	
	//Create globally event for catching event
	static SDL_Event event;

	//check variable for restart purpose
	bool restart = false;
	
	//function to check if the game is still running 
	bool running() { return isRunning; };
	

private:
	//check running variable, using for exit game
	bool isRunning;
	int cnt = 0;
	//Create window 
	SDL_Window *window;
	bool endgame = false;
	//Check variable for menu, endgame, nameInput
	bool menu_checked = false;
	
	int player1nameInput = false;
	int player2nameInput = false;
	// Player info to output when endgame
	std::string player1name, player2name;
	

};