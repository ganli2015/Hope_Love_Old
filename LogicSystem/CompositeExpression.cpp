#include "StdAfx.h"
#include "CompositeExpression.h"

#include "../MindInterface/iConceptInteractTable.h"


namespace LogicSystem
{
	CompositeExpression::CompositeExpression(void)
	{
	}


	CompositeExpression::~CompositeExpression(void)
	{
	}

	void CompositeExpression::AddExpression( const shared_ptr<iExpression> expre )
	{

	}

	void CompositeExpression::AddExpression( const string expre )
	{

	}

	shared_ptr<Mind::iConceptInteractTable> CompositeExpression::GetBaseInteractTable() const
	{
		return NULL;
	}

	shared_ptr<Mind::iConceptInteractTable> CompositeExpression::GetProtoInteractTable() const
	{
		return NULL;
	}


}

