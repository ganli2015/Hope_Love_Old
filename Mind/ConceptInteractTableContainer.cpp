#include "StdAfx.h"
#include "ConceptInteractTableContainer.h"
#include "ConceptInteractTable.h"

namespace Mind
{
	ConceptInteractTableContainer::ConceptInteractTableContainer(void)
	{
	}


	ConceptInteractTableContainer::~ConceptInteractTableContainer(void)
	{
	}

	void ConceptInteractTableContainer::Add( const shared_ptr<ConceptInteractTable> table,const shared_ptr<Concept> from, const shared_ptr<Concept> to )
	{
		TableInfo info;
		info.table=table;
		info.protoPair=make_pair(from,to);
		_tableInfos.push_back(info);
	}

	vector<pair<shared_ptr<Concept>,shared_ptr<Concept>>> ConceptInteractTableContainer::GetAllInteractPairs() const
	{
		class Merge
		{
			shared_ptr<ConceptInteractTable> _table;
		public:
			Merge():_table(new ConceptInteractTable()){}
			~Merge(){}

			void operator()(const TableInfo& table)
			{
				_table->Absorb(table.table);
			}

			shared_ptr<ConceptInteractTable> GetResult(){return _table;}
		};

		vector<pair<shared_ptr<Concept>,shared_ptr<Concept>>> res;
		Merge merge;
		merge=for_each(_tableInfos.begin(),_tableInfos.end(),merge);
		res=merge.GetResult()->GetAllRelations();

		return res;
	}

}

