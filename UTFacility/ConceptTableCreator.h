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
	ConceptTableCreator(void);
	~ConceptTableCreator(void);

	static shared_ptr<Mind::iConceptInteractTable> SimpleCreate(const string str);
	static shared_ptr<Mind::iConceptInteractTable> Create(const string str);

private:
	static shared_ptr<Mind::iConceptInteractTable> Parse(const string str);
	static shared_ptr<Mind::iConcept> ParseConcept( const string str );
};

