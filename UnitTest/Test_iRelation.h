#pragma once
#include "PublicHeader.h"

namespace LogicSystem
{
	class RelationNode;
}

class Test_iRelation
{
public:
	Test_iRelation(void);
	~Test_iRelation(void);

	static void RunTest();

private:
	static void Test_GetString();
	static void Test_RelationLeafSatisfy();
	static void Test_RelationNodeSatisfy();

	///(S0->大,大->于,于->S1)&&(S1->大,大->于,于->S2)
	static shared_ptr<LogicSystem::RelationNode> RelationSample1();
	///(S0->大,大->于,于->S1)||(S1->大,大->于,于->S2)
	static shared_ptr<LogicSystem::RelationNode> RelationSample2();
};

