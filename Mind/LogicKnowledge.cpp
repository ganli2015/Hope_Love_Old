#include "StdAfx.h"
#include "LogicKnowledge.h"

#include "../MindInterface/iLogicStatement.h"

using namespace LogicSystem;

namespace Mind
{
	LogicKnowledge::LogicKnowledge(void)
	{
	}


	LogicKnowledge::~LogicKnowledge(void)
	{
	}

	vector<shared_ptr<LogicSystem::iDeduceResult>> LogicKnowledge::Deduce( const shared_ptr<LogicSystem::iExpression> expre ) const
	{
		class FindResult
		{
			shared_ptr<LogicSystem::iExpression> _condition;
			vector<shared_ptr<iDeduceResult>> _result;

		public:
			FindResult(const shared_ptr<LogicSystem::iExpression> expre):_condition(expre){}
			~FindResult(){}

			vector<shared_ptr<iDeduceResult>> GetResult() const {return _result;}

			void operator()(const shared_ptr<iLogicStatement> logicStatement)
			{
				shared_ptr<iDeduceResult> result=logicStatement->Deduce(_condition);
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
}

