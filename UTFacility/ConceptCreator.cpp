#include "StdAfx.h"
#include "ConceptCreator.h"

#include "../MindInterface/PublicTypedef.h"

#include "../DataCollection/Word.h"

#include "../MindElement/Concept.h"
#include "../MindElement/BaseConcept.h"

#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iMindElementCreator.h"

using namespace Mind;
using namespace DataCollection;
ConceptCreator::ConceptCreator(void)
{
}


ConceptCreator::~ConceptCreator(void)
{
}

shared_ptr<Mind::iConcept> SimpleConceptCreator::Create( const string str, const int i/*=0*/ ) const
{
// 	shared_ptr<Word> w(new Word(str));
// 	shared_ptr<iConcept> res=iMindElementCreator::CreateConcept(w); 


	return CreateBaseConcept(str,i);
}

shared_ptr<Mind::BaseConcept> SimpleConceptCreator::CreateBaseConcept(const string str, const int i /*= 0*/) const
{
	shared_ptr<Word> w(new Word(str));

	shared_ptr<Mind::BaseConcept> base(new Mind::BaseConcept(w));
	base->SetId(i);

	return base;
}

shared_ptr<Mind::iConcept> CerebrumConceptCreator::Create(const string str, const int i/*=0*/) const
{
	iCerebrum* brain=iCerebrum::Instance();
	if(brain==NULL) return NULL;

	Identity id(str,0);
	shared_ptr<iConcept> con=brain->GetConcept(id);

	return con;
}
