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

class MyGlobal: public testing::Environment
{
public:

	virtual void SetUp();
	virtual void TearDown() {}
};

void MyGlobal::SetUp()
{
	LeafCreator::Init();
	shared_ptr<Mind::MindElementCreator> creator(new Mind::MindElementCreator());
	Mind::iMindElementCreator::SetImp(creator);
}


int _cdecl _tmain(int argc, _TCHAR* argv[])
{
//	::testing::GTEST_FLAG(filter) = "Test_LogicKnowledgeInitializer*";
	testing::AddGlobalTestEnvironment(new MyGlobal);
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");

	return 0;

}

