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
	///���������word1_index��word�͵�word2_index��word��GrammarPattern��Ƶ�ʵ��ܺ͡�word1_assoIndexes����word1��������﷨ģʽ��Ӧ��word��ţ�word1_assoPatterns��ÿһ����Ŷ�Ӧ���﷨ģʽ��
	int TotalPatternFrequency(const int word1_index,const int word2_index,const vector<vector<int>>& word1_assoIndexes,const vector<DataCollection::GrammarPattern>& word1_assoPatterns);
	///Compute pattern frequency only if <word1_index> and <word2_index> are adjacent index in <word1_assoIndexes>.
	int TotalPatternFrequency2(const int word1_index,const int word2_index,const vector<vector<int>>& word1_assoIndexes,const vector<DataCollection::GrammarPattern>& word1_assoPatterns);
	vector<vector<double>> NormalizeFreqMatrix(const vector<vector<int>>& freqMatrix);
	///Input <intensityMatrix> to the input sentence.
	void SetEachWordIntenstiy(const vector<vector<double>>& intensityMatrix);
	bool IsAdjacentInVec(const int word1_index,const int word2_index,const vector<int>& vec);
};

