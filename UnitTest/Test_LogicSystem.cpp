#include "StdAfx.h"
#include "Test_LogicSystem.h"

#include "../CommonTools/LogWriter.h"

#include "../LogicSystem/Logic.h"
#include "../LogicSystem/RelationLeaf.h"
#include "../LogicSystem/RelationNode.h"
#include "../LogicSystem/Arbitrariness.h"
#include "../LogicSystem/Symbol.h"
#include "../LogicSystem/LogicStatement.h"
#include "../LogicSystem/Number.h"
#include "../LogicSystem/Verb.h"
#include "../LogicSystem/LogicKnowledge.h"
#include "../LogicSystem/LogicKnowledgeInitializer.h"

#include "../Mind/Cerebrum.h"

#include "../MindElement/ConceptInteractTable.h"
#include "../MindElement/Concept.h"

#include "../MindInterface/iDeduceResult.h"
#include "../MindInterface/iLogicElementCreator.h"
#include "../MindInterface/iReduceResult.h"

#include "../UTFacility/ConceptTableCreator.h"
#include "../UTFacility/MockExpression.h"
#include "../UTFacility/RelationSample.h"
#include "../UTFacility/ConceptCreator.h"

#include "FuncForTest.h"
#include <tinyxml.h>

using namespace DataCollection;
using namespace Mind;
using namespace LogicSystem;
using namespace FuncForTest;
using ::testing::Return;
using ::testing::_;
using testing::Matcher;

typedef Arbitrariness<iConcept> Arb;
typedef LogicType::ConSymbol ConSymbol;
typedef Symbol<iConcept> Sym;

typedef InitCerebrum TestF_Logic;
typedef InitCerebrum Test_Number;
typedef InitCerebrum Test_Verb;
typedef InitCerebrum Test_LogicStatement;
typedef AddPatternToCerebrum Test_LogicKnowledgeInitializer;


namespace LogicSystem
{
	TEST_F(Test_LogicKnowledgeInitializer,ParseRelation)
	{
		string filename=FuncForTest::TestSampleDir+"Test_LogicKnowledgeInitializer_ParseRelation.txt";
		TiXmlDocument *myDocument = new TiXmlDocument();
		myDocument->LoadFile(filename.c_str());
		TiXmlNode *conditionNode=myDocument->FirstChild("Condition");

		LogicKnowledgeInitializer initer;
		shared_ptr<LogicSystem::iRelation> relation=Test_LogicSystem::ParseRelation(conditionNode,initer);

		string result=relation->GetString();
		string expect="S0->��,��->��,��->S1";
		ASSERT_EQ(expect,result);
	}

	TEST_F(Test_LogicKnowledgeInitializer,ParseLogicStatement)
	{
		string filename=FuncForTest::TestSampleDir+"Test_LogicKnowledgeInitializer_ParseLogicStatement.txt";
		TiXmlDocument *myDocument = new TiXmlDocument();
		myDocument->LoadFile(filename.c_str());
		TiXmlNode *logicNode=myDocument->FirstChild("LogicStatement");

		LogicKnowledgeInitializer initer;
		shared_ptr<LogicSystem::iLogicStatement> statement=Test_LogicSystem::ParseLogicStatement(logicNode,initer);

		//test the deduction of statement 
		string conditionTable="��-��,��-��,��-һ,��-��,��-��,��-��";
		shared_ptr<MockExpression> condition=MockExpression::Create(conditionTable);

		shared_ptr<iDeduceResult> deduceResult=statement->Deduce(condition);

		string resultTable="��-��,��-��,��-һ";
		shared_ptr<iExpression> expect=MockExpression::Create(resultTable);
		ASSERT_EQ(deduceResult->Matching(expect),1);
	}


