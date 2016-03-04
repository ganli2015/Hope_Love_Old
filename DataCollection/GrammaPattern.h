#pragma once
#include "InOut.h"
#include "Word.h"
#include <utility>

namespace DataCollection
{
	class _DATACOLLECTIONINOUT GrammarPattern
	{
		std::vector<int> _pattern;
		int _id;

	public:
		GrammarPattern(void);
		~GrammarPattern(void);
		GrammarPattern(const std::vector<PartOfSpeech>& val);

		void SetID(const int id){_id=id;}
		int GetID() const {return _id;};
// 		void SetUsage(const int val) {_usage=val;}
// 		int GetUsage () const {return _usage;}
		unsigned int Size() const {return _pattern.size();}
		std::vector<PartOfSpeech> GetPattern() const;
		PartOfSpeech Get_ithElem(const unsigned int i) const {assert(i>=0 && i<_pattern.size()); return (PartOfSpeech)_pattern[i];}

		//Divide the pattern into two patterns from the location after <index>th element.
		//<index> counts from -1.
		std::pair<GrammarPattern,GrammarPattern> Divide(const int index) const;
		////是否<pattern>包含<me>
		bool IsSubsequenceOf(const GrammarPattern& pattern) const ;
		//是否<me>包含<pattern>
		bool ContainSubsequence(const GrammarPattern& pattern) const;
		int CountSubsequence(const GrammarPattern& pattern) const ;

		bool IsSameWith(const GrammarPattern& pattern) const;
	private:
		GrammarPattern(const std::vector<int>& val);

	};

	_DATACOLLECTIONINOUT bool operator==(const GrammarPattern& left,const GrammarPattern& right);
}


