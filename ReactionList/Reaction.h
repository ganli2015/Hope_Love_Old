#pragma once
#include "InOut.h"
class _REACTIONLISTINOUT Reaction
{
public:
	Reaction(void);
	~Reaction(void);

	virtual void React() =0;
};

