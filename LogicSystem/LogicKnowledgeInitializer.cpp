#include "StdAfx.h"
#include "LogicKnowledgeInitializer.h"
#include "LogicKnowledge.h"

#include "../MindInterface/iLogicStatement.h"
#include "../MindInterface/iRelation.h"
#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iConcept.h"
#include "../MindInterface/iLogicElementCreator.h"

#include "RelationLeaf.h"
#include "RelationNode.h"
#include "Symbol.h"
#include "Arbitrariness.h"
#include "Equality.h"
#include "Inequality.h"
#include "LogicStatement.h"
#include "Number.h"

#include "../CommonTools/CommonStringFunction.h"


#include "tinyxml.h"

using namespace CommonTool;
using namespace Mind;

namespace LogicSystem
{
	const string LogicKnowledgeInitializer::ConditionCollectionNode = "ConditionCollection";
	const string LogicKnowledgeInitializer::ConditionNode = "Condition";
	const string LogicKnowledgeInitializer::ConstraintnNode = "Constraint";
	const string LogicKnowledgeInitializer::ResultCollectionNode = "ResultCollection";
	const string LogicKnowledgeInitializer::ResultNode = "Result";
	const string LogicKnowledgeInitializer::SymbolPairNode = "SymbolPair";
	const string LogicKnowledgeInitializer::SingleNode = "SingleSymbol";
	const string LogicKnowledgeInitializer::FromNode = "From";
	const string LogicKnowledgeInitializer::ToNode = "To";
	const string LogicKnowledgeInitializer::RepNumNode= "RepNum";
	const string LogicKnowledgeInitializer::SymbolNode = "Symbol";
	const string LogicKnowledgeInitializer::EqualityNode = "Equality";
	const string LogicKnowledgeInitializer::InequalityNode = "Inequality";

	const string LogicKnowledgeInitializer::ArbSymbol = "Arb";
	const string LogicKnowledgeInitializer::NumSymbol = "Num";
	const string LogicKnowledgeInitializer::VerbSymbol = "Verb";
	const string LogicKnowledgeInitializer::EqualSymbol = "==";
	const string LogicKnowledgeInitializer::InequalSymbol = "!=";

	LogicKnowledgeInitializer::LogicKnowledgeInitializer(void)
	{
		_constraintNodeTag.push_back(EqualityNode);
		_constraintNodeTag.push_back(InequalityNode);

		_str_type.insert(make_pair(ArbSymbol,iLogicElementCreator::Arb));
		_str_type.insert(make_pair(NumSymbol,iLogicElementCreator::Num));
		_str_type.insert(make_pair(VerbSymbol,iLogicElementCreator::Verb));

	}


	LogicKnowledgeInitializer::~LogicKnowledgeInitializer(void)
	{
	}

	void LogicKnowledgeInitializer::Initialize( const string filename,LogicKnowledge* logicKnowledge )
	{
		TiXmlDocument *myDocument = new TiXmlDocument(filename.c_str());
		myDocument->LoadFile();
		TiXmlNode *root=myDocument->FirstChild("Root");
	
		TiXmlNode *statementNode=root->FirstChild("LogicStatement");
		for (;statementNode!=0;statementNode=statementNode->NextSibling())
		{
			shared_ptr<iLogicStatement> statement=ParseLogicStatement(statementNode);
			logicKnowledge->Add(statement);
		}

		delete root;
	}

	shared_ptr<iLogicStatement> LogicKnowledgeInitializer::ParseLogicStatement(const TiXmlNode * node)
	{
		_spSymbolTable.clear();

		shared_ptr<iRelation> conditions=ParseRelationCollection(node,ConditionCollectionNode,ConditionNode);
		vector<shared_ptr<iRelationConstraint>> constraints=ParseConstraints(node);
		for (unsigned int i=0;i<constraints.size();++i)
		{
			conditions->AddConstraint(constraints[i]);
		}

		shared_ptr<iRelation> results=ParseRelationCollection(node,ResultCollectionNode,ResultNode);

		shared_ptr<iLogicStatement> res(iLogicElementCreator::CreateLogicStatement(conditions,results));

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
			shared_ptr<iRelationNode> nodeRoot(iLogicElementCreator::CreateRelationNode());

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
			if(_spSymbolTable.count(symbolStr)==0)
			{
				throw runtime_error("No symbolStr in _arbTable");
			}
			else
			{
				symbols.push_back(_spSymbolTable.at(symbolStr));
			}
		}
		//Currently assume there are only two symbols in a constraint relation.
		assert(symbols.size()==2);

