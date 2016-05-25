#pragma once
#include "PublicHeader.h"

namespace Mind
{
	class ConceptInteractTable;
	class iConcept;
}

class ConceptCreator;

class ConceptTableCreator
{
	static shared_ptr<ConceptCreator> _myConceptCreator;

public:
	ConceptTableCreator(void);
	~ConceptTableCreator(void);

	static shared_ptr<Mind::ConceptInteractTable> SimpleCreate(const string str);
	static shared_ptr<Mind::ConceptInteractTable> Create(const string str);

private:
	static shared_ptr<Mind::ConceptInteractTable> Parse(const string str);
	static shared_ptr<Mind::iConcept> ParseConcept( const string str );
};