	TEST_F(TestF_Logic,Determine)
	{
		shared_ptr<RelationNode> conditionRel(new RelationNode());
		shared_ptr<RelationLeaf> resultRel(new RelationLeaf());
		iRelationSample::RelationPair(conditionRel,resultRel);

		//Create logic statement
		shared_ptr<LogicStatement> statement(new LogicStatement(conditionRel,resultRel));

		iCerebrum* brain=iCerebrum::Instance();
		brain->SetLogicKnowledge(new LogicKnowledge());
		brain->AddLogicStatement(statement);

		Logic logic;

		string conditionStr="��-��,��-��,��-һ,��-��,��-��,��-��";
		shared_ptr<MockExpression> condition=MockExpression::Create(conditionStr);

		string resultStr_true="��-��,��-��,��-һ";
		string resultStr_false="һ-��,��-��,��-��";
		shared_ptr<iExpression> conclusion_true=MockExpression::Create(resultStr_true);
		shared_ptr<iExpression> conclusion_false=MockExpression::Create(resultStr_false);

		ASSERT_TRUE(logic.Determine(condition,conclusion_true)==True);
		ASSERT_TRUE(logic.Determine(condition,conclusion_false)==False);
	}

	TEST_F(Test_Number,Match)
	{
		Identity iden;
		iden.str="��";
		iden.id=0;
		shared_ptr<iConcept> er=iCerebrum::Instance()->GetConcept(iden);

		shared_ptr<Number<iConcept>> num=Number<iConcept>::Create();

		ASSERT_TRUE(num->Match(er));
	}

	TEST_F(Test_Number,ToInt)
	{
		Identity iden;
		iden.str="��";
		iden.id=0;
		shared_ptr<iConcept> san=iCerebrum::Instance()->GetConcept(iden);

		shared_ptr<Number<iConcept>> num=Number<iConcept>::Create();
		num->BindReferredObject(san);

		int resultInt;
		ASSERT_TRUE(num->ToInt(resultInt));
		ASSERT_EQ(resultInt,3);
	}

	TEST_F(Test_Verb,Match)
	{
		Identity iden;
		iden.str="��";
		iden.id=0;
		shared_ptr<iConcept> er=iCerebrum::Instance()->GetConcept(iden);

		shared_ptr<ConSymbol> verb=iLogicElementCreator::CreateSpecialSymbol(iLogicElementCreator::Verb);

		ASSERT_TRUE(verb->Match(er));
	}

	TEST_F(Test_LogicStatement,Deduce)
	{
		///Construct a logicStatment.
		///Input: "��-��,��-��",
		///Output: "��-��,��-һ,��-��,��-��".
		shared_ptr<RelationLeaf> conditionRel(new RelationLeaf());
		shared_ptr<RelationLeaf> resultRel(new RelationLeaf());
		iRelationSample::RelationPair2(conditionRel,resultRel);

		shared_ptr<iLogicStatement> logicStatment(new LogicStatement(conditionRel,resultRel));

		string condition="��-��,��-��";
		string expect="��-��,��-һ,��-��,��-��";
		Test_LogicSystem::TestLogicStatementDeduce(logicStatment,condition,expect);
	}

	TEST_F(Test_LogicStatement,Deduce2)
	{
		///Construct a logicStatment.
		///Input: "��-��,��-��,��-һ",
		///Output: "��-һ,��-һ,��-һ".
		shared_ptr<RelationLeaf> conditionRel(new RelationLeaf());
		shared_ptr<RelationLeaf> resultRel(new RelationLeaf());
		iRelationSample::RelationPair3(conditionRel,resultRel);

		shared_ptr<iLogicStatement> logicStatment(new LogicStatement(conditionRel,resultRel));
		string condition="��-��,��-��,��-һ";
		string expect="��-һ,��-һ,��-һ";
		Test_LogicSystem::TestLogicStatementDeduce(logicStatment,condition,expect);
	}

	TEST_F(Test_LogicStatement,Deduce3)
	{
		///Test if the sub table satisfies the relation, then output deduce result as well as other part of table.
		///Input: "��-��,��-��,һ-��",
		///Output: "��-��,��-һ,��-��,��-��,һ-��".
		shared_ptr<RelationLeaf> conditionRel(new RelationLeaf());
		shared_ptr<RelationLeaf> resultRel(new RelationLeaf());
		iRelationSample::RelationPair2(conditionRel,resultRel);

		shared_ptr<iLogicStatement> logicStatment(new LogicStatement(conditionRel,resultRel));

		string condition="��-��,��-��,һ-��";
		string expect="��-��,��-һ,��-��,��-��,һ-��";
		Test_LogicSystem::TestLogicStatementDeduce(logicStatment,condition,expect);
	}

