#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Sentence;
	class Word;
	class GrammarPattern;
}

class StructureAnalyzer
{
	shared_ptr<DataCollection::Sentence> _raw_sen;//unanalyzed

public:
	///The input sentence should have built grammara association.
	StructureAnalyzer( shared_ptr<DataCollection::Sentence> sen);
	~StructureAnalyzer(void);

	///Build intensity relation between associated words and store intensity values in the input sentence.
	bool Analyze();

	shared_ptr<DataCollection::Sentence> GetResult(){return _raw_sen;}
private:
	///计算包含第word1_index个word和第word2_index个word的GrammarPattern的频率的总和。word1_assoIndexes是与word1相关联的语法模式对应的word序号，word1_assoPatterns是每一组序号对应的语法模式。
	int TotalPatternFrequency(const int word1_index,const int word2_index,const vector<vector<int>>& word1_assoIndexes,const vector<DataCollection::GrammarPattern>& word1_assoPatterns);
	///Compute pattern frequency only if <word1_index> and <word2_index> are adjacent index in <word1_assoIndexes>.
	int TotalPatternFrequency2(const int word1_index,const int word2_index,const vector<vector<int>>& word1_assoIndexes,const vector<DataCollection::GrammarPattern>& word1_assoPatterns);
	vector<vector<double>> NormalizeFreqMatrix(const vector<vector<int>>& freqMatrix);
	///Input <intensityMatrix> to the input sentence.
	void SetEachWordIntenstiy(const vector<vector<double>>& intensityMatrix);
	bool IsAdjacentInVec(const int word1_index,const int word2_index,const vector<int>& vec);
};

