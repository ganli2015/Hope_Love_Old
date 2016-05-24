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

class Test_iRelation
{
public:
	///Set number of Arbitrariness zero.
	static void ClearArbNum();
};

class Test_iRelationFun
{
public:
	static bool InterTableSatisfyRelation(shared_ptr<LogicSystem::RelationLeaf> leaf1,shared_ptr<Mind::iConceptInteractTable> interTable);
	static bool InterTableSatisfyRelation(shared_ptr<LogicSystem::RelationNode> leaf1,shared_ptr<Mind::iConceptInteractTable> interTable);

	///(S0->��,��->��,��->S1)&&(S1->��,��->��,��->S2)
	static shared_ptr<LogicSystem::RelationNode> RelationSample1();
	///(S0->��,��->��,��->S1)||(S1->��,��->��,��->S2)
	static shared_ptr<LogicSystem::RelationNode> RelationSample2();
	///(Num0->��,��->Num1)
	static shared_ptr<LogicSystem::RelationLeaf> RelationSample3();
	///condition: S0����S1,S1����S2. result: S0����S2.
	static void RelationPair(shared_ptr<LogicSystem::RelationNode> condition,shared_ptr<LogicSystem::RelationLeaf> result );
	///condition: Num0->��,��->Num1. result: Num0->��,��->һ,Num1->��,��->��.
	static void RelationPair2(shared_ptr<LogicSystem::RelationNode> condition,shared_ptr<LogicSystem::RelationLeaf> result );
};
