#include "Menu.h"
#include <iostream>
Menu::Menu() {

}
Menu::~Menu() {

}
int Menu::show() {
	int h[2] = { 900,1500 };
	int w[2] = { 1728,1728 };
	UCW::gFont = TTF_OpenFont("pixelFJ8pt1__.ttf", 60);
	menus[0].loadFromRenderedText(labels[0], color[0]);
	menus[1].loadFromRenderedText(labels[1], color[0]);
	menus[0].render((w[0] - menus[0].getWidth()) / 2, (h[0] - menus[0].getHeight()) / 2);
	menus[1].render((w[1] - menus[1].getWidth()) / 2, (h[1] - menus[1].getHeight()) / 2);
	std::cout << "menu Rendered" << std::endl;
	int orx[2] = { 769,769 };
	int dex[2] = { 964,964 };
	int ory[2] = { 414,716 };
	int dey[2] = { 471,768 };
		
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
						if (x >= orx[i] && x <= dex[i] && y >= ory[i] && y <= dey[i])
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
						if (x >= orx[i] && x <= dex[i] && y >= ory[i] && y <= dey[i])
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
						return 0;
					}
				}
				SDL_RenderPresent(UCW::renderer);
			}
		}
	}
