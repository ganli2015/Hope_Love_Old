#include "StdAfx.h"
#include "iMindElementCreator.h"


namespace Mind
{
	iMindElementCreator::iMindElementCreator(void)
	{
	}


	iMindElementCreator::~iMindElementCreator(void)
	{
	}

	shared_ptr<iConcept> iMindElementCreator::CreateConcept( const ElementType type/*=ConceptD*/ )
	{
		return _imp->CreateConcept(type);
	}

	shared_ptr<iConcept> iMindElementCreator::CreateConcept( const shared_ptr<DataCollection::Word> word,const ElementType type/*=ConceptD*/ )
	{
		return _imp->CreateConcept(word,type);
	}

	shared_ptr<iConceptChain> iMindElementCreator::CreateConceptChain( const ElementType type/*=ConceptChainD*/ )
	{
		return _imp->CreateConceptChain(type);
	}

	shared_ptr<iConceptChain> iMindElementCreator::CreateConceptChain( const vector<shared_ptr<iConcept>>& val,const ElementType type )
	{
		return _imp->CreateConceptChain(val,type);
	}

	shared_ptr<iConceptEdge> iMindElementCreator::CreateConceptEdge( const ElementType type/*=ConceptEdgeD*/ )
	{
		return _imp->CreateConceptEdge(type);
	}

	shared_ptr<iConceptInteractTable> iMindElementCreator::CreateConceptInteractTable( const ElementType type/*=ConceptInteractTableD*/ )
	{
		return _imp->CreateConceptInteractTable(type);
	}

	shared_ptr<iConceptLevelTable> iMindElementCreator::CreateConceptLevelTable( const shared_ptr<iConcept> val ,const ElementType type/*=ConceptLevelTableD*/ )
	{
		return _imp->CreateConceptLevelTable(val,type);
	}

	shared_ptr<iMindElementCreatorImp> iMindElementCreator::_imp;

}

