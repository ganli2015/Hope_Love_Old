#pragma once
#include "InOut.h"

namespace Mind
{
	class iConceptInteractTable;
}

namespace LogicSystem
{
	class _MINDINTERFACEINOUT iExpression
	{
	public:
		iExpression(void);
		virtual ~iExpression(void);

		virtual shared_ptr<Mind::iConceptInteractTable> GetInteractTable() const =0;
	};
}

