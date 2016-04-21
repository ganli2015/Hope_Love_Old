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

	LogicSystem::LogicResult Logic::Determine( const shared_ptr<Expression> condition,const shared_ptr<Expression> conclusion )
	{
		return Unknown;
	}

}

