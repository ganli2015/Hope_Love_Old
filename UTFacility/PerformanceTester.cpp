#include "stdafx.h"
#include "PerformanceTester.h"


std::vector<PerformanceTester*> PerformanceTester::_tests;

PerformanceTester::PerformanceTester(const int runNum, const string classname, const string methodname):_RunNums(runNum),_className(classname),_methodName(methodname)
{
}


PerformanceTester::~PerformanceTester()
{
	
}

void PerformanceTester::RunAll()
{
	for (unsigned int i=0;i<_tests.size();++i)
	{
		_tests[i]->Run();

		PerformanceTester* t = _tests[i];
		cout << t->_className << "  " << t->_methodName << " : " << t->_duration << "s" << endl;
	}
}

void PerformanceTester::ClearTests()
{
// 	for (std::vector< PerformanceTester* >::iterator it = _tests.begin(); it != _tests.end();)
// 	{
// 		delete (*it);
// 	}
// 	_tests.clear();
}
