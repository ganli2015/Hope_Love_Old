#pragma once
#include <memory>
#include <utility>
using std::tr1::shared_ptr;
using namespace std;

namespace Mind
{
	class iConcept;
}

struct MindType
{
	typedef pair<shared_ptr<Mind::iConcept>,shared_ptr<Mind::iConcept>> ConceptPair;
};

namespace LogicSystem
{
	template<class T>
	class iSymbol;
}

struct LogicType
{
	typedef LogicSystem::iSymbol<Mind::iConcept> ConSymbol;//Concept Symbol
	typedef pair<shared_ptr<ConSymbol>,shared_ptr<ConSymbol>> SymbolPair;
};

