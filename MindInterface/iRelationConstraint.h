#pragma once
#include "InOut.h"

namespace LogicSystem
{
	//iRelationConstraint is the constraint on iRelation.
	class _MINDINTERFACEINOUT iRelationConstraint: public MyObject
	{
	public:
		iRelationConstraint(void);
		virtual ~iRelationConstraint(void);

		virtual bool Satisfy() const =0;
	};
}


