#include "StdAfx.h"
#include "RelationSample.h"

#include "SymbolCreator.h"
#include "ConceptCreator.h"

#include "../LogicSystem/RelationLeaf.h"
#include "../LogicSystem/RelationNode.h"
#include "../LogicSystem/Arbitrariness.h"
#include "../LogicSystem/Number.h"
#include "../LogicSystem/Verb.h"
#include "../LogicSystem/Symbol.h"
#include "../LogicSystem/Inequality.h"
#include "../LogicSystem/Equality.h"

#include "../MindElement/ConceptInteractTable.h"
#include "../MindElement/Concept.h"

using namespace LogicSystem;
using namespace Mind;

typedef Arbitrariness<iConcept> Arb;
typedef Number<iConcept> Num;
typedef Verb<iConcept> Vb;
typedef LogicType::ConSymbol ConSymbol;
typedef Symbol<iConcept> Sym;

shared_ptr<SymbolCreator> iRelationSample::_symbolCreator(new SymbolCreator(shared_ptr<SimpleConceptCreator>(new SimpleConceptCreator())));

shared_ptr<LogicSystem::RelationNode> iRelationSample::RelationSample1()
{
	shared_ptr<Arb> arb1=Arb::Create();
	shared_ptr<Sym> s1(_symbolCreator->Create("大"));
	shared_ptr<Sym> s2(_symbolCreator->Create("于"));
	shared_ptr<Arb> arb2=Arb::Create();	

	shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
	leaf1->AddRelation(arb1,s1);
	leaf1->AddRelation(s1,s2);
	leaf1->AddRelation(s2,arb2);

	shared_ptr<Sym> s3(_symbolCreator->Create("大"));
	shared_ptr<Sym> s4(_symbolCreator->Create("于"));
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
	shared_ptr<Sym> s1(_symbolCreator->Create("大"));
	shared_ptr<Sym> s2(_symbolCreator->Create("于"));
	shared_ptr<Arb> arb2=Arb::Create();	

	shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
	leaf1->AddRelation(arb1,s1);
	leaf1->AddRelation(s1,s2);
	leaf1->AddRelation(s2,arb2);

	shared_ptr<Sym> s3(_symbolCreator->Create("大"));
	shared_ptr<Sym> s4(_symbolCreator->Create("于"));
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
	shared_ptr<Sym> jia(_symbolCreator->Create("加"));
	shared_ptr<Num> num2=Num::Create();

	shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
	leaf1->AddRelation(num1,jia);
	leaf1->AddRelation(jia,num2);

	return leaf1;
}


void iRelationSample::RelationPair( shared_ptr<RelationNode> condition,shared_ptr<RelationLeaf> result )
{
	//Create condition
	shared_ptr<Arb> arb1=Arb::Create();
	shared_ptr<Sym> s1(_symbolCreator->Create("大"));
	shared_ptr<Sym> s2(_symbolCreator->Create("于"));
	shared_ptr<Arb> arb2=Arb::Create();	

	shared_ptr<RelationLeaf> leaf1(new RelationLeaf());
	leaf1->AddRelation(arb1,s1);
	leaf1->AddRelation(s1,s2);
	leaf1->AddRelation(s2,arb2);

	shared_ptr<Arb> arb3=Arb::Create();	
	shared_ptr<Sym> s3(_symbolCreator->Create("大"));
	shared_ptr<Sym> s4(_symbolCreator->Create("于"));
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
	shared_ptr<Sym> jia(_symbolCreator->Create("加"));
	shared_ptr<Num> num1=Num::Create();

	condition->AddRelation(num0,jia);
	condition->AddRelation(jia,num1);

	//Create result.
	shared_ptr<Sym> yi(_symbolCreator->Create("一"));
	shared_ptr<Sym> ci(_symbolCreator->Create("次"));

	result->AddRelation(num0,jia);
	result->AddRelation(jia,yi);
	result->AddRelation(num1,ci);
	result->AddRelation(ci,jia);
}

void iRelationSample::RelationPair3( shared_ptr<LogicSystem::RelationLeaf>& condition,shared_ptr<LogicSystem::RelationLeaf>& result )
{
	//Create condition.
	//Num0->次,次->Verb0,Verb1->Arb0.
	condition=shared_ptr<RelationLeaf>(new RelationLeaf());
	shared_ptr<Num> num0=Num::Create();
	shared_ptr<Sym> ci(_symbolCreator->Create("次"));
	shared_ptr<Vb> verb0=Vb::Create();
	shared_ptr<Vb> verb1=Vb::Create();
	shared_ptr<Arb> arb0=Arb::Create();

	condition->AddRelation(num0,ci);
	condition->AddRelation(ci,verb0);
	condition->AddRelation(verb1,arb0);
	condition->AddConstraint(Equality::Create(verb0,verb1));

	//Result:Verb0->Arb0 X3 
	result=shared_ptr<RelationLeaf>(new RelationLeaf());
	result->AddRelation(verb0,arb0);
	result->AddRelation(verb0,arb0);
	result->AddRelation(verb0,arb0);
}
