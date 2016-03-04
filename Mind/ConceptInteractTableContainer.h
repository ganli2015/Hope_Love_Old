#pragma once
#include "InOut.h"

namespace Mind
{
	class ConceptInteractTable;
	class Concept;

	//���ConceptInteractTable���࣬��Ϊ��Concept���ӵ���ʱ������
	class ConceptInteractTableContainer
	{
	private:
		struct TableInfo  
		{
			shared_ptr<ConceptInteractTable> table;
			pair<shared_ptr<Concept>,shared_ptr<Concept>> protoPair;//<table>����Ӧ�������໥���õ�concept
		};

		vector<TableInfo> _tableInfos;
	public:
		ConceptInteractTableContainer(void);
		~ConceptInteractTableContainer(void);

		void Add(const shared_ptr<ConceptInteractTable> table,const shared_ptr<Concept> from, const shared_ptr<Concept> to);
		vector<pair<shared_ptr<Concept>,shared_ptr<Concept>>> GetAllInteractPairs() const;
	};

}

