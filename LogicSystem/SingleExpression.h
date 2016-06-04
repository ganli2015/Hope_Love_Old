#pragma once
#include "InOut.h"
#include "../MindInterface/iExpression.h"

namespace DataCollection
{
	class Sentence;
}

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT SingleExpression : public iExpression
	{
		shared_ptr<DataCollection::Sentence> _sen;

	public:
		SingleExpression(void);
		virtual ~SingleExpression(void);

		SingleExpression(const string val);
		SingleExpression(const shared_ptr<DataCollection::Sentence> val);

		virtual shared_ptr<Mind::iConceptInteractTable> GetBaseInteractTable() const;
		virtual shared_ptr<Mind::iConceptInteractTable> GetProtoInteractTable() const;

		virtual shared_ptr<Mind::iConcept> GetProtoConcept() const ;
	};
}


