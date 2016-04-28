#include "StdAfx.h"
#include "Test_ReactionAnalysisAlgorithm.h"

#include "../ReactionAnalysisAlgorithm/ExtractConceptChains.h"

#include "../MindElement/BaseConcept.h"
#include "../MindElement/ConceptChain.h"

#include "../MindInterface/iConceptChain.h"

#include "../DataCollection/Word.h"

#include <cstdarg>

using namespace Mind;
using namespace DataCollection;

Test_ReactionAnalysisAlgorithm::Test_ReactionAnalysisAlgorithm(void)
{
}


Test_ReactionAnalysisAlgorithm::~Test_ReactionAnalysisAlgorithm(void)
{
}

void Test_ReactionAnalysisAlgorithm::RunTest()
{
	TestExtractConceptChains();
}

void Test_ReactionAnalysisAlgorithm::TestExtractConceptChains()
{
	{
		vector<ConceptPair> pairs;
		pairs.push_back(GenerateBasePair("ĪĪ","�ø�"));
		pairs.push_back(GenerateBasePair("�ø�","�Է�"));
		pairs.push_back(GenerateBasePair("�̶�","�ø�"));
		pairs.push_back(GenerateBasePair("��","�ø�"));
		pairs.push_back(GenerateBasePair("��","�̶�"));
		pairs.push_back(GenerateBasePair("�Լ�","�ø�"));

		vector<shared_ptr<iConceptChain>> chain=ExtractConceptChains::Extract(pairs);

		vector<vector<string>> expect;
		expect.push_back(GenerateChain("ĪĪ", "�ø�", "�Է�"));
		expect.push_back(GenerateChain("ĪĪ", "�ø�", "�Է�"));
		expect.push_back(GenerateChain("��", "�̶�", "�ø�", "�Է�"));
		expect.push_back(GenerateChain("��", "�̶�", "�ø�", "�Է�"));
		expect.push_back(GenerateChain("��", "�̶�", "�ø�", "�Է�"));
		expect.push_back(GenerateChain("��", "�ø�", "�Է�"));
		expect.push_back(GenerateChain("��", "�ø�", "�Է�"));
		expect.push_back(GenerateChain("�Լ�", "�ø�", "�Է�"));
		expect.push_back(GenerateChain("�Լ�", "�ø�", "�Է�"));

		Check(SameChainVec(expect,chain));
	}

	{
		vector<ConceptPair> pairs;
		pairs.push_back(GenerateBasePair("����","�ں�"));
		pairs.push_back(GenerateBasePair("�ں�","��"));
		pairs.push_back(GenerateBasePair("��ô","��"));
		pairs.push_back(GenerateBasePair("����","��"));
		pairs.push_back(GenerateBasePair("�ں�","����"));

		vector<shared_ptr<iConceptChain>> chain=ExtractConceptChains::Extract(pairs);

		CommonFunction::RemoveSameChain(chain);

		vector<vector<string>> expect;
		expect.push_back(GenerateChain("����","�ں�","����","��"));
		expect.push_back(GenerateChain("����","�ں�","��"));
		expect.push_back(GenerateChain("��ô","��"));

		Check(SameChainVec(expect,chain));
	}
}

ConceptPair Test_ReactionAnalysisAlgorithm::GenerateBasePair( const string con1,const string con2 )
{
	shared_ptr<Word> w1(new Word(con1));
	shared_ptr<Word> w2(new Word(con2));
	shared_ptr<BaseConcept> base1(new BaseConcept(w1));
	shared_ptr<BaseConcept> base2(new BaseConcept(w2));
	return make_pair(base1,base2);
}

vector<string> Test_ReactionAnalysisAlgorithm::GenerateChain( const string str1,const string str2,const string str3 )
{
	vector<string> res;
	res.push_back(str1);
	res.push_back(str2);
	res.push_back(str3);

	return res;
}

vector<string> Test_ReactionAnalysisAlgorithm::GenerateChain( const string str1,const string str2,const string str3,const string str4 )
{
	vector<string> res=GenerateChain(str1,str2,str3);
	res.push_back(str4);
	return res;
}

vector<string> Test_ReactionAnalysisAlgorithm::GenerateChain( const string str1,const string str2 )
{
	vector<string> res;
	res.push_back(str1);
	res.push_back(str2);
	return res;
}

bool Test_ReactionAnalysisAlgorithm::SameChainVec( const vector<vector<string>>& expect, const vector<shared_ptr<iConceptChain>>& result )
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

bool Test_ReactionAnalysisAlgorithm::SameChain( const vector<string>& expect,const shared_ptr<Mind::iConceptChain> res )
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

void Test_ReactionAnalysisAlgorithm::DisplayChains( const vector<shared_ptr<Mind::iConceptChain>>& chains )
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
