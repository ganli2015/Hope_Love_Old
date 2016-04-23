#pragma once
#include "InOut.h"

namespace DataCollection
{
	class SegmentedSentence;
	class Word;
	enum PartOfSpeech;
}

class TestClass
{
public:
	TestClass(void);
	~TestClass(void);

	static void RunTest();

private:
	static void Test_Punctuation();
	static void Test_Segmentation();
	static void Test_Grammard();
	static void Test_WordRelationTableBuilder();

	static bool SameSentence(const vector<string> expect,const shared_ptr<DataCollection::SegmentedSentence> res);
	static bool SameGrammar(const vector<DataCollection::PartOfSpeech>& expect,const vector<shared_ptr<DataCollection::Word>>& words);
};

