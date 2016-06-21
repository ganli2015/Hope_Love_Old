#pragma once
#include "InOut.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/CommonFunction.h"

#include <set>
#include <map>
#include <queue>

namespace Mind
{
	///ConceptInteractTable_MultiSet is based on multiset.
	///The concept pair inside of it is in order , thus making it fast to use comparison functions.
	class _MINDELEMENTINOUT ConceptInteractTable_MultiSet : public iConceptInteractTable
	{
	private:
		///A pair of identities.
		class IdentityPair
		{
			pair<Identity, Identity> _pair;
		public:
			IdentityPair(const Identity& from, const Identity& to):_pair(make_pair(from,to))
			{
			}

			~IdentityPair()
			{
			}

			Identity First() const { return _pair.first; }
			Identity Second() const { return _pair.second; }

			IdentityPair& operator=(const IdentityPair& other)
			{
				_pair = other._pair;

				return *this;
			}

			friend bool operator==(const IdentityPair& left, const IdentityPair& right)
			{
				if (left._pair.first == right._pair.first && left._pair.second == right._pair.second)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			friend bool operator<(const IdentityPair& left, const IdentityPair& right)
			{
				if(left._pair.first<right._pair.first)
				{
					return true;
				}
				else if(left._pair.first==right._pair.first && left._pair.second < right._pair.second)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};

		map<Identity, shared_ptr<Mind::iConcept>> _concepts;

		///Record pairs of Identity which are in order.
		multiset<IdentityPair> _identityPairs;

		typedef multiset<IdentityPair> PairSet;
		typedef PairSet::iterator Iter_PairSet;
		typedef PairSet::const_iterator ConstIter_PairSet;

	public:
		ConceptInteractTable_MultiSet();
		~ConceptInteractTable_MultiSet();

		virtual void Add(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to) ;

		virtual vector<shared_ptr<iConcept>> GetFromConcept(const shared_ptr<iConcept> concept) const ;
		virtual vector<shared_ptr<iConcept>> GetToConcept(const shared_ptr<iConcept> concept) const ;
		virtual vector<ConceptPair> GetAllRelations() const ;

		virtual void Absorb(const shared_ptr<iConceptInteractTable> absorbed) ;
		virtual void InteractDeeper() ;

		virtual void RemoveDuplicated() ;

		virtual shared_ptr<iConceptInteractTable> Copy() const ;

		virtual double Similarity(const shared_ptr<iConceptInteractTable> other) const ;
		virtual bool Same(const shared_ptr<iConceptInteractTable> other) const;

		virtual bool ConceptPairExist(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to) const ;

		virtual int GetPairCount() const { return _identityPairs.size(); };
	};
}


