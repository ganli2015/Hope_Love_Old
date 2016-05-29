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

class ConceptCreator;
class SymbolCreator;

class Test_iRelation :public testing::Test
{
protected:
	static shared_ptr<ConceptCreator> _conceptCreator;

public:
	///Set number of Arbitrariness zero.
	static void ClearArbNum();

	static void SetUpTestCase() ;
	static void TearDownTestCase() ;

	static bool InterTableSatisfyRelation(shared_ptr<LogicSystem::RelationLeaf> leaf1,shared_ptr<Mind::iConceptInteractTable> interTable);
	static bool InterTableSatisfyRelation(shared_ptr<LogicSystem::RelationNode> leaf1,shared_ptr<Mind::iConceptInteractTable> interTable);

};


