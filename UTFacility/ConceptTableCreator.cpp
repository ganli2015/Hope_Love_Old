#include "StdAfx.h"
#include "ConceptTableCreator.h"
#include "ConceptCreator.h"

#include "../MindElement/ConceptInteractTable.h"

#include "../MindInterface/iMindElementCreator.h"

#include "../CommonTools/CommonStringFunction.h"

using namespace Mind;

ConceptTableCreator::ConceptTableCreator(void)
{
}


ConceptTableCreator::~ConceptTableCreator(void)
{
}

shared_ptr<Mind::iConceptInteractTable> ConceptTableCreator::SimpleCreate( const string str ,const Type type)
{
	_myConceptCreator=shared_ptr<SimpleConceptCreator>(new SimpleConceptCreator());

	return Parse(str,type);
}

shared_ptr<Mind::iConceptInteractTable> ConceptTableCreator::Create( const string str,const Type type )
{
	_myConceptCreator=shared_ptr<CerebrumConceptCreator>(new CerebrumConceptCreator());

	return Parse(str,type);
}

shared_ptr<Mind::iConceptInteractTable> ConceptTableCreator::Parse( const string str,const Type type  )
{
	shared_ptr<Mind::iConceptInteractTable> res;
	if(type==Concept_Based)
	{
		res=iMindElementCreator::CreateConceptInteractTable(iMindElementCreator::ConceptInteractTable_ConceptBased);
	}
	else if (type == Identity_Based)
	{
		res=iMindElementCreator::CreateConceptInteractTable(iMindElementCreator::ConceptInteractTable_IdentityBased);
	}
	else
	{
		res = iMindElementCreator::CreateConceptInteractTable(iMindElementCreator::ConceptInteractTable_SetBased);
	}

	//split ','
	vector<string> pariStr=CommonTool::SplitString(str,',');
	for (unsigned int i=0;i<pariStr.size();++i)
	{
		//split '-'
		vector<string> fromTo=CommonTool::SplitString(pariStr[i],'-');
		Check(fromTo.size()==2);

		shared_ptr<iConcept> from=ParseConcept(fromTo[0]);

		shared_ptr<iConcept> to=ParseConcept(fromTo[1]);

		res->Add(from,to);
	}

	return res;
}

shared_ptr<Mind::iConcept> ConceptTableCreator::ParseConcept( const string str )
{
	return _myConceptCreator->Create(str);
}

shared_ptr<ConceptCreator> ConceptTableCreator::_myConceptCreator;
