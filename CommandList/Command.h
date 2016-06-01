#pragma once
#include "InOut.h"


namespace DataWrapperCPP
{
	class DataWrapper_Sentence;
}

class _COMMANDINOUT Command : public Obj<Command>
{
protected:
public:
	Command(void);
	virtual ~Command(void);

	virtual void Update()=0;
};

