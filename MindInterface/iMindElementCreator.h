#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;
	class iConceptChain;
	class iConceptEdge;
	class iConceptInteractTable;
	class iConceptLevelTable;

	class iMindElementCreatorImp;

	class _MINDINTERFACEINOUT iMindElementCreator
	{
		static shared_ptr<iMindElementCreatorImp> _imp;

	public:
		///The type for create actions.
		///D means default.
		enum ElementType
		{
			ConceptD,
			ConceptChainD,
			ConceptEdgeD,
			ConceptInteractTableD,
			ConceptInteractTable_IdentityBased,
			ConceptLevelTableD
		};

	public:
		static void SetImp(const shared_ptr<iMindElementCreatorImp> imp){_imp=imp;}

		static shared_ptr<iConcept> CreateConcept(const ElementType type=ConceptD);
		static shared_ptr<iConceptChain> CreateConceptChain(const ElementType type=ConceptChainD);
		static shared_ptr<iConceptEdge> CreateConceptEdge(const ElementType type=ConceptEdgeD);
		static shared_ptr<iConceptInteractTable> CreateConceptInteractTable(const ElementType type=ConceptInteractTableD);
		///<val> is the central concept of level table.
		static shared_ptr<iConceptLevelTable> CreateConceptLevelTable(const shared_ptr<iConcept> val ,const ElementType type=ConceptLevelTableD);

	private:
		iMindElementCreator(void);
		~iMindElementCreator(void);
	};

	class _MINDINTERFACEINOUT iMindElementCreatorImp
	{
	protected:
		typedef iMindElementCreator Host;
		typedef Host::ElementType ElementType;

	public:
		iMindElementCreatorImp(){}
		virtual ~iMindElementCreatorImp(){}

		virtual shared_ptr<iConcept> CreateConcept(const ElementType type) const =0;
		virtual shared_ptr<iConceptChain> CreateConceptChain(const ElementType type) const =0;
		virtual shared_ptr<iConceptEdge> CreateConceptEdge(const ElementType type) const =0;
		virtual shared_ptr<iConceptInteractTable> CreateConceptInteractTable(const ElementType type) const =0;
		virtual shared_ptr<iConceptLevelTable> CreateConceptLevelTable(const shared_ptr<iConcept> val ,const ElementType type) const =0;

	};
}


