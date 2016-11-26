// UnitTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <exception>
#include <iostream>
using namespace std;

#include "TestClass.h"
#include "PublicHeader.h"
#include "FuncForTest.h"
#include "TestPerformance.h"
#include "UTInitializer.h"
#include "IntegrationTest.h"


class MyGlobal: public testing::Environment
{
	int _startObjCount;

public:
	~MyGlobal(){TearDown();}

	virtual void SetUp();
	virtual void TearDown();
};

void MyGlobal::SetUp()
{
	_startObjCount=MyObject::GetObjectCount();
}

void MyGlobal::TearDown()
{
	ASSERT_EQ(MyObject::GetObjectCount(),_startObjCount);
}

void RunFilter(const string filterStr);


void RunUnitTest(int argc, _TCHAR* argv[])
{
//	RunFilter("Test_SubSequence*");

#ifdef _RUN_INTEGRATION_TEST

	RunFilter("Integration*");

#endif // !_RUN_INTEGRATION_TEST

	testing::InitGoogleTest(&argc, argv);
	MEMOCHECK;
	RUN_ALL_TESTS();
	RELEASE_MEMOCHECK;

}

//#define _RUN_PERFORMANCE

Initializer init;
int _cdecl _tmain(int argc, _TCHAR* argv[])
{
#ifdef _RUN_PERFORMANCE

	RunPerformance::Run();

#else

	RunUnitTest(argc, argv);

#endif // _RUN_PERFORMANCE

	system("pause");

	return 0;

}

void RunFilter(const string filterStr)
{
	::testing::GTEST_FLAG(filter) = filterStr;
}

