#include "StdAfx.h"
#include "Equality.h"

#include "../MindInterface/iSymbol.h"
#include "../MindInterface/iConcept.h"

namespace LogicSystem
{
	Equality::Equality(const shared_ptr<ConSymbol> s1,const shared_ptr<ConSymbol> s2):_s1(s1),_s2(s2)
	{
	}


	Equality::~Equality(void)
	{
	}

	shared_ptr<Equality> Equality::Create( const shared_ptr<ConSymbol> s1,const shared_ptr<ConSymbol> s2 )
	{
		return shared_ptr<Equality>(new Equality(s1,s2));
	}

	bool Equality::Satisfy() const
	{
		assert(_s1!=NULL && _s2!=NULL );
		if(_s1==NULL || _s2==NULL)
		{
			return false;
		}

		return _s1->SameReferring(_s2);
	}

}

