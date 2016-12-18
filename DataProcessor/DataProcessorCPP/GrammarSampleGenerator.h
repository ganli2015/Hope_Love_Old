#pragma once
#include <string>
#include <vector>

using namespace std;

const string appDataDir = "..\\..\\HopeLove\\bin\\Debug\\HopeLoveData\\";
const string mindDataDir = "..\\..\\..\\..\\Mind\\HopeLoveData\\";


class GrammarSampleGenerator
{
	
public:
	GrammarSampleGenerator();
	~GrammarSampleGenerator();

	void Run();


private:

	vector<string> ReadValidSentence() const;
	bool IsValid(const string sen) const;

	void POSTaggingAndOutput(const vector<string>& sentences)  const;

	vector<vector<string>> SegmentSentences(const vector<string>& sentences) const;
	void OutputGrammarData(const std::vector<std::vector<std::string>>& sentences) const;


};

