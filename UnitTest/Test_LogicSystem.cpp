#include "StdAfx.h"
#include "Test_LogicSystem.h"

#include "../LogicSystem/Logic.h"
#include "../LogicSystem/CompositeExpression.h"
#include "../LogicSystem/SingleExpression.h"
#include "../LogicSystem/RelationLeaf.h"
#include "../LogicSystem/RelationNode.h"
#include "../LogicSystem/Arbitrariness.h"
#include "../LogicSystem/Symbol.h"

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
	iCerebrum* brain=iCerebrum::Instance();

	Test_Expression();
//	Test_Logic_Determine();
	Test_Relation();
}

void Test_LogicSystem::Test_Expression()
{
	iCerebrum* brain=iCerebrum::Instance();
	vector<PartOfSpeech> pos;
	pos.push_back(Numeral);
	pos.push_back(Adjective);
	pos.push_back(Preposition);
	pos.push_back(Numeral);
	GrammarPattern pattern(pos);
	for (int i=0;i<200;++i)
	{
		brain->IncreasePatternFreqency(pos);
	}


	shared_ptr<SingleExpression> expre(new SingleExpression("二大于一。"));
	shared_ptr<iConceptInteractTable> table=expre->GetProtoInteractTable();
	vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> relations=table->GetAllRelations();
}

void Test_LogicSystem::Test_Logic_Determine()
{
	shared_ptr<CompositeExpression> condition(new CompositeExpression());
	condition->AddExpression("二大于一。");
	condition->AddExpression("三大于二。");

	shared_ptr<iExpression> conclusion_true(new SingleExpression("三大于一"));
	shared_ptr<iExpression> conclusion_false(new SingleExpression("一大于三"));

	Check(Logic::Determine(condition,conclusion_true)==True);
	Check(Logic::Determine(condition,conclusion_true)==False);
}

void Test_LogicSystem::Test_Relation()
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

	{
		iCerebrum* brain=iCerebrum::Instance();
		vector<PartOfSpeech> pos;
		pos.push_back(Numeral);
		pos.push_back(Adjective);
		pos.push_back(Preposition);
		pos.push_back(Numeral);
		GrammarPattern pattern(pos);
		for (int i=0;i<200;++i)
		{
			brain->IncreasePatternFreqency(pos);
		}

		shared_ptr<iRelationNode> relation=RelationSample1();
		shared_ptr<CompositeExpression> expre(new CompositeExpression());
		expre->AddExpression("二大于一。");
		expre->AddExpression("三大于二。");

		Check(relation->Satisfy(expre));
	}
}

shared_ptr<LogicSystem::iRelationNode> Test_LogicSystem::RelationSample1()
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

	shared_ptr<iRelationNode> node(new RelationNode());
	node->AddSubRelation(leaf1);
	node->AddSubRelation(leaf2);
	node->SetState(iRelationNode::And);

	return node;
}


