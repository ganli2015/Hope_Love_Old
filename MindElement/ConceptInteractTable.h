#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;

	//Concept�໥���õ��б����໥������ConceptEdge��ͬ�������Ǵ�����ConceptSet���ԭ�͵����ӣ�
	//��һ���Ѿ��н��ι̹�ϵ�����ӡ�ǰ��������ʱ�����ӣ�ͨ�����������µ�֪ʶ�µ�����ʱ�����ġ�
	class _MINDELEMENTINOUT ConceptInteractTable
	{
		vector<shared_ptr<iConcept>> _concepts;
		multimap<int,int> _interactIndex;

		typedef vector<shared_ptr<iConcept>>::iterator conceptIter;
		typedef vector<shared_ptr<iConcept>>::const_iterator const_conceptIter;

		typedef multimap<int,int>::iterator indexIter;
		typedef multimap<int,int>::const_iterator const_indexIter;
	public:
		ConceptInteractTable(void);
		~ConceptInteractTable(void);

		//��ӵ����Ӳ����ظ�
		void Add(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to);
		//�õ���ʩ��������Concept
		vector<shared_ptr<iConcept>> GetFromConcept(const shared_ptr<iConcept> concept) const;
		//�õ�������������Concept
		vector<shared_ptr<iConcept>> GetToConcept(const shared_ptr<iConcept> concept) const;
		vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> GetAllRelations() const;

		//�ϲ�ConceptInteractTable
		void Absorb(const shared_ptr<ConceptInteractTable> absorbed);
		void InteractDeeper();

	private: 
		bool PairExist(const int index1,const int index2) const;
	};
}


