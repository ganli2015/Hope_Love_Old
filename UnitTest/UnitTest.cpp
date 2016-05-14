// UnitTest.cpp : �������̨Ӧ�ó������ڵ㡣
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

