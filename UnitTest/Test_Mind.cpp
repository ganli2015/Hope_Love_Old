#include "StdAfx.h"
#include "Test_Mind.h"

#include "../Mind/Cerebrum.h"
#include "../Mind/LogicKnowledgeInitializer.h"

#include "../MindElement/Concept.h"

#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iRelation.h"
#include "../MindInterface/iLogicStatement.h"
#include "../MindInterface/iDeduceResult.h"

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

#include <tinyxml.h>

using namespace std;
using namespace Math;
using namespace CommonTool;
using namespace NeuralNetwork;
using namespace DataCollection;
using namespace Mind;
using namespace LogicSystem;

typedef InitCerebrum Test_Concept;
typedef AddPatternToCerebrum Test_LogicKnowledgeInitializer;

TEST_F(Test_Concept,DeepInteraction)
{
	iCerebrum* brain=iCerebrum::Instance();

	Identity iden1;
	iden1.id=0;
	iden1.str="��";
	shared_ptr<iConcept> from=brain->GetConcept(iden1);
	Identity iden2;
	iden2.id=0;
	iden2.str="��";
	shared_ptr<iConcept> to=brain->GetConcept(iden2);

	shared_ptr<iConceptInteractTable> table=from->DeepInteractWith(to);
	table->RemoveDuplicated();

	vector<pair<string,string>> expect;
	expect.push_back(make_pair("��","�̶�"));
	expect.push_back(make_pair("�̶�","�ø�"));
	expect.push_back(make_pair("�ø�","�Է�"));
	expect.push_back(make_pair("��","�ø�"));

	ASSERT_TRUE(FuncForTest::PairSameWithTable(expect,table));

}

TEST_F(Test_Concept,DeepInteraction2)
{
	iCerebrum* brain=iCerebrum::Instance();

	Identity iden1;
	iden1.id=0;
	iden1.str="��";
	shared_ptr<iConcept> from=brain->GetConcept(iden1);
	Identity iden2;
	iden2.id=0;
	iden2.str="��";
	shared_ptr<iConcept> to=brain->GetConcept(iden2);

	shared_ptr<iConceptInteractTable> table=from->DeepInteractWith(to);

	vector<pair<string,string>> expect;
	expect.push_back(make_pair("��","����"));
	expect.push_back(make_pair("��","����"));

	ASSERT_TRUE(FuncForTest::PairSameWithTable(expect,table));
}

TEST_F(Test_LogicKnowledgeInitializer,ParseRelation)
{
	string filename=FuncForTest::TestSampleDir+"Test_LogicKnowledgeInitializer_ParseRelation.txt";
	TiXmlDocument *myDocument = new TiXmlDocument();
	myDocument->LoadFile(filename.c_str());
	TiXmlNode *conditionNode=myDocument->FirstChild("Condition");

	LogicKnowledgeInitializer initer;
	shared_ptr<LogicSystem::iRelation> relation=Test_Mind::ParseRelation(conditionNode,initer);

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
	shared_ptr<LogicSystem::iLogicStatement> statement=Test_Mind::ParseLogicStatement(logicNode,initer);

	//test the deduction of statement 
	shared_ptr<CompositeExpression> condition(new CompositeExpression());
	condition->AddExpression("������һ");
	condition->AddExpression("�����ڶ�");

	shared_ptr<iDeduceResult> deduceResult=statement->Deduce(condition);
	
	shared_ptr<SingleExpression> expect(new SingleExpression("������һ"));
	ASSERT_EQ(deduceResult->Matching(expect),1);
}



shared_ptr<LogicSystem::iRelation> Test_Mind::ParseRelation( const TiXmlNode * node,Mind::LogicKnowledgeInitializer& initer )
{
	return initer.ParseRelation(node);
}

shared_ptr<LogicSystem::iLogicStatement> Test_Mind::ParseLogicStatement( const TiXmlNode * node,Mind::LogicKnowledgeInitializer& initer )
{
	return initer.ParseLogicStatement(node);
}
