#pragma once
#include "InOut.h"

namespace LogicSystem
{
	class TestClass
	{
	public:
		TestClass(void);
		~TestClass(void);

		static void RunTest();

	private:
		static void Test_Expression();
		static void Test_Logic_Determine();
	};
}


