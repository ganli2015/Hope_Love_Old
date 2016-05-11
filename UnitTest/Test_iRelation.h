#pragma once
#include "PublicHeader.h"

namespace LogicSystem
{
	class RelationNode;
	class RelationLeaf;
}

class Test_iRelation
{
public:
	Test_iRelation(void);
	~Test_iRelation(void);

	static void RunTest();

	///condition: S0����S1,S1����S2. result: S0����S2.
	static void RelationPair(shared_ptr<LogicSystem::RelationNode> condition,shared_ptr<LogicSystem::RelationLeaf> result );
private:
	static void Test_GetString();
	static void Test_RelationLeafSatisfy();
	static void Test_RelationNodeSatisfy();
	static void Test_iRelationResonance();

	///(S0->��,��->��,��->S1)&&(S1->��,��->��,��->S2)
	static shared_ptr<LogicSystem::RelationNode> RelationSample1();
	///(S0->��,��->��,��->S1)||(S1->��,��->��,��->S2)
	static shared_ptr<LogicSystem::RelationNode> RelationSample2();
};

