#include "StdAfx.h"
#include "Test_LogicSystem.h"
#include "Test_iRelation.h"

#include "../LogicSystem/Logic.h"
#include "../LogicSystem/CompositeExpression.h"
#include "../LogicSystem/SingleExpression.h"
#include "../LogicSystem/RelationLeaf.h"
#include "../LogicSystem/RelationNode.h"
#include "../LogicSystem/Arbitrariness.h"
#include "../LogicSystem/Symbol.h"
#include "../LogicSystem/LogicStatement.h"
#include "../LogicSystem/Inequality.h"

#include "../Mind/Cerebrum.h"

#include "../MindElement/ConceptInteractTable.h"
#include "../MindElement/Concept.h"

#include "../MindInterface/iCerebrum.h"

#include "../DataCollection/GrammaPattern.h"

#include "FuncForTest.h"

using namespace DataCollection;
using namespace Mind;
using namespace LogicSystem;
using namespace FuncForTest;

typedef Arbitrariness<iConcept> Arb;
typedef LogicType::ConSymbol ConSymbol;
typedef Symbol<iConcept> Sym;

Test_LogicSystem::Test_LogicSystem(void)
{
}


Test_LogicSystem::~Test_LogicSystem(void)
{
}

void Test_LogicSystem::RunTest()
{
	int objCountStart=MyObject::GetObjectCount();

	iCerebrum::SetInstance(Cerebrum::Instance());

	Test_Expression();
	Test_Logic_Determine();
	Test_Relation();

	iCerebrum::KillInstance();

	int objCountEnd=MyObject::GetObjectCount();

//	Check(objCountEnd==objCountStart);
}

void Test_LogicSystem::Test_Expression()
{
// 	iCerebrum* brain=iCerebrum::Instance();
// 	vector<PartOfSpeech> pos;
// 	pos.push_back(Numeral);
// 	pos.push_back(Adjective);
// 	pos.push_back(Preposition);
// 	pos.push_back(Numeral);
// 	GrammarPattern pattern(pos);
// 	for (int i=0;i<200;++i)
// 	{
// 		brain->IncreasePatternFreqency(pos);
// 	}
// 
// 
// 	shared_ptr<SingleExpression> expre(new SingleExpression("二大于一。"));
// 	shared_ptr<iConceptInteractTable> table=expre->GetProtoInteractTable();
// 	vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> relations=table->GetAllRelations();
}

void Test_LogicSystem::Test_Logic_Determine()
{
	FuncForTest::AddGrammarPatternToCerebrum();

	shared_ptr<RelationNode> conditionRel(new RelationNode());
	shared_ptr<RelationLeaf> resultRel(new RelationLeaf());
	Test_iRelation::RelationPair(conditionRel,resultRel);

	//Create logic statement
	shared_ptr<LogicStatement> statement(new LogicStatement(conditionRel,resultRel));

	iCerebrum* brain=iCerebrum::Instance();
	brain->AddLogicStatement(statement);

	Logic logic;

	shared_ptr<CompositeExpression> condition(new CompositeExpression());
	condition->AddExpression("二大于一");
	condition->AddExpression("三大于二");

	shared_ptr<iExpression> conclusion_true(new SingleExpression("三大于一"));
	shared_ptr<iExpression> conclusion_false(new SingleExpression("一大于三"));

	Check(logic.Determine(condition,conclusion_true)==True);
	Check(logic.Determine(condition,conclusion_false)==False);

	brain->KillInstance();
	iCerebrum::SetInstance(Cerebrum::Instance());
}

void Test_LogicSystem::Test_Relation()
{
	Test_iRelation::RunTest();
}




