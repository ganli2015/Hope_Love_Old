#pragma once
#include "InOut.h"

namespace Mind
{
	class iConceptInteractTable;
}

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT Expression
	{
	public:
		Expression(void);
		virtual ~Expression(void);

		virtual shared_ptr<Mind::iConceptInteractTable> GetInteractTable() const =0;
	};
}


