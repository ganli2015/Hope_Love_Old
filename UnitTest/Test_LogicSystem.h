#pragma once
#include "PublicHeader.h"

#include "../MindInterface/PublicTypedef.h"
#include "../MindInterface/iCerebrum.h"

#include "../UTFacility/MockiCerebrum.h"

namespace Mind
{
	struct DescMatchedConceptInfo;
	class iConceptInteractTable;
	class MockiCerebrum;
}

class ConceptCreator;
class ConceptTableCreator;

namespace LogicSystem
{
	typedef MindType::ConceptPair ConceptPair;

	class iLogicStatement;
	class iReduceResult;
	class Logic;

	class Test_LogicSystem
	{

	public:

		static void TestLogicStatementDeduce(const shared_ptr<LogicSystem::iLogicStatement> logicStatment,
			const string conditionStr,const string expectResultStr);

		static shared_ptr<iReduceResult> ReduceFromMatchedConcept(const Logic& logic,
			const Mind::DescMatchedConceptInfo& matchedConceptInfo, const vector<ConceptPair>& subPairs,const vector<ConceptPair>& remainingPairs);

	};

	struct Param_LogicResult
	{
		vector<pair<string,string>> tablePairs;
		string conceptStr;
	};

	struct Param_ReduceFromMatchedConcept
	{
		//input
		Mind::DescMatchedConceptInfo matchedInfo;
		vector<ConceptPair> subPairs;
		vector<ConceptPair> remainingPairs;
		//expect
		vector<pair<string,string>> tablePairs;
		string conceptStr;
	};

	class Test_ReduceFromMatchedConcept : public::testing::TestWithParam<Param_ReduceFromMatchedConcept> 
	{
		
	public:
		Test_ReduceFromMatchedConcept(void){};

		static vector<Param_ReduceFromMatchedConcept> GenerateSamples() ;
	protected:
		static ConceptPair MakeConceptPair(const string c1,const string c2,const shared_ptr<ConceptCreator> conceptCreator);
	};

	struct Param_Reduce
	{
		//input
		shared_ptr<Mind::iConceptInteractTable> inputTable;
		Mind::MockiCerebrum* mockCerebrum;
		//expect
		vector<Param_LogicResult> results;
	};

	class Test_Reduce : public::testing::TestWithParam<Param_Reduce> 
	{
	public:

		static vector<Param_Reduce> GenerateSamples() ;
	};

	struct Param_FinalDeduce
	{
		string inputExpreTable;//mock expression of condition
		vector<Mind::MockiCerebrum::FindMatchConceptParam> matchedConceptParam;//data for FindConceptWithMatchedDisc.
		vector<pair<string,string>> condition_deduce;//data for iCerebrum::Deduce
		Param_LogicResult result;//result of final deduce.
	};

	class Test_FinalDeduce : public::testing::TestWithParam<Param_FinalDeduce> 
	{
	public:
		static vector<Param_FinalDeduce> GenerateSamples() ;
	};
}



