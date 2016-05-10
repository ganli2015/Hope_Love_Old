#pragma once
#include "InOut.h"
#include "../MindInterface/iLogic.h"

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT Logic : public iLogic
	{
	public:
		Logic(void);
		~Logic(void);

		virtual LogicResult Determine(const shared_ptr<iExpression> condition,const shared_ptr<iExpression> conclusion) ;		
	};
}


