#include "StdAfx.h"
#include "WordRelationTable.h"
#include "ConceptInteractTable.h"

namespace Mind
{
	WordRelationTable::WordRelationTable(void)
	{
	}

	WordRelationTable::WordRelationTable( shared_ptr<ConceptInteractTable> table ):_table(table)
	{

	}


	WordRelationTable::~WordRelationTable(void)
	{
	}
}

