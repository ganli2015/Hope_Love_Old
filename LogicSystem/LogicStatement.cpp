#include "StdAfx.h"
#include "LogicStatement.h"
#include "DeduceResult.h"

#include "../MindInterface/iRelation.h"

namespace LogicSystem
{
	LogicStatement::LogicStatement(const shared_ptr<iRelation> condition,const shared_ptr<iRelation> result):_relationPair(make_pair(condition,result))
	{
	}


	LogicStatement::~LogicStatement(void)
	{
	}

	shared_ptr<iDeduceResult> LogicStatement::Deduce( const shared_ptr<iExpression> condition ) const
	{
		if(_relationPair.first->Satisfy(condition))
		{
			shared_ptr<iRelation> resultRelation=_relationPair.first->SymbolResonance(_relationPair.second);

			if(resultRelation!=NULL)
			{
				return shared_ptr<DeduceResult>(new DeduceResult(resultRelation));		
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return NULL;
		}
	}

}

