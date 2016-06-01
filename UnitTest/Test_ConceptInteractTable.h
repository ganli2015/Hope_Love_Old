#pragma once
#include "PublicHeader.h"
#include "FuncForTest.h"

namespace Mind
{
	struct Identity;

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
		static vector<pair<Identity,shared_ptr<iConcept>>> CreateNumberConcept();

	protected:
		///Construct a MockiCerebrum that only contains the concept of number from one to nine.
		void PrepareMockCerebrum();
	};
}


