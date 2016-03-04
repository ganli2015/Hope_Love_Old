#pragma once
#include "command.h"


class _COMMANDINOUT SpeakCommand :
	public Command
{
public:
	SpeakCommand(void);
	~SpeakCommand(void);
	SpeakCommand(DataWrapperCPP::DataWrapper* datawrapper);

	void Update();
};

