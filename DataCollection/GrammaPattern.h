#pragma once
#include "InOut.h"
#include "Word.h"
#include <utility>

namespace DataCollection
{

	///GrammarPattern is a pattern that describes the grammar of sentence.
	class _DATACOLLECTIONINOUT GrammarPattern : public Obj<GrammarPattern>
	{
		///Integers in <_pattern> correspond to indexes of POS.
		///<_pattern> is a sequence of POS.
		std::vector<int> _pattern;
		int _id;

	public:
		GrammarPattern(void);
		~GrammarPattern(void);
		GrammarPattern(const std::vector<PartOfSpeech>& val);

		///Set ID of <me>.
		///Only the GrammarPattern that is recorded in GrammarSet has a valid ID, otherwise the ID is -1.
		void SetID(const int id){_id=id;}
		int GetID() const {return _id;};
		///The number of POS contained in <me>.
		unsigned int Size() const {return _pattern.size();}
		std::vector<PartOfSpeech> GetPattern() const;
		///Get the ith POS of <me>.
		PartOfSpeech Get_ithElem(const unsigned int i) const {assert(i>=0 && i<_pattern.size()); return (PartOfSpeech)_pattern[i];}

		//Divide the pattern into two patterns from the location after <index>th element.
		//The first in pair is the former pattern after divide and the second is the latter.
		///Note! The former pattern is reversed.
		//<index> counts from -1.
		std::pair<GrammarPattern,GrammarPattern> Divide(const int index) const;
		////Check whether <me> is a sub sequence of <pattern>.
		///<me> is not necessarily continuous.
		bool IsSubsequenceOf(const GrammarPattern& pattern) const ;
		////Check whether <pattern> is a sub sequence of <me>.
		///<pattern> is not necessarily continuous.
		bool ContainSubsequence(const GrammarPattern& pattern) const;

		///Check whether <pattern> and <me> are the same.
		bool IsSameWith(const GrammarPattern& pattern) const;
	private:
		GrammarPattern(const std::vector<int>& val);

	};

	_DATACOLLECTIONINOUT bool operator==(const GrammarPattern& left,const GrammarPattern& right);
}


