#pragma once
#include "InOut.h"
#include "../MindInterface/iRelationConstraint.h"

namespace Mind
{
	class iConcept;
}

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT Equality :  public iRelationConstraint
	{
		typedef LogicType::ConSymbol ConSymbol;		

		shared_ptr<ConSymbol> _s1,_s2;

	public:
		Equality(const shared_ptr<ConSymbol> s1,const shared_ptr<ConSymbol> s2);
		~Equality(void);

		static shared_ptr<Equality> Create(const shared_ptr<ConSymbol> s1,const shared_ptr<ConSymbol> s2);

		virtual bool Satisfy() const ;		
	};
}
