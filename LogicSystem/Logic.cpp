#include "StdAfx.h"
#include "Logic.h"

namespace LogicSystem
{
	Logic::Logic(void)
	{
	}


	Logic::~Logic(void)
	{
	}

	LogicSystem::LogicResult Logic::Determine( const shared_ptr<iExpression> condition,const shared_ptr<iExpression> conclusion )
	{
		return Unknown;
	}

}

