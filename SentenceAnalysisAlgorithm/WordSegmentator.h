#pragma once
#include "InOut.h"
#include "../DataCollection/Character.h"
#include "map"

namespace DataCollection
{
	class Word;
	class Sentence;
	class SegmentedSentence;
}

class WordSegmentator
{
    shared_ptr<DataCollection::Sentence> _unsegmented;

	//分词后的句子，key储存子句子，value是该子句子对应的多个分词句子.
	multimap<string,shared_ptr<DataCollection::SegmentedSentence>> _segmented;
public:
	//sentence的标点符号必须是已经是puncture类
	WordSegmentator(shared_ptr<DataCollection::Sentence> sentence);
	~WordSegmentator(void);


	bool Segment();

	vector<shared_ptr<DataCollection::SegmentedSentence>> GetAllSegementedSentence() const;

private:

	struct CharacterProperty
	{
		DataCollection::Character character;
		vector<DataCollection::Word> candidate;
		int index;
	};

	void SegmentSubsentence(const string subsentence);

	std::vector<DataCollection::Character> GetRawSentence(shared_ptr<DataCollection::Sentence> sentence) const ;
	std::vector<DataCollection::Character> ConvertStringToCharacter(const string str) const ;
	WordSegmentator::CharacterProperty GenerateCharacterProperty(const DataCollection::Character& chara,const int myIndex,const vector<DataCollection::Character>& raw_noPunc);
};
void SegmentMannersAccordingToUandA(const vector<shared_ptr<DataCollection::Word>>& words, vector<vector<shared_ptr<DataCollection::Word>>>& segmented);
void MergeCombination_UandA(const vector<shared_ptr<DataCollection::Word>>& words, const vector<vector<int>>& seqs_UandA , const int index,vector<vector<shared_ptr<DataCollection::Word>>>& combinations);
void GetAllPossibleSequentialCombine(const vector<shared_ptr<DataCollection::Word>>& words, vector<vector<shared_ptr<DataCollection::Word>>>& combinations);