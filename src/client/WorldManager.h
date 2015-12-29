#pragma once
#include "InputReader.h"
#include "World.h"

#define TICK_TIME 30.0

/*
	Simulation manager.
	This manager controls simulation threads.
*/
class WorldManager
{
public:
	/*
		Constructor.
		ir - Instance of InputReader to get user provided information
	*/
	WorldManager(InputReader& ir) :inputReader(ir),status(TERMINATED) {}
	~WorldManager();
	/*
		Processing of the manager
	*/
	void process();
	/*
		Close windown of the simulation.
		Terminate threads of the simulation.
		Destory simulation world.
	*/
	void terminate();
private:
	InputReader& inputReader;
	//threads statuses
	enum THS_STATUS
	{
		TERMINATED, ALIVE
	} status;
	/*
		World of simulation
	*/
	World* world;
	/*
		Open new threads for simulation
	*/
	void startThreads();
	/*
		UI thread method
	*/
	static void uiThreadMethod(WorldManager&);
	/*
		Simulation thread method
	*/
	static void simulatorThreadMethod(WorldManager&);
};

