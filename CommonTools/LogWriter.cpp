#include "StdAfx.h"
#include "LogWriter.h"


namespace CommonTool
{
	const string LogWriter::_defaultLogFilename("Log\\DefaultLog.log");

	std::ofstream LogWriter::_currentLog(LogWriter::_defaultLogFilename);

	LogWriter::LogWriter(const string filename)
	{
		_currentLog.close();
		_currentLog.open("Log\\"+filename+".log");
	}

	LogWriter::~LogWriter(void)
	{
		_currentLog.close();
		_currentLog.open(_defaultLogFilename);
	}

	template<> 
	void LogWriter::Output( const string str )
	{
		_currentLog<<str<<endl;
	}

}

