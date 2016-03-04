#pragma once
#include "InOut.h"
#include "GrammaTree.h"

#include "../DataCollection/GrammaPattern.h"

// namespace DataCollection
// {
// 	class GrammaPattern;
// }

namespace Mind
{
	struct GrammarAttribute
	{
		DataCollection::GrammarPattern pattern;
		int frequency;
	};

	class GrammaSet
	{
		std::map<int,GrammaTree> _forwardtree;
		std::map<int,GrammaTree> _backwardtree;

		std::vector<GrammarAttribute> _patterns;

	public:
		GrammaSet(void);
		~GrammaSet(void);

		//找出所有是<pattern>子序列的GrammarPattern
		std::vector<DataCollection::GrammarPattern> ContainSubsequence(const DataCollection::GrammarPattern& pattern) const;
		//找出所有包含<pattern>的GrammarPattern
		std::vector<DataCollection::GrammarPattern> ContainedSubsequence(const DataCollection::GrammarPattern& pattern) const;
		int CountOfSubsequence(const DataCollection::GrammarPattern& pattern) const;
		int GetFreqencyofPattern(const DataCollection::GrammarPattern& pattern) const;
		//会改变pattern的ID
		void AddGrammarPattern(DataCollection::GrammarPattern& pattern);
		void IncreasePatternFreqency(const DataCollection::GrammarPattern& pattern);
		vector<DataCollection::GrammarPattern> GrammarPatternSortByFrequency() const ;

	private:
		void Initialize();
		std::vector<GrammarAttribute> InputGrammaPatterns(std::string filename);
		void AddPatternToTree(const DataCollection::GrammarPattern& pattern);

		int GetMaxID() const;
		int FindPatternIndex(const DataCollection::GrammarPattern& pattern);
	};
}


