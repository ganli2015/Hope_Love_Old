#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;
	class iConceptInteractTable;
	class _MINDINTERFACEINOUT iConceptEdge: public Obj<iConceptEdge>
	{
	public:
		iConceptEdge(void);
		virtual ~iConceptEdge(void);

		virtual shared_ptr<iConcept> GetConcept() const=0;
		virtual double GetSensitivity() const =0;
		//From -1 (negative) to 1(positive)
		virtual void SetSensitivity(double val) =0;

		virtual void AddModification(const shared_ptr<iConcept> modification) =0;
		virtual void AddModification(const shared_ptr<iConceptInteractTable> table) =0;

		///Get the modification represented as a iConceptInteractTable which contains concept pairs 
		///and describe the relation graph about <me>.
		virtual shared_ptr<iConceptInteractTable> GetModification() const =0;

		//Build the deep interaction table of <me> including the interaction from modifications to "to concept".
		virtual shared_ptr<iConceptInteractTable> GetSelfDeepInteract() const =0;

		///Check whether the description of <me> to a concept is exactly matched with <description>.
		virtual bool MatchWithConceptTable(const shared_ptr<iConceptInteractTable> description) const =0;
	};
}


