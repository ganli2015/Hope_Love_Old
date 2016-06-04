#pragma once
#include "PublicHeader.h"
#include "../MindInterface/iExpression.h"
#include "../MindInterface/iConceptInteractTable.h"



///MockExpression control the behavior of <GetProtoInteractTable>
///You can pass the desired table to <me> instead of sentence analysis.
#include <gmock/gmock.h>

class _UTFACILITYINOUT MockExpression : public LogicSystem::iExpression
{
public:
	MOCK_CONST_METHOD0(GetBaseInteractTable, shared_ptr<Mind::iConceptInteractTable>());
	MOCK_CONST_METHOD0(GetProtoInteractTable, shared_ptr<Mind::iConceptInteractTable>());
	MOCK_CONST_METHOD0(GetProtoConcept, shared_ptr<Mind::iConcept>());

	///Create a MockExpression which returns ProtoInteractTable of <table> and BaseInteractTable of null.
	static shared_ptr<MockExpression> Create(const string table);
	static shared_ptr<MockExpression> SimpleCreate(const string table);
	static shared_ptr<MockExpression> Create();

	void AddExpectCall_GetProtoConcept(const string concept);
};



