#include "StdAfx.h"
#include "LogicKnowledge.h"

#include "../MindInterface/iConceptInteractTable.h"

namespace LogicSystem
{
	LogicKnowledge::LogicKnowledge(void)
	{
	}


	LogicKnowledge::~LogicKnowledge(void)
	{
	}

	vector<shared_ptr<LogicSystem::iDeduceResult>> LogicKnowledge::Deduce( const shared_ptr<iExpression> expre ) const
	{
		return Deduce(expre,_statements);
	}

	vector<shared_ptr<LogicSystem::iDeduceResult>> LogicKnowledge::Deduce( const shared_ptr<Mind::iConceptInteractTable> expre ) const
	{
		return Deduce(expre,_statements);
	}

}

