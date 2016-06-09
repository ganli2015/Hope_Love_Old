#pragma once
#include "InOut.h"

#include "../MindInterface/iLogicKnowledge.h"

namespace LogicSystem
{
	class iExpression;

	///LogicKnowledge contains logic statements.
	class _LOGICSYSTEMINOUT LogicKnowledge : public iLogicKnowledge
	{
		vector<shared_ptr<iLogicStatement>> _statements;

	public:
		LogicKnowledge(void);
		virtual ~LogicKnowledge(void);

		void Add(const shared_ptr<LogicSystem::iLogicStatement> statement) {_statements.push_back(statement);}

		virtual vector<shared_ptr<LogicSystem::iDeduceResult>> Deduce(const shared_ptr<iExpression> expre) const;

		virtual vector<shared_ptr<LogicSystem::iDeduceResult>> Deduce(const shared_ptr<Mind::iConceptInteractTable> expre) const;


		template<class ExpreType>
		vector<shared_ptr<LogicSystem::iDeduceResult>> Deduce(const shared_ptr<ExpreType> expre,const vector<shared_ptr<iLogicStatement>>& statements) const
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
			findResult=for_each(statements.begin(),statements.end(),findResult);

			return findResult.GetResult();
		}
	};
}


