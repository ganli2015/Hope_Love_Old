#include "StdAfx.h"
#include "LogicReactor.h"

#include "../MindInterface/iExpression.h"
#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iConceptChain.h"
#include "../MindInterface/iConcept.h"
#include "../MindInterface/iMindElementCreator.h"
#include "../MindInterface/iLogicElementCreator.h"
#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iLogic.h"
#include "../MindInterface/iDeduceResult.h"

#include "../DataCollection/Sentence.h"
#include "../DataCollection/LanguageFunc.h"

#include "../CommonTools/GeneralFunctor.h"

#include "../Mathmatic/FindSequence.h"

using namespace LogicSystem;
using namespace Mind;
using namespace DataCollection;

LogicReactor::LogicReactor(void)
{
}


LogicReactor::~LogicReactor(void)
{
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

shared_ptr<Sentence> LogicReactor::Analyze( const shared_ptr<DataCollection::Sentence> sen ) const
{
	shared_ptr<iExpression> expre = iLogicElementCreator::CreateExpression(sen);

	shared_ptr<iLogic> logic=iLogicElementCreator::CreateLogic();
	vector<shared_ptr<iDeduceResult>> deduceRes=logic->FinalDeduce(expre);
	if(deduceRes.empty())
	{
		return NULL;
	}

	//Currently only consider the first result.
	shared_ptr<iDeduceResult> firstRes=deduceRes.front();
	//Currently only consider the concept result.
	shared_ptr<iConcept> conRes=firstRes->GetSingleConcept();
	if(conRes!=NULL)
	{
		string conStr=conRes->GetString();
		return shared_ptr<Sentence>(new Sentence(conStr));
	}
	else
	{
		return NULL;
	}
}