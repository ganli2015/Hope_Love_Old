#pragma once
#include "InOut.h"

namespace LogicSystem
{
	class iLogicStatement;
	class iRelation;
	class iExpression;
	class iDeduceResult;
}

namespace Mind
{
	///LogicKnowledge contains logic statements.
	class LogicKnowledge
	{
		vector<shared_ptr<LogicSystem::iLogicStatement>> _statements;

	public:
		LogicKnowledge(void);
		~LogicKnowledge(void);

		void Add(const shared_ptr<LogicSystem::iLogicStatement> statement) {_statements.push_back(statement);}

		vector<shared_ptr<LogicSystem::iDeduceResult>> Deduce(const shared_ptr<LogicSystem::iExpression> expre) const;
	};
}


