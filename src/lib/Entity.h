#pragma once
#ifdef EXPORT_API
	#define STRUCT_DECLSPEC __declspec(dllexport)
	#define STRUCT_T_DECLSPEC __declspec(dllexport)
#else
	#define STRUCT_DECLSPEC __declspec(dllimport)
	#define STRUCT_T_DECLSPEC __declspec(dllimport)
#endif

#include "stdafx.h"
/*
Type definition for 2d vector
*/
typedef STRUCT_T_DECLSPEC struct {
	float x;
	float y;
} vec2;

/*
Strct for entity.
Entity is a simple components holder.
In ccurrent realization contains velocity, position and mass of the entity.
In usual cases it is bad, but for simple test application it is normal.
*/
struct STRUCT_DECLSPEC Entity
{
	vec2 velocity;
	//position of entity in world
	vec2 position;
	//position of entity on screen
	vec2 viewPosition;
	//life time of entity
	float time;
	//mass of entity (Ignored for now)
	float mass;
};