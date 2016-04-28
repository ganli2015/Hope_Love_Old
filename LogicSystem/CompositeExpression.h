#pragma once
#include "InOut.h"
#include "../MindInterface/iExpression.h"

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT CompositeExpression : public iExpression
	{
		vector<shared_ptr<iExpression>> _expres;

	public:
		CompositeExpression(void);
		virtual ~CompositeExpression(void);

		void AddExpression(const shared_ptr<iExpression> expre);
		void AddExpression(const string expre);

		virtual shared_ptr<Mind::iConceptInteractTable> GetInteractTable() const ;
	};
}


