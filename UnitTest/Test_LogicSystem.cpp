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
#include "../LogicSystem/Verb.h"

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
#include "../UTFacility/RelationSample.h"

#include "FuncForTest.h"

using namespace DataCollection;
using namespace Mind;
using namespace LogicSystem;
using namespace FuncForTest;
using ::testing::Return;

typedef Arbitrariness<iConcept> Arb;
typedef LogicType::ConSymbol ConSymbol;
typedef Symbol<iConcept> Sym;

typedef InitCerebrum Test_Logic;
typedef InitCerebrum Test_Number;
typedef InitCerebrum Test_Verb;
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

	string conditionStr="二-大,大-于,于-一,三-大,大-于,于-二";
	shared_ptr<MockExpression> condition=MockExpression::Create(conditionStr);

	string resultStr_true="三-大,大-于,于-一";
	string resultStr_false="一-大,大-于,于-三";
	shared_ptr<iExpression> conclusion_true=MockExpression::Create(resultStr_true);
	shared_ptr<iExpression> conclusion_false=MockExpression::Create(resultStr_false);

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

TEST_F(Test_Verb,Match)
{
	Identity iden;
	iden.str="加";
	iden.id=0;
	shared_ptr<iConcept> er=iCerebrum::Instance()->GetConcept(iden);

	shared_ptr<ConSymbol> verb=iLogicElementCreator::CreateSpecialSymbol(iLogicElementCreator::Verb);

	ASSERT_TRUE(verb->Match(er));
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

	string condition="二-加,加-三";
	string expect="二-加,加-一,三-次,次-加";
	Test_LogicSystem::TestLogicStatementDeduce(logicStatment,condition,expect);
}

TEST_F(Test_LogicStatement,Deduce2)
{
	///Construct a logicStatment.
	///Input: "三-次,次-加,加-一",
	///Output: "加-一,加-一,加-一".
	shared_ptr<RelationLeaf> conditionRel(new RelationLeaf());
	shared_ptr<RelationLeaf> resultRel(new RelationLeaf());
	iRelationSample::RelationPair3(conditionRel,resultRel);

	shared_ptr<iLogicStatement> logicStatment(new LogicStatement(conditionRel,resultRel));
	string condition="三-次,次-加,加-一";
	string expect="加-一,加-一,加-一";
	Test_LogicSystem::TestLogicStatementDeduce(logicStatment,condition,expect);
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

void Test_LogicSystem::TestLogicStatementDeduce( const shared_ptr<LogicSystem::iLogicStatement> logicStatment, const string conditionStr,const string expectResultStr )
{
	//Create mock expression of condition.
	shared_ptr<MockExpression> expre=MockExpression::Create(conditionStr);

	shared_ptr<iDeduceResult> result=logicStatment->Deduce(expre);

	//Create mock expression of result.
	shared_ptr<iConceptInteractTable> expectTable=ConceptTableCreator::Create(expectResultStr);

	ASSERT_TRUE(FuncForTest::SameTable(expectTable,result->GetConceptTable()));
}
