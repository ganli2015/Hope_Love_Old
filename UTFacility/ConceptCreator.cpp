#include "StdAfx.h"
#include "ConceptCreator.h"

#include "../MindInterface/PublicTypedef.h"

#include "../DataCollection/Word.h"

#include "../MindElement/Concept.h"

#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iCerebrum.h"

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
	shared_ptr<Word> w(new Word(str));
	shared_ptr<Concept> res(new Concept(w)); 

	return res;
}

shared_ptr<Mind::iConcept> CerebrumConceptCreator::Create( const string str, const int i/*=0*/ ) const
{
	iCerebrum* brain=iCerebrum::Instance();
	if(brain==NULL) return NULL;

	Identity id(str,0);
	shared_ptr<iConcept> con=brain->GetConcept(id);

	return con;
}