	TEST_F(Test_LogicStatement,Deduce4)
	{
		///Test if the sub table satisfies the relation, then output deduce result as well as other part of table.
		///Input: "��-��,��-��,��-��",
		///Output: "��-��,��-һ,��-��,��-��,��-��".
		shared_ptr<RelationLeaf> conditionRel(new RelationLeaf());
		shared_ptr<RelationLeaf> resultRel(new RelationLeaf());
		iRelationSample::RelationPair2(conditionRel,resultRel);

		shared_ptr<iLogicStatement> logicStatment(new LogicStatement(conditionRel,resultRel));

		string condition="��-��,��-��,��-��";
		string expect="��-��,��-һ,��-��,��-��,��-��";
		Test_LogicSystem::TestLogicStatementDeduce(logicStatment,condition,expect);
	}

	INSTANTIATE_TEST_CASE_P(Test_Logic, Test_FinalDeduce, testing::ValuesIn(Test_FinalDeduce::GenerateSamples()));

	TEST_P(Test_FinalDeduce,FinalDeduce)
	{
		MemoryChecker mc(__FUNCTION__);
		LOG("FinalDeduce: ");

		Param_FinalDeduce param=GetParam();

		//Create mock expression of condition.
		shared_ptr<MockExpression> expre=MockExpression::SimpleCreate(param.inputExpreTable);

		MockiCerebrum* mockBrain=MockiCerebrum::Create();

		//Prepare data for FindConceptWithMatchedDisc.
		mockBrain->AddExpectCall_FindConceptWithMatchedDisc(param.matchedConceptParam);

		//Prepare data for iCerebrum::Deduce
		for (unsigned int i=0;i<param.condition_deduce.size();++i)
		{
			mockBrain->AddExpectCall_Deduce(param.condition_deduce[i].first,param.condition_deduce[i].second);
		}
		iCerebrum::SetInstance(mockBrain);

		Logic logic;
		vector<shared_ptr<iDeduceResult>> results=logic.FinalDeduce(expre);

		EXPECT_EQ(results.size(),1);

		ASSERT_TRUE(FuncForTest::SameLogicResult(param.result.tablePairs,param.result.conceptStr,results.front()))
			<<"expect: \n"+FuncForTest::TablePairToString(param.result.tablePairs)
			+param.result.conceptStr+"\n"
			+"result: \n"+results.front()->GetString();

		iCerebrum::KillInstance();
	}

	INSTANTIATE_TEST_CASE_P(Test_Logic, Test_ReduceFromMatchedConcept, testing::ValuesIn(Test_ReduceFromMatchedConcept::GenerateSamples()));

	TEST_P(Test_ReduceFromMatchedConcept,ReduceFromMatchedConcept)
	{
		MemoryChecker mc(__FUNCTION__);

		Param_ReduceFromMatchedConcept param=GetParam();
		Logic logic;
		shared_ptr<iReduceResult> result=Test_LogicSystem::ReduceFromMatchedConcept(logic,param.matchedInfo,param.subPairs,param.remainingPairs);
	
		ASSERT_TRUE(FuncForTest::SameLogicResult(param.tablePairs,param.conceptStr,result));
	}

	INSTANTIATE_TEST_CASE_P(Test_Logic, Test_Reduce, testing::ValuesIn(Test_Reduce::GenerateSamples()));

	TEST_P(Test_Reduce,Reduce)
	{
		MemoryChecker mc(__FUNCTION__);

		Param_Reduce param=GetParam();

		iCerebrum::SetInstance(param.mockCerebrum);

		Logic logic;
		vector<shared_ptr<iReduceResult>> results=logic.Reduce(param.inputTable);

		ASSERT_EQ(results.size(),param.results.size());
		for (unsigned int i=0;i<results.size();++i)
		{
			ASSERT_TRUE(FuncForTest::SameLogicResult(param.results[i].tablePairs,param.results[i].conceptStr,results[i]))
				<<"expect: \n"+FuncForTest::TablePairToString(param.results[i].tablePairs)
				+param.results[i].conceptStr+"\n"
				+"result: \n"+results[i]->GetString();
		}
	}

