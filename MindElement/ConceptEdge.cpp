#include "StdAfx.h"
#include "ConceptEdge.h"
#include "Concept.h"
#include "ConceptInteractTable.h"

#include "../MindInterface/iConcept.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/CommonFunction.h"

namespace Mind
{
	ConceptEdge::ConceptEdge(void)
	{
	}


	ConceptEdge::~ConceptEdge(void)
	{
	}

	ConceptEdge::ConceptEdge( const shared_ptr<iConcept> concept ):_concept(concept),_sensitivity(1)
	{

	}

	ConceptEdge::ConceptEdge(const shared_ptr<iConcept> concept,const double sensi):_concept(concept),_sensitivity(sensi)
	{
		if(abs(sensi)>1)
		{
			throw runtime_error("Sensitivity must be between -1 and 1 !!");
		}
	}

	shared_ptr<iConceptInteractTable> ConceptEdge::GetSelfDeepInteract() const
	{
		shared_ptr<iConceptInteractTable> res(new ConceptInteractTable());

		vector<shared_ptr<iConcept>> base_to=_concept->GetBase();
		for (unsigned int i=0;i<_modification.size();++i)
		{
			vector<shared_ptr<iConcept>> base_mod=_modification[i]->GetBase();
			CommonFunction::AppendToInteractTable(base_mod,base_to,res);
		}

		return res;
	}

	shared_ptr<iConcept> ConceptEdge::GetConcept() const
	{
		return _concept->Copy();
	}

	void ConceptEdge::AddModification( const shared_ptr<iConcept> modification )
	{
		_modification.push_back(modification);
	}

	vector<shared_ptr<iConcept>> ConceptEdge::GetModification() const
	{
		vector<shared_ptr<iConcept>> res(_modification.size());
		for (unsigned int i=0;i<_modification.size();++i)
		{
			res[i]=_modification[i]->Copy();
		}

		return res;
	}

}


