#pragma once
#include "InOut.h"

#include "../MindInterface/iLogicStatement.h"

namespace LogicSystem
{
	class iRelation;
	class iExpression;
	class iDeduceResult;
}

namespace Mind
{
	///LogicKnowledge contains logic statements.
	class LogicKnowledge : public Obj<LogicKnowledge>
	{
		vector<shared_ptr<LogicSystem::iLogicStatement>> _statements;

	public:
		LogicKnowledge(void);
		~LogicKnowledge(void);

		void Add(const shared_ptr<LogicSystem::iLogicStatement> statement) {_statements.push_back(statement);}

		template<class ExpreType>
		vector<shared_ptr<LogicSystem::iDeduceResult>> Deduce(const shared_ptr<ExpreType> expre) const
		{
			class FindResult
			{
				shared_ptr<ExpreType> _condition;
				vector<shared_ptr<LogicSystem::iDeduceResult>> _result;

			public:
				FindResult(const shared_ptr<ExpreType> expre):_condition(expre){}
				~FindResult(){}

				vector<shared_ptr<LogicSystem::iDeduceResult>> GetResult() const {return _result;}

				void operator()(const shared_ptr<LogicSystem::iLogicStatement> logicStatement)
				{
					shared_ptr<LogicSystem::iDeduceResult> result=logicStatement->Deduce(_condition);
					if(result!=NULL)
					{
						_result.push_back(result);
					}
				}
			};

			FindResult findResult(expre);
			findResult=for_each(_statements.begin(),_statements.end(),findResult);

			return findResult.GetResult();
		}
	};
}


