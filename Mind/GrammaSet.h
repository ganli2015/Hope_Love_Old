#pragma once
#include "InOut.h"
#include "GrammaTree.h"

#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/Word.h"

#include "../Mathmatic/Vector.h"

// namespace DataCollection
// {
// 	class GrammaPattern;
// }

namespace Mind
{
	class GrammarLocal;

	struct GrammarAttribute
	{
		DataCollection::GrammarPattern pattern;
		int frequency;
	};

	class GrammarSet
	{
	private:
		struct Sen_Gra
		{
			vector<int> gra;
		};

		struct Pattern_Distribution
		{
			vector<int> pattern;
			int count;
		};

		std::map<int,GrammaTree> _forwardtree;
		std::map<int,GrammaTree> _backwardtree;

		std::vector<GrammarAttribute> _patterns;
		map<DataCollection::PartOfSpeech,shared_ptr<GrammarLocal>> _grammarLocalTable;

	public:
		GrammarSet(void);
		~GrammarSet(void);

		//�ҳ�������<pattern>�����е�GrammarPattern
		std::vector<DataCollection::GrammarPattern> ContainSubsequence(const DataCollection::GrammarPattern& pattern) const;
		//�ҳ����а���<pattern>��GrammarPattern
		std::vector<DataCollection::GrammarPattern> ContainedSubsequence(const DataCollection::GrammarPattern& pattern) const;
		//Return the count of patterns in GrammarSet that is the sub pattern of <pattern>
		int CountOfSubsequence(const DataCollection::GrammarPattern& pattern) const;
		int GetFreqencyofPattern(const DataCollection::GrammarPattern& pattern) const;
		//��ı�pattern��ID
		void AddGrammarPattern(DataCollection::GrammarPattern& pattern);
		void IncreasePatternFreqency(const DataCollection::GrammarPattern& pattern);
		vector<DataCollection::GrammarPattern> GrammarPatternSortByFrequency() const ;

		//���me�ĺ�һ��������forward�ĸ���.
		double GetP_Forward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& forward) const;
		//���me��ǰһ��������backward�ĸ���.
		double GetP_Backward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& backward) const;

	private:
		void Initialize();
		std::vector<GrammarAttribute> InputGrammaPatterns(std::string filename);
		void AddPatternToTree(const DataCollection::GrammarPattern& pattern);

		void ExtractGrammarPatternFromInitialFile() const;
		vector<GrammarSet::Sen_Gra> InputGraSamples(string file) const; 
		std::vector<std::vector<int>> FindAllCommonSequences( const vector<Sen_Gra>& samples) const;
		vector<GrammarSet::Pattern_Distribution> ComputePatternDistribution(const std::vector<std::vector<int>>& allcommon_seqs) const;
		void OutputPatternDistribution(const vector<Pattern_Distribution>& p_d) const;

		void ExtractGrammarLocalDistribution();

		int GetMaxID() const;
		int FindPatternIndex(const DataCollection::GrammarPattern& pattern);
	};
}


