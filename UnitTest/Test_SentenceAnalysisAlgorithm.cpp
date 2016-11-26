#include "StdAfx.h"
#include "Test_SentenceAnalysisAlgorithm.h"
#include "FuncForTest.h"

#include "../SentenceAnalysisAlgorithm/Punctuator.h"
#include "../SentenceAnalysisAlgorithm/WordSegmentator.h"
#include "../SentenceAnalysisAlgorithm/GrammarAnalyzer.h"
#include "../SentenceAnalysisAlgorithm/SentenceAnalyzer.h"
#include "../SentenceAnalysisAlgorithm/WordRelationTableBuilder.h"

#include "../Mathmatic/MathTool.h"

#include "../DataCollection/Sentence.h"

#include "../MindInterface/iCerebrum.h"
#include "../Mind/Cerebrum.h"
#include "../../HopeLoveAPI/HopeLoveAPI/HopeLoveAPI.h"

using namespace Mind;
using namespace DataCollection;

typedef InitCerebrum Test_Segmentation;
typedef InitCerebrum Test_Grammar;
typedef InitCerebrum Test_StructureAnalyzer;
typedef InitCerebrum Test_WordRelationTableBuilder;

bool SameSentence( const vector<string> expect,const shared_ptr<SegmentedSentence> res );
bool SameGrammar( const vector<PartOfSpeech>& expect,const vector<shared_ptr<Word>>& words );


// TEST(HopeLoveAPI, Test)
// {
// 
// 	HopeLove::InitializeBrain("E:\\Artificial Intelligence\\Project\\Hope_Love\\DataProcessor\\Data\\");
// 
// 	auto tt = HopeLove::GetPartOfSpeech("��");
// 
// 	string input = "��ϲ���е�";
// 	vector<string> result = HopeLove::WordSegment(input.c_str());
// 
// }

TEST(Test_Punctuation,Punctuate1)
{
	string sample1_i="ĪĪ�Ұ��㣡";
	string sample1_o="ĪĪ�Ұ��㣡";
	Punctuator punct1(sample1_i);
	shared_ptr<Sentence> result1(new Sentence(sample1_i));
	punct1.Punctuate(result1);
	ASSERT_EQ(result1->GetSubSentence(0),sample1_o);
}

TEST(Test_Punctuation,Punctuate2)
{
	string sample2_i="�ɸɣ�����������";
	string sample2_o1="�ɸɣ�";
	string sample2_o2="����������";
	Punctuator punct2(sample2_i);
	shared_ptr<Sentence> result2(new Sentence(sample2_i));
	punct2.Punctuate(result2);
	ASSERT_EQ(result2->GetSubSentence(0),sample2_o1);
	ASSERT_EQ(result2->GetSubSentence(1),sample2_o2);
}

TEST(Test_Punctuation,Punctuate3)
{
	string sample3_i="��˵��������ȥ��ɣ���";
	string sample3_o1="��˵��";
	string sample3_o2="������ȥ��ɣ���";
	Punctuator punct3(sample3_i);
	shared_ptr<Sentence> result3(new Sentence(sample3_i));
	punct3.Punctuate(result3);
	ASSERT_EQ(result3->GetSubSentence(0),sample3_o1);
	ASSERT_EQ(result3->GetSubSentence(1),sample3_o2);
}

TEST_F(Test_Segmentation,Segment1)
{
	string sample_i="ĪĪ�Ұ��㣡";
	vector<string> expect;
	expect.push_back("ĪĪ");
	expect.push_back("��");
	expect.push_back("��");
	expect.push_back("��");
	expect.push_back("��");
	shared_ptr<Sentence> sen(new Sentence(sample_i));
	sen->AddSubSentence(sample_i);
	WordSegmentator wordSegmentator(sen);
	wordSegmentator.Segment();
	vector<shared_ptr<SegmentedSentence>> res=wordSegmentator.GetAllSegementedSentence();
	ASSERT_TRUE(res.size()==1 && SameSentence(expect,res.front()));
}

TEST_F(Test_Segmentation,Segment2)
{
	string sample_i="����ȥ���";
	vector<string> expect1;
	expect1.push_back("����");
	expect1.push_back("ȥ");
	expect1.push_back("��");
	expect1.push_back("��");
	expect1.push_back("��");
	vector<string> expect2;
	expect2.push_back("����");
	expect2.push_back("ȥ");
	expect2.push_back("����");
	expect2.push_back("��");

	shared_ptr<Sentence> sen(new Sentence(sample_i));
	sen->AddSubSentence(sample_i);
	WordSegmentator wordSegmentator(sen);
	wordSegmentator.Segment();
	vector<shared_ptr<SegmentedSentence>> res=wordSegmentator.GetAllSegementedSentence();
	ASSERT_TRUE(res.size()==2 && SameSentence(expect1,res.front()));
	ASSERT_TRUE(res.size()==2 && SameSentence(expect2,res[1]));
}

