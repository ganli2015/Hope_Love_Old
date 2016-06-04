#include "StdAfx.h"
#include "CompositeExpression.h"
#include "SingleExpression.h"

#include "../MindInterface/iConceptInteractTable.h"

using namespace Mind;

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
		_expres.push_back(expre);
	}

	void CompositeExpression::AddExpression( const string expre )
	{
		_expres.push_back(shared_ptr<SingleExpression>(new SingleExpression(expre)));
	}

	void CompositeExpression::AddExpression( const shared_ptr<DataCollection::Sentence> val )
	{
		_expres.push_back(shared_ptr<SingleExpression>(new SingleExpression(val)));
	}

	shared_ptr<Mind::iConceptInteractTable> CompositeExpression::GetBaseInteractTable() const
	{
		if(_expres.empty()) return NULL;

		shared_ptr<iConceptInteractTable> res=_expres.front()->GetBaseInteractTable();
		for (unsigned int i=1;i<_expres.size();++i)
		{
			res->Absorb(_expres[i]->GetBaseInteractTable());
		}

		return res;
	}

	shared_ptr<Mind::iConceptInteractTable> CompositeExpression::GetProtoInteractTable() const
	{
		if(_expres.empty()) return NULL;

		shared_ptr<iConceptInteractTable> res=_expres.front()->GetProtoInteractTable();
		for (unsigned int i=1;i<_expres.size();++i)
		{
			res->Absorb(_expres[i]->GetProtoInteractTable());
		}

		return res;
	}

	shared_ptr<Mind::iConcept> CompositeExpression::GetProtoConcept() const
	{
		return NULL;
	}


}

