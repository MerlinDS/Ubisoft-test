#pragma once
#ifdef EXPORT_API
	#define CLASS_WORLD __declspec(dllexport)
#else
	#define CLASS_WORLD __declspec(dllimport)
#endif

#include "LoopSystem.h"
#include "Entity.h"
#include "SimulationSystem.h"
#include <vector>

/*
World of simulation.
 Main class of simple realization of Entity/Component System engine.
 Ñombines a system manager and entities holder.
*/
class CLASS_WORLD World
{
public:
	World();
	~World();
	/*
		Execute on every tick of application
	*/
	void tick(float);
	/*
		Add system to CES engine as part of simulation cycle.
	*/
	void addSystem(LoopSystem&, bool);
	/*
	Add system to CES engine as part of simulation cycle
	*/
	void addSystem(LoopSystem&);
	/*
		Create new entity and add it to simulation.
	*/
	Entity* createEntity();
private:
	//vector of added systems
	std::vector<LoopSystem*>* systems;
	//vector of live entities
	std::vector<Entity>* entities;
};

