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

public:
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

	void Run(const string file);

	static vector<Sen_Gra> InputGraSamples(const string file) ;

private:


	void ExtractGrammarPatternFromInitialFile(const string file) const;

	unordered_map<string,int> FindAllCommonSequencesAndDistribution(const vector<Sen_Gra>& samples) const;
	vector<string> ConvertToStrings(const vector<vector<int>>& commonSeq) const;
	void OutputPatternDistribution(const unordered_map<string, int>& p_d) const;
};

