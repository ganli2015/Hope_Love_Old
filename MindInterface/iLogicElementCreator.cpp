#include "StdAfx.h"
#include "iLogicElementCreator.h"


namespace LogicSystem
{
	iLogicElementCreator::iLogicElementCreator(void)
	{
	}


	iLogicElementCreator::~iLogicElementCreator(void)
	{
	}

	shared_ptr<iExpression> iLogicElementCreator::CreateExpression( const string str )
	{
		return _imp->CreateExpression(str);
	}

	shared_ptr<iExpression> iLogicElementCreator::CreateExpression( const vector<string> str )
	{
		return _imp->CreateExpression(str);
	}
	shared_ptr<iExpression> iLogicElementCreator::CreateExpression( const shared_ptr<DataCollection::Sentence> val )
	{
		return _imp->CreateExpression(val);
	}

	shared_ptr<iExpression> iLogicElementCreator::CreateExpression( const vector<shared_ptr<DataCollection::Sentence>> val )
	{
		return _imp->CreateExpression(val);
	}

	shared_ptr<iLogicStatement> iLogicElementCreator::CreateLogicStatement( const shared_ptr<iRelation> condition,const shared_ptr<iRelation> result )
	{
		return _imp->CreateLogicStatement(condition,result);
	}

	shared_ptr<iRelationLeaf> iLogicElementCreator::CreateRelationLeaf()
	{
		return _imp->CreateRelationLeaf();
	}

	shared_ptr<iRelationNode> iLogicElementCreator::CreateRelationNode()
	{
		return _imp->CreateRelationNode();
	}

	shared_ptr<iLogic> iLogicElementCreator::CreateLogic()
	{
		return _imp->CreateLogic();
	}

	shared_ptr<LogicType::ConSymbol> iLogicElementCreator::CreateConceptSymbol( const shared_ptr<Mind::iConcept> con )
	{
		return _imp->CreateConceptSymbol(con);
	}

	shared_ptr<LogicType::ConSymbol> iLogicElementCreator::CreateSpecialSymbol( const SymbolType type )
	{
		return _imp->CreateSpecialSymbol(type);
	}

	shared_ptr<iRelationConstraint> iLogicElementCreator::CreateBinaryConstraint( const ConstraintType type,const shared_ptr<LogicType::ConSymbol> s1,const shared_ptr<LogicType::ConSymbol> s2 )
	{
		return _imp->CreateBinaryConstraint(type,s1,s2);
	}

	void iLogicElementCreator::SetImp( const shared_ptr<iLogicElementCreatorImp> imp )
	{
		_imp=imp;
	}

	shared_ptr<iLogicElementCreatorImp> iLogicElementCreator::_imp;

}

