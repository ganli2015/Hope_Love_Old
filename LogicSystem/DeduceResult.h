#pragma once
#include "InOut.h"
#include "../MindInterface/iDeduceResult.h"

namespace LogicSystem
{
	template<class ResultType>
	class DeduceResult : public iDeduceResult
	{
		shared_ptr<ResultType> _result;
		double _confidence;

	public:
		DeduceResult(void);
		~DeduceResult(void);
		DeduceResult(const shared_ptr<ResultType> val);

		virtual double Matching(const shared_ptr<iExpression> expre) const;

		virtual shared_ptr<Mind::iConceptInteractTable> GetConceptTable() const ;
		virtual shared_ptr<Mind::iConcept> GetSingleConcept() const;
	};

	template<class ResultType>
	DeduceResult<ResultType>::DeduceResult( const shared_ptr<ResultType> val ):_result(val),_confidence(1.)
	{

	}

	template<class ResultType>
	DeduceResult<ResultType>::~DeduceResult( void )
	{

	}

	template<class ResultType>
	DeduceResult<ResultType>::DeduceResult( void )
	{

	}

	template<class ResultType>
	shared_ptr<Mind::iConcept> DeduceResult<ResultType>::GetSingleConcept() const
	{
		return NULL;
	}

	template<>
	_LOGICSYSTEMINOUT shared_ptr<Mind::iConceptInteractTable> DeduceResult<iRelation>::GetConceptTable() const;

	template<>
	_LOGICSYSTEMINOUT shared_ptr<Mind::iConceptInteractTable> DeduceResult<Mind::iConceptInteractTable>::GetConceptTable() const;

	template<>
	_LOGICSYSTEMINOUT shared_ptr<Mind::iConceptInteractTable> DeduceResult<Mind::iConcept>::GetConceptTable() const;

	template<>
	_LOGICSYSTEMINOUT double DeduceResult<iRelation>::Matching( const shared_ptr<iExpression> expre ) const;

	template<>
	_LOGICSYSTEMINOUT double DeduceResult<Mind::iConceptInteractTable>::Matching( const shared_ptr<iExpression> expre ) const;

	template<>
	_LOGICSYSTEMINOUT double DeduceResult<Mind::iConcept>::Matching( const shared_ptr<iExpression> expre ) const;

	template<>
	_LOGICSYSTEMINOUT shared_ptr<Mind::iConcept> DeduceResult<Mind::iConcept>::GetSingleConcept() const;
}


