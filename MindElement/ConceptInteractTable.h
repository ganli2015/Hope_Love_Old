#pragma once
#include "InOut.h"
#include "../MindInterface/iConceptInteractTable.h"

namespace Mind
{
	class ConceptInteractTable: public iConceptInteractTable
	{
	protected:
		typedef MindType::ConceptPair ConceptPair;

		multimap<int,int> _interactIndex;

		typedef map<int,shared_ptr<iConcept>>::iterator conceptIter;
		typedef map<int,shared_ptr<iConcept>>::const_iterator const_conceptIter;

		typedef multimap<int,int>::iterator indexIter;
		typedef multimap<int,int>::const_iterator const_indexIter;

	public:
		ConceptInteractTable();
		virtual ~ConceptInteractTable();

		virtual vector<shared_ptr<iConcept>> GetFromConcept(const shared_ptr<iConcept> concept) const;

		virtual vector<shared_ptr<iConcept>> GetToConcept(const shared_ptr<iConcept> concept) const;

		virtual void RemoveDuplicated() ;

		virtual void Absorb(const shared_ptr<iConceptInteractTable> absorbed);
		virtual void InteractDeeper();

		virtual vector<ConceptInteractTable::ConceptPair> GetAllRelations() const;

	protected:
		bool PairExist(const int index1,const int index2) const;
		int ValueCount(const_indexIter beg, const_indexIter end, const int val);

	private:
		virtual shared_ptr<iConcept> GetSharedConcept(const int i) const =0;
		virtual int GetConceptIndex(const shared_ptr<iConcept> con) const =0;
	};
}


