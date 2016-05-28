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
#include "../LogicSystem/Number.h"

#include "../Mind/Cerebrum.h"

#include "../MindElement/ConceptInteractTable.h"
#include "../MindElement/Concept.h"

#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iDeduceResult.h"
#include "../MindInterface/iLogicElementCreator.h"

#include "../DataCollection/GrammaPattern.h"

#include "../UTFacility/ConceptTableCreator.h"
#include "../UTFacility/MockExpression.h"

#include "FuncForTest.h"

using namespace DataCollection;
using namespace Mind;
using namespace LogicSystem;
using namespace FuncForTest;
using ::testing::Return;

typedef Arbitrariness<iConcept> Arb;
typedef LogicType::ConSymbol ConSymbol;
typedef Symbol<iConcept> Sym;

typedef AddPatternToCerebrum Test_Logic;
typedef InitCerebrum Test_Number;
typedef InitCerebrum Test_LogicStatement;

TEST_F(Test_Logic,Determine)
{
	shared_ptr<RelationNode> conditionRel(new RelationNode());
	shared_ptr<RelationLeaf> resultRel(new RelationLeaf());
	iRelationSample::RelationPair(conditionRel,resultRel);

	//Create logic statement
	shared_ptr<LogicStatement> statement(new LogicStatement(conditionRel,resultRel));

	iCerebrum* brain=iCerebrum::Instance();
	brain->AddLogicStatement(statement);

	Logic logic;

	vector<string> conditionStr;
	conditionStr.push_back("二大于一");
	conditionStr.push_back("三大于二");
	shared_ptr<iExpression> condition(iLogicElementCreator::CreateExpression(conditionStr));

	shared_ptr<iExpression> conclusion_true(iLogicElementCreator::CreateExpression("三大于一"));
	shared_ptr<iExpression> conclusion_false(iLogicElementCreator::CreateExpression("一大于三"));

	ASSERT_TRUE(logic.Determine(condition,conclusion_true)==True);
	ASSERT_TRUE(logic.Determine(condition,conclusion_false)==False);
}

TEST_F(Test_Number,Match)
{
	Identity iden;
	iden.str="二";
	iden.id=0;
	shared_ptr<iConcept> er=iCerebrum::Instance()->GetConcept(iden);

	shared_ptr<Number<iConcept>> num=Number<iConcept>::Create();

	ASSERT_TRUE(num->Match(er));
}

TEST_F(Test_LogicStatement,Deduce)
{
	///Construct a logicStatment.
	///Input: "二-加,加-三",
	///Output: "二-加,加-一,三-次,次-加".
	shared_ptr<RelationLeaf> conditionRel(new RelationLeaf());
	shared_ptr<RelationLeaf> resultRel(new RelationLeaf());
	iRelationSample::RelationPair2(conditionRel,resultRel);

	shared_ptr<iLogicStatement> logicStatment(new LogicStatement(conditionRel,resultRel));
	//Create mock expression of condition.
	string tableStr="二-加,加-三";
	shared_ptr<iConceptInteractTable> table=ConceptTableCreator::Create(tableStr);
	shared_ptr<MockExpression> expre(new MockExpression());
	EXPECT_CALL(*expre,GetProtoInteractTable()).WillRepeatedly(Return(table));
	EXPECT_CALL(*expre,GetBaseInteractTable()).Times(0);

	shared_ptr<iDeduceResult> result=logicStatment->Deduce(expre);

	//Create mock expression of result.
	string resTableStr="二-加,加-一,三-次,次-加";
	shared_ptr<iConceptInteractTable> expectTable=ConceptTableCreator::Create(resTableStr);
	shared_ptr<MockExpression> expect(new MockExpression());
	EXPECT_CALL(*expect,GetProtoInteractTable()).WillRepeatedly(Return(expectTable));
	EXPECT_CALL(*expect,GetBaseInteractTable()).Times(0);

	ASSERT_TRUE(result->Matching(expect)==1);
}

TEST_F(Test_Logic,Deduce)
{
	//Create mock expression of condition.
	string tableStr="二-加,加-三";
	shared_ptr<iConceptInteractTable> table=ConceptTableCreator::Create(tableStr);
	shared_ptr<MockExpression> expre(new MockExpression());
	EXPECT_CALL(*expre,GetProtoInteractTable()).WillRepeatedly(Return(table));
	EXPECT_CALL(*expre,GetBaseInteractTable()).Times(0);

	Logic logic;
	vector<shared_ptr<iDeduceResult>> results=logic.FinalDeduce(expre);

	ASSERT_EQ(results.size(),1);

	shared_ptr<iExpression> expect(iLogicElementCreator::CreateExpression("五"));
	ASSERT_TRUE(results.front()->Matching(expect)==1);
}