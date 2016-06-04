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
			return GenerateResult(_relationPair.first,_relationPair.second);
		}
		else
		{
			return NULL;
		}
	}

	shared_ptr<iDeduceResult> LogicStatement::Deduce( const shared_ptr<Mind::iConceptInteractTable> condition ) const
	{
		if(_relationPair.first->Satisfy(condition))
		{
			return GenerateResult(_relationPair.first,_relationPair.second);
		}
		else
		{
			return NULL;
		}
	}

	shared_ptr<iDeduceResult> LogicStatement::GenerateResult(const shared_ptr<iRelation> conditionRelation, const shared_ptr<iRelation> resultRelation)
	{
		shared_ptr<iRelation> result=conditionRelation->SymbolResonance(resultRelation);

		if(result!=NULL)
		{
			return shared_ptr<iDeduceResult>(new DeduceResult<iRelation>(result));		
		}
		else
		{
			return NULL;
		}
	}

}

