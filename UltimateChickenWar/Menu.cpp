#include "Menu.h"
#include <iostream>
Menu::Menu() {
	//Initialize color array which is declared in base class UI
	color[0] = { 0,0,0 };	//black (based on RGB)
	color[1] = { 255,0,0 }; //red	(based on RGB)
}
Menu::~Menu() {
}
int Menu::draw(std::string labels[2]) {
	// height and width which show the location of 2 button in the window
	int h[2] = { 1100,1500 };
	int w[2] = { 1728,1728 };
	//The upper title
	UCW::gFont = TTF_OpenFont("minercraftory.regular.ttf", 100);	//open font for rendering title
	Game_title[0].loadFromRenderedText("Ultimate", title_color);	//Load Text
	Game_title[0].render(600, 100);									//render the title to window at location (600,100)
	//The lower title
	Game_title[1].loadFromRenderedText("Chicken War", title_color);	//Load Text
	Game_title[1].render(500,250);									//render the title to window at location (500,250) which is below the first one
	TTF_CloseFont(UCW::gFont);										//close font in order to use another font later
	UCW::gFont = NULL;												//reset font variable
		
	UCW::gFont = TTF_OpenFont("pixelFJ8pt1__.ttf", 60);				//open font for rendering button 
	menus[0].loadFromRenderedText(labels[0], color[0]);				//Load Text from a string array that we have defined in UCW.cpp  
	menus[1].loadFromRenderedText(labels[1], color[0]);

	//render it to the window. The formula is using for centering
	menus[0].render((w[0] - menus[0].getWidth()) / 2, (h[0] - menus[0].getHeight()) / 2);	
	menus[1].render((w[1] - menus[1].getWidth()) / 2, (h[1] - menus[1].getHeight()) / 2);

	//output check if menu rendered successfully
	std::cout << "menu Rendered" << std::endl;					

	//below we define 2 rectangle boxes which is the region for 2 button
	int topLeft_x[2] = { 769,769 };									
	int bottomRight_x[2] = { 964,964 };
	int topLeft_y[2] = { 517,716 };
	int bottomRight_y[2] = { 569,768 };

	// infinite loop to render the menu until you select 1 button or choose to quit
	while (1)
	{
		while (SDL_PollEvent(&UCW::event))			//get event				
		{
			switch (UCW::event.type)				//check event type
			{
			case SDL_QUIT:							// if we press X button in the window, the program will stop by returning 1 
				menus[0].free();					// to the check condition of UCW and free/destroyed the text that we have rendered
				menus[1].free();
				return 1;
			case SDL_MOUSEMOTION:					// get the position (x,y) of mouse when the mouse move 
				x = UCW::event.motion.x;
				y = UCW::event.motion.y;
				// when you mouse your mouse to the region of the button, it will turn from black to red
				for (int i = 0; i < 2; i += 1) {
					//check if the mouse position is in the region
					if (x >= topLeft_x[i] && x <= bottomRight_x[i] && y >= topLeft_y[i] && y <= bottomRight_y[i])	
					{
						if (!selected[i])		// if we have not select it 
						{						// then we check the select boolean variable
							selected[i] = 1;	// and destroy the black old texture to render a red one with exactly the same position and texture																					
							menus[i].free();
							menus[i].loadFromRenderedText(labels[i], color[1]);
							menus[i].render((w[i] - menus[i].getWidth()) / 2, (h[i] - menus[i].getHeight()) / 2);
						}
					}
					else						// if the mouse is not in the region
					{ 
						if (selected[i])		// and there a button that have turn red
						{						// we do the same method like previous one which gave us the black one back
							selected[i] = 0;
							menus[i].free();
							menus[i].loadFromRenderedText(labels[i], color[0]);
							menus[i].render((w[i] - menus[i].getWidth()) / 2, (h[i] - menus[i].getHeight()) / 2);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:			// if we press to choose one button 
				x = UCW::event.button.x;
				y = UCW::event.button.y;
				// it will check the location the we click with the button box
				for (int i = 0; i < 2; i += 1) {	
					// if we click in the box 
					if (x >= topLeft_x[i] && x <= bottomRight_x[i] && y >= topLeft_y[i] && y <= bottomRight_y[i])
					{
						menus[0].free();		
						menus[1].free();
						if (i == 0) {		//click start or reset	
							return i;		//return 0 to start game
						}
						else {				//click exit
							return i + 1;	//return 2 to exit game
						}
					}
				}
				break;
			// final case is when you press the ESC key on keyboard the game will automatically exit like the first case (SDL_Quit)
			case SDL_KEYDOWN:
				if (UCW::event.key.keysym.sym == SDLK_ESCAPE)
				{
					menus[0].free();
					menus[1].free();
					return 2;
				}
			}
			// Render the Texture to the window through UCW::renderer
			SDL_RenderPresent(UCW::renderer);
		}
	}
}

