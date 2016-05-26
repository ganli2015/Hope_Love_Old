#pragma once
#include "InOut.h"
#include "../MindInterface/iDeduceResult.h"

namespace LogicSystem
{
	class DeduceResult : public iDeduceResult
	{
		shared_ptr<iRelation> _result;
		double _confidence;

	public:
		DeduceResult(void);
		~DeduceResult(void);
		DeduceResult(const shared_ptr<iRelation> val);

		virtual void Set(const shared_ptr<iRelation> val,const double confidence=1.);

		virtual double Matching(const shared_ptr<iExpression> expre) ;

		virtual shared_ptr<Mind::iConceptInteractTable> GetConceptTable() const ;
	};
}


