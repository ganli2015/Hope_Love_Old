#pragma once
#include "InOut.h"
#include "../MindInterface/iReduceResult.h"

namespace LogicSystem
{
	class ReduceResult : public iReduceResult
	{
		shared_ptr<Mind::iConceptInteractTable> _table;

	public:
		ReduceResult(void);
		~ReduceResult(void);
		ReduceResult(const shared_ptr<Mind::iConceptInteractTable> val);

		virtual shared_ptr<Mind::iConceptInteractTable> GetConceptTable() const {return _table;} ;

		virtual shared_ptr<Mind::iConcept> GetSingleConcept() const {return NULL;}

	};

	class ReduceResult_SingleConcept: public iReduceResult
	{
		shared_ptr<Mind::iConcept> _concept;

	public:
		ReduceResult_SingleConcept(void);
		~ReduceResult_SingleConcept(void);
		ReduceResult_SingleConcept(const shared_ptr<Mind::iConcept> val);

		virtual shared_ptr<Mind::iConceptInteractTable> GetConceptTable() const {return NULL;} ;

		virtual shared_ptr<Mind::iConcept> GetSingleConcept() const {return _concept;}
	};
}


