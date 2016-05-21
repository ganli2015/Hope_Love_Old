#include "StdAfx.h"
#include "LogicKnowledgeInitializer.h"

#include "../MindInterface/iLogicStatement.h"
#include "../MindInterface/iRelation.h"

#include "../LogicSystem/RelationLeaf.h"
#include "../LogicSystem/RelationNode.h"

#include "tinyxml.h"

using namespace LogicSystem;

namespace Mind
{
	const string LogicKnowledgeInitializer::ConditionCollectionNode = "ConditionCollection";
	const string LogicKnowledgeInitializer::ConditionNode = "Condition";
	const string LogicKnowledgeInitializer::ConstraintnNode = "Constraint";
	const string LogicKnowledgeInitializer::ResultNode = "Result";
	const string LogicKnowledgeInitializer::SymbolPairNode = "SymbolPair";
	const string LogicKnowledgeInitializer::FromNode = "From";
	const string LogicKnowledgeInitializer::ToNode = "To";
	const string LogicKnowledgeInitializer::SymbolNode = "Symbol";

	LogicKnowledgeInitializer::LogicKnowledgeInitializer(void)
	{
	}


	LogicKnowledgeInitializer::~LogicKnowledgeInitializer(void)
	{
	}

	void LogicKnowledgeInitializer::Initialize( const string filename,LogicKnowledge* logicKnowledge )
	{
		TiXmlDocument *myDocument = new TiXmlDocument();
		myDocument->LoadFile(filename.c_str());
		TiXmlNode *root=myDocument->FirstChild("Root");
	
		TiXmlNode *statementNode=root->FirstChild("LogicStatement");
		for (;statementNode!=0;statementNode=statementNode->NextSibling())
		{

		}
	}

	shared_ptr<iLogicStatement> LogicKnowledgeInitializer::ParseLogicStatement(const TiXmlNode * node)
	{
		const TiXmlElement *conditionCollectionNode=node->FirstChildElement(ConditionCollectionNode.c_str());
		const TiXmlElement *conditionNode=conditionCollectionNode->FirstChildElement(ConditionNode.c_str());
		
		shared_ptr<iRelationNode> relationNode(new RelationNode());
		//Read logic relation , Or or And
		string logicRelation=conditionCollectionNode->Attribute("Relation");
		if(logicRelation=="Or")
		{
			relationNode->SetState(iRelationNode::Or);
		}
		else
		{
			relationNode->SetState(iRelationNode::And);
		}
		for (;conditionNode!=0;conditionNode=conditionNode->NextSiblingElement())
		{

		}
		return NULL;
	}

	shared_ptr<iRelation> LogicKnowledgeInitializer::ParseCondition(const TiXmlNode * node)
	{
		const TiXmlNode *symbolPairNode=node->FirstChild(ConditionNode.c_str());
		for (;symbolPairNode!=0;symbolPairNode=symbolPairNode->NextSibling())
		{
			
		}

		return NULL;
	}

	LogicType::SymbolPair LogicKnowledgeInitializer::ParseSymbolPair( const TiXmlNode * node )
	{
		const TiXmlElement *fromNode=node->FirstChildElement(FromNode.c_str());
		string innerText=fromNode->Value();
		if(innerText=="")//Common Symbol
		{
			
		}
		return LogicType::SymbolPair();
	}

}
