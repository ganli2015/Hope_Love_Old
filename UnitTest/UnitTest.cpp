// UnitTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <exception>
#include <iostream>
using namespace std;

#include "TestClass.h"
#include "PublicHeader.h"


int _cdecl _tmain(int argc, _TCHAR* argv[])
{
	int objCountStart=MyObject::GetObjectCount();

	TestClass testClass;

	try
	{
		testClass.RunTest();
	}
	catch(exception e)
	{
		cout<<e.what()<<endl;
		system("pause");
	}

	int objCountEnd=MyObject::GetObjectCount();

	Check(objCountEnd==objCountStart);

	return 0;
}

