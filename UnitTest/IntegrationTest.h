#pragma once
#include "PublicHeader.h"

#define _RUN_INTEGRATION_TEST

struct ParamIntegration
{
	string input;
	vector<string> output;
};

///Test the integration of all functions and classes .
///The test run from the very beginning, input a string sentence, to output a string sentence.
class IntegrationTest : public::testing::TestWithParam<ParamIntegration>
{
public:
	IntegrationTest();
	~IntegrationTest();

	static vector<ParamIntegration> GenerateSamples();

	static void Initialize();

	static bool StringInVector(const string str, const vector<string>& strVec);
};

