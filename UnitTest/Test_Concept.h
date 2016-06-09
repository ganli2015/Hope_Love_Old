#pragma once
#include "PublicHeader.h"

#include "../MindInterface/CommonFunction.h"

namespace Mind
{
	struct Param_DeepInteraction
	{
		Identity from;
		Identity to;
		vector<pair<string,string>> expect;
	};

	class Test_Concept: public::testing::TestWithParam<Param_DeepInteraction>
	{
	public:
		static vector<Param_DeepInteraction> GenerateSamples();

	};
}


