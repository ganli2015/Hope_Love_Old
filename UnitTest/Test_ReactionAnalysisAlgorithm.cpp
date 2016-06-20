#include "StdAfx.h"
#include "Test_ReactionAnalysisAlgorithm.h"

#include "../ReactionAnalysisAlgorithm/ExtractConceptChains.h"

#include "../MindElement/BaseConcept.h"
#include "../MindElement/ConceptChain.h"

#include "../MindInterface/iConceptChain.h"

#include "../DataCollection/Word.h"
#include "../DataCollection/Sentence.h"
#include "../DataCollection/LanguageFunc.h"

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

INSTANTIATE_TEST_CASE_P(Test_ReactionAnalysisAlgorithm, Test_SentenceTypeDetermination, testing::ValuesIn(Test_SentenceTypeDetermination::GenerateSamples()));

TEST_P(Test_SentenceTypeDetermination, Determine_Interrogative)
{
	MEMOCHECK;

	Param_SentenceTypeDetermination param = GetParam();

	SentenceTypeDetermination det;
	SentenceTypeDetermination::Type resultType=det.Determine(param.sentence);

	ASSERT_EQ(resultType, param.type);

	shared_ptr<DataCollection::Sentence> questionPart = det.GetQuestionPart();
	if(questionPart==NULL)
	{
		ASSERT_TRUE(param.questionPart == NULL);
	}
	else
	{
		ASSERT_EQ(questionPart->GetString(), param.questionPart->GetString());
	}
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

std::vector<Param_SentenceTypeDetermination> Test_SentenceTypeDetermination::GenerateSamples()
{
	///Initialize SentenceTypeDetermination.
	///If it is initialized in the test, memory will leak.
	SentenceTypeDetermination init;

	vector<Param_SentenceTypeDetermination> res;

	{
		//���Ӷ����ڶ���.
		Param_SentenceTypeDetermination param;
		shared_ptr<DataCollection::Sentence> sen = make_shared<DataCollection::Sentence>("���Ӷ����ڶ���");
		vector<shared_ptr<Word>> grammarWords;
		grammarWords.push_back(LanguageFunc::GetParticularWord("��", Numeral));
		grammarWords.push_back(LanguageFunc::GetParticularWord("��", Verb));
		grammarWords.push_back(LanguageFunc::GetParticularWord("��", Numeral));
		grammarWords.push_back(LanguageFunc::GetParticularWord("����", Verb));
		grammarWords.push_back(LanguageFunc::GetParticularWord("����", Pronoun));
		sen->SetGrammard(grammarWords);
		param.sentence = sen;

		param.type = SentenceTypeDetermination::Interrogative;

		shared_ptr<DataCollection::Sentence> qPart = make_shared<DataCollection::Sentence>("���Ӷ�");
		qPart->SetGrammard(vector<shared_ptr<Word>>(grammarWords.begin(), grammarWords.begin() + 2));
		param.questionPart = qPart;

		res.push_back(param);
	}

	return res;
}
