#include "StdAfx.h"
#include "LogicReactor.h"

#include "../MindInterface/iExpression.h"
#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iConceptChain.h"
#include "../MindInterface/iConcept.h"
#include "../MindInterface/iMindElementCreator.h"
#include "../MindInterface/iLogicElementCreator.h"
#include "../MindInterface/CommonFunction.h"

#include "../DataCollection/Sentence.h"
#include "../DataCollection/LanguageFunc.h"

#include "../CommonTools/GeneralFunctor.h"

#include "../Mathmatic/FindSequence.h"

using namespace LogicSystem;
using namespace Mind;
using namespace DataCollection;

LogicReactor::LogicReactor(void)
{
	InitLogicPattern();
}


LogicReactor::~LogicReactor(void)
{
}


bool LogicReactor::ContainLogicExpression( const shared_ptr<DataCollection::Sentence> sen, shared_ptr<LogicSystem::iExpression>& expression ) const
{
	vector<shared_ptr<Mind::iConceptChain>> subConceptChains=ConvertToSubChains(sen);
	CREATE_FUNCTOR_IR(SatifyPattern,shared_ptr<LogicPattern>,shared_ptr<iConceptChain>,bool,
		if(_init->Satify(input))
		{
			return true;
		}
		else
		{
			return false;
		}
	);

	vector<shared_ptr<Mind::iConceptChain>>::iterator matchIter=find_if(subConceptChains.begin(),subConceptChains.end(),SatifyPattern(_logicPattern));
	if(matchIter!=subConceptChains.end())
	{
		expression=iLogicElementCreator::CreateExpression(sen);
		return true;
	}
	else
	{
		expression=NULL;
		return false;
	}
}

vector<shared_ptr<Mind::iConceptChain>> LogicReactor::ConvertToSubChains( const shared_ptr<DataCollection::Sentence> sen ) const
{
	vector<shared_ptr<Mind::iConceptChain>> res;

	iCerebrum* brain=iCerebrum::Instance();
	if(brain==NULL) 
	{
		return res;
	}
	
	//Contain puncture
	vector<shared_ptr<Word>> grammaWords=sen->GetGrammard();
	vector<shared_ptr<Word>> grammaWords_NoPunc=LanguageFunc::RemovePuncs(grammaWords);
	CREATE_FUNCTOR_R(ToConcept,shared_ptr<Word>,shared_ptr<iConcept>,
		shared_ptr<iConcept> con=iCerebrum::Instance()->GetConcept(input);
		Check(con!=NULL);
		return con;
	);
	//Transform words to concepts.
	vector<shared_ptr<iConcept>> concepts(grammaWords_NoPunc.size());
	try
	{
		transform(grammaWords_NoPunc.begin(),grammaWords_NoPunc.end(),concepts.begin(),ToConcept());
	}
	catch(...)
	{
		return res;
	}

	vector<vector<shared_ptr<iConcept>>> subConceptsSequence=Math::GetAllSubSequence<shared_ptr<iConcept>>::Get(concepts);
	//Transform concepts to concept chains.
	CREATE_FUNCTOR_R(ToConceptChain,vector<shared_ptr<iConcept>>,shared_ptr<iConceptChain>,
		return iMindElementCreator::CreateConceptChain(input);
	);
	transform(subConceptsSequence.begin(),subConceptsSequence.end(),back_inserter(res),ToConceptChain());

	return res;
}

void LogicReactor::InitLogicPattern()
{
	iCerebrum* brain=iCerebrum::Instance();
	if(brain==NULL) 
	{
		return ;
	}

	//Plus 
	vector<Identity> patternIdentity;
	patternIdentity.push_back(Identity("数字",0));
	patternIdentity.push_back(Identity("加",0));
	patternIdentity.push_back(Identity("数字",0));
	patternIdentity.push_back(Identity("等于",0));
	patternIdentity.push_back(Identity("多少",0));

	CREATE_FUNCTOR_R(ToConcept,Identity,shared_ptr<iConcept>,
		shared_ptr<iConcept> con=iCerebrum::Instance()->GetConcept(input);
	Check(con!=NULL);
	return con;
	);

	vector<shared_ptr<iConcept>> concepts(patternIdentity.size());
	try
	{
		transform(patternIdentity.begin(),patternIdentity.end(),concepts.begin(),ToConcept());
	}
	catch(...)
	{
		return;
	}

	_logicPattern=shared_ptr<LogicPattern>(new LogicPattern(iMindElementCreator::CreateConceptChain(concepts)));
}

bool LogicReactor::LogicPattern::Satify( const shared_ptr<Mind::iConceptChain> chain )
{
	if(_pattern->Size()!=chain->Size() || iCerebrum::Empty())
	{
		return false;
	}

	vector<shared_ptr<iConcept>> meVec=_pattern->GetConceptVec();
	vector<shared_ptr<iConcept>> inputVec=chain->GetConceptVec();
	for (unsigned int i=0;i<meVec.size();++i)
	{
		//check whether the base of inputVec match meVec
		vector<shared_ptr<iConcept>> base=inputVec[i]->GetBase();
		vector<shared_ptr<iConcept>>::iterator sameConceptIter=find_if(base.begin(),base.end(),CommonFunction::SameConcept(meVec[i]));
		if(sameConceptIter==base.end())
		{
			return false;
		}
	}

	return true;
}
