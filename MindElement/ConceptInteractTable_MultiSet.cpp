#include "stdafx.h"
#include "ConceptInteractTable_MultiSet.h"


namespace Mind
{
	ConceptInteractTable_MultiSet::ConceptInteractTable_MultiSet()
	{
	}


	ConceptInteractTable_MultiSet::~ConceptInteractTable_MultiSet()
	{
	}

	void ConceptInteractTable_MultiSet::Add(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to)
	{
		Identity fromID = from->GetIdentity();
		Identity toID = to->GetIdentity();

		_concepts[fromID] = from;
		_concepts[toID] = to;

		_identityPairs.insert(IdentityPair(fromID, toID));
	}

	std::vector<shared_ptr<Mind::iConcept>> ConceptInteractTable_MultiSet::GetFromConcept(const shared_ptr<iConcept> concept) const
	{
		throw runtime_error("Not Implemented");
	}

	std::vector<shared_ptr<Mind::iConcept>> ConceptInteractTable_MultiSet::GetToConcept(const shared_ptr<iConcept> concept) const
	{
		throw runtime_error("Not Implemented");
	}

	std::vector<Mind::iConceptInteractTable::ConceptPair> ConceptInteractTable_MultiSet::GetAllRelations() const
	{
		vector<ConceptPair> res;
		res.reserve(_identityPairs.size());

		for (ConstIter_PairSet iter=_identityPairs.begin();iter!=_identityPairs.end();++iter)
		{
			shared_ptr<iConcept> fromCon = _concepts.at(iter->First());
			shared_ptr<iConcept> toCon = _concepts.at(iter->Second());
			assert(fromCon != NULL && toCon != NULL);

			res.push_back(make_pair(fromCon, toCon));
		}

		return res;
	}

	void ConceptInteractTable_MultiSet::Absorb(const shared_ptr<iConceptInteractTable> absorbed)
	{
		class Aborbing
		{
			ConceptInteractTable_MultiSet* _table;

		public:
			Aborbing(ConceptInteractTable_MultiSet* table) :_table(table) {}
			~Aborbing() {}

			void operator()(const pair<shared_ptr<iConcept>, shared_ptr<iConcept>> relation)
			{
				_table->Add(relation.first, relation.second);
			}
		};

		vector<pair<shared_ptr<iConcept>, shared_ptr<iConcept>>> relations = absorbed->GetAllRelations();
		for_each(relations.begin(), relations.end(), Aborbing(this));
	}

	void ConceptInteractTable_MultiSet::InteractDeeper()
	{
		throw runtime_error("Not Implemented");
	}

	void ConceptInteractTable_MultiSet::RemoveDuplicated()
	{
		set<IdentityPair> uniqueSet(_identityPairs.begin(), _identityPairs.end());

		_identityPairs.clear();
		_identityPairs.insert(uniqueSet.begin(), uniqueSet.end());
	}

	shared_ptr<Mind::iConceptInteractTable> ConceptInteractTable_MultiSet::Copy() const
	{
		shared_ptr<ConceptInteractTable_MultiSet> res(new ConceptInteractTable_MultiSet());
		res->_concepts = _concepts;
		res->_identityPairs = _identityPairs;

		return res;
	}

	double ConceptInteractTable_MultiSet::Similarity(const shared_ptr<iConceptInteractTable> other) const
	{
		vector<ConceptPair> otherPairs = other->GetAllRelations();
		int otherPairCount = otherPairs.size();

		//The number of same concept pairs
		int sameCount = 0;
		PairSet myIdentityPair_Copy = _identityPairs;
		//Determine how many pairs are duplicated in <me> and <other>
		for (unsigned int i=0;i<otherPairs.size();++i)
		{
			Identity fromID = otherPairs[i].first->GetIdentity();
			Identity toID = otherPairs[i].second->GetIdentity();
			//Check whether the identity pair of <other> is in <myIdentityPair_Copy>.
			//If so ,remove the same one  in <myIdentityPair_Copy>.
			IdentityPair otherIDPair(fromID, toID);
			ConstIter_PairSet iter = find(myIdentityPair_Copy.begin(), myIdentityPair_Copy.end(), otherIDPair);
			if (iter != myIdentityPair_Copy.end())
			{
				myIdentityPair_Copy.erase(iter);
				sameCount += 2;
			}
		}

		return (double)sameCount / (otherPairCount + _identityPairs.size());
	}

	bool ConceptInteractTable_MultiSet::Same(const shared_ptr<iConceptInteractTable> other) const
	{
		if (other->GetPairCount() != GetPairCount())
		{
			return false;
		}

		throw runtime_error("Not Implemented!");
	}

	bool ConceptInteractTable_MultiSet::ConceptPairExist(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to) const
	{
		IdentityPair otherIDPair(from->GetIdentity(), to->GetIdentity());
		ConstIter_PairSet iter = find(_identityPairs.begin(), _identityPairs.end(), otherIDPair);

		if(iter!=_identityPairs.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

