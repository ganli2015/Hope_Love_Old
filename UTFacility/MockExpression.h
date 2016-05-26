#pragma once
#include "PublicHeader.h"
#include "../MindInterface/iExpression.h"
#include "../MindInterface/iConceptInteractTable.h"



///MockExpression control the behavior of <GetProtoInteractTable>
///You can pass the desired table to <me> instead of sentence analysis.
#include <gmock/gmock.h>

class MockExpression : public LogicSystem::iExpression
{
public:
	MOCK_CONST_METHOD0(GetBaseInteractTable, shared_ptr<Mind::iConceptInteractTable>());
	MOCK_CONST_METHOD0(GetProtoInteractTable, shared_ptr<Mind::iConceptInteractTable>());
};

