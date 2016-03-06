#pragma once
#include "command.h"


class _COMMANDINOUT SpeakCommand :
	public Command
{
	DataWrapperCPP::DataWrapper_Sentence* _datawrapper;

public:
	SpeakCommand(void);
	~SpeakCommand(void);
	SpeakCommand(DataWrapperCPP::DataWrapper_Sentence* datawrapper);

	void Update();
};

