#pragma once
#include "InOut.h"

namespace LogicSystem
{
	class iRelation;
	class iExpression;
	class iDeduceResult;

	///A logic statement tells a result under some input conditions.
	///It is not necessarily true, but has some confidence.
	class _MINDINTERFACEINOUT iLogicStatement: public Obj<iLogicStatement>
	{

	public:
		iLogicStatement(void);
		~iLogicStatement(void);

		virtual shared_ptr<iDeduceResult> Deduce(const shared_ptr<iExpression> condition) const =0;
	};
}


