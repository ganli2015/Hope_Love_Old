#pragma once
#include "InOut.h"

namespace Mind
{
	class iConceptInteractTable;
}

namespace LogicSystem
{
	///iReduceResult contains the information of reduction .
	class _MINDINTERFACEINOUT iReduceResult: public Obj<iReduceResult>
	{
	public:
		iReduceResult(void);
		~iReduceResult(void);

		///Get the result represented as .iConceptInteractTable.
		virtual shared_ptr<Mind::iConceptInteractTable> GetConceptTable() const =0;
	};
}


