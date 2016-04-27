#pragma once
#include "PublicHeader.h"
#include "MyTest.h"

class TestClass
{
	vector<shared_ptr<Test>> _tests;
public:
	TestClass(void);
	~TestClass(void);

	//void Register(const string testName) {_testNames.push_back(testName);}

	void RunTest();
};

