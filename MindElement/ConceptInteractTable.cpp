#include "StdAfx.h"
#include "ConceptInteractTable.h"
#include "Concept.h"

#include "../MindInterface/CommonFunction.h"

namespace Mind
{
	ConceptInteractTable::ConceptInteractTable(void)
	{
	}


	ConceptInteractTable::~ConceptInteractTable(void)
	{
	}

	void ConceptInteractTable::Add( const shared_ptr<iConcept> from, const shared_ptr<iConcept> to )
	{
		int fromIndex=CommonFunction::IndexOf(_concepts,from);
		int toIndex=CommonFunction::IndexOf(_concepts,to);

		if(fromIndex==-1)//如果没有找到from，则添加进容器，index改为容器的末尾
		{
			_concepts.push_back(from);
			fromIndex=_concepts.size()-1;
		}
		
		if(toIndex==-1)//同上
		{
			_concepts.push_back(to);
			toIndex=_concepts.size()-1;
		}

		if(!PairExist(fromIndex,toIndex))
			_interactIndex.insert(make_pair(fromIndex,toIndex));
	}

	vector<shared_ptr<iConcept>> ConceptInteractTable::GetFromConcept( const shared_ptr<iConcept> concept ) const
	{
		vector<shared_ptr<iConcept>> res;

		int index=CommonFunction::IndexOf(_concepts,concept);
		if(index==-1)//如果没找到
		{
			return res;
		}

		vector<int> fromIndexes;//用来记录所有的FromIndex，并且保证index不重复。
		for (const_indexIter iter=_interactIndex.begin();iter!=_interactIndex.end();++iter)
		{
			if(iter->second==index)
			{
				if(find(fromIndexes.begin(),fromIndexes.end(),iter->first)==fromIndexes.end())//如果Concept不重复，则存进去。
				{
					fromIndexes.push_back(iter->first);
					res.push_back(_concepts[iter->first]);
				}
			}
		}

		return res;
	}

	vector<shared_ptr<iConcept>> ConceptInteractTable::GetToConcept( const shared_ptr<iConcept> concept ) const
	{
		vector<shared_ptr<iConcept>> res;

		int index=CommonFunction::IndexOf(_concepts,concept);
		if(index==-1)//如果没找到
		{
			return res;
		}

		const_indexIter beg=_interactIndex.lower_bound(index);
		const_indexIter end=_interactIndex.upper_bound(index);

		while(beg!=end)
		{
			res.push_back(_concepts[beg->second]);
			beg++;
		}

		return res;
	}


	vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> ConceptInteractTable::GetAllRelations() const
	{
		vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> res;
		for (const_indexIter it=_interactIndex.begin();it!=_interactIndex.end();++it)
		{
			res.push_back(make_pair(_concepts[it->first],_concepts[it->second]));
		}

		return res;
	}

	void ConceptInteractTable::InteractDeeper()
	{
		for (const_indexIter it=_interactIndex.begin();it!=_interactIndex.end();++it)
		{
			shared_ptr<iConceptInteractTable> newTable=_concepts[it->first]->InteractWith(_concepts[it->second]);
			Absorb(newTable);
		}
	}

	void ConceptInteractTable::Absorb( const shared_ptr<iConceptInteractTable> absorbed )
	{
		class Aborbing
		{
			ConceptInteractTable* _table;

		public:
			Aborbing(ConceptInteractTable* table):_table(table){}
			~Aborbing(){}

			void operator()(const pair<shared_ptr<iConcept>,shared_ptr<iConcept>> relation)
			{
				_table->Add(relation.first,relation.second);
			}
		};

		vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> relations=absorbed->GetAllRelations();
		for_each(relations.begin(),relations.end(),Aborbing(this));
	}

	bool ConceptInteractTable::PairExist( const int index1,const int index2 ) const
	{
		const_indexIter iter=_interactIndex.find(index1);
		if(iter==_interactIndex.end())
		{
			return false;
		}

		const_indexIter beg=_interactIndex.lower_bound(index1);
		const_indexIter end=_interactIndex.upper_bound(index1);

		while(beg!=end)
		{
			if(beg->second==index2)
			{
				return true;
			}
			beg++;
		}

		return false;
	}

}

