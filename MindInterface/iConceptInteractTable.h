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
		///Make pairs in <me> interact with each other again and derive the new pairs.
		virtual void InteractDeeper() =0;
		///Remove duplicated pairs.
		virtual void RemoveDuplicated() =0;

		virtual shared_ptr<iConceptInteractTable> Copy() const =0;

		///Compute the similarity between <me> and <other>.Return -1 to 1.
		///Returning 1 indicates they are exactly the same and -1 totally different.
		virtual double Similarity(const shared_ptr<iConceptInteractTable> other) const =0;
		virtual bool Same(const shared_ptr<iConceptInteractTable> other) const = 0;
		///Check whether the <from>-<to> pair exists in <me>
		virtual bool ConceptPairExist(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to) const=0;

		virtual string GetString() const;

		virtual int GetPairCount() const = 0;
	};
}


