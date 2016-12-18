#pragma once
#include "PublicHeader.h"

namespace DataCollection
{
	class SegmentedSentence;
	class Word;
	enum PartOfSpeech;
}

struct Param_Grammar
{
	string raw;
	string segSentence;
	vector<DataCollection::PartOfSpeech> expectedPOS;
};

class Test_Grammar : public::testing::TestWithParam<Param_Grammar>
{
public:
	static vector<Param_Grammar> GenerateSamples();
};


