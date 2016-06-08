#include "StdAfx.h"
#include "Test_iRelation.h"

#include "../LogicSystem/Logic.h"
#include "../LogicSystem/CompositeExpression.h"
#include "../LogicSystem/SingleExpression.h"
#include "../LogicSystem/RelationLeaf.h"
#include "../LogicSystem/RelationNode.h"
#include "../LogicSystem/Arbitrariness.h"
#include "../LogicSystem/Number.h"
#include "../LogicSystem/Symbol.h"
#include "../LogicSystem/Inequality.h"
#include "../LogicSystem/Equality.h"

#include "../MindElement/ConceptInteractTable.h"
#include "../MindElement/Concept.h"

#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/PublicTypedef.h"
#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iMindElementCreator.h"
#include "../MindInterface/iLogicElementCreator.h"

#include "../Mind/Cerebrum.h"

#include "../DataCollection/GrammaPattern.h"

#include "../UTFacility/LeafCreator.h"
#include "../UTFacility/ConceptCreator.h"
#include "../UTFacility/SymbolCreator.h"
#include "../UTFacility/RelationSample.h"
#include "../UTFacility/ConceptTableCreator.h"

#include "FuncForTest.h"

using namespace DataCollection;
using namespace Mind;
using namespace LogicSystem;
using namespace FuncForTest;

typedef Arbitrariness<iConcept> Arb;
typedef Number<iConcept> Num;
typedef LogicType::ConSymbol ConSymbol;
typedef Symbol<iConcept> Sym;


TEST_F(Test_iRelation,GetString1)
{
	Test_iRelation::ClearArbNum();
	shared_ptr<iRelationNode> node=iRelationSample::RelationSample1();

	string result=node->GetString();
	string expect="(S0->大,大->于,于->S1)&&(S1->大,大->于,于->S2)";
	ASSERT_EQ(result,expect);
}

TEST_F(Test_iRelation,GetString2)
{
	Test_iRelation::ClearArbNum();

	shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
	shared_ptr<Arb> arb1=Arb::Create();
	shared_ptr<Arb> arb2=Arb::Create();
	leaf1->AddRelation(arb1,arb2);
	shared_ptr<RelationLeaf> leaf2(new RelationLeaf());
	shared_ptr<Arb> arb3=Arb::Create();
	shared_ptr<Arb> arb4=Arb::Create();
	leaf2->AddRelation(arb3,arb4);
	shared_ptr<iRelationNode> node1(new RelationNode());
	node1->AddSubRelation(leaf1);
	node1->AddSubRelation(leaf2);
	node1->SetState(iRelationNode::And);

	shared_ptr<RelationLeaf> leaf3(new RelationLeaf());
	shared_ptr<Arb> arb5=Arb::Create();
	shared_ptr<Arb> arb6=Arb::Create();
	leaf3->AddRelation(arb5,arb6);
	shared_ptr<RelationLeaf> leaf4(new RelationLeaf());
	shared_ptr<Arb> arb7=Arb::Create();
	shared_ptr<Arb> arb8=Arb::Create();
	leaf4->AddRelation(arb7,arb8);
	shared_ptr<iRelationNode> node2(new RelationNode());
	node2->AddSubRelation(leaf3);
	node2->AddSubRelation(leaf4);
	node2->SetState(iRelationNode::And);

	shared_ptr<iRelationNode> node3(new RelationNode());
	node3->AddSubRelation(node1);
	node3->AddSubRelation(node2);
	node3->SetState(iRelationNode::Or);

	string result=node3->GetString();
	string expect="((S0->S1)&&(S2->S3))||((S4->S5)&&(S6->S7))";
	ASSERT_EQ(result,expect);
}

TEST_F(Test_iRelation,RelationLeafSatisfy)
{
	//InterTableSatisfyRelation
	shared_ptr<iConcept> san=_conceptCreator->Create("三");
	shared_ptr<iConcept> da=_conceptCreator->Create("大");
	shared_ptr<iConcept> yu=_conceptCreator->Create("于");
	shared_ptr<iConcept> er=_conceptCreator->Create("二");

	string leafStr="三-大,大-于,于-二";
	shared_ptr<RelationLeaf> leaf1=LeafCreator::SimpleCreate(leafStr);

	shared_ptr<iConceptInteractTable> interTable=iMindElementCreator::CreateConceptInteractTable();
	interTable->Add(san,da);
	interTable->Add(da,yu);
	interTable->Add(yu,er);

	ASSERT_TRUE(InterTableSatisfyRelation(leaf1,interTable));

}

