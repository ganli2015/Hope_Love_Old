#include "StdAfx.h"
#include "MindElementCreator.h"
#include "Concept.h"
#include "ConceptEdge.h"
#include "ConceptChain.h"
#include "ConceptInteractTable_iConcept.h"
#include "ConceptInteractTable_Identity.h"
#include "ConceptLevelTable.h"

namespace Mind
{
	MindElementCreator::MindElementCreator(void)
	{

	}


	MindElementCreator::~MindElementCreator(void)
	{
	}

	shared_ptr<iConcept> MindElementCreator::CreateConcept( const ElementType type ) const
	{
		switch(type)
		{
		case Host::ConceptD:
			{
				return shared_ptr<Concept>(new Concept());
			}
		default:
			{
				return NULL;
			}
		}
	}

	shared_ptr<iConcept> MindElementCreator::CreateConcept(const shared_ptr<DataCollection::Word> word, const ElementType type ) const
	{
		switch(type)
		{
		case Host::ConceptD:
			{
				return shared_ptr<Concept>(new Concept(word));
			}
		default:
			{
				return NULL;
			}
		}
	}

	shared_ptr<iConceptChain> MindElementCreator::CreateConceptChain( const ElementType type ) const
	{
		switch(type)
		{
		case Host::ConceptChainD:
			{
				return shared_ptr<ConceptChain>(new ConceptChain());
			}
		default:
			{
				return NULL;
			}
		}
	}

	shared_ptr<iConceptChain> MindElementCreator::CreateConceptChain( const vector<shared_ptr<iConcept>>& val,const ElementType type ) const
	{
		switch(type)
		{
		case Host::ConceptChainD:
			{
				return shared_ptr<ConceptChain>(new ConceptChain(val));
			}
		default:
			{
				return NULL;
			}
		}
	}

	shared_ptr<iConceptEdge> MindElementCreator::CreateConceptEdge( const ElementType type ) const
	{
		switch(type)
		{
		case Host::ConceptEdgeD:
			{
				return shared_ptr<ConceptEdge>(new ConceptEdge());
			}
		default:
			{
				return NULL;
			}
		}
	}

	shared_ptr<iConceptInteractTable> MindElementCreator::CreateConceptInteractTable( const ElementType type ) const
	{
		switch(type)
		{
		case Host::ConceptInteractTableD:
			{
				return shared_ptr<ConceptInteractTable_iConcept>(new ConceptInteractTable_iConcept());
			}
		case Host::ConceptInteractTable_IdentityBased:
			{
				return shared_ptr<ConceptInteractTable_Identity>(new ConceptInteractTable_Identity());
			}
		default:
			{
				return NULL;
			}
		}
	}

	shared_ptr<iConceptLevelTable> MindElementCreator::CreateConceptLevelTable(const shared_ptr<iConcept> val ,const  ElementType type ) const
	{
		switch(type)
		{
		case Host::ConceptLevelTableD:
			{
				return shared_ptr<ConceptLevelTable>(new ConceptLevelTable(val));
			}
		default:
			{
				return NULL;
			}
		}
	}

}

