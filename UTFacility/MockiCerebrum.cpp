#include "StdAfx.h"
#include "MockiCerebrum.h"
#include "ConceptCreator.h"
#include "ConceptTableCreator.h"
#include "Matchers.h"

#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/iDeduceResult.h"

#include "../LogicSystem/DeduceResult.h"

using testing::Return;
using testing::_;
using testing::Matcher;
using namespace LogicSystem;

namespace Mind
{
	void MockiCerebrum::AddExpectCall_FindConceptWithMatchedDisc( const string conceptTableStr, const string matchedConceptStr, const string toConceptStr, const shared_ptr<ConceptTableCreator> tableCreator, const shared_ptr<ConceptCreator> conceptCreator )
	{
		shared_ptr<ConceptTableCreator> myTableCreator=tableCreator;
		shared_ptr<ConceptCreator> myConceptCreator=conceptCreator;
		if(myConceptCreator==NULL)
		{
			myConceptCreator=shared_ptr<SimpleConceptCreator>(new SimpleConceptCreator());
		}
		if(myTableCreator==NULL)
		{
			myTableCreator=shared_ptr<ConceptTableCreator>(new ConceptTableCreator());
		}

		AddFindMatchedConceptExpectCall(conceptTableStr,matchedConceptStr,toConceptStr,myTableCreator,myConceptCreator);
	}

	void MockiCerebrum::AddExpectCall_FindConceptWithMatchedDisc( const vector<FindMatchConceptParam>& param, 
		const shared_ptr<ConceptTableCreator> tableCreator, const shared_ptr<ConceptCreator> conceptCreator )
	{
		shared_ptr<ConceptTableCreator> myTableCreator=tableCreator;
		shared_ptr<ConceptCreator> myConceptCreator=conceptCreator;
		if(myConceptCreator==NULL)
		{
			myConceptCreator=shared_ptr<SimpleConceptCreator>(new SimpleConceptCreator());
		}
		if(myTableCreator==NULL)
		{
			myTableCreator=shared_ptr<ConceptTableCreator>(new ConceptTableCreator());
		}


		MockiCerebrum* mockCerebrum=new MockiCerebrum();
		//Default
		EXPECT_CALL(*mockCerebrum,FindConceptWithMatchedDisc(_,_)).WillRepeatedly(Return());

		for (unsigned int i=0;i<param.size();++i)
		{
			FindMatchConceptParam p=param[i];
			AddFindMatchedConceptExpectCall(p.conceptTableStr,p.matchedConceptStr,p.toConceptStr,myTableCreator,myConceptCreator);			
		}
	}

	void MockiCerebrum::AddFindMatchedConceptExpectCall(const string conceptTableStr, const string matchedConceptStr, const string toConceptStr, const shared_ptr<ConceptTableCreator> tableCreator, const shared_ptr<ConceptCreator> conceptCreator)
	{
		//Create the description table to find matched concept.
		shared_ptr<iConceptInteractTable> descTable=tableCreator->SimpleCreate(conceptTableStr);
		//Create the output DescMatchedConceptInfo.
		vector<DescMatchedConceptInfo> matchedInfo;
		DescMatchedConceptInfo info;
		info.matchedConcept=conceptCreator->Create(matchedConceptStr);
		info.toConcept=conceptCreator->Create(toConceptStr);
		matchedInfo.push_back(info);
		//Create MockiCerebrum

		EXPECT_CALL(*this,FindConceptWithMatchedDisc(SameConceptTable(descTable),_))
			.WillRepeatedly(testing::SetArgReferee<1>(matchedInfo));
	}

	void MockiCerebrum::AddExpectCall_Deduce( const string inputTable, const vector<string>& outputResults)
	{
		shared_ptr<ConceptTableCreator> myTableCreator(new ConceptTableCreator());
		shared_ptr<iConceptInteractTable> conceptTable=myTableCreator->SimpleCreate(inputTable);

		vector<shared_ptr<iDeduceResult>> results;
		for (unsigned int i=0;i<outputResults.size();++i)
		{
			shared_ptr<iConceptInteractTable> resTable=myTableCreator->SimpleCreate(outputResults[i]);
			results.push_back(shared_ptr<iDeduceResult>(new DeduceResult<iConceptInteractTable>(resTable)));
		}

		//Any other call will return empty vector.
// 		EXPECT_CALL(*this,Deduce(Matcher<shared_ptr<iConceptInteractTable>>(_)))
// 			.WillRepeatedly(Return(vector<shared_ptr<iDeduceResult>>()));
		//For the designated call.
		EXPECT_CALL(*this,Deduce(Matcher<shared_ptr<iConceptInteractTable>>(SameConceptTable(conceptTable))))
			.WillRepeatedly(Return(results));
	}

	void MockiCerebrum::AddExpectCall_Deduce( const string inputTable, const string& outputResults)
	{
		vector<string> outputResultsVec;
		outputResultsVec.push_back(outputResults);

		AddExpectCall_Deduce(inputTable,outputResultsVec);
	}

	Mind::MockiCerebrum* MockiCerebrum::Create()
	{
		MockiCerebrum* brain= new MockiCerebrum;

		EXPECT_CALL(*brain,FindConceptWithMatchedDisc(_,_)).WillRepeatedly(Return());

		EXPECT_CALL(*brain,Deduce(Matcher<shared_ptr<iConceptInteractTable>>(_)))
			.WillRepeatedly(Return(vector<shared_ptr<iDeduceResult>>()));

		return brain;
	}

}
