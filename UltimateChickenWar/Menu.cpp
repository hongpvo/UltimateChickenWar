#include "Menu.h"
#include <iostream>
Menu::Menu() {
	color[0] = { 0,0,0 };
	color[1] = { 255,0,0 };  
}
Menu::~Menu() {
}
int Menu::draw(std::string labels[2]) {
	int h[2] = { 1100,1500 };
	int w[2] = { 1728,1728 };
	//The upper title
	UCW::gFont = TTF_OpenFont("HUMANOID.TTF", 180);
	Game_title[0].loadFromRenderedText("Ultimate", color2);
	Game_title[0].render(501, 101);
	Game_title[0].loadFromRenderedText("Ultimate", color[1]);
	Game_title[0].render(503, 103);
	Game_title[0].loadFromRenderedText("Ultimate", color[0]);
	Game_title[0].render(505, 105);
	TTF_CloseFont(UCW::gFont);
	UCW::gFont = NULL;
	//the lower title
	UCW::gFont = TTF_OpenFont("HUMANOIDSTRAIGHT.TTF", 140);
	Game_title[1].loadFromRenderedText("Chicken War!", color3);
	Game_title[1].render(501,251);
	Game_title[1].loadFromRenderedText("Chicken War!", color[1]);
	Game_title[1].render(503, 253);
	Game_title[1].loadFromRenderedText("Chicken War!", color[0]);
	Game_title[1].render(505, 255);
	TTF_CloseFont(UCW::gFont);
	UCW::gFont = NULL;

	UCW::gFont = TTF_OpenFont("pixelFJ8pt1__.ttf", 60);
	menus[0].loadFromRenderedText(labels[0], color[0]);
	menus[1].loadFromRenderedText(labels[1], color[0]);
	menus[0].render((w[0] - menus[0].getWidth()) / 2, (h[0] - menus[0].getHeight()) / 2);
	menus[1].render((w[1] - menus[1].getWidth()) / 2, (h[1] - menus[1].getHeight()) / 2);

	std::cout << "menu Rendered" << std::endl;
	int topLeft_x[2] = { 769,769 };
	int bottomRight_x[2] = { 964,964 };
	int topLeft_y[2] = { 517,716 };
	int bottomRight_y[2] = { 569,768 };
	while (1)
	{
		while (SDL_PollEvent(&UCW::event))
		{
			switch (UCW::event.type)
			{
			case SDL_QUIT:
				menus[0].free();
				menus[1].free();
				return 1;
			case SDL_MOUSEMOTION:
				x = UCW::event.motion.x;
				y = UCW::event.motion.y;
				for (int i = 0; i < 2; i += 1) {
					if (x >= topLeft_x[i] && x <= bottomRight_x[i] && y >= topLeft_y[i] && y <= bottomRight_y[i])
					{
						if (!selected[i])
						{
							selected[i] = 1;
							menus[i].free();
							menus[i].loadFromRenderedText(labels[i], color[1]);
							menus[i].render((w[i] - menus[i].getWidth()) / 2, (h[i] - menus[i].getHeight()) / 2);
						}
					}
					else
					{
						if (selected[i])
						{
							selected[i] = 0;
							menus[i].free();
							menus[i].loadFromRenderedText(labels[i], color[0]);
							menus[i].render((w[i] - menus[i].getWidth()) / 2, (h[i] - menus[i].getHeight()) / 2);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = UCW::event.button.x;
				y = UCW::event.button.y;
				for (int i = 0; i < 2; i += 1) {
					if (x >= topLeft_x[i] && x <= bottomRight_x[i] && y >= topLeft_y[i] && y <= bottomRight_y[i])
					{
						menus[0].free();
						menus[1].free();
						if (i == 0) {
							return i;
						}
						else {
							return i + 1;
						}
					}
				}
				break;
			case SDL_KEYDOWN:
				if (UCW::event.key.keysym.sym == SDLK_ESCAPE)
				{
					menus[0].free();
					menus[1].free();
					return 2;
				}
			}
			SDL_RenderPresent(UCW::renderer);
		}
	}
}

