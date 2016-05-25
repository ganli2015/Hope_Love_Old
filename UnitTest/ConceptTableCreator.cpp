#include "StdAfx.h"
#include "ConceptTableCreator.h"
#include "ConceptCreator.h"

#include "../MindElement/ConceptInteractTable.h"

#include "../CommonTools/CommonStringFunction.h"

using namespace Mind;

ConceptTableCreator::ConceptTableCreator(void)
{
}


ConceptTableCreator::~ConceptTableCreator(void)
{
}

shared_ptr<Mind::ConceptInteractTable> ConceptTableCreator::SimpleCreate( const string str )
{
	_myConceptCreator=shared_ptr<SimpleConceptCreator>(new SimpleConceptCreator());

	return Parse(str);
}

shared_ptr<Mind::ConceptInteractTable> ConceptTableCreator::Create( const string str )
{
	_myConceptCreator=shared_ptr<CerebrumConceptCreator>(new CerebrumConceptCreator());

	return Parse(str);
}

shared_ptr<Mind::ConceptInteractTable> ConceptTableCreator::Parse( const string str )
{
	shared_ptr<Mind::ConceptInteractTable> res(new ConceptInteractTable());

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
