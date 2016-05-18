#include "StdAfx.h"
#include "FuncForTest.h"

#include "../Mind/Cerebrum.h"

#include "../MindElement/Concept.h"
#include "../MindElement/ConceptInteractTable.h"
#include "../MindElement/ConceptChain.h"

#include "../MindInterface/iConceptChain.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/iCerebrum.h"

#include "../DataCollection/Word.h"
#include "../DataCollection/GrammaPattern.h"

#include "../CommonTools/MyObject.h"

using namespace Mind;
using namespace DataCollection;


namespace FuncForTest
{

	shared_ptr<iConcept> SimpleConcept( const string str )
	{
		shared_ptr<Word> w(new Word(str));
		shared_ptr<Concept> res(new Concept(w)); 

		return res;
	}

	bool PairSameWithTable( const vector<pair<string,string>>& expect,const shared_ptr<iConceptInteractTable> table )
	{
		class FindRelation
		{
			pair<string,string> _p;
		public: 
			FindRelation(const pair<string,string> p):_p(p){}
			~FindRelation(){}

			bool operator()(const pair<shared_ptr<iConcept>,shared_ptr<iConcept>> conceptPair)
			{
				if(conceptPair.first->GetString()==_p.first && conceptPair.second->GetString()==_p.second)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};

		vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> relations=table->GetAllRelations();
		if(relations.size()!=expect.size())
		{
			return false;
		}

		for (unsigned int i=0;i<expect.size();++i)
		{
			vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>>::iterator iter=find_if(relations.begin(),relations.end(),FindRelation(expect[i]));
			if(iter==relations.end())
			{
				return false;
			}
			else
			{
				relations.erase(iter);
			}
		}

		return true;
	}

	bool SameChainVec( const vector<vector<string>>& expect, const vector<shared_ptr<iConceptChain>>& result )
	{
		if(expect.size()!=result.size())
		{
			return false;
		}

		vector<shared_ptr<iConceptChain>> resCopy=result;

		for (unsigned int i=0;i<expect.size();++i)
		{
			bool hasSameChain=false;
			for (unsigned int j=0;j<resCopy.size();++j)
			{
				if(SameChain(expect[i],resCopy[j]))
				{
					resCopy.erase(resCopy.begin()+j);
					hasSameChain=true;
					break;
				}
			}

			if(!hasSameChain)
			{
				return false;
			}
		}

		return true;
	}

	bool SameChain( const vector<string>& expect,const shared_ptr<Mind::iConceptChain> res )
	{
		vector<shared_ptr<iConcept> > conVec=res->GetConceptVec();
		if(expect.size()!=conVec.size())
		{
			return false;
		}

		for (unsigned int i=0;i<expect.size();++i)
		{
			if(expect[i]!=conVec[i]->GetString())
			{
				return false;
			}
		}

		return true;
	}

	void DisplayChains( const vector<shared_ptr<Mind::iConceptChain>>& chains )
	{
		for (unsigned int i=0;i<chains.size();++i)
		{
			vector<shared_ptr<iConcept>> cons=chains[i]->GetConceptVec();
			for (unsigned int j=0;j<cons.size();++j)
			{
				cout<<cons[j]->GetString()<<" ";
			}
			cout<<endl;
		}
	}

	void AddGrammarPatternToCerebrum()
	{
		iCerebrum* brain=iCerebrum::Instance();

		vector<PartOfSpeech> pos;
		pos.push_back(Numeral);
		pos.push_back(Adjective);
		pos.push_back(Preposition);
		pos.push_back(Numeral);
		GrammarPattern pattern(pos);
		for (int i=0;i<200;++i)
		{
			brain->IncreasePatternFreqency(pattern);
		}
	}

}

void InitCerebrum::SetUp()
{
	_initObjectCount=MyObject::GetObjectCount();
	iCerebrum::SetInstance(Cerebrum::Instance());
}

void InitCerebrum::TearDown()
{
	iCerebrum::KillInstance();
	Check(_initObjectCount==MyObject::GetObjectCount());
}

void AddPatternToCerebrum::SetUp()
{
	_initObjectCount=MyObject::GetObjectCount();
	iCerebrum::SetInstance(Cerebrum::Instance());
	FuncForTest::AddGrammarPatternToCerebrum();
}

void AddPatternToCerebrum::TearDown()
{
	iCerebrum::KillInstance();
	Check(_initObjectCount==MyObject::GetObjectCount());
}
