#pragma once
#include "InOut.h"
#include "../MindInterface/iMindElementCreator.h"

namespace Mind
{
	class _MINDELEMENTINOUT MindElementCreator : public iMindElementCreatorImp
	{
	public:
		MindElementCreator(void);
		~MindElementCreator(void);

		virtual shared_ptr<iConcept> CreateConcept(const ElementType type) const ;
		virtual shared_ptr<iConceptChain> CreateConceptChain(const ElementType type) const ;
		virtual shared_ptr<iConceptEdge> CreateConceptEdge(const ElementType type) const ;
		virtual shared_ptr<iConceptInteractTable> CreateConceptInteractTable(const ElementType type) const ;
		virtual shared_ptr<iConceptLevelTable> CreateConceptLevelTable(const shared_ptr<iConcept> val ,const ElementType type) const ;
	};
}


