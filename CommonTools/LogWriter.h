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
}



#define _USE_LOG

#ifdef _USE_LOG

#define LOG(object) CommonTool::LogWriter::Output(object) 

///Write information of object as well as its description.
#define LOG_DESC(desc,object) CommonTool::LogWriter::Output(desc);CommonTool::LogWriter::Output(object);

#define CREATELOG(filename) CommonTool::LogWriter NEWLOG(filename)

#else 
#define LOG_DESC(object)
#endif // _USE_LOG

