#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;

	//Concept相互作用的列表。该相互作用与ConceptEdge不同，后者是存在于ConceptSet里的原型的连接，
	//是一个已经有较牢固关系的连接。前者则是临时的连接，通常是在遇见新的知识新的语句的时候建立的。
	class _MINDINTERFACEINOUT iConceptInteractTable
	{
	public:
		iConceptInteractTable(void);
		virtual ~iConceptInteractTable(void);

		//添加的连接不会重复
		virtual void Add(const shared_ptr<iConcept> from, const shared_ptr<iConcept> to) =0;
		//得到“施力方”的Concept
		virtual vector<shared_ptr<iConcept>> GetFromConcept(const shared_ptr<iConcept> concept) const =0;
		//得到“受力方”的Concept
		virtual vector<shared_ptr<iConcept>> GetToConcept(const shared_ptr<iConcept> concept) const =0;
		virtual vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> GetAllRelations() const =0;

		//合并ConceptInteractTable
		virtual void Absorb(const shared_ptr<iConceptInteractTable> absorbed) =0;
		virtual void InteractDeeper() =0;
	};
}


