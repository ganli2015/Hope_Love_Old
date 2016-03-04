#pragma once
#include "InOut.h"

namespace Mind
{
	class Concept;

	//Concept�໥���õ��б����໥������ConceptEdge��ͬ�������Ǵ�����ConceptSet���ԭ�͵����ӣ�
	//��һ���Ѿ��н��ι̹�ϵ�����ӡ�ǰ��������ʱ�����ӣ�ͨ�����������µ�֪ʶ�µ�����ʱ�����ġ�
	class ConceptInteractTable
	{
		vector<shared_ptr<Concept>> _concepts;
		multimap<int,int> _interactIndex;

		typedef vector<shared_ptr<Concept>>::iterator conceptIter;
		typedef vector<shared_ptr<Concept>>::const_iterator const_conceptIter;

		typedef multimap<int,int>::iterator indexIter;
		typedef multimap<int,int>::const_iterator const_indexIter;
	public:
		ConceptInteractTable(void);
		~ConceptInteractTable(void);

		//��ӵ����Ӳ����ظ�
		void Add(const shared_ptr<Concept> from, const shared_ptr<Concept> to);
		//�õ���ʩ��������Concept
		vector<shared_ptr<Concept>> GetFromConcept(const shared_ptr<Concept> concept) const;
		//�õ�������������Concept
		vector<shared_ptr<Concept>> GetToConcept(const shared_ptr<Concept> concept) const;
		vector<pair<shared_ptr<Concept>,shared_ptr<Concept>>> GetAllRelations() const;

		//�ϲ�ConceptInteractTable
		void Absorb(const shared_ptr<ConceptInteractTable> absorbed);
		void InteractDeeper();

	private: 
		bool PairExist(const int index1,const int index2) const;
	};
}


