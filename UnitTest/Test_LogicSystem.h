#pragma once
#include "PublicHeader.h"

namespace LogicSystem
{
	class iRelationNode;
}

class Test_LogicSystem
{
public:
	Test_LogicSystem(void);
	~Test_LogicSystem(void);

	static void RunTest();

private:
	static void Test_Expression();
	static void Test_Logic_Determine();
	static void Test_Relation();

private:
	///(S0->大,大->于,于->S1)&&(S1->大,大->于,于->S2)
	static shared_ptr<LogicSystem::iRelationNode> RelationSample1();
};

