#pragma once
#include "InOut.h"
#include "../MindInterface/PublicTypedef.h"

class TiXmlNode;

namespace LogicSystem
{
	class iLogicStatement;
	class iRelation;
}

namespace Mind
{
	class LogicKnowledge;

	///Append initial logic statements to the object of LogicKnowledge.
	class LogicKnowledgeInitializer
	{
		const static string ConditionCollectionNode;
		const static string ConditionNode;
		const static string ConstraintnNode;
		const static string ResultNode;
		const static string SymbolPairNode;
		const static string FromNode ;
		const static string ToNode ;
		const static string SymbolNode;

	public:
		LogicKnowledgeInitializer(void);
		~LogicKnowledgeInitializer(void);

		static void Initialize(const string filename,LogicKnowledge* logicKnowledge);

	private:
		//I make an assumption that the condition depth is 1, i.e.,there is no tag "ConditionCollection" under "ConditionCollection" in the xml file.
		static shared_ptr<LogicSystem::iLogicStatement> ParseLogicStatement(const TiXmlNode * node);
		static shared_ptr<LogicSystem::iRelation> ParseCondition(const TiXmlNode * node);
		static LogicType::SymbolPair ParseSymbolPair(const TiXmlNode * node);
	};
}


