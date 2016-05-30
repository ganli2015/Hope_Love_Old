#pragma once
#include "PublicHeader.h"

namespace Mind
{
	struct ConceptTableSimilarityParam
	{
		string meStr;
		string otherStr;
		double similarity;
	};

	class Test_Similarity : public::testing::TestWithParam<ConceptTableSimilarityParam>
	{
	public:

		void Test_ConceptInteractTable_iConcept(const ConceptTableSimilarityParam& param);
		void Test_ConceptInteractTable_Identity(const ConceptTableSimilarityParam& param);

		static vector<ConceptTableSimilarityParam> GenerateSamples() ;
	};
}


