#include "Popup.h"

Popup::Popup(std::string str,int h, int w) {
	// set member text is the input text
	text = str;

	//location of the box
	src.x = 0;
	src.y = 0;
	src.h = 210;
	src.w = 610;

	dest.h = 210;
	dest.w = 610;
	dest.x = 550;
	dest.y = 650;
	
	//location of the text
	height = h;
	width = w;
};
Popup::~Popup(){
	//clean the Texture
	SDL_DestroyTexture(box);
	gTextTexture.free(); 
};
int Popup::draw() {
	//Load the texture from *.PNG
	box = TextureManager::LoadTexture("assets/box/box.png");
	//Draw the box
	TextureManager::Draw(box, src, dest);
	//Open the font
	UCW::gFont = TTF_OpenFont("pixelFJ8pt1__.ttf", 60);
	//Render text
	SDL_Color textColor = { 0, 0, 0 }; //set black color (based on RGB)
	gTextTexture.loadFromRenderedText(text, textColor);
	//Render text at the center of the box
	gTextTexture.render((width - gTextTexture.getWidth()) / 2, (height- gTextTexture.getHeight()) / 2);
	return 0;
};
void Popup::clean() {
	//close the font, text, and box
	gTextTexture.free();
	TTF_CloseFont(UCW::gFont);
	UCW::gFont = NULL;
	SDL_DestroyTexture(box);
	gTextTexture.free();
}