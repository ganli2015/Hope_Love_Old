// UnitTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <exception>
#include <iostream>
using namespace std;

#include "TestClass.h"
#include "PublicHeader.h"
#include "FuncForTest.h"


int _cdecl _tmain(int argc, _TCHAR* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");

	return 0;

}

