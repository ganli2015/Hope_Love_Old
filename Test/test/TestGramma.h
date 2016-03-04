#pragma once

class Test_Gramma
{
public:
	Test_Gramma(void);
	~Test_Gramma(void);

	static void RunTest();

private:
	static void Test_Network();
	static void Test_Subsequence();
	static void Test_GetIndexOfMatchedPattern();
	static void Test_BuildGrammarAssociation();
};

