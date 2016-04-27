#pragma once
#include "InOut.h"
#include "Expression.h"

namespace DataCollection
{
	class Sentence;
}

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT SingleExpression : public Expression
	{
		shared_ptr<DataCollection::Sentence> _sen;

	public:
		SingleExpression(void);
		virtual ~SingleExpression(void);

		SingleExpression(const string val);
		SingleExpression(const shared_ptr<DataCollection::Sentence> val);

		virtual shared_ptr<Mind::iConceptInteractTable> GetInteractTable() const;
	};
}


