#pragma once
#include "InOut.h"
#include "../MindInterface/iLogicStatement.h"

namespace Mind
{
	class iConceptInteractTable;
}

namespace LogicSystem
{
	class iLogicStatement;
	class iDeduceResult;
	class iExpression;

	//////////////////////////////////////////////////////////////////////////
	///Contain logic statements.
	//////////////////////////////////////////////////////////////////////////
	class _MINDINTERFACEINOUT iLogicKnowledge : public Obj<iLogicKnowledge>
	{
	public:
		iLogicKnowledge(void);
		virtual~iLogicKnowledge(void);

		virtual void Add(const shared_ptr<LogicSystem::iLogicStatement> statement) =0;

		//////////////////////////////////////////////////////////////////////////
		///Deduce from the condition <expre>.
		//////////////////////////////////////////////////////////////////////////
		virtual vector<shared_ptr<LogicSystem::iDeduceResult>> Deduce(const shared_ptr<iExpression> expre) const =0;

		virtual vector<shared_ptr<LogicSystem::iDeduceResult>> Deduce(const shared_ptr<Mind::iConceptInteractTable> expre) const =0;

	};
}