TEST_F(Test_iRelation,RelationLeafSatisfy2)
{
	//AddConstraint
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("三");
		shared_ptr<iConcept> da=_conceptCreator->Create("大");
		shared_ptr<iConcept> yu=_conceptCreator->Create("于");
		shared_ptr<iConcept> san2=_conceptCreator->Create("三");

		shared_ptr<Arb> arb1=Arb::Create();
		shared_ptr<Sym> s1(new Sym(da));
		shared_ptr<Sym> s2(new Sym(yu));
		shared_ptr<Arb> arb2=Arb::Create();	

		shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
		leaf1->AddRelation(arb1,s1);
		leaf1->AddRelation(s1,s2);
		leaf1->AddRelation(s2,arb2);
		leaf1->AddConstraint(Inequality::Create(arb1,arb2));

		shared_ptr<iConceptInteractTable> interTable=iMindElementCreator::CreateConceptInteractTable();
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,san2);

		ASSERT_FALSE(InterTableSatisfyRelation(leaf1,interTable));

	}
	
}

TEST_F(Test_iRelation,RelationLeafSatisfy3)
{
	//InterTableSatisfyRelation
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("三");
		shared_ptr<iConcept> da=_conceptCreator->Create("大");
		shared_ptr<iConcept> yu=_conceptCreator->Create("于");
		shared_ptr<iConcept> er=_conceptCreator->Create("二");
		shared_ptr<iConcept> yi=_conceptCreator->Create("一");
		shared_ptr<iConcept> si=_conceptCreator->Create("四");

		shared_ptr<Arb> arb1=Arb::Create();
		shared_ptr<Sym> s1(new Sym(da));
		shared_ptr<Sym> s2(new Sym(yu));
		shared_ptr<Arb> arb2=Arb::Create();	

		shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
		leaf1->AddRelation(arb1,s1);
		leaf1->AddRelation(s1,s2);
		leaf1->AddRelation(s2,arb2);

		shared_ptr<iConceptInteractTable> interTable=iMindElementCreator::CreateConceptInteractTable();
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);
		interTable->Add(er,yi);
		interTable->Add(si,da);
		interTable->Add(san,si);

		ASSERT_TRUE(InterTableSatisfyRelation(leaf1,interTable));

	}	
}

TEST_F(Test_iRelation,RelationLeafSatisfy4)
{
	//InterTableSatisfyRelation
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("三");
		shared_ptr<iConcept> da=_conceptCreator->Create("大");
		shared_ptr<iConcept> yu=_conceptCreator->Create("于");
		shared_ptr<iConcept> er=_conceptCreator->Create("二");
		shared_ptr<iConcept> yi=_conceptCreator->Create("一");
		shared_ptr<iConcept> si=_conceptCreator->Create("四");

		shared_ptr<Arb> arb1=Arb::Create();
		shared_ptr<Sym> s1(new Sym(da));
		shared_ptr<Sym> s2(new Sym(yu));
		shared_ptr<Arb> arb2=Arb::Create();	

		shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
		leaf1->AddRelation(arb1,s1);
		leaf1->AddRelation(s1,s2);
		leaf1->AddRelation(s2,arb2);

		shared_ptr<iConceptInteractTable> interTable=iMindElementCreator::CreateConceptInteractTable();
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(si,er);

		ASSERT_FALSE(InterTableSatisfyRelation(leaf1,interTable));

	}
}

TEST_F(Test_iRelation,RelationLeafSatisfy5)
{
	//If relation contains numbers of the same pairs, then iConceptInteractTable containing the same number of pairs will satisfy the relation.
	
	//Add three same pairs of s1,s2
	string leafStr="三-四,三-四,三-四";
	shared_ptr<RelationLeaf> leaf1=LeafCreator::SimpleCreate(leafStr);

	string tableStr="三-四";
	shared_ptr<iConceptInteractTable> interTable=ConceptTableCreator::SimpleCreate(tableStr);

	ASSERT_FALSE(InterTableSatisfyRelation(leaf1,interTable));
}

TEST_F(Test_iRelation,RelationLeafSatisfy6)
{
	//If one of the relation satisfy and another fails, then expect not to satisfy.

	string leafStr="三-四,四-五";
	shared_ptr<RelationLeaf> leaf1=LeafCreator::SimpleCreate(leafStr);

	string tableStr="三-四,五-六";
	shared_ptr<iConceptInteractTable> interTable=ConceptTableCreator::SimpleCreate(tableStr);

	ASSERT_FALSE(InterTableSatisfyRelation(leaf1,interTable));
}

