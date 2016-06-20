#pragma once
#include "PublicHeader.h"
#include <time.h>


class _UTFACILITYINOUT PerformanceTester
{
	static vector<PerformanceTester*> _tests;

protected:
	int _RunNums;	
	double _duration;
	string _className;
	string _methodName;

public:
	PerformanceTester(const int runNum,const string classname,const string methodname);
	~PerformanceTester();

	static void Add(PerformanceTester* val) { _tests.push_back(val); }
	static void RunAll();
	static void ClearTests();

	virtual void Run() = 0;
};

///Test the performance of a method of a class.
#define TEST_PERFORMANCE(ClassName,Method,RunNums)  \
class ClassName##_##Method : public PerformanceTester  \
{	\
public:	\
	ClassName##_##Method(const int runNums):PerformanceTester(runNums,#ClassName,#Method)	\
	{	\
PerformanceTester::Add(this);	\
	}	\
	~ClassName##_##Method()	\
	{	\
	}	\
void Run()	\
{	\
double start=(double)clock()/CLOCKS_PER_SEC;	\
for (int i=0;i<_RunNums;++i)	\
{	\
OneIteration();	\
}	\
_duration=(double)clock()/CLOCKS_PER_SEC-start;	\
}	\
private:	\
void OneIteration() const;	\
};	\
ClassName##_##Method ClassName##_##Method##_Object(RunNums);	\
void ClassName##_##Method::OneIteration() const

///With initial data.
#define TEST_PERFORMANCE_I(ClassName,Method,RunNums)  \
template<class T>	\
class ClassName##_##Method : public PerformanceTester  \
{	\
T _init;	\
public:	\
	ClassName##_##Method(const int runNums,const T initParam):PerformanceTester(runNums,#ClassName,#Method),_init(initParam)	\
	{	\
PerformanceTester::Add(this);	\
	}	\
	~ClassName##_##Method()	\
	{	\
	}	\
void Run()	\
{	\
double start=(double)clock()/CLOCKS_PER_SEC;	\
for (int i=0;i<_RunNums;++i)	\
{	\
OneIteration();	\
}	\
_duration=(double)clock()/CLOCKS_PER_SEC-start;	\
}	\
private:	\
void OneIteration() const;	\
};	\
ClassName##_##Method<PerformanceParam_##ClassName##_##Method> ClassName##_##Method##_Object(RunNums,p_##ClassName##_##Method);	\
template<class T>	\
void ClassName##_##Method<T>::OneIteration() const

///Initial params for PerformanceTester
#define INIT_PARAM(ClassName,Method,Vars)	\
class PerformanceParam_##ClassName##_##Method		\
{	\
public:		\
	Vars;	\
PerformanceParam_##ClassName##_##Method()	\
{	\
Initializer init;	\
PrepareData();	\
};	\
private:	\
		void PrepareData();		\
};	\
PerformanceParam_##ClassName##_##Method  p_##ClassName##_##Method;	\
void PerformanceParam_##ClassName##_##Method::PrepareData()	


