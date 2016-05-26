#pragma once
#include "PublicHeader.h"
#include "../MindInterface/PublicTypedef.h"

namespace LogicSystem
{
	class RelationLeaf;
}

class ConceptCreator;

class _UTFACILITYINOUT LeafCreator
{
private:

	class iSpecialSymbol
	{
	public:
		virtual shared_ptr<LogicType::ConSymbol> Create()=0;
	};

	template<class T>
	class SpecialSymbol : public iSpecialSymbol
	{
	public:
		SpecialSymbol(){}
		shared_ptr<LogicType::ConSymbol> Create(){return T::Create();}
	};

private:
	///Restore special symbol creators
	static map<string,iSpecialSymbol*> SpSym;

	static shared_ptr<ConceptCreator> MyConceptCreator;

public:
	LeafCreator(void);
	~LeafCreator(void);

	static void Init();
	///Create a leaf containing simple concepts.
	static shared_ptr<LogicSystem::RelationLeaf> SimpleCreate(const string str);

	///Create a leaf containing concepts from cerebrum.
	///The id of a word is 0 for default.
	static shared_ptr<LogicSystem::RelationLeaf> Create(const string str);

private:
	static shared_ptr<LogicSystem::RelationLeaf> Parse(const string str);
	static bool Contain(const string raw,const string search);
	static shared_ptr<LogicType::ConSymbol> ParseSpSymbol(const string str);
	static shared_ptr<LogicType::ConSymbol> ParseSymbol( const string str );
};

