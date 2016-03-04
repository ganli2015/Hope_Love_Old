#pragma once
#include "InOut.h"
#include "../DataCollection/Character.h"


namespace DataCollection
{
	class Word;
	class Sentence;
}

class WordSegmentator
{
    shared_ptr<DataCollection::Sentence> _unsegmented;
	//std::vector<shared_ptr<DataCollection::Word>> _segmented;
public:
	WordSegmentator(void);
	~WordSegmentator(void);

	//void SetUnsegementedSentence(shared_ptr<DataCollection::Sentence> sen) {_unsegmented=sen;}

	bool Segment(shared_ptr<DataCollection::Sentence> sentence);

private:

	struct CharacterProperty
	{
		DataCollection::Character character;
		vector<DataCollection::Word> candidate;
		int index;
	};


	std::vector<DataCollection::Character> GetRawSentence(shared_ptr<DataCollection::Sentence> sentence) const ;
	WordSegmentator::CharacterProperty GenerateCharacterProperty(const DataCollection::Character& chara,const int myIndex,const vector<DataCollection::Character>& raw_noPunc);
};
void SegmentMannersAccordingToUandA(const vector<shared_ptr<DataCollection::Word>>& words, vector<vector<shared_ptr<DataCollection::Word>>>& segmented);
void MergeCombination_UandA(const vector<shared_ptr<DataCollection::Word>>& words, const vector<vector<int>>& seqs_UandA , const int index,vector<vector<shared_ptr<DataCollection::Word>>>& combinations);
void GetAllPossibleSequentialCombine(const vector<shared_ptr<DataCollection::Word>>& words, vector<vector<shared_ptr<DataCollection::Word>>>& combinations);