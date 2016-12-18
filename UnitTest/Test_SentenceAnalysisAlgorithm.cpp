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

#include "../CommonTools/CommonStringFunction.h"

#include "../MindInterface/iCerebrum.h"
#include "../Mind/Cerebrum.h"

using namespace Mind;
using namespace DataCollection;

typedef InitCerebrum Test_Segmentation;
typedef InitCerebrum Test_StructureAnalyzer;
typedef InitCerebrum Test_WordRelationTableBuilder;

bool SameSentence( const vector<string> expect,const shared_ptr<SegmentedSentence> res );
bool SameGrammar( const vector<PartOfSpeech>& expect,const vector<shared_ptr<Word>>& words );


// TEST(HopeLoveAPI, Test)
// {
// 
// 	HopeLove::InitializeBrain("E:\\Artificial Intelligence\\Project\\Hope_Love\\DataProcessor\\Data\\");
// 
// 	auto tt = HopeLove::GetPartOfSpeech("，");
// 
// 	string input = "你喜欢男的";
// 	vector<string> result = HopeLove::WordSegment(input.c_str());
// 
// }

TEST(Test_Punctuation,Punctuate1)
{
	string sample1_i="莫莫我爱你！";
	string sample1_o="莫莫我爱你！";
	Punctuator punct1(sample1_i);
	shared_ptr<Sentence> result1(new Sentence(sample1_i));
	punct1.Punctuate(result1);
	ASSERT_EQ(result1->GetSubSentence(0),sample1_o);
}

TEST(Test_Punctuation,Punctuate2)
{
	string sample2_i="干干，来接我了吗";
	string sample2_o1="干干，";
	string sample2_o2="来接我了吗";
	Punctuator punct2(sample2_i);
	shared_ptr<Sentence> result2(new Sentence(sample2_i));
	punct2.Punctuate(result2);
	ASSERT_EQ(result2->GetSubSentence(0),sample2_o1);
	ASSERT_EQ(result2->GetSubSentence(1),sample2_o2);
}

TEST(Test_Punctuation,Punctuate3)
{
	string sample3_i="她说：“我们去玩吧！”";
	string sample3_o1="她说：";
	string sample3_o2="“我们去玩吧！”";
	Punctuator punct3(sample3_i);
	shared_ptr<Sentence> result3(new Sentence(sample3_i));
	punct3.Punctuate(result3);
	ASSERT_EQ(result3->GetSubSentence(0),sample3_o1);
	ASSERT_EQ(result3->GetSubSentence(1),sample3_o2);
}

TEST_F(Test_Segmentation,ForwardSegment1)
{
	string sample_i="莫莫我爱你！";
	vector<string> expect;
	expect.push_back("莫莫");
	expect.push_back("我");
	expect.push_back("爱");
	expect.push_back("你");
	expect.push_back("！");
	shared_ptr<Sentence> sen(new Sentence(sample_i));
	sen->AddSubSentence(sample_i);
	WordSegmentator wordSegmentator(sen);
	wordSegmentator.Segment();
	vector<shared_ptr<SegmentedSentence>> res=wordSegmentator.GetAllSegementedSentence();
	ASSERT_TRUE(res.size()==1 && SameSentence(expect,res.front()));
}

TEST_F(Test_Segmentation, ForwardSegment2)
{
	string sample_i="今天去哪里？";
	vector<string> expect1;
	expect1.push_back("今天");
	expect1.push_back("去");
	expect1.push_back("哪");
	expect1.push_back("里");
	expect1.push_back("？");
	vector<string> expect2;
	expect2.push_back("今天");
	expect2.push_back("去");
	expect2.push_back("哪里");
	expect2.push_back("？");

	shared_ptr<Sentence> sen(new Sentence(sample_i));
	sen->AddSubSentence(sample_i);
	WordSegmentator wordSegmentator(sen);
	wordSegmentator.Segment();
	vector<shared_ptr<SegmentedSentence>> res=wordSegmentator.GetAllSegementedSentence();
	ASSERT_TRUE(res.size()==2 && SameSentence(expect1,res.front()));
	ASSERT_TRUE(res.size()==2 && SameSentence(expect2,res[1]));
}

