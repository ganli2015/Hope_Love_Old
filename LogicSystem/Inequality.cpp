#include "StdAfx.h"
#include "Inequality.h"

#include "../MindInterface/iSymbol.h"
#include "../MindInterface/iConcept.h"

namespace LogicSystem
{
	Inequality::Inequality(const shared_ptr<ConSymbol> s1,const shared_ptr<ConSymbol> s2):_s1(s1),_s2(s2)
	{
	}


	Inequality::~Inequality(void)
	{
	}

	bool Inequality::Satisfy() const
	{
		assert(_s1!=NULL && _s2!=NULL );
		if(_s1==NULL || _s2==NULL)
		{
			return false;
		}

		return !_s1->SameReferring(_s2);
	}

	shared_ptr<Inequality> Inequality::Create( const shared_ptr<ConSymbol> s1,const shared_ptr<ConSymbol> s2 )
	{
		return shared_ptr<Inequality>(new Inequality(s1,s2));
	}

}

