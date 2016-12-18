#pragma once

#include <vector>
#include <string>

using namespace std;

class TestSegmentation
{
	struct SentenceSample
	{
		string raw;
		string segmented;
	};

public:
	TestSegmentation();
	~TestSegmentation();

	void Run();

private:

	vector<SentenceSample> ReadSentences(const string filename);
	bool IsCorrect(const string expect, const vector<string>& result);
	//As long as one of the <result> matches <expect>, return true.
	bool IsCorrect(const string expect, const vector<vector<string>>& result);

	void OutputResult(const string expect, const vector<vector<string>>& result , ofstream& out);
};

