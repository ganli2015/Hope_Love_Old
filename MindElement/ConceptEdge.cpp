#include "StdAfx.h"
#include "ConceptEdge.h"
#include "Concept.h"
#include "ConceptInteractTable_iConcept.h"

#include "../MindInterface/iConcept.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/PublicTypedef.h"
#include "../MindInterface/iMindElementCreator.h"

#include "../Mathmatic/MathTool.h"

namespace Mind
{
	ConceptEdge::ConceptEdge(void)
	{
		Init();
	}


	ConceptEdge::~ConceptEdge(void)
	{
	}

	ConceptEdge::ConceptEdge( const shared_ptr<iConcept> concept ):_concept(concept),_sensitivity(1)
	{
		Init();
	}

	ConceptEdge::ConceptEdge(const shared_ptr<iConcept> concept,const double sensi):_concept(concept),_sensitivity(sensi)
	{
		if(abs(sensi)>1)
		{
			throw runtime_error("Sensitivity must be between -1 and 1 !!");
		}

		Init();
	}

	shared_ptr<iConceptInteractTable> ConceptEdge::GetSelfDeepInteract() const
	{
		shared_ptr<iConceptInteractTable> res(new ConceptInteractTable_iConcept());

		
		vector<MindType::ConceptPair> pairs=_modTable->GetAllRelations();
		//Go through all concept pairs and collect base interaction pairs.
		for (unsigned int i=0;i<pairs.size();++i)
		{
			vector<shared_ptr<iConcept>> base_from=pairs[i].first->GetBase();
			vector<shared_ptr<iConcept>> base_to=pairs[i].second->GetBase();
			CommonFunction::AppendToInteractTable(base_from,base_to,res);
		}

		return res;
	}

	shared_ptr<iConcept> ConceptEdge::GetConcept() const
	{
		return _concept.lock()->Copy();
	}

	void ConceptEdge::AddModification( const shared_ptr<iConcept> modification )
	{
		//_modification.push_back(modification);
		_modTable->Add(modification,_concept.lock());
	}

	void ConceptEdge::AddModification( const shared_ptr<iConceptInteractTable> table )
	{
		_modTable->Absorb(table);
	}

	void ConceptEdge::Init()
	{
		_modTable=iMindElementCreator::CreateConceptInteractTable(iMindElementCreator::ConceptInteractTable_IdentityBased);
	}

	shared_ptr<iConceptInteractTable> ConceptEdge::GetModification() const
	{
		return _modTable->Copy();
	}

	bool ConceptEdge::MatchWithConceptTable( const shared_ptr<iConceptInteractTable> description ) const
	{
		if(_modTable->Same(description))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool ConceptEdge::MatchWithConceptTable( const shared_ptr<iConceptInteractTable> description,shared_ptr<iConcept>& toConcept ) const
	{
		if(MatchWithConceptTable(description))
		{
			toConcept=_concept.lock()->Copy();
			return true;
		}
		else
		{
			return false;
		}
	}

}


