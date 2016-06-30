#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;

	//////////////////////////////////////////////////////////////////////////
	///iConceptLevelTable contains a concept and distances to its all base concepts.
	//////////////////////////////////////////////////////////////////////////
	class _MINDINTERFACEINOUT iConceptLevelTable: public Obj<iConceptLevelTable>
	{
	public:
		iConceptLevelTable(void);
		virtual ~iConceptLevelTable(void);

		//////////////////////////////////////////////////////////////////////////
		///Add a distance <level> to a base concept <concept>.
		///<concept> should be a base concept.
		///If there already exists <concept> in me, then update the level to <concept> with the smaller one.
		//////////////////////////////////////////////////////////////////////////
		virtual void Insert(const shared_ptr<iConcept> concept,const int level) =0;
		
		//////////////////////////////////////////////////////////////////////////
		///Get the level between the concept in <me> and the base concept <concept>.
		///If there is no base concept in <me>, return -1.
		//////////////////////////////////////////////////////////////////////////
		virtual int LevelTo(const shared_ptr<iConcept> concept) const =0;
	};
}


