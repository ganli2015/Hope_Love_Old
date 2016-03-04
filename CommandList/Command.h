#pragma once
#include "InOut.h"


namespace DataWrapperCPP
{
	class DataWrapper;
}

class _COMMANDINOUT Command
{
protected:
	DataWrapperCPP::DataWrapper* _datawrapper;
public:
	Command(void);
	virtual ~Command(void);

	virtual void Update()=0;
};

