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


		vector<shared_ptr<iConcept>> _concepts;
		multimap<int,int> _interactIndex;

		typedef vector<shared_ptr<iConcept>>::iterator conceptIter;
		typedef vector<shared_ptr<iConcept>>::const_iterator const_conceptIter;

		typedef multimap<int,int>::iterator indexIter;
		typedef multimap<int,int>::const_iterator const_indexIter;
	public:
		ConceptInteractTable(void);
		virtual ~ConceptInteractTable(void);

		//��ӵ����Ӳ����ظ�
		virtual void Add(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to);
		//�õ���ʩ��������Concept
		virtual vector<shared_ptr<iConcept>> GetFromConcept(const shared_ptr<iConcept> concept) const;
		//�õ�������������Concept
		virtual vector<shared_ptr<iConcept>> GetToConcept(const shared_ptr<iConcept> concept) const;
		virtual vector<ConceptInteractTable::ConceptPair> GetAllRelations() const;

		//�ϲ�ConceptInteractTable
		virtual void Absorb(const shared_ptr<iConceptInteractTable> absorbed);
		virtual void InteractDeeper();

	private: 
		bool PairExist(const int index1,const int index2) const;
	};
}


