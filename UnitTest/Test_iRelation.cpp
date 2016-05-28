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

#include "../Mind/Cerebrum.h"

#include "../DataCollection/GrammaPattern.h"

#include "../UTFacility/LeafCreator.h"
#include "../UTFacility/ConceptCreator.h"
#include "../UTFacility/SymbolCreator.h"

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
	string expect="(S0->��,��->��,��->S1)&&(S1->��,��->��,��->S2)";
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
	shared_ptr<iConcept> san=_conceptCreator->Create("��");
	shared_ptr<iConcept> da=_conceptCreator->Create("��");
	shared_ptr<iConcept> yu=_conceptCreator->Create("��");
	shared_ptr<iConcept> er=_conceptCreator->Create("��");

	string leafStr="��-��,��-��,��-��";
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
		shared_ptr<iConcept> san=_conceptCreator->Create("��");
		shared_ptr<iConcept> da=_conceptCreator->Create("��");
		shared_ptr<iConcept> yu=_conceptCreator->Create("��");
		shared_ptr<iConcept> san2=_conceptCreator->Create("��");

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
		shared_ptr<iConcept> san=_conceptCreator->Create("��");
		shared_ptr<iConcept> da=_conceptCreator->Create("��");
		shared_ptr<iConcept> yu=_conceptCreator->Create("��");
		shared_ptr<iConcept> er=_conceptCreator->Create("��");
		shared_ptr<iConcept> yi=_conceptCreator->Create("һ");
		shared_ptr<iConcept> si=_conceptCreator->Create("��");

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
		shared_ptr<iConcept> san=_conceptCreator->Create("��");
		shared_ptr<iConcept> da=_conceptCreator->Create("��");
		shared_ptr<iConcept> yu=_conceptCreator->Create("��");
		shared_ptr<iConcept> er=_conceptCreator->Create("��");
		shared_ptr<iConcept> yi=_conceptCreator->Create("һ");
		shared_ptr<iConcept> si=_conceptCreator->Create("��");

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

