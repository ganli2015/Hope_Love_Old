#pragma once
#include "InOut.h"
#include "PublicTypedef.h"

namespace Mind
{
	class iConcept;

	
	///iConceptInteractTable contains concept pairs that describe the temporary relationship between them. 
	class _MINDINTERFACEINOUT iConceptInteractTable: public Obj<iConceptInteractTable>
	{
	protected:
		typedef MindType::ConceptPair ConceptPair;


	public:
		iConceptInteractTable();
		virtual ~iConceptInteractTable(void);

		virtual void Add(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to) =0;
		///Get concepts that <concept> interact with.
		virtual vector<shared_ptr<iConcept>> GetFromConcept(const shared_ptr<iConcept> concept) const =0;
		///Get concepts that interact with <concept>.
		virtual vector<shared_ptr<iConcept>> GetToConcept(const shared_ptr<iConcept> concept) const =0;
		virtual vector<ConceptPair> GetAllRelations() const =0;

		///Merge ConceptInteractTable
		virtual void Absorb(const shared_ptr<iConceptInteractTable> absorbed) =0;
		virtual void InteractDeeper() =0;

		virtual void RemoveDuplicated() =0;

		virtual shared_ptr<iConceptInteractTable> Copy() const =0;

		virtual double Similarity(const shared_ptr<iConceptInteractTable> other) const =0;

		virtual bool ConceptPairExist(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to) const=0;

		virtual string GetString() const;

		virtual int GetPairCount() const = 0;
	};
}


