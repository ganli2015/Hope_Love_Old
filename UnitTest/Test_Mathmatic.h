#pragma once
#include "PublicHeader.h"

class Test_Mathmatic
{
public:
	Test_Mathmatic(void);
	~Test_Mathmatic(void);

	static void RunTest();

private:
	static void TestRand();

	static void TestMatrix();
	static void TestSubSequence();

	static void TestMyInt();
};

