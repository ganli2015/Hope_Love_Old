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

	class iExpression;

	class _LOGICSYSTEMINOUT Logic
	{
	public:
		Logic(void);
		~Logic(void);

		//�ж��ܷ��������condition���ó�����conclusion.
		//<condition> should have been analyzed!
		static LogicResult Determine(const shared_ptr<iExpression> condition,const shared_ptr<iExpression> conclusion);
	};
}


