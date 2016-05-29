#pragma once
#include "PublicHeader.h"

namespace LogicSystem
{
	class RelationNode;
	class RelationLeaf;
	class iLogicElementCreator;
}

class ConceptCreator;
class SymbolCreator;



class _UTFACILITYINOUT iRelationSample
{
	static shared_ptr<SymbolCreator> _symbolCreator;

	typedef LogicSystem::iLogicElementCreator LogicCreator;

public:

	///(S0->��,��->��,��->S1)&&(S1->��,��->��,��->S2)
	static shared_ptr<LogicSystem::RelationNode> RelationSample1();
	///(S0->��,��->��,��->S1)||(S1->��,��->��,��->S2)
	static shared_ptr<LogicSystem::RelationNode> RelationSample2();
	///(Num0->��,��->Num1)
	static shared_ptr<LogicSystem::RelationLeaf> RelationSample3();


	///condition: S0����S1,S1����S2. result: S0����S2.
	static void RelationPair(shared_ptr<LogicSystem::RelationNode> condition,shared_ptr<LogicSystem::RelationLeaf> result );
	///condition: Num0->��,��->Num1. result: Num0->��,��->һ,Num1->��,��->��.
	static void RelationPair2(shared_ptr<LogicSystem::RelationLeaf> condition,shared_ptr<LogicSystem::RelationLeaf> result );
	///condition: Num0->��,��->Verb0,Verb1->Arb0. result: Verb0->Arb0 X3 
	static void RelationPair3(shared_ptr<LogicSystem::RelationLeaf>& condition,shared_ptr<LogicSystem::RelationLeaf>& result );
 
};
