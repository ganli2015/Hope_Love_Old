#pragma once
#include "InOut.h"

namespace Mind
{
	class Concept;

	//Concept相互作用的列表。该相互作用与ConceptEdge不同，后者是存在于ConceptSet里的原型的连接，
	//是一个已经有较牢固关系的连接。前者则是临时的连接，通常是在遇见新的知识新的语句的时候建立的。
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

		//添加的连接不会重复
		void Add(const shared_ptr<Concept> from, const shared_ptr<Concept> to);
		//得到“施力方”的Concept
		vector<shared_ptr<Concept>> GetFromConcept(const shared_ptr<Concept> concept) const;
		//得到“受力方”的Concept
		vector<shared_ptr<Concept>> GetToConcept(const shared_ptr<Concept> concept) const;
		vector<pair<shared_ptr<Concept>,shared_ptr<Concept>>> GetAllRelations() const;

		//合并ConceptInteractTable
		void Absorb(const shared_ptr<ConceptInteractTable> absorbed);
		void InteractDeeper();

	private: 
		bool PairExist(const int index1,const int index2) const;
	};
}


