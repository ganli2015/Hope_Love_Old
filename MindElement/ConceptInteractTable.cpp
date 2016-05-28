#include "StdAfx.h"
#include "ConceptInteractTable.h"
#include "Concept.h"


namespace Mind
{


	ConceptInteractTable::ConceptInteractTable()
	{

	}

	ConceptInteractTable::~ConceptInteractTable()
	{

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

	int ConceptInteractTable::ValueCount(const_indexIter beg, const_indexIter end, const int val)
	{
		int res=0;
		while(beg!=end)
		{
			if(beg->second==val)
			{
				++res;
			}

			++beg;
		}

		return res;
	}

	void ConceptInteractTable::RemoveDuplicated()
	{
		multimap<int,int> newIndex;

		for (const_indexIter index_it=_interactIndex.begin();index_it!=_interactIndex.end();++index_it)
		{
			int index1=index_it->first;
			int index2=index_it->second;
			indexIter beg=newIndex.lower_bound(index1);
			indexIter end=newIndex.upper_bound(index1);

			//check whether <index1> and <index2> exists in <newIndex>.
			if(ValueCount(beg,end,index2)==0)
			{
				newIndex.insert(make_pair(index1,index2));
			}
		}

		_interactIndex=newIndex;
	}


	vector<shared_ptr<iConcept>> ConceptInteractTable::GetFromConcept( const shared_ptr<iConcept> concept ) const
	{
		vector<shared_ptr<iConcept>> res;

		int index=GetConceptIndex(concept);
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
					res.push_back(GetSharedConcept(iter->first));
				}
			}
		}

		return res;
	}

	vector<shared_ptr<iConcept>> ConceptInteractTable::GetToConcept( const shared_ptr<iConcept> concept ) const
	{
		vector<shared_ptr<iConcept>> res;

		int index=GetConceptIndex(concept);
		if(index==-1)//如果没找到
		{
			return res;
		}

		const_indexIter beg=_interactIndex.lower_bound(index);
		const_indexIter end=_interactIndex.upper_bound(index);

		while(beg!=end)
		{
			res.push_back(GetSharedConcept(beg->second));
			beg++;
		}

		return res;
	}

	void ConceptInteractTable::InteractDeeper()
	{
		for (const_indexIter it=_interactIndex.begin();it!=_interactIndex.end();++it)
		{
			shared_ptr<iConcept> con=GetSharedConcept(it->first);
			shared_ptr<iConceptInteractTable> newTable=con->InteractWith(GetSharedConcept(it->second));
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

	vector<ConceptInteractTable::ConceptPair> ConceptInteractTable::GetAllRelations() const
	{
		vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> res;
		for (const_indexIter it=_interactIndex.begin();it!=_interactIndex.end();++it)
		{
			res.push_back(make_pair(GetSharedConcept(it->first),GetSharedConcept(it->second)));
		}

		return res;
	}
}