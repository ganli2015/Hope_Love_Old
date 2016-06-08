#include "StdAfx.h"
#include "iConceptInteractTable.h"
#include "iConcept.h"

namespace Mind
{
	iConceptInteractTable::iConceptInteractTable()
	{
	}


	iConceptInteractTable::~iConceptInteractTable(void)
	{
	}

	std::string iConceptInteractTable::GetString() const
	{
		string res="";

		vector<MindType::ConceptPair> pairs=GetAllRelations();
		for (unsigned int i=0;i<pairs.size();++i)
		{
			res+=pairs[i].first->GetString()+" "+pairs[i].second->GetString()+"\n";
		}

		return res;
	}

}