	void Test_LogicSystem::TestLogicStatementDeduce( const shared_ptr<LogicSystem::iLogicStatement> logicStatment, const string conditionStr,const string expectResultStr )
	{
		//Create mock expression of condition.
		shared_ptr<MockExpression> expre=MockExpression::Create(conditionStr);

		shared_ptr<iDeduceResult> result=logicStatment->Deduce(expre);

		//Create mock expression of result.
		shared_ptr<iConceptInteractTable> expectTable=ConceptTableCreator::Create(expectResultStr);
		shared_ptr<iConceptInteractTable> resultTable=result->GetConceptTable();
		ASSERT_TRUE(FuncForTest::SameTable(expectTable,resultTable))
			<<"expect: \n"+expectTable->GetString()
			+"result: \n"+resultTable->GetString();
	}

	shared_ptr<iReduceResult> Test_LogicSystem::ReduceFromMatchedConcept( const Logic& logic, const Mind::DescMatchedConceptInfo& matchedConceptInfo, const vector<ConceptPair>& subPairs,const vector<ConceptPair>& remainingPairs )
	{
		return logic.ReduceFromMatchedConcept(matchedConceptInfo,subPairs,remainingPairs);
	}


	shared_ptr<LogicSystem::iRelation> Test_LogicSystem::ParseRelation( const TiXmlNode * node,LogicKnowledgeInitializer& initer )
	{
		return initer.ParseRelation(node);
	}

	shared_ptr<LogicSystem::iLogicStatement> Test_LogicSystem::ParseLogicStatement( const TiXmlNode * node,LogicKnowledgeInitializer& initer )
	{
		return initer.ParseLogicStatement(node);
	}

	ConceptPair Test_ReduceFromMatchedConcept::MakeConceptPair( const string c1,const string c2,const shared_ptr<ConceptCreator> conceptCreator )
	{
		return make_pair(conceptCreator->Create(c1),conceptCreator->Create(c2));
	}

