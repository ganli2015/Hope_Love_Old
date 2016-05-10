#pragma once
#include "InOut.h"
#include "../MindInterface/iDeduceResult.h"

namespace LogicSystem
{
	class DeduceResult : public iDeduceResult
	{
		vector<shared_ptr<iRelation>> _relation;

	public:
		DeduceResult(void);
		~DeduceResult(void);
		DeduceResult(const shared_ptr<iRelation> val);

		virtual void Add(const shared_ptr<iRelation> val) {_relation.push_back(val);}

		virtual double Matching(const shared_ptr<iExpression> expre) ;
	};
}


