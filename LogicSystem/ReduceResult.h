#pragma once
#include "InOut.h"
#include "../MindInterface/iReduceResult.h"

namespace LogicSystem
{
	class ReduceResult : public iReduceResult
	{
		shared_ptr<Mind::iConceptInteractTable> _table;

	public:
		ReduceResult(void);
		~ReduceResult(void);

		virtual shared_ptr<Mind::iConceptInteractTable> GetConceptTable() const {return _table;} ;
	};
}


