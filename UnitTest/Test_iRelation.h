#pragma once
#include "PublicHeader.h"

namespace LogicSystem
{
	class RelationNode;
	class RelationLeaf;
}

namespace Mind
{
	class iConceptInteractTable;
}

class Test_iRelationFun
{
public:
	static bool InterTableSatisfyRelation(shared_ptr<LogicSystem::RelationLeaf> leaf1,shared_ptr<Mind::iConceptInteractTable> interTable);
	static bool InterTableSatisfyRelation(shared_ptr<LogicSystem::RelationNode> leaf1,shared_ptr<Mind::iConceptInteractTable> interTable);

	///(S0->大,大->于,于->S1)&&(S1->大,大->于,于->S2)
	static shared_ptr<LogicSystem::RelationNode> RelationSample1();
	///(S0->大,大->于,于->S1)||(S1->大,大->于,于->S2)
	static shared_ptr<LogicSystem::RelationNode> RelationSample2();
	///condition: S0大于S1,S1大于S2. result: S0大于S2.
	static void RelationPair(shared_ptr<LogicSystem::RelationNode> condition,shared_ptr<LogicSystem::RelationLeaf> result );
};
