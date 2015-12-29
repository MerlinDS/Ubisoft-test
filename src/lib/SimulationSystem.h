#pragma once
#ifdef EXPORT_API
	#define CLASS_SIMULATION_SYS __declspec(dllexport)
#else
	#define CLASS_SIMULATION_SYS __declspec(dllimport)
#endif
#include "LoopSystem.h"
/*
	System responsible for physics simulation.
	This concrete system simulates an free falling body, without air resistance
*/
class CLASS_SIMULATION_SYS SimulationSystem :
	public LoopSystem
{
public:
	SimulationSystem();
	~SimulationSystem();
	/*
		Prepare entity for simulation. Convert user input to entity structur.
		Static as an utility method
	*/
	static void setupEntity(Entity* entity, double angle, float velocity, float mass);
	/*
		@inherited doc
	*/
	void init(vector<Entity>*);
	/*
	@inherited doc
	*/
	void tick(float deltaTime);

private:
	//vector of all entities
	vector<Entity>* entities;
};

