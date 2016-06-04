#include "StdAfx.h"
#include "DeduceResult.h"

#include "../MindInterface/iRelation.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/iExpression.h"
#include "../MindInterface/iConcept.h"

#include "../Mathmatic/MathTool.h"

namespace LogicSystem
{
	template<>
	double DeduceResult<iRelation>::Matching( const shared_ptr<iExpression> expre ) const
	{
		if(!_result->Satisfy(expre))
		{
			return 0.;
		}
		else
		{
			return _confidence;
		}
	}

	template<>
	double DeduceResult<Mind::iConceptInteractTable>::Matching( const shared_ptr<iExpression> expre ) const
	{
		shared_ptr<Mind::iConceptInteractTable> protoTable=expre->GetProtoInteractTable();

		if(protoTable==NULL || Math::DoubleCompare(protoTable->Similarity(_result),1)!=0)
		{
			return 0.;
		}
		else
		{
			return _confidence;
		}
	}

	template<>
	double DeduceResult<Mind::iConcept>::Matching( const shared_ptr<iExpression> expre ) const
	{
		shared_ptr<Mind::iConcept> con=expre->GetProtoConcept();

		if(con==NULL || !con->Same(_result))
		{
			return 0.;
		}
		else
		{
			return _confidence;
		}
	}

	template<>
	shared_ptr<Mind::iConceptInteractTable> DeduceResult<iRelation>::GetConceptTable() const
	{
		if(_result==NULL) 
		{
			return NULL;
		}
		else
			return _result->GenerateConceptTable();
	}

	template<>
	shared_ptr<Mind::iConceptInteractTable> DeduceResult<Mind::iConceptInteractTable>::GetConceptTable() const
	{
		return _result;
	}

	template<>
	shared_ptr<Mind::iConceptInteractTable> DeduceResult<Mind::iConcept>::GetConceptTable() const
	{
		return NULL;
	}

	template<>
	shared_ptr<Mind::iConcept> DeduceResult<Mind::iConcept>::GetConcept() const
	{
		return _result;
	}
}