TEST_F(Test_Segmentation, ForwardSegment3)
{
	string sample_i="动物园";
	vector<string> expect1;
	expect1.push_back("动");
	expect1.push_back("物");
	expect1.push_back("园");
	vector<string> expect2;
	expect2.push_back("动物");
	expect2.push_back("园");
	vector<string> expect3;
	expect3.push_back("动");
	expect3.push_back("物园");
	vector<string> expect4;
	expect4.push_back("动物园");

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

TEST_F(Test_Segmentation, BackwardSegment1)
{
	string sample_i = "莫莫我爱你！";
	vector<string> expect;
	expect.push_back("莫莫");
	expect.push_back("我");
	expect.push_back("爱");
	expect.push_back("你");
	expect.push_back("！");
	shared_ptr<Sentence> sen(new Sentence(sample_i));
	sen->AddSubSentence(sample_i);
	WordSegmentator wordSegmentator(sen);
	wordSegmentator.SetSegmentMethod(WordSegmentator::Backward);
	wordSegmentator.Segment();
	vector<shared_ptr<SegmentedSentence>> res = wordSegmentator.GetAllSegementedSentence();
	ASSERT_TRUE(res.size() == 1 && SameSentence(expect, res.front()));
}

TEST_F(Test_Segmentation, BackwardSegment2)
{
	string sample_i = "今天去哪里？";
	vector<string> expect1;
	expect1.push_back("今天");
	expect1.push_back("去");
	expect1.push_back("哪");
	expect1.push_back("里");
	expect1.push_back("？");
	vector<string> expect2;
	expect2.push_back("今天");
	expect2.push_back("去");
	expect2.push_back("哪里");
	expect2.push_back("？");

	shared_ptr<Sentence> sen(new Sentence(sample_i));
	sen->AddSubSentence(sample_i);
	WordSegmentator wordSegmentator(sen);
	wordSegmentator.SetSegmentMethod(WordSegmentator::Backward);
	wordSegmentator.Segment();
	vector<shared_ptr<SegmentedSentence>> res = wordSegmentator.GetAllSegementedSentence();
	ASSERT_TRUE(res.size() == 2 && SameSentence(expect1, res.front()));
	ASSERT_TRUE(res.size() == 2 && SameSentence(expect2, res[1]));
}

TEST_F(Test_Segmentation, BackwardSegment3)
{
	string sample_i = "动物园";
	vector<string> expect1;
	expect1.push_back("动");
	expect1.push_back("物");
	expect1.push_back("园");
	vector<string> expect2;
	expect2.push_back("动物");
	expect2.push_back("园");
	vector<string> expect3;
	expect3.push_back("动");
	expect3.push_back("物园");
	vector<string> expect4;
	expect4.push_back("动物园");

	shared_ptr<Sentence> sen(new Sentence(sample_i));
	sen->AddSubSentence(sample_i);
	WordSegmentator wordSegmentator(sen);
	wordSegmentator.SetSegmentMethod(WordSegmentator::Backward);
	wordSegmentator.Segment();
	vector<shared_ptr<SegmentedSentence>> res = wordSegmentator.GetAllSegementedSentence();
	ASSERT_TRUE(res.size() == 4 && SameSentence(expect1, res.front()));
	ASSERT_TRUE(res.size() == 4 && SameSentence(expect3, res[1]));
	ASSERT_TRUE(res.size() == 4 && SameSentence(expect2, res[2]));
	ASSERT_TRUE(res.size() == 4 && SameSentence(expect4, res[3]));
}

TEST_F(Test_Segmentation, WithPunctuation)
{
	string sample_i = "她说“莫莫”";

	shared_ptr<Sentence> sen(new Sentence(sample_i));
	sen->AddSubSentence(sample_i);
	WordSegmentator wordSegmentator(sen);
	wordSegmentator.SetSegmentMethod(WordSegmentator::Backward);
	wordSegmentator.Segment();
	vector<shared_ptr<SegmentedSentence>> res = wordSegmentator.GetAllSegementedSentence();

	string expect = "她/说/“/莫莫/”";
 	ASSERT_TRUE(res.size() == 1);
	ASSERT_EQ(expect,res.front()->GetString());

}

TEST_F(Test_Segmentation, LongSentence)
{
	string sample_i = "射击场上，将由安徽许海峰、辽宁王义夫、河南李金豹和苏之勃等争夺男子自选手枪慢射的冠军；宁夏祁春霞、湖南文芝芳、天津常丽娟等争夺女子小口径手枪６０发的金牌；宁夏祁春霞、湖南文芝芳、天津常丽娟等争夺女子小口径手枪６０发的金牌；浙江吴小璇、北京李丹、湖南张秋萍等角逐女子气步枪。";

	shared_ptr<Sentence> sen(new Sentence(sample_i));
	sen->AddSubSentence("射击场上，");
	sen->AddSubSentence("将由安徽许海峰、辽宁王义夫、河南李金豹和苏之勃等争夺男子自选手枪慢射的冠军；");
	sen->AddSubSentence("宁夏祁春霞、湖南文芝芳、天津常丽娟等争夺女子小口径手枪６０发的金牌；");
	sen->AddSubSentence("浙江吴小璇、北京李丹、湖南张秋萍等角逐女子气步枪。");
	WordSegmentator wordSegmentator(sen);
	wordSegmentator.SetSegmentMethod(WordSegmentator::Backward);
	wordSegmentator.Segment();

	//Reach here safely.
	ASSERT_TRUE(true);
}

INSTANTIATE_TEST_CASE_P(Test_SentenceAnalysisAlgorithm, Test_Grammar, testing::ValuesIn(Test_Grammar::GenerateSamples()));

TEST_P(Test_Grammar,Analyze)
{
	Cerebrum* brain = Cerebrum::Instance();
	iCerebrum::SetInstance(brain);

	Param_Grammar param= GetParam();

	string sample_i= param.raw;
	shared_ptr<Sentence> sen(new Sentence(sample_i));
	sen->AddSubSentence(sample_i);

	vector<string> split = CommonTool::SplitString(param.segSentence, '/');
	vector<shared_ptr<Word>> segWords;
	for (unsigned int i=0;i<split.size();++i)
	{
		segWords.push_back(shared_ptr<Word>(new Word(split[i])));
	}

	GrammarAnalyzer grammarAnalyzer(sen);
	grammarAnalyzer.AddSegment(shared_ptr<SegmentedSentence>(new SegmentedSentence(segWords)));
	grammarAnalyzer.Analyze();

	vector<shared_ptr<Word>> graWords=sen->GetGrammard();
	ASSERT_TRUE(SameGrammar(param.expectedPOS, graWords));

	iCerebrum::KillInstance();
}

vector<Param_Grammar> Test_Grammar::GenerateSamples()
{
	vector<Param_Grammar> res;

	{
		Param_Grammar param;
		param.raw = "莫莫我爱你！";
		param.segSentence = "莫莫/我/爱/你/！";
		vector<PartOfSpeech> expect;
		expect.push_back(Pronoun);
		expect.push_back(Pronoun);
		expect.push_back(Verb);
		expect.push_back(Pronoun);
		expect.push_back(Punctuation);
		
		param.expectedPOS = expect;

		res.push_back(param);
	}

	{
		Param_Grammar param;
		param.raw = "今天要回家";
		param.segSentence = "今天/要/回/家";
		vector<PartOfSpeech> expect{Adverb,Verb,Verb,Noun};

		param.expectedPOS = expect;

		res.push_back(param);
	}

	{
		Param_Grammar param;
		param.raw = "三加二等于多少";
		param.segSentence = "三/加/二/等于/多少";
		vector<PartOfSpeech> expect{ Numeral,Verb,Numeral,Verb,Pronoun };

		param.expectedPOS = expect;

		res.push_back(param);
	}

	return res;
}

TEST_F(Test_WordRelationTableBuilder,Analyze)
{
	//Check that the grammar interaction only affects the adjacent words.
	FuncForTest::AddGrammarPatternToCerebrum();

	SentenceAnalyzer analyzer("二大于一");
	analyzer.Analyze();
	shared_ptr<Sentence> sen=analyzer.GetAnalyzedSentences();

	WordRelationTableBuilder builder(sen);
	builder.Build();
	shared_ptr<iConceptInteractTable> table=builder.GetProtoInteractTable();

	vector<pair<string,string>> expect;
	expect.push_back(make_pair("二","大"));
	expect.push_back(make_pair("大","于"));
	expect.push_back(make_pair("于","一"));

	ASSERT_TRUE(FuncForTest::PairSameWithTable(expect,table));
}

TEST_F(Test_StructureAnalyzer,Analyze)
{
	//Check that the grammar interaction only affects the adjacent words.
	FuncForTest::AddGrammarPatternToCerebrum();

	SentenceAnalyzer analyzer("二大于一");
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


