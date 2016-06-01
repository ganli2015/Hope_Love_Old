#pragma once
#include "InOut.h"

namespace Mind
{
	class iConceptInteractTable;
	class iConcept;

	//���ConceptInteractTable���࣬��Ϊ��Concept���ӵ���ʱ������
	class ConceptInteractTableContainer : public Obj<ConceptInteractTableContainer>
	{
	private:
		struct TableInfo  
		{
			shared_ptr<iConceptInteractTable> table;
			pair<shared_ptr<iConcept>,shared_ptr<iConcept>> protoPair;//<table>����Ӧ�������໥���õ�concept
		};

		vector<TableInfo> _tableInfos;
	public:
		ConceptInteractTableContainer(void);
		~ConceptInteractTableContainer(void);

		void Add(const shared_ptr<iConceptInteractTable> table,const shared_ptr<iConcept> from, const shared_ptr<iConcept> to);
		vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> GetAllInteractPairs() const;
	};

}

