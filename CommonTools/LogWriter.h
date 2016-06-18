#pragma once
#include "InOut.h"
#include <fstream>
#include <list>
#include <time.h>

namespace CommonTool
{
	///Write log file.
	class _COMMONTOOLSINOUT LogWriter
	{
	private:
		const static string _defaultLogFilename;

		///The default time when pushing enter key.
		static double _startTime;

	private:
		///The current log file.
		static ofstream _currentLog;

		template<class T>
		class OutputObjectVal
		{
		public:
			void operator()(const T& obj)
			{
				_currentLog<<obj.GetString()<<"		"<<GetDuration()<<endl;
			}
		};

		template<class T>
		class OutputObjectPointer
		{
		public:
			void operator()(const T& obj)
			{
				_currentLog<<obj->GetString()<<"		"<<GetDuration()<<endl;
			}
		};

	public:
		LogWriter(const string filename);
		~LogWriter(void);

		///General
		template<class T> 
		static void Output(const T object)
		{
			OutputObjectVal<T> output;
			output(object);
		}

		///For string
		template<> 
		static void Output(const string str)
		{
			_currentLog<<str<<"		"<<GetDuration()<<endl;
		}

		///For const char
		template<> 
		static void Output(const char* str)
		{
			string chStr(str);
			Output(chStr);
		}

		///For shared_ptr
		template<class T> 
		static void Output(const shared_ptr<T> object)
		{
			OutputObjectPointer<shared_ptr<T>> output;
			output(object);
		}

		///For vector
		template<class T> 
		static void Output(const vector<T> objects)
		{
			for_each(object.begin(),object.end(),OutputObjectVal<T>());
		}

		///For list shared_ptr
		template<class T> 
		static void Output(const list<shared_ptr<T>> objects)
		{
			for_each(objects.begin(),objects.end(),OutputObjectPointer<shared_ptr<T>>());
		}

		///For vector shared_ptr
		template<class T> 
		static void Output(const vector<shared_ptr<T>> objects)
		{
			for_each(objects.begin(),objects.end(),OutputObjectPointer<shared_ptr<T>>());
		}


		static void ResetStartTime();

	private:

		static double GetDuration() ;
	};

	///Record time durations of each code section.
	class _COMMONTOOLSINOUT EfficiencyRecorder
	{
		///The section key and its total duration.
		static map<string, double> _section_duration;
		const static string _outFilename;

		friend class CodeSection;
	public:
		EfficiencyRecorder();
		~EfficiencyRecorder();

		static void Output();
		static void Clear() { _section_duration.clear(); }
	};


	class _COMMONTOOLSINOUT CodeSection
	{
		string _secName;
		double _startTime;
		bool _released;
	public:
		CodeSection(const string secName);
		~CodeSection();

		void Release();
	};

	
}



#define _USE_LOG

#ifdef _USE_LOG

///Output object.<Object> must have a method of GetString().
#define LOG(object) CommonTool::LogWriter::Output(object) 

///Write information of object as well as its description.
#define LOG_DESC(desc,object) CommonTool::LogWriter::Output(desc);CommonTool::LogWriter::Output(object);

#define CREATELOG(filename) CommonTool::LogWriter NEWLOG(filename)

///Create a section and record the time consuming of it.
#define SECTION_TIME(tag) CommonTool::CodeSection tag##CodeSection(#tag)
#define END_SECTION(tag) tag##CodeSection.Release()

#else 
#define LOG_DESC(object)
#endif // _USE_LOG

