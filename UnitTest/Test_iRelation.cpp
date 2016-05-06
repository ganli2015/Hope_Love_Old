#include "StdAfx.h"
#include "Test_iRelation.h"

#include "../LogicSystem/Logic.h"
#include "../LogicSystem/CompositeExpression.h"
#include "../LogicSystem/SingleExpression.h"
#include "../LogicSystem/RelationLeaf.h"
#include "../LogicSystem/RelationNode.h"
#include "../LogicSystem/Arbitrariness.h"
#include "../LogicSystem/Symbol.h"
#include "../LogicSystem/Inequality.h"

#include "../MindElement/ConceptInteractTable.h"
#include "../MindElement/Concept.h"

#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/PublicTypedef.h"

#include "../Mind/Cerebrum.h"

#include "../DataCollection/GrammaPattern.h"

#include "FuncForTest.h"

using namespace DataCollection;
using namespace Mind;
using namespace LogicSystem;
using namespace FuncForTest;

typedef Arbitrariness<iConcept> Arb;
typedef LogicType::ConSymbol ConSymbol;
typedef Symbol<iConcept> Sym;

Test_iRelation::Test_iRelation(void)
{
}


Test_iRelation::~Test_iRelation(void)
{
}

void Test_iRelation::RunTest()
{
	Test_GetString();
	Test_RelationLeafSatisfy();
	Test_RelationNodeSatisfy();
}

void Test_iRelation::Test_GetString()
{
	{
		shared_ptr<iRelationNode> node=RelationSample1();

		string result=node->GetString();
		string expect="(S0->大,大->于,于->S1)&&(S1->大,大->于,于->S2)";
		Check(result==expect);
	}

	{
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
		Check(result==expect);
	}
}

void Test_iRelation::Test_RelationLeafSatisfy()
{
	//InterTableSatisfyRelation
	{
		shared_ptr<iConcept> san=SimpleConcept("三");
		shared_ptr<iConcept> da=SimpleConcept("大");
		shared_ptr<iConcept> yu=SimpleConcept("于");
		shared_ptr<iConcept> er=SimpleConcept("二");

		shared_ptr<Arb> arb1=Arb::Create();
		shared_ptr<Sym> s1(new Sym(da));
		shared_ptr<Sym> s2(new Sym(yu));
		shared_ptr<Arb> arb2=Arb::Create();	

		shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
		leaf1->AddRelation(arb1,s1);
		leaf1->AddRelation(s1,s2);
		leaf1->AddRelation(s2,arb2);
		leaf1->AddConstraint(Inequality::Create(arb1,arb2));

		shared_ptr<iConceptInteractTable> interTable(new ConceptInteractTable());
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);
		
		Check(leaf1->InterTableSatisfyRelation(interTable));
	}

	//AddConstraint
	{
		shared_ptr<iConcept> san=SimpleConcept("三");
		shared_ptr<iConcept> da=SimpleConcept("大");
		shared_ptr<iConcept> yu=SimpleConcept("于");
		shared_ptr<iConcept> san2=SimpleConcept("三");

		shared_ptr<Arb> arb1=Arb::Create();
		shared_ptr<Sym> s1(new Sym(da));
		shared_ptr<Sym> s2(new Sym(yu));
		shared_ptr<Arb> arb2=Arb::Create();	

		shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
		leaf1->AddRelation(arb1,s1);
		leaf1->AddRelation(s1,s2);
		leaf1->AddRelation(s2,arb2);
		leaf1->AddConstraint(Inequality::Create(arb1,arb2));

		shared_ptr<iConceptInteractTable> interTable(new ConceptInteractTable());
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,san2);

		Check(leaf1->InterTableSatisfyRelation(interTable)==false);
	}
	//InterTableSatisfyRelation
	{
		shared_ptr<iConcept> san=SimpleConcept("三");
		shared_ptr<iConcept> da=SimpleConcept("大");
		shared_ptr<iConcept> yu=SimpleConcept("于");
		shared_ptr<iConcept> er=SimpleConcept("二");
		shared_ptr<iConcept> yi=SimpleConcept("一");
		shared_ptr<iConcept> si=SimpleConcept("四");

		shared_ptr<Arb> arb1=Arb::Create();
		shared_ptr<Sym> s1(new Sym(da));
		shared_ptr<Sym> s2(new Sym(yu));
		shared_ptr<Arb> arb2=Arb::Create();	

		shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
		leaf1->AddRelation(arb1,s1);
		leaf1->AddRelation(s1,s2);
		leaf1->AddRelation(s2,arb2);

		shared_ptr<iConceptInteractTable> interTable(new ConceptInteractTable());
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);
		interTable->Add(er,yi);
		interTable->Add(si,da);
		interTable->Add(san,si);

		Check(leaf1->InterTableSatisfyRelation(interTable));
	}
	//InterTableSatisfyRelation
	{
		shared_ptr<iConcept> san=SimpleConcept("三");
		shared_ptr<iConcept> da=SimpleConcept("大");
		shared_ptr<iConcept> yu=SimpleConcept("于");
		shared_ptr<iConcept> er=SimpleConcept("二");
		shared_ptr<iConcept> yi=SimpleConcept("一");
		shared_ptr<iConcept> si=SimpleConcept("四");

		shared_ptr<Arb> arb1=Arb::Create();
		shared_ptr<Sym> s1(new Sym(da));
		shared_ptr<Sym> s2(new Sym(yu));
		shared_ptr<Arb> arb2=Arb::Create();	

		shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
		leaf1->AddRelation(arb1,s1);
		leaf1->AddRelation(s1,s2);
		leaf1->AddRelation(s2,arb2);

		shared_ptr<iConceptInteractTable> interTable(new ConceptInteractTable());
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(si,er);

		Check(leaf1->InterTableSatisfyRelation(interTable)==false);
	}

	
}

