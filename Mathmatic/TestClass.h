#pragma once
#include "InOut.h"

class TestClass
{
public:
	TestClass(void);
	~TestClass(void);

	static void RunTest();

private:
	static void TestRand();

	static void TestMatrix();
	static void TestSubSequence();

	static void TestMyInt();
};

