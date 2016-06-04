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
	class _MINDINTERFACEINOUT iDeduceResult: public Obj<iDeduceResult>
	{

	public:
		iDeduceResult(void);
		~iDeduceResult(void);

		///Return a value indicating how matching <expre> and <me> are.
		///Return 0 for non-matching, and 1 for complete matching.
		virtual double Matching(const shared_ptr<iExpression> expre) const =0;

		///Get the result of the most possibility.
		virtual shared_ptr<Mind::iConceptInteractTable> GetConceptTable() const =0;

		virtual shared_ptr<Mind::iConcept> GetConcept() const =0;
	};
}


