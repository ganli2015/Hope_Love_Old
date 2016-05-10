#pragma once
#include "InOut.h"
#include "../MindInterface/iConceptInteractTable.h"

namespace Mind
{
	class iConcept;

	//Concept�໥���õ��б����໥������ConceptEdge��ͬ�������Ǵ�����ConceptSet���ԭ�͵����ӣ�
	//��һ���Ѿ��н��ι̹�ϵ�����ӡ�ǰ��������ʱ�����ӣ�ͨ�����������µ�֪ʶ�µ�����ʱ�����ġ�
	class _MINDELEMENTINOUT ConceptInteractTable : public iConceptInteractTable
	{
		typedef MindType::ConceptPair ConceptPair;


		map<int,shared_ptr<iConcept>> _concepts;
		multimap<int,int> _interactIndex;

		typedef map<int,shared_ptr<iConcept>>::iterator conceptIter;
		typedef map<int,shared_ptr<iConcept>>::const_iterator const_conceptIter;

		typedef multimap<int,int>::iterator indexIter;
		typedef multimap<int,int>::const_iterator const_indexIter;
	public:
		ConceptInteractTable();
		virtual ~ConceptInteractTable(void);

		virtual void Add(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to);
		//�õ���ʩ��������Concept
		virtual vector<shared_ptr<iConcept>> GetFromConcept(const shared_ptr<iConcept> concept) const;
		//�õ�������������Concept
		virtual vector<shared_ptr<iConcept>> GetToConcept(const shared_ptr<iConcept> concept) const;
		virtual vector<ConceptInteractTable::ConceptPair> GetAllRelations() const;

		//�ϲ�ConceptInteractTable
		virtual void Absorb(const shared_ptr<iConceptInteractTable> absorbed);
		virtual void InteractDeeper();

		virtual void RemoveDuplicated() ;

	private: 
		bool PairExist(const int index1,const int index2) const;
		int ValueCount(const_indexIter beg, const_indexIter end, const int val);
	};
}


