#include "StdAfx.h"
#include "BaseConcept.h"

#include "../DataCollection/Word.h"

namespace Mind
{
	BaseConcept::BaseConcept(void)
	{
	}


	BaseConcept::~BaseConcept(void)
	{
	}

	BaseConcept::BaseConcept(shared_ptr<DataCollection::Word> word):Concept(word)
	{

	}

	void BaseConcept::AddForwardConcept( const shared_ptr<Concept> concept,const double sensitivity/*=1*/ )
	{
		throw runtime_error("Forbidden Method!");
	}

	shared_ptr<iConcept> BaseConcept::Copy() const
	{
		shared_ptr<BaseConcept> res(new BaseConcept());
		res->_backward=_backward;
		res->_forward=_forward;
		res->_color=_color;
		res->_identity=_identity;
		res->_partofspeech=_partofspeech;
		res->_baseId=_baseId;

		return res;
	}

}

