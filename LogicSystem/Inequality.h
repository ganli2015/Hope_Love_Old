#pragma once
#include "InOut.h"
#include "../MindInterface/iRelationConstraint.h"
#include "../MindInterface/iRelation.h"

namespace Mind
{
	class iConcept;
}

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT Inequality :  public iRelationConstraint
	{
		typedef LogicType::ConSymbol ConSymbol;		

		shared_ptr<ConSymbol> _s1,_s2;

	public:
		Inequality(const shared_ptr<ConSymbol> s1,const shared_ptr<ConSymbol> s2);
		~Inequality(void);

		static shared_ptr<Inequality> Create(const shared_ptr<ConSymbol> s1,const shared_ptr<ConSymbol> s2);

		virtual bool Satisfy() const ;		
	};
}


