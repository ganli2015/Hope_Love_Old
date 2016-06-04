#pragma once
#include "InOut.h"
#include "../MindInterface/iLogicStatement.h"

namespace LogicSystem
{
	
	class _LOGICSYSTEMINOUT LogicStatement : public iLogicStatement
	{
		pair<shared_ptr<iRelation>,shared_ptr<iRelation>> _relationPair;

	public:
		LogicStatement(const shared_ptr<iRelation> condition,const shared_ptr<iRelation> result);
		~LogicStatement(void);

		virtual shared_ptr<iDeduceResult> Deduce(const shared_ptr<iExpression> condition) const ;
		virtual shared_ptr<iDeduceResult> Deduce(const shared_ptr<Mind::iConceptInteractTable> condition) const;

	private:
		static shared_ptr<iDeduceResult> GenerateResult(const shared_ptr<iRelation> conditionRelation, const shared_ptr<iRelation> resultRelation);
	};
}


