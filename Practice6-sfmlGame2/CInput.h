#ifndef CINPUT_H
#define CINPUT_H

#include "Component.h"


struct CInput : public Component
{
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool shoot = false;
};

#endif
