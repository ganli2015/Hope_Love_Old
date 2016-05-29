#pragma once
#include "PublicHeader.h"

namespace LogicSystem
{
	class iLogicStatement;
}

class Test_LogicSystem
{
public:

	static void TestLogicStatementDeduce(const shared_ptr<LogicSystem::iLogicStatement> logicStatment,
		const string conditionStr,const string expectResultStr);
};