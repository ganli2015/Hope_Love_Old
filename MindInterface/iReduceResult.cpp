#include "StdAfx.h"
#include "iReduceResult.h"

#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/iConcept.h"

namespace LogicSystem
{
	iReduceResult::iReduceResult(void)
	{
	}


	iReduceResult::~iReduceResult(void)
	{
	}

	std::string iReduceResult::GetString() const
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

