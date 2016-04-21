#pragma once
#include "InOut.h"
#include "Expression.h"

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT CompositeExpression : public Expression
	{
	public:
		CompositeExpression(void);
		~CompositeExpression(void);

		void AddExpression(const shared_ptr<Expression> expre);
		void AddExpression(const string expre);
	};
}


