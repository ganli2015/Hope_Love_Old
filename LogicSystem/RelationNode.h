#pragma once
#include "InOut.h"
#include "../MindInterface/iRelation.h"

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT RelationNode : public iRelationNode
	{
		const string _andTag;
		const string _orTag;
	public:
		RelationNode(void);
		~RelationNode(void);

		virtual string GetString() const ;
		virtual bool Satisfy(const shared_ptr<iExpression> expre) const ;

	};
}


