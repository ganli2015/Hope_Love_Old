#include "StdAfx.h"
#include "ConceptInteractTableContainer.h"
#include "../MindInterface/iMindElementCreator.h"
#include "../MindInterface/iConceptInteractTable.h"


namespace Mind
{
	ConceptInteractTableContainer::ConceptInteractTableContainer(void)
	{
	}


	ConceptInteractTableContainer::~ConceptInteractTableContainer(void)
	{
	}

	void ConceptInteractTableContainer::Add( const shared_ptr<iConceptInteractTable> table,const shared_ptr<iConcept> from, const shared_ptr<iConcept> to )
	{
		TableInfo info;
		info.table=table;
		info.protoPair=make_pair(from,to);
		_tableInfos.push_back(info);
	}

	vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> ConceptInteractTableContainer::GetAllInteractPairs() const
	{
		class Merge
		{
			shared_ptr<iConceptInteractTable> _table;
		public:
			Merge():_table(iMindElementCreator::CreateConceptInteractTable()){}
			~Merge(){}

			void operator()(const TableInfo& table)
			{
				_table->Absorb(table.table);
			}

			shared_ptr<iConceptInteractTable> GetResult(){return _table;}
		};

		vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> res;
		Merge merge;
		merge=for_each(_tableInfos.begin(),_tableInfos.end(),merge);
		res=merge.GetResult()->GetAllRelations();

		return res;
	}

}

