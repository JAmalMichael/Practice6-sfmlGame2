#ifndef CSCORE_H
#define CSCORE_H

#include "Component.h"

struct CScore: public Component {
	int value = 0;
	explicit CScore(int v = 0) :value(v) {};
};


#endif
