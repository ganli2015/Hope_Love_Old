// UnitTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <exception>
#include <iostream>
using namespace std;

#include "TestClass.h"
#include "PublicHeader.h"
#include "FuncForTest.h"
#include "../UTFacility/LeafCreator.h"
#include "../MindElement/MindElementCreator.h"
#include "../LogicSystem/LogicElementCreator.h"

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

void Init()
{
	LeafCreator::Init();
	shared_ptr<Mind::MindElementCreator> mindCreator(new Mind::MindElementCreator());
	Mind::iMindElementCreator::SetImp(mindCreator);

	shared_ptr<LogicSystem::LogicElementCreator> logicCreator(new LogicSystem::LogicElementCreator());
	LogicSystem::iLogicElementCreator::SetImp(logicCreator);
}

int _cdecl _tmain(int argc, _TCHAR* argv[])
{
//	RunFilter("Test_Logic/Test_FinalDeduce*");

	Init();

//	testing::AddGlobalTestEnvironment(new MyGlobal);
	testing::InitGoogleTest(&argc, argv);
	MEMOCHECK;
	RUN_ALL_TESTS();
	RELEASE_MEMOCHECK;

	system("pause");


	return 0;

}

void RunFilter(const string filterStr)
{
	::testing::GTEST_FLAG(filter) = filterStr;

	
}

