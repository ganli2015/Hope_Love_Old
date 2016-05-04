#pragma once
#include "InOut.h"
#include "../MindInterface/iConceptInteractTable.h"

namespace Mind
{
	class iConcept;

	//Concept相互作用的列表。该相互作用与ConceptEdge不同，后者是存在于ConceptSet里的原型的连接，
	//是一个已经有较牢固关系的连接。前者则是临时的连接，通常是在遇见新的知识新的语句的时候建立的。
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

		//添加的连接不会重复
		virtual void Add(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to);
		//得到“施力方”的Concept
		virtual vector<shared_ptr<iConcept>> GetFromConcept(const shared_ptr<iConcept> concept) const;
		//得到“受力方”的Concept
		virtual vector<shared_ptr<iConcept>> GetToConcept(const shared_ptr<iConcept> concept) const;
		virtual vector<ConceptInteractTable::ConceptPair> GetAllRelations() const;

		//合并ConceptInteractTable
		virtual void Absorb(const shared_ptr<iConceptInteractTable> absorbed);
		virtual void InteractDeeper();

	private: 
		bool PairExist(const int index1,const int index2) const;
	};
}


