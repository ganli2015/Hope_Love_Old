#include "StdAfx.h"
#include "LogWriter.h"


namespace CommonTool
{
	const string LogWriter::_defaultLogFilename("Log\\DefaultLog.log");

	std::ofstream LogWriter::_currentLog(LogWriter::_defaultLogFilename);

	double LogWriter::_startTime=(double)clock()/CLOCKS_PER_SEC;

	LogWriter::LogWriter(const string filename)
	{
		_currentLog.close();
		_currentLog.open("Log\\"+filename+".log");
	}

	LogWriter::~LogWriter(void)
	{
		_currentLog.close();
		_currentLog.open(_defaultLogFilename,ios::app);
	}

	void LogWriter::ResetStartTime()
	{
		_startTime=clock()/CLOCKS_PER_SEC;
	}

	double LogWriter::GetDuration()
	{
		double duration=(double)clock()/CLOCKS_PER_SEC-_startTime;

		return duration;
	}

}

