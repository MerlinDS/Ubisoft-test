#include "SimulationSystem.h"
#include <iostream>

//Math pi
#define PI 3.14159265
//Gravity factor
#define G 9.8

SimulationSystem::SimulationSystem() {}

SimulationSystem::~SimulationSystem()
{
	entities = nullptr;
}

void SimulationSystem::init(vector<Entity>* collection)
{
	entities = collection;
}

void SimulationSystem::setupEntity(Entity* entity, double angle, float velocity, float mass)
{
	angle = angle * PI / 180;//conver to rads
	entity->position.y = entity->position.x = 0;
	//not needs in double precision
	entity->velocity.x = (float) ( velocity * cos(angle) );
	entity->velocity.y = (float) ( velocity * sin(angle) );
}

void SimulationSystem::tick(float deltaTime)
{
	//conver deltaTime from ms to s
	deltaTime = deltaTime / 1000;
	int n = entities->size();
	for (int i = 0; i < n; i++)
	{
		auto e = &entities->at(i);
		e->time += deltaTime;
		e->position.x = e->velocity.x * e->time;
		// v * sin(a) - ( G * pow(t) ) / 2;
		e->position.y = e->velocity.y * e->time;
		//not needs in double precision
		e->position.y -= (float) ( 0.5 * G * ( e->time * e->time ) ); 
	}

}
