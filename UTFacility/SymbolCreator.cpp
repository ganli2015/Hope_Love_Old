#include "StdAfx.h"
#include "SymbolCreator.h"
#include "ConceptCreator.h"

#include "../LogicSystem/Symbol.h"

#include "../MindInterface/iConcept.h"

SymbolCreator::SymbolCreator(const shared_ptr<ConceptCreator> val):_conceptCreator(val)
{
}


SymbolCreator::~SymbolCreator(void)
{
}

shared_ptr<LogicSystem::Symbol<Mind::iConcept>> SymbolCreator::Create( const string str) const
{
	shared_ptr<LogicSystem::Symbol<Mind::iConcept>> res(new LogicSystem::Symbol<Mind::iConcept>(_conceptCreator->Create(str)));

	return res;
}
