#include "StdAfx.h"
#include "LogicKnowledgeInitializer.h"
#include "LogicKnowledge.h"

#include "../MindInterface/iLogicStatement.h"
#include "../MindInterface/iRelation.h"
#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iConcept.h"

#include "../LogicSystem/RelationLeaf.h"
#include "../LogicSystem/RelationNode.h"
#include "../LogicSystem/Symbol.h"
#include "../LogicSystem/Arbitrariness.h"
#include "../LogicSystem/Equality.h"
#include "../LogicSystem/Inequality.h"
#include "../LogicSystem/LogicStatement.h"

#include "../CommonTools/CommonStringFunction.h"


#include "tinyxml.h"

using namespace LogicSystem;
using namespace CommonTool;

namespace Mind
{
	const string LogicKnowledgeInitializer::ConditionCollectionNode = "ConditionCollection";
	const string LogicKnowledgeInitializer::ConditionNode = "Condition";
	const string LogicKnowledgeInitializer::ConstraintnNode = "Constraint";
	const string LogicKnowledgeInitializer::ResultCollectionNode = "ResultCollection";
	const string LogicKnowledgeInitializer::ResultNode = "Result";
	const string LogicKnowledgeInitializer::SymbolPairNode = "SymbolPair";
	const string LogicKnowledgeInitializer::FromNode = "From";
	const string LogicKnowledgeInitializer::ToNode = "To";
	const string LogicKnowledgeInitializer::SymbolNode = "Symbol";
	const string LogicKnowledgeInitializer::EqualityNode = "Equality";
	const string LogicKnowledgeInitializer::InequalityNode = "Inequality";

	const string LogicKnowledgeInitializer::ArbSymbol = "Arb";
	const string LogicKnowledgeInitializer::EqualSymbol = "==";
	const string LogicKnowledgeInitializer::InequalSymbol = "!=";

	LogicKnowledgeInitializer::LogicKnowledgeInitializer(void)
	{
		_constraintNodeTag.push_back(EqualityNode);
		_constraintNodeTag.push_back(InequalityNode);
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
			shared_ptr<iLogicStatement> statement=ParseLogicStatement(statementNode);
			logicKnowledge->Add(statement);
		}

