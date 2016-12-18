#pragma once

#include <vector>
#include <string>

#include <HopeLoveAPI.h>

using namespace std;

class TestPOSTagging
{
	struct POSSample
	{
		string raw;
		vector<pair<string, HopeLove::PartOfSpeech>> POSTag;
		string POSUnsplit;
	};

public:
	TestPOSTagging();
	~TestPOSTagging();

	void Run(const string corpusFilename);

private:

	vector<POSSample> ReadSentences(const string filename);

	vector<pair<string, HopeLove::PartOfSpeech>> ParsePOSTagging(const string line);

	bool IsCorrect(const vector<pair<string, HopeLove::PartOfSpeech>>& expect, const vector<pair<string, HopeLove::PartOfSpeech>>& result);

	void OutputResult(const string POSUnsplit, const vector<pair<string, HopeLove::PartOfSpeech>>& result, ofstream& out);
};

