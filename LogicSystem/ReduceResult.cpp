#include "StdAfx.h"
#include "ReduceResult.h"

#include "../MindInterface/iConcept.h"
#include "../MindInterface/iConceptInteractTable.h"

namespace LogicSystem
{
	ReduceResult::ReduceResult(void)
	{
	}


	ReduceResult::~ReduceResult(void)
	{
	}

	ReduceResult::ReduceResult(const shared_ptr<Mind::iConceptInteractTable> val):_table(val)
	{

	}

	ReduceResult_SingleConcept::ReduceResult_SingleConcept()
	{

	}

	ReduceResult_SingleConcept::ReduceResult_SingleConcept( const shared_ptr<Mind::iConcept> val ):_concept(val)
	{

	}

	ReduceResult_SingleConcept::~ReduceResult_SingleConcept( void )
	{

	}

}

