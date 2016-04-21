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

		//�ж��ܷ��������condition���ó�����conclusion.
		static LogicResult Determine(const shared_ptr<Expression> condition,const shared_ptr<Expression> conclusion);
	};
}


