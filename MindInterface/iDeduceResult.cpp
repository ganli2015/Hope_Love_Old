#include "StdAfx.h"
#include "iDeduceResult.h"

#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/iConcept.h"

namespace LogicSystem
{
	iDeduceResult::iDeduceResult(void)
	{
	}

	iDeduceResult::~iDeduceResult(void)
	{
	}

	std::string iDeduceResult::GetString() const
	{
		string res="";

		shared_ptr<Mind::iConceptInteractTable> table=GetConceptTable();
		if(table!=NULL)
		{
			res+=table->GetString();
		}

		shared_ptr<Mind::iConcept> con=GetSingleConcept();
		if(con!=NULL)
		{
			res+=con->GetString();
		}

		return res;
	}

}