		return CreateConstraint(constraintNodeTag,symbols[0],symbols[1]);
	}

	shared_ptr<iRelation> LogicKnowledgeInitializer::ParseRelation(const TiXmlNode * node)
	{
		shared_ptr<iRelationLeaf> leaf(iLogicElementCreator::CreateRelationLeaf());

		const TiXmlNode *symbolPairNode=node->FirstChild(SymbolPairNode.c_str());
		for (;symbolPairNode!=0;symbolPairNode=symbolPairNode->NextSibling())
		{
			shared_ptr<Num> repNum;
			LogicType::SymbolPair pair=ParseSymbolPair(symbolPairNode,repNum);
			if(repNum==NULL)
				leaf->AddRelation(pair.first,pair.second);	
			else
				leaf->AddRelation(pair.first,pair.second,repNum);	
		}

		return leaf;
	}

	LogicType::SymbolPair LogicKnowledgeInitializer::ParseSymbolPair( const TiXmlNode * node ,shared_ptr<Num>& repNum)
	{
		//Parse from
		const TiXmlElement *fromNode=node->FirstChildElement(FromNode.c_str());
		shared_ptr<LogicType::ConSymbol> fromSym=ParseFromToSymbol(fromNode);
		//Parse to
		const TiXmlElement *toNode=node->FirstChildElement(ToNode.c_str());
		shared_ptr<LogicType::ConSymbol> toSym=ParseFromToSymbol(toNode);
		//Parse repetition number
		const TiXmlElement *repNumNode=node->FirstChildElement(RepNumNode.c_str());
		if(repNumNode!=NULL)
		{
			shared_ptr<LogicType::ConSymbol> spSymbol=ParseSpecialSymbol(repNumNode,iLogicElementCreator::Num);
			repNum=dynamic_pointer_cast<Num>(spSymbol);
		}
		
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
		else//Special symbol
		{
			string innerText(textCh);
			for (map<string,iLogicElementCreator::SymbolType>::const_iterator it=_str_type.begin();it!=_str_type.end();++it)
			{
				if(innerText.find(it->first)!=string::npos)
				{
					sym=ParseSpecialSymbol(node,it->second);
					break;
				}
			}

		}

		assert(sym!=NULL);

		return sym;
	}

	shared_ptr<LogicType::ConSymbol> LogicKnowledgeInitializer::ParseConSymbol( const TiXmlElement * element ) const
	{
		//Read identity of the concept.
		int id=StrToInt(element->Attribute("ID"));
		string word=element->Attribute("Word");
		Identity w_i;
		w_i.id=id;
		w_i.str=word;

		//Get concept from Cerebrum as logic statement needs knowledgh about the concept.
		shared_ptr<iConcept> concept=iCerebrum::Instance()->GetConcept(w_i);
		shared_ptr<LogicType::ConSymbol> sym(iLogicElementCreator::CreateConceptSymbol(concept));
		return sym;
	}

	shared_ptr<LogicType::ConSymbol> LogicKnowledgeInitializer::ParseSpecialSymbol( const TiXmlElement * element ,const iLogicElementCreator::SymbolType type)
	{
		string arbStr=element->GetText();
		if(_spSymbolTable.count(arbStr)!=0)
		{
			return _spSymbolTable[arbStr];
		}
		else
		{
			shared_ptr<LogicType::ConSymbol> arb=iLogicElementCreator::CreateSpecialSymbol(type);
			_spSymbolTable[arbStr]=arb;
			return arb;
		}	

	}

	shared_ptr<LogicSystem::iRelationConstraint> LogicKnowledgeInitializer::CreateConstraint( const string constaintStr ,
		const shared_ptr<LogicType::ConSymbol> sym1,const shared_ptr<LogicType::ConSymbol> sym2) const
	{
		if(constaintStr==EqualityNode)
		{
			return iLogicElementCreator::CreateBinaryConstraint(iLogicElementCreator::Eq,sym1,sym2);
		}
		else if(constaintStr==InequalityNode)
		{
			return iLogicElementCreator::CreateBinaryConstraint(iLogicElementCreator::Ineq,sym1,sym2);
		}
		else
		{
			throw runtime_error("Invalid constaintStr");
		}
	}


}
