#include "NameInput.h"
#include <iostream>

NameInput::NameInput(std::string str) {
	//we store the input string to the default player name 
	if (str != "") player = str;
	// box Rectangle 
	color[0] = { 0,0,0 }; // set color to be black (based on RGB)
	// top-left corner
	src.x = 0;
	src.y = 0;
	src.h = 210*1.5;	//scale it by 1.5
	src.w = 610*1.5;
	//bottom right corner
	dest.h = 210*1.5;
	dest.w = 610*1.5;
	dest.x = 390;
	dest.y = 300;
	
	// background Rectangle 
	//top-left corner
	bsrc.x = 0;
	bsrc.y = 0;
	bsrc.w = 1728;
	bsrc.h = 900;
	//bottom right corner
	bdest.x = 0;
	bdest.y = 0;
	bdest.w = 1728;
	bdest.h = 900;
}
NameInput::~NameInput() {
	gInput.free();
	title.free();
	TTF_CloseFont(UCW::gFont);
	UCW::gFont = NULL;
	SDL_DestroyTexture(box);
	SDL_DestroyTexture(background);
}
int NameInput::draw(Player* manager) {
	//Empty the previous name (if any)
	manager->name = "";
	//Load Texture from *.PNG image 
	box = TextureManager::LoadTexture("assets/box/box.png");
	background = TextureManager::LoadTexture("assets/background/background.png");

	//Clear the screen to blank
	SDL_RenderClear(UCW::renderer);

	//Draw the background again because this is the infinite loop to render itself until we got the name (not go into UCW::render() until got the name)
	TextureManager::Draw(background, bsrc, bdest);

	//Draw the box for player to input there name
	TextureManager::Draw(box, src, dest);

	//Open font 
	UCW::gFont = TTF_OpenFont("pixelFJ8pt1__.ttf", 30);

	//we set the default_name in case you didn't type in any character
	if (player != "") default_name = player;

	//set the render instruction 
	name = "Input name & Enter when done";
	player = "Enter " + default_name + " 's name:";

	//Load and render it in the midle of the box
	title.loadFromRenderedText(player, color[0]);
	gInput.loadFromRenderedText(name, color[0]);
	title.render((1728 - title.getWidth()) / 2, (900 - title.getHeight()-60) / 2);
	gInput.render((1728 - gInput.getWidth()) / 2, (900 - gInput.getHeight()+60) / 2);

	//render it the screen the first time 
	SDL_RenderPresent(UCW::renderer);
	//set name back to empty
	name = "";
	//Start input section
	SDL_StartTextInput();
	while (!end) {								//if we haven't pressed ENTER key
		while (SDL_PollEvent(&event) != 0) {	//return 2 to UCW in order to quit the program when you click the X key on window
			if(event.type == SDL_QUIT) {
				return 2;
			}
			if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {		//we will get the key you pressed 1 time
				//if you press the backspace it will delete the last character (just in case you have input something)
				if (event.key.keysym.sym == SDLK_BACKSPACE && name.length() > 0) {		
					name.pop_back();
					renderText = true;
				}
				//if you use the Ctrl + c to copy something, we will save it in clipboard
				else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
				{
					SDL_SetClipboardText(name.c_str());
				}
				//then if you use the Ctrl + v to paste it, the text will be coppied from clipboard
				else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
				{
					name = SDL_GetClipboardText();
					renderText = true;
				}
			}
			// this event is when you type in any character instead of Ctrl + c or Ctrl + v
			else if (event.type == SDL_TEXTINPUT)
			{	
				if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
				{	
					SDL_RenderClear(UCW::renderer);				//replace the old rendered text with the new one
					name += event.text.text;					//add the new character into the last of name
					renderText = true;
				}
			}
			if (renderText) {									//if we have rendered
				if (name != "") {					
					gInput.loadFromRenderedText(name.c_str(), color[0]);	// if name is not empty, we wil display it on the screen
				}
				else {														// if it is empty, we will display nothing but a space " "
					gInput.loadFromRenderedText(" ", color[0]);				// beacuse it is not legal to render nothing
				}

				TextureManager::Draw(background, bsrc, bdest);				//draw background and namebox again like at first
				TextureManager::Draw(box, src, dest);

				title.render((1728 - title.getWidth()) / 2, (900 - title.getHeight() - 60) / 2);
				gInput.render((1728 - gInput.getWidth()) / 2, (900 - gInput.getHeight() + 60) / 2);
				SDL_RenderPresent(UCW::renderer);							//render the new name in the screen
																			//notice that we only render again if there is new input from key board
			}
			if (event.type = SDL_KEYDOWN && event.key.repeat==0) {			//if we pressed ENTER key the input name section will be over
				if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
					end = true;
					if (name.length()==0) name = default_name;				//if you have not input anything, we will give you default name such as "player 1"
					manager->name = name;									// Return the name to Player
					SDL_Delay(300);											//Delay for the next section
			
				}
			}
		}
	}
	
	SDL_StopTextInput();													//stop the input section
	return 1;																//return that the input section is over
}

void NameInput::clean() {
	//close box, background, font and texture that we have used. 
	gInput.free();
	title.free();
	TTF_CloseFont(UCW::gFont);
	UCW::gFont = NULL;
	SDL_DestroyTexture(box);
	SDL_DestroyTexture(background);
	//set the variable back to default in case of restart
	end = false;
	renderText = false;
	name = "";
	player = "";
}