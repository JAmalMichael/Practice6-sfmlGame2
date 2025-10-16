#ifndef CLIFESPAN_H
#define CLIFESPAN_H

#include "Component.h"

struct CLifespan : public Component {
	int remaining;
	int total;
	CLifespan(int t)
		: remaining(t), total(t) {};
};
#endif
