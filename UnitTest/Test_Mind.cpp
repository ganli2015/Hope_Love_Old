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
		string line="0 �� to 0 ϲ�� 0 ���� 0 �ǳ�";

		ConceptSet* conceptSet=new ConceptSet();
		Connection_Info info=Test_Mind::ParseStrToConnectionInfo(line,conceptSet);

		Identity expectMe("��",0);
		Identity expectTo("ϲ��",0);
		vector<pair<string,string>> expectMod;
		expectMod.push_back(make_pair("����","ϲ��"));
		expectMod.push_back(make_pair("�ǳ�","ϲ��"));

		ASSERT_EQ(info.me,expectMe);
		ASSERT_EQ(info.edge_infos[0].to,expectTo);
		ASSERT_TRUE(FuncForTest::PairSameWithTable(expectMod,info.edge_infos[0].modifications));
		delete conceptSet;
	}

	TEST(Test_ConceptSetInitializer,ParseStrToConnectionInfo2)
	{
		MEMOCHECK;

		//Test modifications of a concept interact table.
		string line="0 �� to 0 �� 0@��-0@��,0@��-0@һ";

		ConceptSet* conceptSet=new ConceptSet();
		Connection_Info info=Test_Mind::ParseStrToConnectionInfo(line,conceptSet);

		Identity expectMe("��",0);
		Identity expectTo("��",0);
		vector<pair<string,string>> expectMod;
		expectMod.push_back(make_pair("��","��"));
		expectMod.push_back(make_pair("��","һ"));

		ASSERT_EQ(info.me,expectMe);
		ASSERT_EQ(info.edge_infos[0].to,expectTo);
		ASSERT_TRUE(FuncForTest::PairSameWithTable(expectMod,info.edge_infos[0].modifications));
		delete conceptSet;
	}

	TEST(Test_ConceptSetInitializer,ParseStrToConnectionInfo3)
	{
		MEMOCHECK;

		//Test modifications of a concept interact table.
		string line="0 һ to 0 ���� to 0 �� 0@��-0@��,0@��-0@һ";

		ConceptSet* conceptSet=new ConceptSet();
		Connection_Info info=Test_Mind::ParseStrToConnectionInfo(line,conceptSet);

		Identity expectMe("һ",0);
		Identity expectTo("��",0);
		vector<pair<string,string>> expectMod;
		expectMod.push_back(make_pair("��","��"));
		expectMod.push_back(make_pair("��","һ"));

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
		string conditionTable="��-��,��-��,��-һ,��-��,��-��,��-��";
		shared_ptr<MockExpression> condition=MockExpression::Create(conditionTable);

		vector<shared_ptr<LogicSystem::iDeduceResult>> deduceResult=brain->Deduce(condition);

		string resultTable="��-��,��-��,��-һ";
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