		delete root;
		delete myDocument;
	}

	shared_ptr<iLogicStatement> LogicKnowledgeInitializer::ParseLogicStatement(const TiXmlNode * node)
	{
		_arbTable.clear();

		shared_ptr<iRelation> conditions=ParseRelationCollection(node,ConditionCollectionNode,ConditionNode);
		vector<shared_ptr<iRelationConstraint>> constraints=ParseConstraints(node);
		for (unsigned int i=0;i<constraints.size();++i)
		{
			conditions->AddConstraint(constraints[i]);
		}

		shared_ptr<iRelation> results=ParseRelationCollection(node,ResultCollectionNode,ResultNode);

		shared_ptr<iLogicStatement> res(new LogicStatement(conditions,results));

		return res;
	}

	shared_ptr<iRelation> LogicKnowledgeInitializer::ParseRelationCollection(const TiXmlNode * node,
		const string relationCollectionNodeStr,const string relationNodeStr)
	{
		const TiXmlElement *relationCollectionNode=node->FirstChildElement(relationCollectionNodeStr.c_str());
		if(relationCollectionNode==NULL)//Parse relation leaf
		{
			const TiXmlElement *relationNode=node->FirstChildElement(relationNodeStr.c_str());
			shared_ptr<iRelation> res=ParseRelation(relationNode);
			return res;
		}
		else//Parse relation node
		{
			const TiXmlElement *relationNode=relationCollectionNode->FirstChildElement(relationNodeStr.c_str());
			shared_ptr<iRelationNode> nodeRoot(new RelationNode());

			//Read logic relation , Or or And
			string logicRelation=relationCollectionNode->Attribute("Relation");
			if(logicRelation=="Or")
			{
				nodeRoot->SetState(iRelationNode::Or);
			}
			else
			{
				nodeRoot->SetState(iRelationNode::And);
			}
			for (;relationNode!=0;relationNode=relationNode->NextSiblingElement())
			{
				shared_ptr<iRelation> subRelation=ParseRelation(relationNode);
				nodeRoot->AddSubRelation(subRelation);
			}

			return nodeRoot;
		}	
	}

	vector<shared_ptr<iRelationConstraint>> LogicKnowledgeInitializer::ParseConstraints(const TiXmlNode * node) const
	{
		vector<shared_ptr<iRelationConstraint>> res;

		for (unsigned int i=0;i<_constraintNodeTag.size();++i)//Parse each constraint node type.
		{
			const TiXmlElement *constraintNode=node->FirstChildElement(_constraintNodeTag[i].c_str());

			//Parse each node of the same type.
			for (;constraintNode!=0;constraintNode=constraintNode->NextSiblingElement(_constraintNodeTag[i].c_str()))
			{
				res.push_back(ParseSingleConstraint(constraintNode,_constraintNodeTag[i]));
			}
		}

		return res;
	}

	shared_ptr<iRelationConstraint> LogicKnowledgeInitializer::ParseSingleConstraint(const TiXmlNode * node,const string constraintNodeTag) const
	{
		//Collect symbols.
		vector<shared_ptr<LogicType::ConSymbol>> symbols;
		const TiXmlElement *symbolNode=node->FirstChildElement(SymbolNode.c_str());
		for (;symbolNode!=0;symbolNode=symbolNode->NextSiblingElement(SymbolNode.c_str()))
		{
			//Currently assume only Arbitrariness appear in the constraint node.
			string symbolStr=symbolNode->GetText();
			if(_arbTable.count(symbolStr)==0)
			{
				throw runtime_error("No symbolStr in _arbTable");
			}
			else
			{
				symbols.push_back(_arbTable.at(symbolStr));
			}
		}
		//Currently assume there are only two symbols in a constraint relation.
		assert(symbols.size()==2);

		return CreateConstraint(constraintNodeTag,symbols[0],symbols[1]);
	}

	shared_ptr<iRelation> LogicKnowledgeInitializer::ParseRelation(const TiXmlNode * node)
	{
		shared_ptr<RelationLeaf> leaf(new RelationLeaf());

		const TiXmlNode *symbolPairNode=node->FirstChild(SymbolPairNode.c_str());
		for (;symbolPairNode!=0;symbolPairNode=symbolPairNode->NextSibling())
		{
			LogicType::SymbolPair pair=ParseSymbolPair(symbolPairNode);
			leaf->AddRelation(pair.first,pair.second);	
		}

		return leaf;
	}



	LogicType::SymbolPair LogicKnowledgeInitializer::ParseSymbolPair( const TiXmlNode * node )
	{
		const TiXmlElement *fromNode=node->FirstChildElement(FromNode.c_str());
		shared_ptr<LogicType::ConSymbol> fromSym=ParseFromToSymbol(fromNode);

		const TiXmlElement *toNode=node->FirstChildElement(ToNode.c_str());
		shared_ptr<LogicType::ConSymbol> toSym=ParseFromToSymbol(toNode);

		return make_pair(fromSym,toSym);
	}

	shared_ptr<LogicType::ConSymbol> LogicKnowledgeInitializer::ParseFromToSymbol(const TiXmlElement *node)
	{
		const char *textCh=node->GetText();
		shared_ptr<LogicType::ConSymbol> sym;
		if(textCh==NULL)//Common Symbol
		{
			sym=ParseConSymbol(node);
		}
		else
		{
			string innerText(textCh);
			if(innerText.find(ArbSymbol)!=string::npos)
			{
				sym=ParseArbSymbol(node);
			}
		}

		assert(sym!=NULL);

		return sym;
	}

	shared_ptr<LogicType::ConSymbol> LogicKnowledgeInitializer::ParseConSymbol( const TiXmlElement * element ) const
	{
		int id=StrToInt(element->Attribute("ID"));
		string word=element->Attribute("Word");
		Identity w_i;
		w_i.id=id;
		w_i.str=word;

		shared_ptr<iConcept> concept=iCerebrum::Instance()->GetConcept(w_i);
		shared_ptr<Sym> sym(new Sym(concept));
		return sym;
	}

	shared_ptr<LogicType::ConSymbol> LogicKnowledgeInitializer::ParseArbSymbol( const TiXmlElement * element )
	{
		string arbStr=element->GetText();
		if(_arbTable.count(arbStr)!=0)
		{
			return _arbTable[arbStr];
		}
		else
		{
			shared_ptr<Arb> arb=Arb::Create();
			_arbTable[arbStr]=arb;
			return arb;
		}	

	}

	shared_ptr<LogicSystem::iRelationConstraint> LogicKnowledgeInitializer::CreateConstraint( const string constaintStr ,
		const shared_ptr<LogicType::ConSymbol> sym1,const shared_ptr<LogicType::ConSymbol> sym2) const
	{
		if(constaintStr==EqualityNode)
		{
			return Equality::Create(sym1,sym2);
		}
		else if(constaintStr==InequalityNode)
		{
			return Inequality::Create(sym1,sym2);
		}
		else
		{
			throw runtime_error("Invalid constaintStr");
		}
	}


}
