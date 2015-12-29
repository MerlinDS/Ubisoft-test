#include "World.h"
/*
Public region
*/
World::World()
{
	systems = new std::vector<LoopSystem*>();
	//vector of live entities
	entities = new std::vector<Entity>();
}


World::~World()
{
	systems->clear();
	entities->clear();
	delete systems;
	delete entities;
}

void World::tick(float deltaTime)
{
	int n = systems->size();
	for (int i = 0; i < n; i++)
	{
		LoopSystem* system = systems->at(i);
		system->tick(deltaTime);
	}
}

void World::addSystem(LoopSystem& system)
{
	addSystem(system, false);
}

void World::addSystem(LoopSystem& system, bool dontLoop)
{
	system.init(entities);
	if (!dontLoop)
	{
		systems->push_back(&system);
	}
}

Entity* World::createEntity() 
{
	entities->push_back({});
	return &entities->back();
}