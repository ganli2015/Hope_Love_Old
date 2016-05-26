#include "StdAfx.h"
#include "LeafCreator.h"
#include "ConceptCreator.h"

#include "../LogicSystem/Arbitrariness.h"
#include "../LogicSystem/Number.h"
#include "../LogicSystem/RelationLeaf.h"
#include "../LogicSystem/Symbol.h"

#include "../MindInterface/iConcept.h"
#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iCerebrum.h"

#include "../CommonTools/CommonStringFunction.h"

using namespace LogicSystem;
using namespace Mind;

typedef Arbitrariness<Mind::iConcept> Arb;
typedef Number<Mind::iConcept> Num;

map<string,LeafCreator::iSpecialSymbol*> LeafCreator::SpSym;

shared_ptr<ConceptCreator> LeafCreator::MyConceptCreator;

LeafCreator::LeafCreator(void)
{
}


LeafCreator::~LeafCreator(void)
{
}

shared_ptr<LogicSystem::RelationLeaf> LeafCreator::SimpleCreate( const string str )
{
	MyConceptCreator=shared_ptr<SimpleConceptCreator>(new SimpleConceptCreator());

	return Parse(str);
}

shared_ptr<LogicSystem::RelationLeaf> LeafCreator::Create( const string str )
{
	MyConceptCreator=shared_ptr<CerebrumConceptCreator>(new CerebrumConceptCreator());

	return Parse(str);
}

shared_ptr<LogicSystem::RelationLeaf> LeafCreator::Parse( const string str )
{
	shared_ptr<LogicSystem::RelationLeaf> res(new RelationLeaf());

	//split ','
	vector<string> pariStr=CommonTool::SplitString(str,',');
	for (unsigned int i=0;i<pariStr.size();++i)
	{
		//split '-'
		vector<string> fromTo=CommonTool::SplitString(pariStr[i],'-');
		Check(fromTo.size()==2);

		shared_ptr<LogicType::ConSymbol> from=ParseSpSymbol(fromTo[0]);
		if(from==NULL)//Parse common symbol.
		{
			from=ParseSymbol(fromTo[0]);
		}

		shared_ptr<LogicType::ConSymbol> to=ParseSpSymbol(fromTo[1]);
		if(to==NULL)//Parse common symbol.
		{
			to=ParseSymbol(fromTo[1]);
		}

		res->AddRelation(from,to);
	}

	return res;
}

void LeafCreator::Init()
{
	SpSym["Arb"]=new SpecialSymbol<Arb>();
	SpSym["Num"]=new SpecialSymbol<Num>();
}

bool LeafCreator::Contain( const string raw,const string search )
{
	return raw.find(search)!=string::npos;
}

shared_ptr<LogicType::ConSymbol> LeafCreator::ParseSpSymbol( const string str )
{
	if(Contain(str,"S"))
	{
		return SpSym["Arb"]->Create();
	}
	else if(Contain(str,"Num"))
	{
		return SpSym["Num"]->Create();
	}
	else
	{
		return NULL;
	}
}

shared_ptr<LogicType::ConSymbol> LeafCreator::ParseSymbol( const string str )
{
	shared_ptr<iConcept> con=MyConceptCreator->Create(str);

	return shared_ptr<LogicType::ConSymbol>(new Symbol<iConcept>(con));
}
