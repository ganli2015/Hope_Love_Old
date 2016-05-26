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

	///iDeduceResult contains the information of deduction .
	class _MINDINTERFACEINOUT iDeduceResult: public MyObject
	{

	public:
		iDeduceResult(void);
		~iDeduceResult(void);

		virtual void Set(const shared_ptr<iRelation> val,const double confidence=1.) =0;

		///Return a value indicating how matching <expre> and <me> are.
		///Return 0 for non-matching, and 1 for complete matching.
		virtual double Matching(const shared_ptr<iExpression> expre) =0;

		///Get the result of the most possibility.
		virtual shared_ptr<Mind::iConceptInteractTable> GetConceptTable() const =0;
	};
}


