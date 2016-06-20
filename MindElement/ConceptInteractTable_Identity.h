#pragma once
#include "InOut.h"
#include "ConceptInteractTable.h"
#include "../MindInterface/CommonFunction.h"

namespace Mind
{
	class iCerebrum;

	///ConceptInteractTable_Identity contains the identities of concept pairs instead of concepts.
	///Therefore, it is more slower than ConceptInteractTable calling some member functions.
	///But it helps to break circular dependency.
	class _MINDELEMENTINOUT ConceptInteractTable_Identity : public ConceptInteractTable
	{
		map<int,Identity> _concepts;

		typedef map<int,Identity>::iterator IdentityIter;
		typedef map<int,Identity>::const_iterator Const_IdentityIter;
	public:
		ConceptInteractTable_Identity(void);
		virtual ~ConceptInteractTable_Identity(void);


		virtual void Add(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to);

		virtual shared_ptr<iConceptInteractTable> Copy() const ;

		virtual bool ConceptPairExist(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to) const;

		virtual double Similarity(const shared_ptr<iConceptInteractTable> other) const;

	private:
		virtual shared_ptr<iConcept> GetSharedConcept(const int i) const;
		virtual int GetConceptIndex(const shared_ptr<iConcept> con) const ;

		iCerebrum* GetBrain() const;

		bool RemoveFirstExistConceptPair(const Identity from, const Identity to, vector<ConceptPair>& pairs) const;
	};
}


