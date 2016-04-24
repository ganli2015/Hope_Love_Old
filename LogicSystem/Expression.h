#pragma once
#include "InOut.h"

namespace Mind
{
	class ConceptInteractTable;
}

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT Expression
	{
	public:
		Expression(void);
		virtual ~Expression(void);

		virtual shared_ptr<Mind::ConceptInteractTable> GetInteractTable() const =0;
	};
}


