#include "StdAfx.h"
#include "LogicElementCreator.h"
#include "SingleExpression.h"
#include "CompositeExpression.h"
#include "LogicStatement.h"
#include "RelationLeaf.h"
#include "RelationNode.h"
#include "Logic.h"
#include "Symbol.h"
#include "Arbitrariness.h"
#include "Number.h"
#include "Equality.h"
#include "Inequality.h"

#include "../MindInterface/iConcept.h"

namespace LogicSystem
{
	LogicElementCreator::LogicElementCreator(void)
	{
		Init();
	}


	LogicElementCreator::~LogicElementCreator(void)
	{
	}

	shared_ptr<iExpression> LogicElementCreator::CreateExpression( const string str ) const
	{
		return shared_ptr<SingleExpression>(new SingleExpression(str));
	}

	shared_ptr<iExpression> LogicElementCreator::CreateExpression( const vector<string> str ) const
	{
		shared_ptr<CompositeExpression> com(new CompositeExpression());
		for (unsigned int i=0;i<str.size();++i)
		{
			com->AddExpression(str[i]);
		}

		return com;
	}

	shared_ptr<iExpression> LogicElementCreator::CreateExpression( const shared_ptr<DataCollection::Sentence> val ) const
	{
		return shared_ptr<SingleExpression>(new SingleExpression(val));
	}

	shared_ptr<iExpression> LogicElementCreator::CreateExpression( const vector<shared_ptr<DataCollection::Sentence>> val ) const
	{
		shared_ptr<CompositeExpression> com(new CompositeExpression());
		for (unsigned int i=0;i<val.size();++i)
		{
			com->AddExpression(val[i]);
		}

		return com;
	}

	shared_ptr<iLogicStatement> LogicElementCreator::CreateLogicStatement( const shared_ptr<iRelation> condition,const shared_ptr<iRelation> result ) const
	{
		return shared_ptr<LogicStatement>(new LogicStatement(condition,result));
	}

	shared_ptr<iRelationLeaf> LogicElementCreator::CreateRelationLeaf() const
	{
		return shared_ptr<RelationLeaf>(new RelationLeaf());
	}

	shared_ptr<iRelationNode> LogicElementCreator::CreateRelationNode() const
	{
		return shared_ptr<RelationNode>(new RelationNode());
	}

	shared_ptr<iLogic> LogicElementCreator::CreateLogic() const
	{
		return shared_ptr<Logic>(new Logic());
	}

	shared_ptr<LogicType::ConSymbol> LogicElementCreator::CreateConceptSymbol( const shared_ptr<Mind::iConcept> con ) const
	{
		return shared_ptr<LogicType::ConSymbol>(new Symbol<Mind::iConcept>(con));
	}

	shared_ptr<LogicType::ConSymbol> LogicElementCreator::CreateSpecialSymbol( const SymbolType type ) const
	{
		if(_spSym.count(type)==0)
		{
			return NULL;
		}
		else
			return _spSym.at(type)->Create();
	}

	void LogicElementCreator::Init()
	{
		_spSym[Host::Arb]=new SpecialSymbolCreator<Arbitrariness<Mind::iConcept>>();
		_spSym[Host::Num]=new SpecialSymbolCreator<Number<Mind::iConcept>>();

		_biContr[Host::Eq]=new BinaryConstraintCreator<Equality>();
		_biContr[Host::Ineq]=new BinaryConstraintCreator<Inequality>();

	}

	shared_ptr<iRelationConstraint> LogicElementCreator::CreateBinaryConstraint( const ConstraintType type,const shared_ptr<LogicType::ConSymbol> s1,const shared_ptr<LogicType::ConSymbol> s2 ) const
	{
		if(_biContr.count(type)==0)
		{
			return NULL;
		}
		else
			return _biContr.at(type)->Create(s1,s2);
	}

}

