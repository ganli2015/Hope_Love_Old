#pragma once
#include "PublicHeader.h"

namespace Mind
{
	class iConceptInteractTable;
	class iConcept;
}

class ConceptCreator;

class _UTFACILITYINOUT ConceptTableCreator
{
	static shared_ptr<ConceptCreator> _myConceptCreator;

public:
	enum Type
	{
		Concept_Based,
		Identity_Based,
		Set_Based
	};

public:
	ConceptTableCreator(void);
	~ConceptTableCreator(void);

	///Create ConceptInteractTable_iConcept.
	static shared_ptr<Mind::iConceptInteractTable> SimpleCreate(const string str,const Type type=Concept_Based);
	static shared_ptr<Mind::iConceptInteractTable> Create(const string str,const Type type=Concept_Based);

private:
	static shared_ptr<Mind::iConceptInteractTable> Parse(const string str,const Type type );
	static shared_ptr<Mind::iConcept> ParseConcept( const string str );
};



