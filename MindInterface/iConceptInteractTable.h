#pragma once
#include "InOut.h"
#include "PublicTypedef.h"

namespace Mind
{
	class iConcept;

	
	///iConceptInteractTable contains concept pairs that describe the temporary relationship between them. 
	class _MINDINTERFACEINOUT iConceptInteractTable: public MyObject
	{
		typedef MindType::ConceptPair ConceptPair;


	public:
		iConceptInteractTable();
		virtual ~iConceptInteractTable(void);

		virtual void Add(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to) =0;
		//得到“施力方”的Concept
		virtual vector<shared_ptr<iConcept>> GetFromConcept(const shared_ptr<iConcept> concept) const =0;
		//得到“受力方”的Concept
		virtual vector<shared_ptr<iConcept>> GetToConcept(const shared_ptr<iConcept> concept) const =0;
		virtual vector<ConceptPair> GetAllRelations() const =0;

		//合并ConceptInteractTable
		virtual void Absorb(const shared_ptr<iConceptInteractTable> absorbed) =0;
		virtual void InteractDeeper() =0;

		virtual void RemoveDuplicated() =0;

		virtual shared_ptr<iConceptInteractTable> Copy() const =0;

		virtual double Similarity(const shared_ptr<iConceptInteractTable> other) const =0;
	};
}


