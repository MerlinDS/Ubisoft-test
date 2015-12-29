#include "stdafx.h"
#include "WorldManager.h"
#include <thread>
#include <mutex>
#include <iostream>
#include "DisplaySystem.h"
#include "PositionSystem.h"
#include "SimulationSystem.h"

std::mutex th_mutex;

WorldManager::~WorldManager()
{
}

void WorldManager::process()
{
	if (inputReader.hasRequest())
	{
		if(status == TERMINATED)startThreads();
		auto ur = inputReader.popRequest();
		auto e = world->createEntity();
		SimulationSystem::setupEntity(e, ur.a, ur.v, ur.m);
		inputReader.showMessage("Entity created: v.x = " +  std::to_string(e->velocity.x) + ", "
			+ "v.y = " + std::to_string(e->velocity.x) + ", angle = " + std::to_string(ur.a) + 
			", mass = " + std::to_string(ur.m));
	}
		
}

void WorldManager::terminate()
{
	status = TERMINATED;
	inputReader.showMessage("Simulation was closed");
}

void WorldManager::startThreads()
{
	DebugOut("startThreads");
	status = ALIVE;
	world = new World();
	std::thread uit(uiThreadMethod, std::ref(*this));
	std::thread st(simulatorThreadMethod, std::ref(*this));
	uit.detach();
	st.detach();
	inputReader.showMessage("Simulation was created", false);
}

void WorldManager::uiThreadMethod(WorldManager& tm)
{
	DebugOut("Create UI thread");
	auto config = tm.inputReader.getConfig();
	DisplaySystem ds = DisplaySystem(L"MainWClass", L"Ubi-soft test", 
		tm, config.width, config.height, config.x, config.y);
	tm.world->addSystem(ds, true);
	while (tm.status >= ALIVE)
	{
		th_mutex.lock();
		ds.tick(TICK_TIME);
		th_mutex.unlock();
		Sleep((DWORD)TICK_TIME);
	}
	delete tm.world;
	DebugOut("UI thread terminated");
}

void WorldManager::simulatorThreadMethod(WorldManager& tm)
{
	DebugOut("Create SIMULATION thread");
	auto config = tm.inputReader.getConfig();
	auto sm = SimulationSystem();
	tm.world->addSystem(sm);
	auto ps = PositionSystem(config.x, config.height - config.y, 
		config.width, config.height, config.scale);
	tm.world->addSystem(ps);
	while (tm.status >= ALIVE)
	{
		th_mutex.lock();
		tm.world->tick(TICK_TIME);
		th_mutex.unlock();
		Sleep((DWORD)TICK_TIME);
	}
	DebugOut("SIMULATION thread terminated");
}