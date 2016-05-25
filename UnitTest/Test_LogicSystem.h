#pragma once
#include "PublicHeader.h"

#include "../MindInterface/iExpression.h"
#include "../MindInterface/iConceptInteractTable.h"

///Stub_Expression control the behavior of <GetProtoInteractTable>
///You can pass the desired table to <me> instead of sentence analysis.
class Stub_Expression : public LogicSystem::iExpression
{
	shared_ptr<Mind::iConceptInteractTable> _table;
public:
	///Pass the desired table to <me>
	Stub_Expression(const shared_ptr<Mind::iConceptInteractTable> table):_table(table){};
	~Stub_Expression(){}

	virtual shared_ptr<Mind::iConceptInteractTable> GetBaseInteractTable() const { return NULL ;};
	virtual shared_ptr<Mind::iConceptInteractTable> GetProtoInteractTable() const {return _table;};
};