TEST_F(Test_iRelation,Test_RelationNodeSatisfy)
{
	//"�����ڶ�" and "������һ"
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("��");
		shared_ptr<iConcept> da=_conceptCreator->Create("��");
		shared_ptr<iConcept> yu=_conceptCreator->Create("��");
		shared_ptr<iConcept> er=_conceptCreator->Create("��");
		shared_ptr<iConcept> yi=_conceptCreator->Create("һ");

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

	//"�����ڶ�" and "��С��һ"
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("��");
		shared_ptr<iConcept> da=_conceptCreator->Create("��");
		shared_ptr<iConcept> yu=_conceptCreator->Create("��");
		shared_ptr<iConcept> er=_conceptCreator->Create("��");
		shared_ptr<iConcept> yi=_conceptCreator->Create("һ");
		shared_ptr<iConcept> xiao=_conceptCreator->Create("С");

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

	//"�����ڶ�" and "������һ" with perturbation
	{		
		shared_ptr<iConcept> san=_conceptCreator->Create("��");
		shared_ptr<iConcept> da=_conceptCreator->Create("��");
		shared_ptr<iConcept> yu=_conceptCreator->Create("��");
		shared_ptr<iConcept> er=_conceptCreator->Create("��");
		shared_ptr<iConcept> yi=_conceptCreator->Create("һ");
		shared_ptr<iConcept> si=_conceptCreator->Create("��");
		shared_ptr<iConcept> wu=_conceptCreator->Create("��");
		shared_ptr<iConcept> liu=_conceptCreator->Create("��");

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
	//"�����ڶ�" and "��С��һ" with perturbation
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("��");
		shared_ptr<iConcept> da=_conceptCreator->Create("��");
		shared_ptr<iConcept> yu=_conceptCreator->Create("��");
		shared_ptr<iConcept> er=_conceptCreator->Create("��");
		shared_ptr<iConcept> yi=_conceptCreator->Create("һ");
		shared_ptr<iConcept> xiao=_conceptCreator->Create("С");

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
	//"�����ڶ�" or "������һ"
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("��");
		shared_ptr<iConcept> da=_conceptCreator->Create("��");
		shared_ptr<iConcept> yu=_conceptCreator->Create("��");
		shared_ptr<iConcept> er=_conceptCreator->Create("��");
		shared_ptr<iConcept> yi=_conceptCreator->Create("һ");

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
	//"�����ڶ�" or "������һ"
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("��");
		shared_ptr<iConcept> da=_conceptCreator->Create("��");
		shared_ptr<iConcept> yu=_conceptCreator->Create("��");
		shared_ptr<iConcept> er=_conceptCreator->Create("��");
		shared_ptr<iConcept> yi=_conceptCreator->Create("һ");

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
	//"�����ڶ�" or "������һ"
	{
		shared_ptr<iConcept> san=_conceptCreator->Create("��");
		shared_ptr<iConcept> xiao=_conceptCreator->Create("С");
		shared_ptr<iConcept> yu=_conceptCreator->Create("��");
		shared_ptr<iConcept> er=_conceptCreator->Create("��");
		shared_ptr<iConcept> yi=_conceptCreator->Create("һ");

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
	string leafStr="��-��,��-��,��-��";
	shared_ptr<RelationLeaf> leaf=LeafCreator::SimpleCreate(leafStr);

	shared_ptr<iConceptInteractTable> result=leaf->GenerateConceptTable();

	vector<pair<string,string>> expect;
	expect.push_back(make_pair("��","��"));
	expect.push_back(make_pair("��","��"));
	expect.push_back(make_pair("��","��"));

	ASSERT_TRUE(FuncForTest::PairSameWithTable(expect,result));
}

typedef AddPatternToCerebrum Test_RelationNeedGrammarPatten;
TEST_F(Test_RelationNeedGrammarPatten,iRelationResonance)
{
	shared_ptr<RelationNode> conditionRel(new RelationNode());
	shared_ptr<RelationLeaf> resultRel(new RelationLeaf());
	iRelationSample::RelationPair(conditionRel,resultRel);

	shared_ptr<CompositeExpression> condition(new CompositeExpression());
	condition->AddExpression("������һ");
	condition->AddExpression("�����ڶ�");
	if(conditionRel->Satisfy(condition))
	{
		shared_ptr<iRelation> specialRel=conditionRel->SymbolResonance(resultRel);

		string relStr=specialRel->GetString();

		shared_ptr<iExpression> conclusion_true(new SingleExpression("������һ"));
		ASSERT_TRUE(specialRel->Satisfy(conclusion_true));
	}
}

typedef InitCerebrum Test_RelationNeedCerebrum;
TEST_F(Test_RelationNeedCerebrum,PlusOfNumber)
{
	shared_ptr<iConcept> san=GetConcept("��",0);
	shared_ptr<iConcept> jia=GetConcept("��",0);
	shared_ptr<iConcept> er=GetConcept("��",0);

	shared_ptr<iConceptInteractTable> interTable=iMindElementCreator::CreateConceptInteractTable();
	interTable->Add(san,jia);
	interTable->Add(jia,er);

	shared_ptr<RelationLeaf> leaf=iRelationSample::RelationSample3();

	ASSERT_TRUE(Test_iRelation::InterTableSatisfyRelation(leaf,interTable));
}

void iRelationSample::RelationPair( shared_ptr<RelationNode> condition,shared_ptr<RelationLeaf> result )
{
	//Create condition
	shared_ptr<Arb> arb1=Arb::Create();
	shared_ptr<Sym> s1(_symbolCreator->Create("��"));
	shared_ptr<Sym> s2(_symbolCreator->Create("��"));
	shared_ptr<Arb> arb2=Arb::Create();	

	shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
	leaf1->AddRelation(arb1,s1);
	leaf1->AddRelation(s1,s2);
	leaf1->AddRelation(s2,arb2);

	shared_ptr<Arb> arb3=Arb::Create();	
	shared_ptr<Sym> s3(_symbolCreator->Create("��"));
	shared_ptr<Sym> s4(_symbolCreator->Create("��"));
	shared_ptr<Arb> arb4=Arb::Create();	

	shared_ptr<RelationLeaf> leaf2(new RelationLeaf());
	leaf2->AddRelation(arb3,s3);
	leaf2->AddRelation(s3,s4);
	leaf2->AddRelation(s4,arb4);

	condition->AddSubRelation(leaf1);
	condition->AddSubRelation(leaf2);
	condition->SetState(iRelationNode::And);
	condition->AddConstraint(Equality::Create(arb2,arb3));
	condition->AddConstraint(Inequality::Create(arb2,arb4));
	condition->AddConstraint(Inequality::Create(arb1,arb2));

	//Create result
	result->AddRelation(arb1,s1);
	result->AddRelation(s1,s2);
	result->AddRelation(s2,arb4);
}

void iRelationSample::RelationPair2( shared_ptr<LogicSystem::RelationLeaf> condition,shared_ptr<LogicSystem::RelationLeaf> result )
{
	//Create condition.
	shared_ptr<Num> num0=Num::Create();
	shared_ptr<Sym> jia(_symbolCreator->Create("��"));
	shared_ptr<Num> num1=Num::Create();

	condition->AddRelation(num0,jia);
	condition->AddRelation(jia,num1);

	//Create result.
	shared_ptr<Sym> yi(_symbolCreator->Create("һ"));
	shared_ptr<Sym> ci(_symbolCreator->Create("��"));

	result->AddRelation(num0,jia);
	result->AddRelation(jia,yi);
	result->AddRelation(num1,ci);
	result->AddRelation(ci,jia);
}

shared_ptr<LogicSystem::RelationNode> iRelationSample::RelationSample1()
{
	shared_ptr<Arb> arb1=Arb::Create();
	shared_ptr<Sym> s1(_symbolCreator->Create("��"));
	shared_ptr<Sym> s2(_symbolCreator->Create("��"));
	shared_ptr<Arb> arb2=Arb::Create();	

	shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
	leaf1->AddRelation(arb1,s1);
	leaf1->AddRelation(s1,s2);
	leaf1->AddRelation(s2,arb2);

	shared_ptr<Sym> s3(_symbolCreator->Create("��"));
	shared_ptr<Sym> s4(_symbolCreator->Create("��"));
	shared_ptr<Arb> arb3=Arb::Create();	

	shared_ptr<RelationLeaf> leaf2(new RelationLeaf());
	leaf2->AddRelation(arb2,s3);
	leaf2->AddRelation(s3,s4);
	leaf2->AddRelation(s4,arb3);

	shared_ptr<RelationNode> node(new RelationNode());
	node->AddSubRelation(leaf1);
	node->AddSubRelation(leaf2);
	node->SetState(iRelationNode::And);

	return node;
}

shared_ptr<LogicSystem::RelationNode> iRelationSample::RelationSample2()
{
	shared_ptr<Arb> arb1=Arb::Create();
	shared_ptr<Sym> s1(_symbolCreator->Create("��"));
	shared_ptr<Sym> s2(_symbolCreator->Create("��"));
	shared_ptr<Arb> arb2=Arb::Create();	

	shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
	leaf1->AddRelation(arb1,s1);
	leaf1->AddRelation(s1,s2);
	leaf1->AddRelation(s2,arb2);

	shared_ptr<Sym> s3(_symbolCreator->Create("��"));
	shared_ptr<Sym> s4(_symbolCreator->Create("��"));
	shared_ptr<Arb> arb3=Arb::Create();	

	shared_ptr<RelationLeaf> leaf2(new RelationLeaf());
	leaf2->AddRelation(arb2,s3);
	leaf2->AddRelation(s3,s4);
	leaf2->AddRelation(s4,arb3);

	shared_ptr<RelationNode> node(new RelationNode());
	node->AddSubRelation(leaf1);
	node->AddSubRelation(leaf2);
	node->SetState(iRelationNode::Or);

	return node;
}

shared_ptr<LogicSystem::RelationLeaf> iRelationSample::RelationSample3()
{
	shared_ptr<Num> num1=Num::Create();
	shared_ptr<Sym> jia(_symbolCreator->Create("��"));
	shared_ptr<Num> num2=Num::Create();

	shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
	leaf1->AddRelation(num1,jia);
	leaf1->AddRelation(jia,num2);

	return leaf1;
}

shared_ptr<SymbolCreator> iRelationSample::_symbolCreator(new SymbolCreator(shared_ptr<SimpleConceptCreator>(new SimpleConceptCreator())));

bool Test_iRelation::InterTableSatisfyRelation( shared_ptr<RelationLeaf> leaf1,shared_ptr<iConceptInteractTable> interTable )
{
	return leaf1->InterTableSatisfyRelation(interTable);
}

bool Test_iRelation::InterTableSatisfyRelation( shared_ptr<RelationNode> node,shared_ptr<iConceptInteractTable> interTable )
{
	return node->InterTableSatisfyRelation(interTable);
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
