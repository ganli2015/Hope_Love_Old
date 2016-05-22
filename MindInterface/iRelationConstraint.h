#pragma once
#include "InOut.h"

namespace LogicSystem
{
	///iRelationConstraint is the constraint on iRelation.
	///It is the relationship of symbols in a relation.
	class _MINDINTERFACEINOUT iRelationConstraint: public MyObject
	{
	public:
		iRelationConstraint(void);
		virtual ~iRelationConstraint(void);

		virtual bool Satisfy() const =0;
	};
}