void Test_iRelation::Test_RelationNodeSatisfy()
{
	//"三大于二" and "二大于一"
	{
		shared_ptr<iConcept> san=SimpleConcept("三");
		shared_ptr<iConcept> da=SimpleConcept("大");
		shared_ptr<iConcept> yu=SimpleConcept("于");
		shared_ptr<iConcept> er=SimpleConcept("二");
		shared_ptr<iConcept> yi=SimpleConcept("一");

		shared_ptr<iConceptInteractTable> interTable(new ConceptInteractTable());
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);
		interTable->Add(er,da);
		interTable->Add(da,yu);
		interTable->Add(yu,yi);

		shared_ptr<RelationNode> relation=RelationSample1();

		Check(relation->InterTableSatisfyRelation(interTable));

	}

	//"三大于二" and "二小于一"
	{
		shared_ptr<iConcept> san=SimpleConcept("三");
		shared_ptr<iConcept> da=SimpleConcept("大");
		shared_ptr<iConcept> yu=SimpleConcept("于");
		shared_ptr<iConcept> er=SimpleConcept("二");
		shared_ptr<iConcept> yi=SimpleConcept("一");
		shared_ptr<iConcept> xiao=SimpleConcept("小");

		shared_ptr<iConceptInteractTable> interTable(new ConceptInteractTable());
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);
		interTable->Add(er,xiao);
		interTable->Add(xiao,yu);
		interTable->Add(yu,yi);

		shared_ptr<RelationNode> relation=RelationSample1();

		Check(relation->InterTableSatisfyRelation(interTable)==false);

	}

	//"三大于二" and "二大于一" with perturbation
	{		
		shared_ptr<iConcept> san=SimpleConcept("三");
		shared_ptr<iConcept> da=SimpleConcept("大");
		shared_ptr<iConcept> yu=SimpleConcept("于");
		shared_ptr<iConcept> er=SimpleConcept("二");
		shared_ptr<iConcept> yi=SimpleConcept("一");
		shared_ptr<iConcept> si=SimpleConcept("四");
		shared_ptr<iConcept> wu=SimpleConcept("五");
		shared_ptr<iConcept> liu=SimpleConcept("六");

		shared_ptr<iConceptInteractTable> interTable(new ConceptInteractTable());
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);
		interTable->Add(er,da);
		interTable->Add(da,yu);
		interTable->Add(yu,yi);
		interTable->Add(si,da);
		interTable->Add(san,liu);
		interTable->Add(wu,yu);

		shared_ptr<RelationNode> relation=RelationSample1();

		Check(relation->InterTableSatisfyRelation(interTable));
	}
	//"三大于二" and "二小于一" with perturbation
	{
		shared_ptr<iConcept> san=SimpleConcept("三");
		shared_ptr<iConcept> da=SimpleConcept("大");
		shared_ptr<iConcept> yu=SimpleConcept("于");
		shared_ptr<iConcept> er=SimpleConcept("二");
		shared_ptr<iConcept> yi=SimpleConcept("一");
		shared_ptr<iConcept> xiao=SimpleConcept("小");

		shared_ptr<iConceptInteractTable> interTable(new ConceptInteractTable());
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);
		interTable->Add(er,xiao);
		interTable->Add(xiao,yu);
		interTable->Add(yu,yi);
		interTable->Add(er,da);

		shared_ptr<RelationNode> relation=RelationSample1();

		Check(relation->InterTableSatisfyRelation(interTable)==false);
	}
	//"三大于二" or "二大于一"
	{
		shared_ptr<iConcept> san=SimpleConcept("三");
		shared_ptr<iConcept> da=SimpleConcept("大");
		shared_ptr<iConcept> yu=SimpleConcept("于");
		shared_ptr<iConcept> er=SimpleConcept("二");
		shared_ptr<iConcept> yi=SimpleConcept("一");

		shared_ptr<iConceptInteractTable> interTable(new ConceptInteractTable());
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);
		interTable->Add(er,da);
		interTable->Add(da,yu);
		interTable->Add(yu,yi);

		shared_ptr<RelationNode> relation=RelationSample2();

		Check(relation->InterTableSatisfyRelation(interTable));
	}
	//"三大于二" or "二大于一"
	{
		shared_ptr<iConcept> san=SimpleConcept("三");
		shared_ptr<iConcept> da=SimpleConcept("大");
		shared_ptr<iConcept> yu=SimpleConcept("于");
		shared_ptr<iConcept> er=SimpleConcept("二");
		shared_ptr<iConcept> yi=SimpleConcept("一");

		shared_ptr<iConceptInteractTable> interTable(new ConceptInteractTable());
		interTable->Add(san,da);
		interTable->Add(da,yu);
		interTable->Add(yu,er);

		shared_ptr<RelationNode> relation=RelationSample2();

		Check(relation->InterTableSatisfyRelation(interTable));
	}
	//"三大于二" or "二大于一"
	{
		shared_ptr<iConcept> san=SimpleConcept("三");
		shared_ptr<iConcept> xiao=SimpleConcept("小");
		shared_ptr<iConcept> yu=SimpleConcept("于");
		shared_ptr<iConcept> er=SimpleConcept("二");
		shared_ptr<iConcept> yi=SimpleConcept("一");

		shared_ptr<iConceptInteractTable> interTable(new ConceptInteractTable());
		interTable->Add(san,xiao);
		interTable->Add(xiao,yu);
		interTable->Add(yu,er);
		interTable->Add(er,xiao);
		interTable->Add(xiao,yu);
		interTable->Add(yu,yi);

		shared_ptr<RelationNode> relation=RelationSample2();

		Check(relation->InterTableSatisfyRelation(interTable)==false);
	}
}

