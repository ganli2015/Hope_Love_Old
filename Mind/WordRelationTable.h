#pragma once
#include "InOut.h"

namespace Mind
{
	class ConceptInteractTable;

	class _MINDINOUT WordRelationTable
	{
		shared_ptr<ConceptInteractTable> _table;

	public:
		WordRelationTable(void);
		~WordRelationTable(void);
		WordRelationTable(shared_ptr<ConceptInteractTable> table);

	};
}


