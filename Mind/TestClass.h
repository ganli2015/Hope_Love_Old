#pragma once
#include "InOut.h"

namespace Mind
{
	class TestClass
	{
	public:
		TestClass(void);
		~TestClass(void);

		static void RunTest();

	private:
		static void Test_Network();
		static void Test_Subsequence();
		static void Test_GetIndexOfMatchedPattern();
		static void Test_BuildGrammarAssociation();
	};
}