TEST_F(Test_Segmentation,Segment3)
{
	string sample_i="����԰";
	vector<string> expect1;
	expect1.push_back("��");
	expect1.push_back("��");
	expect1.push_back("԰");
	vector<string> expect2;
	expect2.push_back("����");
	expect2.push_back("԰");
	vector<string> expect3;
	expect3.push_back("��");
	expect3.push_back("��԰");
	vector<string> expect4;
	expect4.push_back("����԰");

	shared_ptr<Sentence> sen(new Sentence(sample_i));
	sen->AddSubSentence(sample_i);
	WordSegmentator wordSegmentator(sen);
	wordSegmentator.Segment();
	vector<shared_ptr<SegmentedSentence>> res=wordSegmentator.GetAllSegementedSentence();
	ASSERT_TRUE(res.size()==4 && SameSentence(expect1,res.front()));
	ASSERT_TRUE(res.size()==4 && SameSentence(expect3,res[1]));
	ASSERT_TRUE(res.size()==4 && SameSentence(expect2,res[2]));
	ASSERT_TRUE(res.size()==4 && SameSentence(expect4,res[3]));
}

TEST_F(Test_Grammar,Analyze)
{
	string sample_i="ĪĪ�Ұ��㣡";
	shared_ptr<Sentence> sen(new Sentence(sample_i));
	sen->AddSubSentence(sample_i);

	vector<shared_ptr<Word>> segWords;
	segWords.push_back(shared_ptr<Word>(new Word("ĪĪ")));
	segWords.push_back(shared_ptr<Word>(new Word("��")));
	segWords.push_back(shared_ptr<Word>(new Word("��")));
	segWords.push_back(shared_ptr<Word>(new Word("��")));
	segWords.push_back(shared_ptr<Word>(new puncture("��")));

	GrammarAnalyzer grammarAnalyzer(sen);
	grammarAnalyzer.AddSegment(shared_ptr<SegmentedSentence>(new SegmentedSentence(segWords)));
	grammarAnalyzer.Analyze();

	vector<PartOfSpeech> expect;
	expect.push_back(Pronoun);
	expect.push_back(Pronoun);
	expect.push_back(Verb);
	expect.push_back(Pronoun);
	expect.push_back(Punctuation);
	vector<shared_ptr<Word>> graWords=sen->GetGrammard();
	ASSERT_TRUE(SameGrammar(expect,graWords));
}

TEST_F(Test_WordRelationTableBuilder,Analyze)
{
	//Check that the grammar interaction only affects the adjacent words.
	FuncForTest::AddGrammarPatternToCerebrum();

	SentenceAnalyzer analyzer("������һ");
	analyzer.Analyze();
	shared_ptr<Sentence> sen=analyzer.GetAnalyzedSentences();

	WordRelationTableBuilder builder(sen);
	builder.Build();
	shared_ptr<iConceptInteractTable> table=builder.GetProtoInteractTable();

	vector<pair<string,string>> expect;
	expect.push_back(make_pair("��","��"));
	expect.push_back(make_pair("��","��"));
	expect.push_back(make_pair("��","һ"));

	ASSERT_TRUE(FuncForTest::PairSameWithTable(expect,table));
}

TEST_F(Test_StructureAnalyzer,Analyze)
{
	//Check that the grammar interaction only affects the adjacent words.
	FuncForTest::AddGrammarPatternToCerebrum();

	SentenceAnalyzer analyzer("������һ");
	analyzer.Analyze();
	shared_ptr<Sentence> sen=analyzer.GetAnalyzedSentences();
	for (unsigned int i=0;i<sen->GrammarWordCount();++i)
	{
		for (unsigned int j=0;j<sen->GrammarWordCount();++j)
		{
			double inten=sen->GetWordIntensity(i,j);
			if(j-i==1 || i-j==1)
			{
				ASSERT_NE(inten,0);
			}
			else
			{
				ASSERT_EQ(Math::DoubleCompare(inten,0),0);
			}
		}
	}
}

bool SameSentence( const vector<string> expect,const shared_ptr<SegmentedSentence> res )
{
	vector<shared_ptr<Word>> words=res->Get();

	if(words.size()!=expect.size())
	{
		return false;
	}

	for (unsigned int i=0;i<words.size();++i)
	{
		if(words[i]->GetString()!=expect[i])
		{
			return false;
		}
	}

	return true;
}

bool SameGrammar( const vector<PartOfSpeech>& expect,const vector<shared_ptr<Word>>& words )
{
	if(expect.size()!=words.size())
	{
		return false;
	}

	for (unsigned int i=0;i<expect.size();++i)
	{
		if(expect[i]!=words[i]->Type())
		{
			return false;
		}
	}

	return true;
}

