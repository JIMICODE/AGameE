#pragma once
#ifndef TYPEDEF_H_
#define TYPEDEF_H_

typedef unsigned long ActorId;

//Actor type.
enum ActorType {
	RenderComponent,
	AudioComponent,
	Player,
	Enemy,
	Unknow
};

enum ActorComponentType
{
	Unknow
};

#endif // !TYPEDEF_H_
