#pragma once
#include "LoopSystem.h"
/*
 System responsible for converting "real world"
 position of entities to screen position
*/
class PositionSystem :
	public LoopSystem
{
public:
	/*
		Constructor
		x - X coordinate of the center of the screen
		y - Y coordinate of the center of the screen
		width - width of the screen
		height - hegith of the screen
		scale - Scale of the screen (pixel * scale = meter)
	*/
	PositionSystem(int _x, int _y, int w, int h, float s) :
		 x(_x),y(_y),width(w), height(h), scale(s){}
	~PositionSystem();
	/*
		@inherited doc
	*/
	void init(vector<Entity>*);
	/*
		@inherited doc
	*/
	void tick(float deltaTime);

private:
	int x;
	int y;
	int width;
	int height;
	float scale;
	vector<Entity>* entities;
	/*
		Entities that need to be destrcuted 
		cause they go out of the viewport.
	*/
	vector<int> destructable;
};

