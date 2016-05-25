#pragma once
#include "PublicHeader.h"

class ConceptCreator;

namespace LogicSystem
{
	template<class T>
	class Symbol;
}

namespace Mind
{
	class iConcept;
}

class SymbolCreator
{
	shared_ptr<ConceptCreator> _conceptCreator;
public:
	SymbolCreator(const shared_ptr<ConceptCreator> val);
	~SymbolCreator(void);

	shared_ptr<LogicSystem::Symbol<Mind::iConcept>> Create(const string) const;
};

