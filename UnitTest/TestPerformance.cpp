#include "stdafx.h"
#include "TestPerformance.h"

#include "Test_ConceptInteractTable.h"
#include "UTInitializer.h"

#include "../MindElement/ConceptInteractTable_iConcept.h"
#include "../MindElement/ConceptInteractTable_Identity.h"
#include "../MindElement/ConceptInteractTable_MultiSet.h"

#include "../MindInterface/iConcept.h"
#include "../MindInterface/iConceptInteractTable.h"

#include "../UTFacility/ConceptCreator.h"
#include "../UTFacility/ConceptTableCreator.h"
#include "../UTFacility/MockiCerebrum.h"


using namespace Mind;

namespace RunPerformance
{
	void Run()
	{
		PerformanceTester::RunAll();
		PerformanceTester::ClearTests();
	}

	const int add_runNum = 10000;
	void CreateRandomConceptPair(shared_ptr<iConcept>& from, shared_ptr<iConcept>& to)
	{
		srand((unsigned)time(NULL));
		int iRange1 = 0xf7 - 0xb0;
		int iRange2 = 0xfe - 0xa1;

		char iCode1 = rand() % iRange1 + 0xb0;
		char iCode2 = rand() % iRange2 + 0xa1;
		char ch[3] = { iCode1,iCode2,0 };

		iCode1 = rand() % iRange1 + 0xb0;
		iCode2 = rand() % iRange2 + 0xa1;
		char ch2[3] = { iCode1,iCode2,0 };

		shared_ptr<ConceptCreator> conCreator(new SimpleConceptCreator());
		from = conCreator->Create(ch);
		to = conCreator->Create(ch2);
	}

	TEST_PERFORMANCE(ConceptInteractTable_iConcept, Add, add_runNum)
	{
		ConceptInteractTable_iConcept  table;
		shared_ptr<iConcept> from, to;
		CreateRandomConceptPair(from, to);
		table.Add(from, to);
	}

	TEST_PERFORMANCE(ConceptInteractTable_Identity, Add, add_runNum)
	{
		ConceptInteractTable_Identity  table;
		shared_ptr<iConcept> from, to;
		CreateRandomConceptPair(from, to);
		table.Add(from, to);
	}

	TEST_PERFORMANCE(ConceptInteractTable_MultiSet, Add, add_runNum)
	{
		ConceptInteractTable_MultiSet  table;
		shared_ptr<iConcept> from, to;
		CreateRandomConceptPair(from, to);
		table.Add(from, to);
	}

	const static int similarity_runNum = 30000;
	INIT_PARAM(ConceptInteractTable_iConcept, Similarity, shared_ptr<iConceptInteractTable> me; shared_ptr<iConceptInteractTable> comparedTable)
	{
		ConceptTableSimilarityParam param = Test_Similarity::GenerateSamples()[1];
		me = ConceptTableCreator::SimpleCreate(param.meStr, ConceptTableCreator::Concept_Based);
		comparedTable = ConceptTableCreator::SimpleCreate(param.otherStr, ConceptTableCreator::Concept_Based);
	}

	TEST_PERFORMANCE_I(ConceptInteractTable_iConcept, Similarity, similarity_runNum)
	{
		_init.me->Similarity(_init.comparedTable);
	}

	INIT_PARAM(ConceptInteractTable_Identity, Similarity, shared_ptr<iConceptInteractTable> me; shared_ptr<iConceptInteractTable> comparedTable)
	{
		ConceptTableSimilarityParam param = Test_Similarity::GenerateSamples()[1];
		me = ConceptTableCreator::SimpleCreate(param.meStr, ConceptTableCreator::Identity_Based);
		comparedTable = ConceptTableCreator::SimpleCreate(param.otherStr, ConceptTableCreator::Concept_Based);
	}

	TEST_PERFORMANCE_I(ConceptInteractTable_Identity, Similarity, similarity_runNum)
	{
		_init.me->Similarity(_init.comparedTable);
	}

	INIT_PARAM(ConceptInteractTable_MultiSet, Similarity, shared_ptr<iConceptInteractTable> me; shared_ptr<iConceptInteractTable> comparedTable)
	{
		ConceptTableSimilarityParam param = Test_Similarity::GenerateSamples()[1];
		me = ConceptTableCreator::SimpleCreate(param.meStr, ConceptTableCreator::Set_Based);
		comparedTable = ConceptTableCreator::SimpleCreate(param.otherStr, ConceptTableCreator::Concept_Based);
	}

	TEST_PERFORMANCE_I(ConceptInteractTable_MultiSet, Similarity, similarity_runNum)
	{
		_init.me->Similarity(_init.comparedTable);
	}
}

