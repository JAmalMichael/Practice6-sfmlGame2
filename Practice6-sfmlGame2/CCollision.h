#ifndef CCOLLISION_H
#define CCOLLISION_H

#include "Component.h"

struct CCollision : public Component
{
	float radius;
	explicit CCollision(float r)
		: radius(r) {};
};


#endif
