#include "StdAfx.h"
#include "Test_Mind.h"

#include "../Mind/Cerebrum.h"
#include "../Mind/ConceptSetInitializer.h"
#include "../Mind/ConceptSet.h"

#include "../MindElement/Concept.h"

#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iRelation.h"
#include "../MindInterface/iLogicStatement.h"
#include "../MindInterface/iDeduceResult.h"
#include "../MindInterface/iLogicElementCreator.h"

#include "../Neural Network Design/CompetitiveNetwork.h"
#include "../Neural Network Design/Neuron_compet.h"

#include "../CommonTools/IOFunction.h"

#include "../Mathmatic/Vector.h"
#include "../Mathmatic/FindSequence.h"
#include "../Mathmatic/MathTool.h"

#include "../DataCollection/GrammardSentence.h"
#include "../DataCollection/LanguageFunc.h"
#include "../DataCollection/Word.h"
#include "../DataCollection/GrammaPattern.h"

#include "../LogicSystem/CompositeExpression.h"
#include "../LogicSystem/SingleExpression.h"
#include "../LogicSystem/LogicKnowledge.h"
#include "../LogicSystem/LogicKnowledgeInitializer.h"

#include "../UTFacility/MockExpression.h"
#include "../UTFacility/ConceptTableCreator.h"

using namespace std;
using namespace Math;
using namespace CommonTool;
using namespace NeuralNetwork;
using namespace DataCollection;
using namespace LogicSystem;

typedef InitCerebrum Test_Cerebrum;

namespace Mind
{
	const string logicFilename="HopeLoveData//LogicStatements.txt";

	TEST_F(Test_Cerebrum, IsInMind_Punctuation)
	{
		ASSERT_TRUE(iCerebrum::Instance()->IsInMind("“"));
		ASSERT_TRUE(iCerebrum::Instance()->IsInMind("，"));
	}

	TEST_F(Test_Cerebrum, GetAllKindsofWord_Punctuation)
	{
		shared_ptr<DataCollection::Word> word(new Word("”"));
		auto words=iCerebrum::Instance()->GetAllKindsofWord(word);
		ASSERT_TRUE(!words.empty());
		ASSERT_TRUE(words.front()->GetString()== "”");
	}

	TEST(Test_ConceptSetInitializer,ParseStrToConnectionInfo)
	{
		MEMOCHECK;

		//Test modifications of single words.
		string line="0 爱 to 0 喜欢 0 深深 0 非常";

		ConceptSet* conceptSet=new ConceptSet();
		Connection_Info info=Test_Mind::ParseStrToConnectionInfo(line,conceptSet);

		Identity expectMe("爱",0);
		Identity expectTo("喜欢",0);
		vector<pair<string,string>> expectMod;
		expectMod.push_back(make_pair("深深","喜欢"));
		expectMod.push_back(make_pair("非常","喜欢"));

		ASSERT_EQ(info.me,expectMe);
		ASSERT_EQ(info.edge_infos[0].to,expectTo);
		ASSERT_TRUE(FuncForTest::PairSameWithTable(expectMod,info.edge_infos[0].modifications));
		delete conceptSet;
	}

	TEST(Test_ConceptSetInitializer,ParseStrToConnectionInfo2)
	{
		MEMOCHECK;

		//Test modifications of a concept interact table.
		string line="0 三 to 0 二 0@二-0@加,0@加-0@一";

		ConceptSet* conceptSet=new ConceptSet();
		Connection_Info info=Test_Mind::ParseStrToConnectionInfo(line,conceptSet);

		Identity expectMe("三",0);
		Identity expectTo("二",0);
		vector<pair<string,string>> expectMod;
		expectMod.push_back(make_pair("二","加"));
		expectMod.push_back(make_pair("加","一"));

		ASSERT_EQ(info.me,expectMe);
		ASSERT_EQ(info.edge_infos[0].to,expectTo);
		ASSERT_TRUE(FuncForTest::PairSameWithTable(expectMod,info.edge_infos[0].modifications));
		delete conceptSet;
	}

	TEST(Test_ConceptSetInitializer,ParseStrToConnectionInfo3)
	{
		MEMOCHECK;

		//Test modifications of a concept interact table.
		string line="0 一 to 0 整数 to 0 零 0@零-0@加,0@加-0@一";

		ConceptSet* conceptSet=new ConceptSet();
		Connection_Info info=Test_Mind::ParseStrToConnectionInfo(line,conceptSet);

		Identity expectMe("一",0);
		Identity expectTo("零",0);
		vector<pair<string,string>> expectMod;
		expectMod.push_back(make_pair("零","加"));
		expectMod.push_back(make_pair("加","一"));

		ASSERT_EQ(info.me,expectMe);
		ASSERT_EQ(info.edge_infos[1].to,expectTo);
		ASSERT_TRUE(FuncForTest::PairSameWithTable(expectMod,info.edge_infos[1].modifications));

		delete conceptSet;
	}

	INSTANTIATE_TEST_CASE_P(Test_Cerebrum, Test_LogicStatementInitialized, testing::ValuesIn(Test_LogicStatementInitialized::GenerateSamples()));

	TEST_P(Test_LogicStatementInitialized,LogicStatementInitialized)
	{
		MEMOCHECK;

		Param_LogicStatementInitialized param=GetParam();

		Cerebrum* brain=Cerebrum::Instance();
		iCerebrum::SetInstance(brain);

		LogicKnowledge* knowledge=new LogicKnowledge();
		LogicKnowledgeInitializer init;
		init.Initialize(logicFilename,knowledge);
		brain->SetLogicKnowledge(knowledge);

		//test the deduction of statement 
		shared_ptr<MockExpression> condition=MockExpression::Create(param.conditionTable);

		vector<shared_ptr<LogicSystem::iDeduceResult>> deduceResult=brain->Deduce(condition);

		shared_ptr<iExpression> expect=MockExpression::Create(param.resultTable);
		ASSERT_EQ(deduceResult.size(),1);
		ASSERT_EQ(deduceResult.front()->Matching(expect),1);

		iCerebrum::KillInstance();
	}

	TEST_F(Test_Cerebrum,FindConceptWithMatchedDisc)
	{
		shared_ptr<ConceptTableCreator> tableCreator(new ConceptTableCreator());

		shared_ptr<iConceptInteractTable> inputTable=tableCreator->SimpleCreate("二-加,加-一");

		vector<DescMatchedConceptInfo> matchedInfo;
		iCerebrum::Instance()->FindConceptWithMatchedDisc(inputTable,matchedInfo);

		ASSERT_EQ(matchedInfo.size(),1);
		ASSERT_EQ(matchedInfo.front().matchedConcept->GetString(),"三");
	}

	Mind::Connection_Info Test_Mind::ParseStrToConnectionInfo( const string line,const Mind::ConceptSet* conceptSet )
	{
		return ConceptSetInitializer::ParseStrToConnectionInfo(line,conceptSet);
	}

	vector<Param_LogicStatementInitialized> Test_LogicStatementInitialized::GenerateSamples()
	{
		vector<Param_LogicStatementInitialized> res;

		{
			Param_LogicStatementInitialized param;
			param.conditionTable="二-大,大-于,于-一,三-大,大-于,于-二";
			param.resultTable="三-大,大-于,于-一";

			res.push_back(param);
		}

		{
			Param_LogicStatementInitialized param;
			param.conditionTable="三-次,次-加,加-一";
			param.resultTable="加-一,加-一,加-一";

			res.push_back(param);
		}

		return res;
	}

}