TEST_F(Test_iRelation,Test_RelationNodeSatisfy)
{
	//"三大于二" and "二大于一"
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("三");
		shared_ptr<iConcept> da=_conceptCreator->Create("大");
		shared_ptr<iConcept> yu=_conceptCreator->Create("于");
		shared_ptr<iConcept> er=_conceptCreator->Create("二");
		shared_ptr<iConcept> yi=_conceptCreator->Create("一");

		shared_ptr<iConceptInteractTable> interTable=iMindElementCreator::CreateConceptInteractTable();
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);
		interTable->Add(er,da);
		interTable->Add(da,yu);
		interTable->Add(yu,yi);

		shared_ptr<RelationNode> relation=iRelationSample::RelationSample1();

		ASSERT_TRUE(InterTableSatisfyRelation(relation,interTable));

	}

}

TEST_F(Test_iRelation,Test_RelationNodeSatisfy2)
{

	//"三大于二" and "二小于一"
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("三");
		shared_ptr<iConcept> da=_conceptCreator->Create("大");
		shared_ptr<iConcept> yu=_conceptCreator->Create("于");
		shared_ptr<iConcept> er=_conceptCreator->Create("二");
		shared_ptr<iConcept> yi=_conceptCreator->Create("一");
		shared_ptr<iConcept> xiao=_conceptCreator->Create("小");

		shared_ptr<iConceptInteractTable> interTable=iMindElementCreator::CreateConceptInteractTable();
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);
		interTable->Add(er,xiao);
		interTable->Add(xiao,yu);
		interTable->Add(yu,yi);

		shared_ptr<RelationNode> relation=iRelationSample::RelationSample1();

		ASSERT_FALSE(InterTableSatisfyRelation(relation,interTable));

	}

}

TEST_F(Test_iRelation,Test_RelationNodeSatisfy3)
{

	//"三大于二" and "二大于一" with perturbation
	{		
		shared_ptr<iConcept> san=_conceptCreator->Create("三");
		shared_ptr<iConcept> da=_conceptCreator->Create("大");
		shared_ptr<iConcept> yu=_conceptCreator->Create("于");
		shared_ptr<iConcept> er=_conceptCreator->Create("二");
		shared_ptr<iConcept> yi=_conceptCreator->Create("一");
		shared_ptr<iConcept> si=_conceptCreator->Create("四");
		shared_ptr<iConcept> wu=_conceptCreator->Create("五");
		shared_ptr<iConcept> liu=_conceptCreator->Create("六");

		shared_ptr<iConceptInteractTable> interTable=iMindElementCreator::CreateConceptInteractTable();
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);
		interTable->Add(er,da);
		interTable->Add(da,yu);
		interTable->Add(yu,yi);
		interTable->Add(si,da);
		interTable->Add(san,liu);
		interTable->Add(wu,yu);

		shared_ptr<RelationNode> relation=iRelationSample::RelationSample1();

		ASSERT_TRUE(InterTableSatisfyRelation(relation,interTable));
	}
	
}

TEST_F(Test_iRelation,Test_RelationNodeSatisfy4)
{
	//"三大于二" and "二小于一" with perturbation
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("三");
		shared_ptr<iConcept> da=_conceptCreator->Create("大");
		shared_ptr<iConcept> yu=_conceptCreator->Create("于");
		shared_ptr<iConcept> er=_conceptCreator->Create("二");
		shared_ptr<iConcept> yi=_conceptCreator->Create("一");
		shared_ptr<iConcept> xiao=_conceptCreator->Create("小");

		shared_ptr<iConceptInteractTable> interTable=iMindElementCreator::CreateConceptInteractTable();
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);
		interTable->Add(er,xiao);
		interTable->Add(xiao,yu);
		interTable->Add(yu,yi);
		interTable->Add(er,da);

		shared_ptr<RelationNode> relation=iRelationSample::RelationSample1();

		ASSERT_FALSE(InterTableSatisfyRelation(relation,interTable));
	}
	
}

TEST_F(Test_iRelation,Test_RelationNodeSatisfy5)
{
	//"三大于二" or "二大于一"
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("三");
		shared_ptr<iConcept> da=_conceptCreator->Create("大");
		shared_ptr<iConcept> yu=_conceptCreator->Create("于");
		shared_ptr<iConcept> er=_conceptCreator->Create("二");
		shared_ptr<iConcept> yi=_conceptCreator->Create("一");

		shared_ptr<iConceptInteractTable> interTable=iMindElementCreator::CreateConceptInteractTable();
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);
		interTable->Add(er,da);
		interTable->Add(da,yu);
		interTable->Add(yu,yi);

		shared_ptr<RelationNode> relation=iRelationSample::RelationSample2();

		ASSERT_TRUE(InterTableSatisfyRelation(relation,interTable));
	}
	
}

