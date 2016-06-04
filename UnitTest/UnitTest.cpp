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
public:

	virtual void SetUp();
	virtual void TearDown() {}
};

void MyGlobal::SetUp()
{
	LeafCreator::Init();
	shared_ptr<Mind::MindElementCreator> mindCreator(new Mind::MindElementCreator());
	Mind::iMindElementCreator::SetImp(mindCreator);

	shared_ptr<LogicSystem::LogicElementCreator> logicCreator(new LogicSystem::LogicElementCreator());
	LogicSystem::iLogicElementCreator::SetImp(logicCreator);
}

void RunFilter(const string filterStr);

int _cdecl _tmain(int argc, _TCHAR* argv[])
{
	RunFilter("Test_Logic*");

	MyGlobal global;
	global.SetUp();

//	testing::AddGlobalTestEnvironment(new MyGlobal);
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");

	return 0;

}

void RunFilter(const string filterStr)
{
//	::testing::GTEST_FLAG(filter) = filterStr;

	
}

