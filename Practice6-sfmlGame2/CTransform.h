#ifndef CTRANSFORM_H
#define CTRANSFORM_H

#include "Component.h"
#include "Vec2.h"

struct CTransform : public Component
{
	Vec2 position;
	Vec2 velocity;
	float angle = 0.0f;

	CTransform(const Vec2& pos = {}, const Vec2 vel = {}, float ang = 0.f)
		:position(pos), velocity(vel), angle(ang) {	};
};



#endif
