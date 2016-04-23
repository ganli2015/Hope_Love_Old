#include "StdAfx.h"
#include "TestClass.h"

#include "Punctuator.h"
#include "WordSegmentator.h"
#include "GrammarAnalyzer.h"

#include "../DataCollection/Sentence.h"

#include "../Mind/Cerebrum.h"

using namespace Mind;
using namespace DataCollection;
TestClass::TestClass(void)
{
}


TestClass::~TestClass(void)
{
}

void TestClass::RunTest()
{
	Test_Punctuation();
	Test_Segmentation();
	Test_Grammard();
}

void TestClass::Test_Punctuation()
{
	string sample1_i="ĪĪ�Ұ��㣡";
	string sample1_o="ĪĪ�Ұ��㣡";
	Punctuator punct1(sample1_i);
	shared_ptr<Sentence> result1(new Sentence(sample1_i));
	punct1.Punctuate(result1);
	Check(result1->GetSubSentence(0)==sample1_o);

	string sample2_i="�ɸɣ�����������";
	string sample2_o1="�ɸɣ�";
	string sample2_o2="����������";
	Punctuator punct2(sample2_i);
	shared_ptr<Sentence> result2(new Sentence(sample2_i));
	punct2.Punctuate(result2);
	Check(result2->GetSubSentence(0)==sample2_o1 && result2->GetSubSentence(1)==sample2_o2);

	string sample3_i="��˵��������ȥ��ɣ���";
	string sample3_o1="��˵��";
	string sample3_o2="������ȥ��ɣ���";
	Punctuator punct3(sample3_i);
	shared_ptr<Sentence> result3(new Sentence(sample3_i));
	punct3.Punctuate(result3);
	Check(result3->GetSubSentence(0)==sample3_o1 && result3->GetSubSentence(1)==sample3_o2);
}

void TestClass::Test_Segmentation()
{
	Cerebrum* brain=Cerebrum::Instance();

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
		Check(res.size()==1 && SameSentence(expect,res.front()));
	}

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
		Check(res.size()==2 && SameSentence(expect1,res.front()));
		Check(res.size()==2 && SameSentence(expect2,res[1]));
	}

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
		Check(res.size()==4 && SameSentence(expect1,res.front()));
		Check(res.size()==4 && SameSentence(expect3,res[1]));
		Check(res.size()==4 && SameSentence(expect2,res[2]));
		Check(res.size()==4 && SameSentence(expect4,res[3]));
	}
}

bool TestClass::SameSentence( const vector<string> expect,const shared_ptr<SegmentedSentence> res )
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

void TestClass::Test_Grammard()
{
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
		expect.push_back(Puncture);
		vector<shared_ptr<Word>> graWords=sen->GetGrammard();
		Check(SameGrammar(expect,graWords));
	}
}

bool TestClass::SameGrammar( const vector<PartOfSpeech>& expect,const vector<shared_ptr<Word>>& words )
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

void TestClass::Test_WordRelationTableBuilder()
{

}
