#pragma once
#include "LoopSystem.h"
#include "WorldManager.h"
#include <Windows.h>

using namespace std;

/*
 System responsible for entities drawing.
 Also this system create window for drawing and handle window procedures
*/
class DisplaySystem : public LoopSystem
{
public:
	/*
		Constructor.
		window class name
		window title
		world of simulation
		window width
		window height
		window greeed center x
		window greeed center y
	*/
	DisplaySystem(LPCWSTR, LPCWSTR, WorldManager&, int, int, int, int);
	~DisplaySystem();
	/*
		@inheritedDoc
	*/
	void init(vector<Entity>*);
	/*
		@inheritedDoc
	*/
	void tick(float deltaTime);
	/*
		Create new window
	*/
	int createWindow();
protected:
	//list of all entities 
	vector<Entity>* entities;
private:
	WorldManager& threadManager;
	//window properties
	LPCWSTR className;
	LPCWSTR title;
	int x;
	int y;
	int width;
	int height;
	//window instance
	HWND window;
	//struct with window class setups
	WNDCLASSEX wndclass;
	//window procedures callback function
	//static wrapper for window procedures callback function
	static LRESULT CALLBACK WndProc(HWND, unsigned int, WPARAM, LPARAM);
	LRESULT CALLBACK _WndProc(HWND, unsigned int, WPARAM, LPARAM);
};