	vector<Param_ReduceFromMatchedConcept> Test_ReduceFromMatchedConcept::GenerateSamples()
	{
		shared_ptr<ConceptCreator> conceptCreator(new SimpleConceptCreator());
		vector<Param_ReduceFromMatchedConcept> res;

		{
			//��-��,��-һ,��-һ -->  ��-��,��-һ
			Param_ReduceFromMatchedConcept param;
			DescMatchedConceptInfo matchedInfo;
			matchedInfo.matchedConcept=conceptCreator->Create("��");
			matchedInfo.toConcept=conceptCreator->Create("��");
			param.matchedInfo=matchedInfo;

			vector<ConceptPair> subPairs;
			subPairs.push_back(MakeConceptPair("��","��",conceptCreator));
			subPairs.push_back(MakeConceptPair("��","һ",conceptCreator));
			param.subPairs=subPairs;

			vector<ConceptPair> remainingPairs;
			remainingPairs.push_back(MakeConceptPair("��","һ",conceptCreator));
			param.remainingPairs=remainingPairs;

			vector<pair<string,string>> tablePairs;
			tablePairs.push_back(make_pair("��","��"));
			tablePairs.push_back(make_pair("��","һ"));
			param.tablePairs=tablePairs;

			res.push_back(param);
		}

		{
			//��-��,��-һ -->  ��
			Param_ReduceFromMatchedConcept param;
			DescMatchedConceptInfo matchedInfo;
			matchedInfo.matchedConcept=conceptCreator->Create("��");
			matchedInfo.toConcept=conceptCreator->Create("��");
			param.matchedInfo=matchedInfo;

			vector<ConceptPair> subPairs;
			subPairs.push_back(MakeConceptPair("��","��",conceptCreator));
			subPairs.push_back(MakeConceptPair("��","һ",conceptCreator));
			param.subPairs=subPairs;

			vector<ConceptPair> remainingPairs;
			param.remainingPairs=remainingPairs;

			string concept="��";
			param.conceptStr=concept;

			res.push_back(param);
		}

		{
			//����һ,��-�� -->  Null
			Param_ReduceFromMatchedConcept param;
			DescMatchedConceptInfo matchedInfo;
			matchedInfo.matchedConcept=conceptCreator->Create("��");
			matchedInfo.toConcept=conceptCreator->Create("��");
			param.matchedInfo=matchedInfo;

			vector<ConceptPair> subPairs;
			subPairs.push_back(MakeConceptPair("��","��",conceptCreator));
			subPairs.push_back(MakeConceptPair("��","һ",conceptCreator));
			param.subPairs=subPairs;

			vector<ConceptPair> remainingPairs;
			remainingPairs.push_back(MakeConceptPair("��","��",conceptCreator));
			param.remainingPairs=remainingPairs;

			res.push_back(param);
		}


		{
			//��-��,һ-��,һ-�� -->  һ-��,��-��
			Param_ReduceFromMatchedConcept param;
			DescMatchedConceptInfo matchedInfo;
			matchedInfo.matchedConcept=conceptCreator->Create("��");
			matchedInfo.toConcept=conceptCreator->Create("��");
			param.matchedInfo=matchedInfo;

			vector<ConceptPair> subPairs;
			subPairs.push_back(MakeConceptPair("��","��",conceptCreator));
			subPairs.push_back(MakeConceptPair("һ","��",conceptCreator));
			param.subPairs=subPairs;

			vector<ConceptPair> remainingPairs;
			remainingPairs.push_back(MakeConceptPair("һ","��",conceptCreator));
			param.remainingPairs=remainingPairs;

			vector<pair<string,string>> tablePairs;
			tablePairs.push_back(make_pair("��","��"));
			tablePairs.push_back(make_pair("һ","��"));
			param.tablePairs=tablePairs;

			res.push_back(param);
		}

		{
			//һ-��,��-�� -->  ��
			Param_ReduceFromMatchedConcept param;
			DescMatchedConceptInfo matchedInfo;
			matchedInfo.matchedConcept=conceptCreator->Create("��");
			matchedInfo.toConcept=conceptCreator->Create("��");
			param.matchedInfo=matchedInfo;

			vector<ConceptPair> subPairs;
			subPairs.push_back(MakeConceptPair("һ","��",conceptCreator));
			subPairs.push_back(MakeConceptPair("��","��",conceptCreator));
			param.subPairs=subPairs;

			vector<ConceptPair> remainingPairs;
			param.remainingPairs=remainingPairs;

			string concept="��";
			param.conceptStr=concept;

			res.push_back(param);
		}

		{
			//һ�Ӷ�,��-�� -->  Null
			Param_ReduceFromMatchedConcept param;
			DescMatchedConceptInfo matchedInfo;
			matchedInfo.matchedConcept=conceptCreator->Create("��");
			matchedInfo.toConcept=conceptCreator->Create("��");
			param.matchedInfo=matchedInfo;

			vector<ConceptPair> subPairs;
			subPairs.push_back(MakeConceptPair("һ","��",conceptCreator));
			subPairs.push_back(MakeConceptPair("��","��",conceptCreator));
			param.subPairs=subPairs;

			vector<ConceptPair> remainingPairs;
			remainingPairs.push_back(MakeConceptPair("��","��",conceptCreator));
			param.remainingPairs=remainingPairs;

			res.push_back(param);
		}

		return res;
	}


