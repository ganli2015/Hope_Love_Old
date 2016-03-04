#pragma once
#include "InOut.h"

namespace Mind
{
	class ConceptInteractTable;
	class Concept;

	//存放ConceptInteractTable的类，作为对Concept连接的临时记忆体
	class ConceptInteractTableContainer
	{
	private:
		struct TableInfo  
		{
			shared_ptr<ConceptInteractTable> table;
			pair<shared_ptr<Concept>,shared_ptr<Concept>> protoPair;//<table>所对应的两个相互作用的concept
		};

		vector<TableInfo> _tableInfos;
	public:
		ConceptInteractTableContainer(void);
		~ConceptInteractTableContainer(void);

		void Add(const shared_ptr<ConceptInteractTable> table,const shared_ptr<Concept> from, const shared_ptr<Concept> to);
		vector<pair<shared_ptr<Concept>,shared_ptr<Concept>>> GetAllInteractPairs() const;
	};

}

