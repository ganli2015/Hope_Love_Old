#pragma once
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class GrammarPatternExtractor
{
	struct Pattern_Distribution
	{
		vector<int> pattern;
		int count;
	};

	struct Sen_Gra
	{
		//////////////////////////////////////////////////////////////////////////
		///Vector of Part of Speech.
		//////////////////////////////////////////////////////////////////////////
		vector<int> gra;
	};


public:
	GrammarPatternExtractor();
	~GrammarPatternExtractor();

	void Run();


private:

	vector<Sen_Gra> InputGraSamples(string file) const;

	void ExtractGrammarPatternFromInitialFile() const;

	unordered_map<string,int> FindAllCommonSequencesAndDistribution(const vector<Sen_Gra>& samples) const;
	vector<string> ConvertToStrings(const vector<vector<int>>& commonSeq) const;
	void OutputPatternDistribution(const unordered_map<string, int>& p_d) const;

	std::vector<std::vector<int>> FindAllCommonSequences(const vector<Sen_Gra>& samples) const;
	vector<Pattern_Distribution> ComputePatternDistribution(const std::vector<std::vector<int>>& allcommon_seqs) const;
	void OutputPatternDistribution(const vector<Pattern_Distribution>& p_d) const;
};

