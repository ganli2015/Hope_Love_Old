#pragma once
#include "InOut.h"

namespace LogicSystem
{
	enum LogicResult
	{
		True,
		False,
		Unknown
	};

	class Expression;

	class _LOGICSYSTEMINOUT Logic
	{
	public:
		Logic(void);
		~Logic(void);

		//判断能否根据条件condition来得出结论conclusion.
		static LogicResult Determine(const shared_ptr<Expression> condition,const shared_ptr<Expression> conclusion);
	};
}


