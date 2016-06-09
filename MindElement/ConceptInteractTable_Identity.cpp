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

		if(fromIndex==-1)//���û���ҵ�from�������ӽ�������index��Ϊ������ĩβ
		{
			fromIndex=_concepts.size();
			_concepts[fromIndex]=from->GetIdentity();
		}

		if(toIndex==-1)//ͬ��
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

	bool ConceptInteractTable_Identity::ConceptPairExist( const shared_ptr<iConcept> from, const shared_ptr<iConcept> to ) const
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
	

}