TEST_F(Test_iRelation,Test_RelationNodeSatisfy6)
{
	//"三大于二" or "二大于一"
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("三");
		shared_ptr<iConcept> da=_conceptCreator->Create("大");
		shared_ptr<iConcept> yu=_conceptCreator->Create("于");
		shared_ptr<iConcept> er=_conceptCreator->Create("二");
		shared_ptr<iConcept> yi=_conceptCreator->Create("一");

		shared_ptr<iConceptInteractTable> interTable=iMindElementCreator::CreateConceptInteractTable();
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);

		shared_ptr<RelationNode> relation=iRelationSample::RelationSample2();

		ASSERT_TRUE(InterTableSatisfyRelation(relation,interTable));
	}
	
}

TEST_F(Test_iRelation,Test_RelationNodeSatisfy7)
{
	//"三大于二" or "二大于一"
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("三");
		shared_ptr<iConcept> xiao=_conceptCreator->Create("小");
		shared_ptr<iConcept> yu=_conceptCreator->Create("于");
		shared_ptr<iConcept> er=_conceptCreator->Create("二");
		shared_ptr<iConcept> yi=_conceptCreator->Create("一");

		shared_ptr<iConceptInteractTable> interTable=iMindElementCreator::CreateConceptInteractTable();
		interTable->Add(san,xiao);
		interTable->Add(xiao,yu);
		interTable->Add(yu,er);
		interTable->Add(er,xiao);
		interTable->Add(xiao,yu);
		interTable->Add(yu,yi);

		shared_ptr<RelationNode> relation=iRelationSample::RelationSample2();

		ASSERT_FALSE(InterTableSatisfyRelation(relation,interTable));
	}
}

TEST_F(Test_iRelation,GenerateConceptTable)
{
	string leafStr="三-大,大-于,于-二";
	shared_ptr<RelationLeaf> leaf=LeafCreator::SimpleCreate(leafStr);

	shared_ptr<iConceptInteractTable> result=leaf->GenerateConceptTable();

	vector<pair<string,string>> expect;
	expect.push_back(make_pair("三","大"));
	expect.push_back(make_pair("大","于"));
	expect.push_back(make_pair("于","二"));

	ASSERT_TRUE(FuncForTest::PairSameWithTable(expect,result));
}

typedef AddPatternToCerebrum Test_RelationNeedGrammarPatten;
TEST_F(Test_RelationNeedGrammarPatten,iRelationResonance)
{
	shared_ptr<RelationNode> conditionRel(new RelationNode());
	shared_ptr<RelationLeaf> resultRel(new RelationLeaf());
	iRelationSample::RelationPair(conditionRel,resultRel);

	vector<string> conditionStr;
	conditionStr.push_back("二大于一");
	conditionStr.push_back("三大于二");
	shared_ptr<iExpression> condition(iLogicElementCreator::CreateExpression(conditionStr));

	if(conditionRel->Satisfy(condition))
	{
		shared_ptr<iRelation> specialRel=conditionRel->SymbolResonance(resultRel);

		string relStr=specialRel->GetString();

		shared_ptr<iExpression> conclusion_true(iLogicElementCreator::CreateExpression("三大于一"));
		ASSERT_TRUE(specialRel->Satisfy(conclusion_true));
	}
}

typedef InitCerebrum Test_RelationNeedCerebrum;
TEST_F(Test_RelationNeedCerebrum,PlusOfNumber)
{
	shared_ptr<iConcept> san=GetConcept("三",0);
	shared_ptr<iConcept> jia=GetConcept("加",0);
	shared_ptr<iConcept> er=GetConcept("二",0);

	shared_ptr<iConceptInteractTable> interTable=iMindElementCreator::CreateConceptInteractTable();
	interTable->Add(san,jia);
	interTable->Add(jia,er);

	shared_ptr<RelationLeaf> leaf=iRelationSample::RelationSample3();

	ASSERT_TRUE(Test_iRelation::InterTableSatisfyRelation(leaf,interTable));
}




bool Test_iRelation::InterTableSatisfyRelation( shared_ptr<RelationLeaf> leaf1,shared_ptr<iConceptInteractTable> interTable )
{
	return leaf1->InterTableSatisfyRelation(interTable);
}

bool Test_iRelation::InterTableSatisfyRelation( shared_ptr<RelationNode> node,shared_ptr<iConceptInteractTable> interTable )
{
	return node->InterTableSatisfyRelation(interTable,false);
}

void Test_iRelation::ClearArbNum()
{
	Arbitrariness<iConcept>::ArbNum=0;
}

void Test_iRelation::SetUpTestCase()
{
	_conceptCreator=shared_ptr<SimpleConceptCreator>(new SimpleConceptCreator());
}

void Test_iRelation::TearDownTestCase()
{

}

shared_ptr<ConceptCreator> Test_iRelation::_conceptCreator;
