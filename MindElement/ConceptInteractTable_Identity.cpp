#include "StdAfx.h"
#include "ConceptInteractTable_Identity.h"

#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iConcept.h"

namespace Mind
{
	ConceptInteractTable_Identity::ConceptInteractTable_Identity(void)
	{
	}


	ConceptInteractTable_Identity::~ConceptInteractTable_Identity(void)
	{
	}

	shared_ptr<iConcept> ConceptInteractTable_Identity::GetSharedConcept( const int i ) const
	{
		if(_concepts.count(i)==0)
		{
			return NULL;
		}
		else
		{
			Identity id=_concepts.at(i);


			return GetBrain()->GetConcept(id);
		}
	}

	int ConceptInteractTable_Identity::GetConceptIndex( const shared_ptr<iConcept> con ) const
	{
		Identity id=con->GetIdentity();

		//Search over <_concepts>
		for (Const_IdentityIter it=_concepts.begin();it!=_concepts.end();++it)
		{
			Identity curID=it->second;
			if(id.str==curID.str && id.id==curID.id)
			{
				return it->first;
			}
		}

		return -1;
	}

	void ConceptInteractTable_Identity::Add( const shared_ptr<iConcept> from, const shared_ptr<iConcept> to )
	{
		int fromIndex=GetConceptIndex(from);
		int toIndex=GetConceptIndex(to);

		if(fromIndex==-1)//如果没有找到from，则添加进容器，index改为容器的末尾
		{
			fromIndex=_concepts.size();
			_concepts[fromIndex]=from->GetIdentity();
		}

		if(toIndex==-1)//同上
		{
			toIndex=_concepts.size();
			_concepts[toIndex]=to->GetIdentity();
		}

		//if(!PairExist(fromIndex,toIndex))
		_interactIndex.insert(make_pair(fromIndex,toIndex));
	}

	shared_ptr<iConceptInteractTable> ConceptInteractTable_Identity::Copy() const
	{
		shared_ptr<ConceptInteractTable_Identity> res(new ConceptInteractTable_Identity());
		res->_interactIndex=_interactIndex;

		//Copy iConcept in <_concepts>.
		map<int,Identity> concept_copy;
		for (Const_IdentityIter it=_concepts.begin();it!=_concepts.end();++it)
		{
			concept_copy.insert(make_pair(it->first,it->second));
		}
		res->_concepts=concept_copy;

		return res;
	}

	iCerebrum* ConceptInteractTable_Identity::GetBrain() const
	{
		return iCerebrum::Instance();
	}

	bool ConceptInteractTable_Identity::RemoveFirstExistConceptPair(const Identity from, const Identity to, vector<ConceptPair>& pairs) const
	{
		vector<ConceptPair>::iterator sameIt = find_if(pairs.begin(), pairs.end(), CommonFunction::SameConceptPair_Identity(from, to));

		if (sameIt != pairs.end())
		{
			pairs.erase(sameIt);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool ConceptInteractTable_Identity::ConceptPairExist(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to) const
	{
		for (const_indexIter indexIt=_interactIndex.begin();indexIt!=_interactIndex.end();++indexIt)
		{
			Identity from_me=_concepts.at(indexIt->first);
			Identity to_me=_concepts.at(indexIt->second);
			if(from_me==from->GetIdentity() && to_me==to->GetIdentity())
			{
				return true;
			}
		}

		return false;
	}
	

	double ConceptInteractTable_Identity::Similarity(const shared_ptr<iConceptInteractTable> other) const
	{
		vector<ConceptPair> otherPairs = other->GetAllRelations();
		int otherPairCount = otherPairs.size();

		//The number of same concept pairs
		int sameCount = 0;
		//Determine how many pairs are duplicated in <me> and <other>
		for (const_indexIter indexIt = _interactIndex.begin(); indexIt != _interactIndex.end(); ++indexIt)
		{
			if (RemoveFirstExistConceptPair(_concepts.at(indexIt->first), _concepts.at(indexIt->second), otherPairs))
			{
				sameCount += 2;
			}
		}

		return (double)sameCount / (otherPairCount + _interactIndex.size());
	}

	bool ConceptInteractTable_Identity::Same(const shared_ptr<iConceptInteractTable> other) const
	{
		if (other->GetPairCount() != GetPairCount())
		{
			return false;
		}

		//Check whether all pair exist in <me>.
		vector<ConceptPair> otherPairs = other->GetAllRelations();
		for (const_indexIter indexIt = _interactIndex.begin(); indexIt != _interactIndex.end(); ++indexIt)
		{
			//If pair in <otherPairs> is duplicated , then remove it.
			if (!RemoveFirstExistConceptPair(_concepts.at(indexIt->first), _concepts.at(indexIt->second), otherPairs))
			{
				return false;
			}
		}

		return true;
	}

}

