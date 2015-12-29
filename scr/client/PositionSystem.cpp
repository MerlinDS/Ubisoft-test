#include "stdafx.h"
#include "PositionSystem.h"

PositionSystem::~PositionSystem()
{
	entities = nullptr;
	destructable.clear();
	DebugOut("destroy");
}

void PositionSystem::init(vector<Entity>* collection)
{
	DebugOut("initialize");
	entities = collection;
}

void PositionSystem::tick(float deltaTime)
{
	int n = entities->size();
	for (int i = 0; i < n; i++)
	{
		auto entity = &entities->at(i);
		entity->viewPosition.x = x + entity->position.x * scale;
		entity->viewPosition.y = y + entity->position.y * scale;
		
		//set entity to destructable if it go out of viewport
		if(
			entity->viewPosition.y < -10.0 ||
			entity->viewPosition.x < -10.0 ||
			entity->viewPosition.x > width + 10
			)destructable.push_back(i);

		//invert position by y
		entity->viewPosition.y = height - entity->viewPosition.y;
	}
	//delete destructables
	while (destructable.size() > 0)
	{
		auto i = destructable.back();
		destructable.pop_back();
		//remove from entities list
		entities->erase(entities->begin() + i);
	}

}

