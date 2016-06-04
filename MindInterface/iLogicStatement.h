#pragma once
#include "InOut.h"

namespace Mind
{
	class iConceptInteractTable;
}

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

		///Deduce results from <condition>.
		///If only part of <condition> can deduce something , 
		///then the result only contains deduction result from that part and the other part will be dropped.
		virtual shared_ptr<iDeduceResult> Deduce(const shared_ptr<iExpression> condition) const =0;
		virtual shared_ptr<iDeduceResult> Deduce(const shared_ptr<Mind::iConceptInteractTable> condition) const =0;
	};
}


