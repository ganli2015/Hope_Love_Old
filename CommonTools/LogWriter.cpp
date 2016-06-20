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

	std::map<std::string, double> EfficiencyRecorder::_section_duration;
	const string EfficiencyRecorder::_outFilename("Log//Performance Detect.txt");

	EfficiencyRecorder::EfficiencyRecorder()
	{

	}

	EfficiencyRecorder::~EfficiencyRecorder()
	{

	}

	void EfficiencyRecorder::Output()
	{
		ofstream out(_outFilename);
		for (map<std::string, double>::const_iterator it=_section_duration.begin();it!=_section_duration.end();++it)
		{
			out << it->first << "    " << it->second << endl;
		}

		out.close();
	}

	CodeSection::CodeSection(const string secName) :_secName(secName),_released(false)
	{
		_startTime = (double)clock() / CLOCKS_PER_SEC;
	}

	CodeSection::~CodeSection()
	{
		if(!_released)
		{
			Release();
		}
	}

	void CodeSection::Release()
	{
		double duration = (double)clock() / CLOCKS_PER_SEC - _startTime;

		//Check whether  EfficiencyRecorder contain same section.
		//If so , then add time duration based on previous time.
		if (EfficiencyRecorder::_section_duration.count(_secName) != 0)
		{
			EfficiencyRecorder::_section_duration[_secName] += duration;
		}
		else
		{
			EfficiencyRecorder::_section_duration[_secName] = duration;
		}

		_released = true;
	}

}

