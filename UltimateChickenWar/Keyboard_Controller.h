#pragma once


#include "UCW.h"
#include "ECS.h"
#include "Component.h"

class Keyboard_Controller : public Component {
public:
	TransformComponent* transform;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}
	void update() override {
		if (UCW::event.type == SDL_KEYDOWN) {
			switch (UCW::event.key.keysym.sym) {				
			case SDLK_q:
				transform->position.x -= 54;
				transform->position.y -= 68;
				break;
			case SDLK_a:
				transform->position.x -= 108;
				transform->position.y -= 0;
				break;
			case SDLK_z:
				transform->position.x -= 54;
				transform->position.y += 68;
				break;
			case SDLK_e:
				transform->position.x += 54;
				transform->position.y -= 68;
				break;
			case SDLK_d:
				transform->position.x += 108;
				transform->position.y += 0;
				break;
			case SDLK_c:
				transform->position.x += 54;
				transform->position.y += 68;
				break;
			default:
				break;
			}
		}

		if (UCW::event.type == SDL_KEYUP) {
			switch (UCW::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;

			default:
				break;
			}
		}
	}
};