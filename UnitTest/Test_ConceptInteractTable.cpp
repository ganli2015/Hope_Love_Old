#include "StdAfx.h"
#include "Test_ConceptInteractTable.h"

#include "../MindInterface/iConceptInteractTable.h"

#include "../UTFacility/ConceptTableCreator.h"

namespace Mind
{
	INSTANTIATE_TEST_CASE_P(Test_ConceptInteractTable, Test_Similarity, testing::ValuesIn(Test_Similarity::GenerateSamples()));

	TEST_P(Test_Similarity,Similarity)
	{
		ConceptTableSimilarityParam param=GetParam();
		Test_ConceptInteractTable_iConcept(param);
		Test_ConceptInteractTable_Identity(param);
	}

	void Test_Similarity::Test_ConceptInteractTable_iConcept( const ConceptTableSimilarityParam& param )
	{
		shared_ptr<iConceptInteractTable> me=ConceptTableCreator::SimpleCreate(param.meStr);
		shared_ptr<iConceptInteractTable> other=ConceptTableCreator::SimpleCreate(param.otherStr);

		ASSERT_EQ(me->Similarity(other),param.similarity);
	}

	void Test_Similarity::Test_ConceptInteractTable_Identity( const ConceptTableSimilarityParam& param )
	{
		shared_ptr<iConceptInteractTable> me=ConceptTableCreator::SimpleCreate(param.meStr,ConceptTableCreator::Identity_Based);
		shared_ptr<iConceptInteractTable> other=ConceptTableCreator::SimpleCreate(param.otherStr,ConceptTableCreator::Identity_Based);

		ASSERT_EQ(me->Similarity(other),param.similarity);
	}

	vector<ConceptTableSimilarityParam> Test_Similarity::GenerateSamples()
	{
		vector<ConceptTableSimilarityParam> res;

		{
			ConceptTableSimilarityParam p;
			p.meStr="一-二,二-三";
			p.otherStr="一-二,二-三,三-四,四-五";
			p.similarity=0.5;
			res.push_back(p);
		}

		{
			ConceptTableSimilarityParam p;
			p.meStr="一-二,二-三,三-四,四-五";
			p.otherStr="一-二,二-三";
			p.similarity=0.5;
			res.push_back(p);
		}

		{
			ConceptTableSimilarityParam p;
			p.meStr="一-二,二-三";
			p.otherStr="一-二,二-三";
			p.similarity=1;
			res.push_back(p);
		}

		return res;
	}
}


