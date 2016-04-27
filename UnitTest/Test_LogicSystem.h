#pragma once
#include "PublicHeader.h"


class Test_LogicSystem
{
public:
	Test_LogicSystem(void);
	~Test_LogicSystem(void);

	static void RunTest();

private:
	static void Test_Expression();
	static void Test_Logic_Determine();
};

