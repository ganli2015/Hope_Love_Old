// UnitTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <exception>
#include <iostream>
using namespace std;

#include "TestClass.h"

int _cdecl _tmain(int argc, _TCHAR* argv[])
{
	TestClass testClass;
	//testClass.Register("SentenceAnalysisAlgorithm");

	try
	{
		testClass.RunTest();
	}
	catch(exception e)
	{
		cout<<e.what()<<endl;
		system("pause");
	}

	return 0;
}

