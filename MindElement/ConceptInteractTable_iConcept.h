#pragma once

#include "InOut.h"
#include "ConceptInteractTable.h"

namespace Mind
{
	class iConcept;

	///ConceptInteractTable contains pointers of concept pairs.
	///It may have problem of circular dependency.
	class _MINDELEMENTINOUT ConceptInteractTable_iConcept : public ConceptInteractTable
	{
		typedef MindType::ConceptPair ConceptPair;

		map<int,shared_ptr<iConcept>> _concepts;

		typedef map<int,shared_ptr<iConcept>>::iterator conceptIter;
		typedef map<int,shared_ptr<iConcept>>::const_iterator const_conceptIter;

		typedef multimap<int,int>::iterator indexIter;
		typedef multimap<int,int>::const_iterator const_indexIter;
	public:
		ConceptInteractTable_iConcept();
		virtual ~ConceptInteractTable_iConcept(void);


		virtual void Add(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to);
		
		virtual shared_ptr<iConceptInteractTable> Copy() const ;

		virtual bool ConceptPairExist(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to) const;

	private:
		virtual shared_ptr<iConcept> GetSharedConcept(const int i) const;
		virtual int GetConceptIndex(const shared_ptr<iConcept> con) const ;

	};
}
