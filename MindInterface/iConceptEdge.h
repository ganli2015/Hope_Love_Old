#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;
	class ConceptInteractTable;
	class _MINDINTERFACEINOUT iConceptEdge
	{
	public:
		iConceptEdge(void);
		~iConceptEdge(void);

		virtual shared_ptr<iConcept> GetConcept() const=0;
		virtual double GetSensitivity() const =0;
		//From -1 (negative) to 1(positive)
		virtual void SetSensitivity(double val) =0;

		virtual void AddModification(const shared_ptr<iConcept> modification) =0;
		virtual vector<shared_ptr<iConcept>> GetModification() const =0;

		//����<_modification>��<_concept>������õ��б�
		virtual shared_ptr<ConceptInteractTable> GetSelfDeepInteract() const =0;
	};
}