	vector<Param_Reduce> Test_Reduce::GenerateSamples()
	{
		shared_ptr<ConceptTableCreator> tableCreator(new ConceptTableCreator());
		shared_ptr<ConceptCreator> conceptCreator(new SimpleConceptCreator());
		vector<Param_Reduce> res;

		{
			//��-��,��-һ,��-һ  --> ��-��,��-һ
			Param_Reduce param;
			param.inputTable=tableCreator->SimpleCreate("��-��,��-һ,��-һ");

			param.mockCerebrum=MockiCerebrum::Create();
			param.mockCerebrum->AddExpectCall_FindConceptWithMatchedDisc("��-��,��-һ",
				"��",
				"��",
				tableCreator,
				conceptCreator);

			//Create result.
			vector<Param_LogicResult> results;
			Param_LogicResult resP;
			vector<pair<string,string>> tablePairs;
			tablePairs.push_back(make_pair("��","��"));
			tablePairs.push_back(make_pair("��","һ"));
			resP.tablePairs=tablePairs;
			results.push_back( resP);
			//The second one is the same as the first.
			Param_LogicResult resP2;
			resP2.tablePairs=tablePairs;
			results.push_back( resP2);
			param.results=results;

			res.push_back(param);
		}

		{
			//��-��,��-һ,��-һ,��-һ  --> ��-��,��-һ,��-һ
			Param_Reduce param;
			param.inputTable=tableCreator->SimpleCreate("��-��,��-һ,��-һ,��-һ");

			param.mockCerebrum=MockiCerebrum::Create();
			param.mockCerebrum->AddExpectCall_FindConceptWithMatchedDisc("��-��,��-һ",
				"��",
				"��",
				tableCreator,
				conceptCreator);

			//Create result.
			vector<Param_LogicResult> results;
			Param_LogicResult resP;
			vector<pair<string,string>> tablePairs;
			tablePairs.push_back(make_pair("��","��"));
			tablePairs.push_back(make_pair("��","һ"));
			tablePairs.push_back(make_pair("��","һ"));
			resP.tablePairs=tablePairs;
			results.push_back( resP);
			//The second one is the same as the first.
			Param_LogicResult resP2;
			resP2.tablePairs=tablePairs;
			results.push_back( resP2);
			//The third is tha same too.
			Param_LogicResult resP3;
			resP3.tablePairs=tablePairs;
			results.push_back( resP3);
			param.results=results;

			res.push_back(param);
		}

		{
			//��-��,��-һ  --> ��
			Param_Reduce param;
			param.inputTable=tableCreator->SimpleCreate("��-��,��-һ");

			param.mockCerebrum=MockiCerebrum::Create();
			param.mockCerebrum->AddExpectCall_FindConceptWithMatchedDisc("��-��,��-һ",
				"��",
				"��",
				tableCreator,
				conceptCreator);

			//Create result.
			vector<Param_LogicResult> results;
			Param_LogicResult resP;
			string conceptStr="��";
			resP.conceptStr=conceptStr;
			results.push_back( resP);
			
			param.results=results;

			res.push_back(param);
		}

		return res;
	}

	vector<Param_FinalDeduce> Test_FinalDeduce::GenerateSamples()
	{
		typedef MockiCerebrum::FindMatchConceptParam FindMatchConceptParam;

		vector<Param_FinalDeduce> res;

		{
			//������������
			Param_FinalDeduce param;
			param.inputExpreTable="��-��,��-��";

			vector<FindMatchConceptParam> matchedParams;
			matchedParams.push_back(FindMatchConceptParam("��-��,��-һ","��","��"));
			matchedParams.push_back(FindMatchConceptParam("��-��,��-һ","��","��"));
			matchedParams.push_back(FindMatchConceptParam("��-��,��-һ","��","��"));
			param.matchedConceptParam=matchedParams;

			string condition="��-��,��-��";
			string deduceRes="��-��,��-һ,��-��,��-��";
			param.condition_deduce.push_back(make_pair(condition,deduceRes));
			string condition2="��-��,��-��,��-��,��-һ";
			string deduceRes2="��-��,��-һ,��-һ,��-һ";
			param.condition_deduce.push_back(make_pair(condition2,deduceRes2));

			param.result.conceptStr="��";

			res.push_back(param);
		}

		{
			//������������
			Param_FinalDeduce param;
			param.inputExpreTable="��-��,��-��";

			string condition="��-��,��-��";
			string deduceRes="��-��,��-��,��-��,��-��";
			param.condition_deduce.push_back(make_pair(condition,deduceRes));
			string condition2="��-��,��-��,��-��,��-��";
			string deduceRes2="��-��,��-��,��-��";
			param.condition_deduce.push_back(make_pair(condition2,deduceRes2));

			vector<FindMatchConceptParam> matchedParams;
			matchedParams.push_back(FindMatchConceptParam("��-��,��-��","��","��"));
			matchedParams.push_back(FindMatchConceptParam("��-��,��-��","��","��"));
			param.matchedConceptParam=matchedParams;

			param.result.conceptStr="��";

			res.push_back(param);
		}


		return res;
	}

}

