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


using namespace std;
using namespace Math;
using namespace CommonTool;
using namespace NeuralNetwork;
using namespace DataCollection;
using namespace LogicSystem;

namespace Mind
{
	const string logicFilename="HopeLoveData//LogicStatements.xml";

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

	TEST(Test_Cerebrum,LogicStatementInitialized)
	{
		MEMOCHECK;

		Cerebrum* brain=Cerebrum::Instance();
		iCerebrum::SetInstance(brain);

		LogicKnowledge* knowledge=new LogicKnowledge();
		LogicKnowledgeInitializer init;
		init.Initialize(logicFilename,knowledge);
		brain->SetLogicKnowledge(knowledge);

		//test the deduction of statement 
		string conditionTable="二-大,大-于,于-一,三-大,大-于,于-二";
		shared_ptr<MockExpression> condition=MockExpression::Create(conditionTable);

		vector<shared_ptr<LogicSystem::iDeduceResult>> deduceResult=brain->Deduce(condition);

		string resultTable="三-大,大-于,于-一";
		shared_ptr<iExpression> expect=MockExpression::Create(resultTable);
		ASSERT_EQ(deduceResult.size(),1);
		ASSERT_EQ(deduceResult.front()->Matching(expect),1);

		iCerebrum::KillInstance();
	}

	Mind::Connection_Info Test_Mind::ParseStrToConnectionInfo( const string line,const Mind::ConceptSet* conceptSet )
	{
		return ConceptSetInitializer::ParseStrToConnectionInfo(line,conceptSet);
	}
}




