#include "StdAfx.h"
#include "CompositeExpression.h"

#include "../MindElement/ConceptInteractTable.h"

namespace LogicSystem
{
	CompositeExpression::CompositeExpression(void)
	{
	}


	CompositeExpression::~CompositeExpression(void)
	{
	}

	void CompositeExpression::AddExpression( const shared_ptr<Expression> expre )
	{

	}

	void CompositeExpression::AddExpression( const string expre )
	{

	}

	shared_ptr<Mind::ConceptInteractTable> CompositeExpression::GetInteractTable() const
	{
		return NULL;
	}

}

