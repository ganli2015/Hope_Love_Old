#include "StdAfx.h"
#include "Test_ConceptInteractTable.h"

#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/CommonFunction.h"

#include "../Mind/Cerebrum.h"

#include "../UTFacility/ConceptTableCreator.h"
#include "../UTFacility/ConceptCreator.h"
#include "../UTFacility/MockiCerebrum.h"

#include "FuncForTest.h"
#include <gmock/gmock.h>
#include <gmock/gmock-generated-nice-strict.h>

using ::testing::Return;

namespace Mind
{
	INSTANTIATE_TEST_CASE_P(Test_ConceptInteractTable, Test_Similarity, testing::ValuesIn(Test_Similarity::GenerateSamples()));

	TEST_P(Test_Similarity,Similarity)
	{
		PrepareMockCerebrum();

		ConceptTableSimilarityParam param=GetParam();
		Test_ConceptInteractTable_iConcept(param);
		Test_ConceptInteractTable_Identity(param);

		iCerebrum::KillInstance();
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
			p.meStr="һ-��,��-��,��-��,��-��";
			p.otherStr="һ-��,��-��,��-��,��-��";
			p.similarity=0.5;
			res.push_back(p);
		}

		{
			ConceptTableSimilarityParam p;
			p.meStr="һ-��,��-��,��-��,��-��";
			p.otherStr="һ-��,��-��,��-��,��-��";
			p.similarity=0.5;
			res.push_back(p);
		}

		{
			ConceptTableSimilarityParam p;
			p.meStr="һ-��,��-��";
			p.otherStr="һ-��,��-��";
			p.similarity=1;
			res.push_back(p);
		}

		return res;
	}

	vector<pair<Identity,shared_ptr<iConcept>>> Test_Similarity::CreateNumberConcept()
	{
		shared_ptr<ConceptCreator> conCreator(new SimpleConceptCreator());

		vector<pair<Identity,shared_ptr<iConcept>>> res;
		res.push_back(make_pair(Identity("һ",0),conCreator->Create("һ")));
		res.push_back(make_pair(Identity("��",0),conCreator->Create("��")));
		res.push_back(make_pair(Identity("��",0),conCreator->Create("��")));
		res.push_back(make_pair(Identity("��",0),conCreator->Create("��")));
		res.push_back(make_pair(Identity("��",0),conCreator->Create("��")));
		res.push_back(make_pair(Identity("��",0),conCreator->Create("��")));
		res.push_back(make_pair(Identity("��",0),conCreator->Create("��")));
		res.push_back(make_pair(Identity("��",0),conCreator->Create("��")));
		res.push_back(make_pair(Identity("��",0),conCreator->Create("��")));


		return res;
	}

	void Test_Similarity::PrepareMockCerebrum()
	{
		MockiCerebrum* mockCerebrum=new MockiCerebrum();

		vector<pair<Identity,shared_ptr<iConcept>>> concepts=CreateNumberConcept();
		for (unsigned int i=0;i<concepts.size();++i)
		{
			EXPECT_CALL(*mockCerebrum,GetConcept(testing::Eq(concepts[i].first)))
			.WillRepeatedly(Return(concepts[i].second));
		}

		iCerebrum::SetInstance(mockCerebrum);
	}

}


