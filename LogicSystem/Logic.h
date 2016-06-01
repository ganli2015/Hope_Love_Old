#pragma once
#include "InOut.h"
#include "../MindInterface/iLogic.h"

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT Logic : public iLogic
	{
	public:
		Logic(void);
		~Logic(void);

		virtual LogicResult Determine(const shared_ptr<iExpression> condition,const shared_ptr<iExpression> conclusion) const;

		virtual vector<shared_ptr<iDeduceResult>> Deduce(const shared_ptr<iExpression> condition)  const;

		virtual vector<shared_ptr<iDeduceResult>> FinalDeduce(const shared_ptr<iExpression> condition)  const;

		virtual vector<shared_ptr<iReduceResult>> Reduce(const shared_ptr<Mind::iConceptInteractTable> conceptTable) const ;
	};
}


