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

ConceptPair GenerateBasePair( const string con1,const string con2 );
vector<string> GenerateChain( const string str1,const string str2,const string str3 );
vector<string> GenerateChain( const string str1,const string str2,const string str3,const string str4 );
vector<string> GenerateChain( const string str1,const string str2 );

TEST(Test_ExtractConceptChains,Extract1)
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

	ASSERT_TRUE(FuncForTest::SameChainVec(expect,chain));
}

TEST(Test_ExtractConceptChains,Extract2)
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

	ASSERT_TRUE(FuncForTest::SameChainVec(expect,chain));
}

ConceptPair GenerateBasePair( const string con1,const string con2 )
{
	shared_ptr<Word> w1(new Word(con1));
	shared_ptr<Word> w2(new Word(con2));
	shared_ptr<BaseConcept> base1(new BaseConcept(w1));
	shared_ptr<BaseConcept> base2(new BaseConcept(w2));
	return make_pair(base1,base2);
}

vector<string> GenerateChain( const string str1,const string str2,const string str3 )
{
	vector<string> res;
	res.push_back(str1);
	res.push_back(str2);
	res.push_back(str3);

	return res;
}

vector<string> GenerateChain( const string str1,const string str2,const string str3,const string str4 )
{
	vector<string> res=GenerateChain(str1,str2,str3);
	res.push_back(str4);
	return res;
}

vector<string> GenerateChain( const string str1,const string str2 )
{
	vector<string> res;
	res.push_back(str1);
	res.push_back(str2);
	return res;
}
