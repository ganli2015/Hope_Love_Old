#include "StdAfx.h"
#include "ConceptInteractTable_iConcept.h"
#include "Concept.h"

#include "../MindInterface/CommonFunction.h"

namespace Mind
{
	ConceptInteractTable_iConcept::ConceptInteractTable_iConcept()
	{
	}


	ConceptInteractTable_iConcept::~ConceptInteractTable_iConcept(void)
	{
	}

	void ConceptInteractTable_iConcept::Add( const shared_ptr<iConcept> from, const shared_ptr<iConcept> to )
	{
		int fromIndex=GetConceptIndex(from);
		int toIndex=GetConceptIndex(to);

		if(fromIndex==-1)//如果没有找到from，则添加进容器，index改为容器的末尾
		{
			fromIndex=_concepts.size();
			_concepts[fromIndex]=from->Copy();
		}

		if(toIndex==-1)//同上
		{
			toIndex=_concepts.size();
			_concepts[toIndex]=to->Copy();
		}

		//if(!PairExist(fromIndex,toIndex))
		_interactIndex.insert(make_pair(fromIndex,toIndex));
	}

	shared_ptr<iConcept> ConceptInteractTable_iConcept::GetSharedConcept(const int i) const
	{
		if(_concepts.count(i)==0)
		{
			return NULL;
		}
		else
			return _concepts.at(i);
	}

	shared_ptr<iConceptInteractTable> ConceptInteractTable_iConcept::Copy() const
	{
		shared_ptr<ConceptInteractTable_iConcept> res(new ConceptInteractTable_iConcept());
		res->_interactIndex=_interactIndex;

		//Copy iConcept in <_concepts>.
		map<int,shared_ptr<iConcept>> concept_copy;
		for (const_conceptIter it=_concepts.begin();it!=_concepts.end();++it)
		{
			concept_copy.insert(make_pair(it->first,it->second->Copy()));
		}
		res->_concepts=concept_copy;

		return res;
	}

	int ConceptInteractTable_iConcept::GetConceptIndex( const shared_ptr<iConcept> con ) const
	{
		return CommonFunction::IndexOf(_concepts,con);
	}

}

