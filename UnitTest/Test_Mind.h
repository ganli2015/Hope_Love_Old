#pragma once
#include "PublicHeader.h"

namespace LogicSystem
{
	class iRelation;
	class iLogicStatement;
}

namespace Mind
{
	class iConceptInteractTable;
	class ConceptSet;
	struct Connection_Info;

	class Test_Mind
	{
	public:

		static Mind::Connection_Info ParseStrToConnectionInfo(const string line,const Mind::ConceptSet* conceptSet);
	};
}