shared_ptr<LogicSystem::RelationNode> Test_iRelation::RelationSample1()
{
	shared_ptr<Arb> arb1=Arb::Create();
	shared_ptr<Sym> s1(new Sym(SimpleConcept("大")));
	shared_ptr<Sym> s2(new Sym(SimpleConcept("于")));
	shared_ptr<Arb> arb2=Arb::Create();	

	shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
	leaf1->AddRelation(arb1,s1);
	leaf1->AddRelation(s1,s2);
	leaf1->AddRelation(s2,arb2);

	shared_ptr<Sym> s3(new Sym(SimpleConcept("大")));
	shared_ptr<Sym> s4(new Sym(SimpleConcept("于")));
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

shared_ptr<LogicSystem::RelationNode> Test_iRelation::RelationSample2()
{
	shared_ptr<Arb> arb1=Arb::Create();
	shared_ptr<Sym> s1(new Sym(SimpleConcept("大")));
	shared_ptr<Sym> s2(new Sym(SimpleConcept("于")));
	shared_ptr<Arb> arb2=Arb::Create();	

	shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
	leaf1->AddRelation(arb1,s1);
	leaf1->AddRelation(s1,s2);
	leaf1->AddRelation(s2,arb2);

	shared_ptr<Sym> s3(new Sym(SimpleConcept("大")));
	shared_ptr<Sym> s4(new Sym(SimpleConcept("于")));
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
