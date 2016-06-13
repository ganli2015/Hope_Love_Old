#pragma once
#include "InOut.h"
#include <fstream>
#include <list>


namespace CommonTool
{
	///Write log file.
	class _COMMONTOOLSINOUT LogWriter
	{
		const static string _defaultLogFilename;

		///The current log file.
		static ofstream _currentLog;

		template<class T>
		class OutputObjectVal
		{
		public:
			void operator()(const T& obj)
			{
				_currentLog<<obj.GetString()<<endl;
			}
		};

		template<class T>
		class OutputObjectPointer
		{
		public:
			void operator()(const T& obj)
			{
				_currentLog<<obj->GetString()<<endl;
			}
		};

	public:
		LogWriter(const string filename);
		~LogWriter(void);

		///General
		template<class T> 
		static void Output(const T object)
		{
			_currentLog<<object.GetString()<<endl;
		}

		///For string
		template<> 
		static void Output(const string str);

		///For const char
		template<> 
		static void Output(const char* str)
		{
			_currentLog<<str<<endl;
		}

		///For shared_ptr
		template<class T> 
		static void Output(const shared_ptr<T> object)
		{
			_currentLog<<object->GetString()<<endl;
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
	};




}

#define LOG(object) CommonTool::LogWriter::Output(object)
///Write information of object as well as its description.
#define LOG_DESC(desc,object) CommonTool::LogWriter::Output(desc);CommonTool::LogWriter::Output(object);
