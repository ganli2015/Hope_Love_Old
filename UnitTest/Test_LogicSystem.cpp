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

typedef AddPatternToCerebrum Test_Logic;

TEST_F(Test_Logic,Determine)
{
	shared_ptr<RelationNode> conditionRel(new RelationNode());
	shared_ptr<RelationLeaf> resultRel(new RelationLeaf());
	Test_iRelationFun::RelationPair(conditionRel,resultRel);

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

	ASSERT_TRUE(logic.Determine(condition,conclusion_true)==True);
	ASSERT_TRUE(logic.Determine(condition,conclusion_false)==False);
}

