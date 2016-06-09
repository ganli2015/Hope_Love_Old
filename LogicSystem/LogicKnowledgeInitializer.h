#pragma once
#include "InOut.h"
#include "../MindInterface/PublicTypedef.h"
#include "../MindInterface/iLogicElementCreator.h"

class TiXmlNode;
class TiXmlElement;

namespace LogicSystem
{
	class LogicKnowledge;
	class iLogicStatement;
	class iRelation;
	class iRelationConstraint;

	template<class T>
	class Arbitrariness;
	template<class T>
	class Symbol;

	///Append initial logic statements to the object of LogicKnowledge.
	class _LOGICSYSTEMINOUT LogicKnowledgeInitializer
	{
		const static string ConditionCollectionNode;
		const static string ConditionNode;
		const static string ConstraintnNode;
		const static string ResultCollectionNode;
		const static string ResultNode;
		const static string SymbolPairNode;
		const static string FromNode ;
		const static string ToNode ;
		const static string SymbolNode;
		const static string EqualityNode ;
		const static string InequalityNode ;

		const static string ArbSymbol ;
		const static string NumSymbol ;
		const static string VerbSymbol ;
		const static string EqualSymbol ;
		const static string InequalSymbol ;

		///Record the special symbol string in Xml file and special symbol during parsing the file.
		map<string,shared_ptr<LogicType::ConSymbol>> _spSymbolTable;
		vector<string> _constraintNodeTag;

		friend class Test_LogicSystem;

	public:
		LogicKnowledgeInitializer(void);
		~LogicKnowledgeInitializer(void);

		void Initialize(const string filename,LogicKnowledge* logicKnowledge);

	private:
		//I make an assumption that the condition depth is 1, i.e.,there is no tag "ConditionCollection" under "ConditionCollection" in the xml file.
		shared_ptr<LogicSystem::iLogicStatement> ParseLogicStatement(const TiXmlNode * node);
		shared_ptr<LogicSystem::iRelation> ParseRelation(const TiXmlNode * node);
		LogicType::SymbolPair ParseSymbolPair(const TiXmlNode * node);
		shared_ptr<LogicType::ConSymbol> ParseFromToSymbol(const TiXmlElement *node);
		shared_ptr<LogicType::ConSymbol> ParseConSymbol(const TiXmlElement * element) const;
		shared_ptr<LogicType::ConSymbol> ParseArbSymbol(const TiXmlElement * element,const iLogicElementCreator::SymbolType type);
		shared_ptr<LogicSystem::iRelation> ParseRelationCollection(const TiXmlNode * node,
			const string relationCollectionNodeStr,//Tag name of relation node
			const string relationNodeStr);//Tag name of relation leaf

		vector<shared_ptr<LogicSystem::iRelationConstraint>> ParseConstraints(const TiXmlNode * node) const;
		shared_ptr<LogicSystem::iRelationConstraint> ParseSingleConstraint(const TiXmlNode * node,const string constraintStr) const;
		shared_ptr<LogicSystem::iRelationConstraint> CreateConstraint(const string constaintStr,
			const shared_ptr<LogicType::ConSymbol> sym1,const shared_ptr<LogicType::ConSymbol> sym2) const;

	};
}


