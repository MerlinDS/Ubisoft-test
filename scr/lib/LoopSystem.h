#pragma once
#ifdef EXPORT_API
	#define CLASS_LOOP_SYS __declspec(dllexport)
#else
	#define CLASS_LOOP_SYS __declspec(dllimport)
#endif
#include "stdafx.h"
#include <vector>
#include "Entity.h"

using namespace std;
/*
 Public abstract class of loop systems. 
 A part of the very simple Entity/Component System engine realisation.
*/
class CLASS_LOOP_SYS LoopSystem {

public:
	//Virtual destructor
	virtual ~LoopSystem() {}
	/*
	Set entity collection to system and initialize system
	Will be executed when systems becomes a part of Entity/Component System world
	*/
	virtual void init(vector<Entity>*) = 0;
	/*
	Executed on every application tick
	*/
	virtual void tick(float deltaTime) = 0;
	
};