#include "NameInput.h"
#include <iostream>
NameInput::NameInput(std::string str) {
	if (str != "") player = str;
	else player = "Player";
	// box Rect
	src.x = 0;
	src.y = 0;
	src.h = 210*1.5;
	src.w = 610*1.5;

	dest.h = 210*1.5;
	dest.w = 610*1.5;
	dest.x = 390;
	dest.y = 300;
	// background Rect
	bsrc.x = 0;
	bsrc.y = 0;
	bsrc.w = 1728;
	bsrc.h = 900;

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
}
int NameInput::draw() {
	//Load
	box = TextureManager::LoadTexture("assets/button/box.png");
	background = TextureManager::LoadTexture("assets/island/background.png");

	SDL_RenderClear(UCW::renderer);
	//Draw
	TextureManager::Draw(background, bsrc, bdest);
	TextureManager::Draw(box, src, dest);

	UCW::gFont = TTF_OpenFont("pixelFJ8pt1__.ttf", 30);

	std::string temp = player;
	name = "Input name & Enter when done";
	player = "Enter " + player + " 's name:";

	title.loadFromRenderedText(player, color);
	gInput.loadFromRenderedText(name.c_str(), color);

	title.render((1728 - title.getWidth()) / 2, (900 - title.getHeight()-60) / 2);
	gInput.render((1728 - gInput.getWidth()) / 2, (900 - gInput.getHeight()+60) / 2);

	SDL_RenderPresent(UCW::renderer);

	name = "";
	SDL_StartTextInput();
	while (!end) {
		SDL_Delay(300);
		while (SDL_PollEvent(&event) != 0 && end == false) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_BACKSPACE && name.length() > 0) {
					name.pop_back();
					renderText = true;
				}
				else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
				{
					SDL_SetClipboardText(name.c_str());
				}
				else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
				{
					name = SDL_GetClipboardText();
					renderText = true;
				}
			}
			else if (event.type == SDL_TEXTINPUT)
			{	
				if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
				{	
					SDL_RenderClear(UCW::renderer);
					name += event.text.text;
					renderText = true;
				}
			}
			if (renderText) {
				if (name != "") {
					gInput.loadFromRenderedText(name.c_str(), color);
				}
				else {
					gInput.loadFromRenderedText(" ", color);
				}
			}
			TextureManager::Draw(background, bsrc, bdest);
			TextureManager::Draw(box, src, dest);

			title.render((1728 - title.getWidth()) / 2, (900 - title.getHeight() - 60) / 2);
			gInput.render((1728 - gInput.getWidth()) / 2, (900 - gInput.getHeight()+60) / 2);
			SDL_RenderPresent(UCW::renderer);
			
			if (event.type = SDL_KEYDOWN && event.key.repeat==0) {
				if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
					end = true;
					if (name.length()==0) name = temp;
					//SDL_Delay(100);
				}
			}

		}
	}
	SDL_StopTextInput;
	return 1;
}

std::string NameInput::getName() {
	return name;
}
void NameInput::clean() {
	gInput.free();
	title.free();
	TTF_CloseFont(UCW::gFont);
	UCW::gFont = NULL;
	SDL_DestroyTexture(box);
	end = false;
	renderText = false;
	name = "";
	player = "";
}