#pragma once
#include "Component.h"
//#include "ECS.h"
#include "TransformComponent.h"
#include "StatsComponent.h"
#include "SDL.h"
#include "TextureManager.h"



class SpriteComponent : public Component
{
private:
	TransformComponent* transform;

	SDL_Texture *texture;
	SDL_Texture *indicator;
	SDL_Rect srcRect, destRect;
	bool indicator_allowing;
	StatsComponent *stats;

public:

	SpriteComponent() = default;
	SpriteComponent(const char* path, char* background)
	{
		setTex(path,background);
	}
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}
	void setTex(const char* path, char* background) {
		texture = TextureManager::LoadTexture(path);
		indicator = TextureManager::LoadTexture(background);
	}
	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}
	void update() override {
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
	void draw() override {
		if (indicator_allowing) TextureManager::Draw(indicator, srcRect, destRect);
		//else SDL_DestroyTexture(indicator);
		TextureManager::Draw(texture, srcRect, destRect);
		indicator_allowing = (entity->getComponent<StatsComponent>()).myturn;
		
	}
};