#pragma once
#include "InOut.h"
#include "GrammaTree.h"

#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/Word.h"

#include "../Mathmatic/Vector.h"
#include "../Mathmatic/MyInt.h"

#include "../MindInterface/PublicTypedef.h"

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

	class _MINDINOUT GrammarSet : public Obj<GrammarSet>
	{
	private:
		struct Sen_Gra
		{
			//////////////////////////////////////////////////////////////////////////
			///Vector of Part of Speech.
			//////////////////////////////////////////////////////////////////////////
			vector<int> gra;
		};



		std::map<int,GrammaTree> _forwardtree;
		std::map<int,GrammaTree> _backwardtree;

		std::vector<GrammarAttribute> _patterns;
		map<DataCollection::PartOfSpeech,shared_ptr<GrammarLocal>> _grammarLocalTable;

		//////////////////////////////////////////////////////////////////////////
		///The weight of grammar pattern used for computation of <ComputePossibility>.
		//////////////////////////////////////////////////////////////////////////
		double _wPattern;
		//////////////////////////////////////////////////////////////////////////
		///The weight of local grammar used for computation of <ComputePossibility>.
		//////////////////////////////////////////////////////////////////////////
		double _wLocal;

	public:
		GrammarSet(void);
		~GrammarSet(void);

		//////////////////////////////////////////////////////////////////////////
		///Search all grammar patterns which are sub patterns of <pattern>.
		//////////////////////////////////////////////////////////////////////////
		std::vector<DataCollection::GrammarPattern> ContainSubsequence(const DataCollection::GrammarPattern& pattern) const;
		//////////////////////////////////////////////////////////////////////////
		///Search all grammar patterns of which <pattern> is a sub grammar pattern.
		//////////////////////////////////////////////////////////////////////////
		std::vector<DataCollection::GrammarPattern> ContainedSubsequence(const DataCollection::GrammarPattern& pattern) const;

		//////////////////////////////////////////////////////////////////////////
		///Return the count of patterns in GrammarSet that is the sub pattern of <pattern>.
		//////////////////////////////////////////////////////////////////////////
		int CountOfSubsequence(const DataCollection::GrammarPattern& pattern) const;
		int GetFreqencyofPattern(const DataCollection::GrammarPattern& pattern) const;


		void AddGrammarPattern(DataCollection::GrammarPattern& pattern);

		//////////////////////////////////////////////////////////////////////////
		///Increase the frequency of <pattern> by one.
		//////////////////////////////////////////////////////////////////////////
		void IncreasePatternFreqency(const DataCollection::GrammarPattern& pattern);
		vector<DataCollection::GrammarPattern> GrammarPatternSortByFrequency() const ;

		//////////////////////////////////////////////////////////////////////////
		///Get the ratio between the frequency of <pos> and total frequency among all POSes in front of.
		//////////////////////////////////////////////////////////////////////////
		double GetP_Forward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& forward) const;
		//////////////////////////////////////////////////////////////////////////
		///Get the ratio between the frequency of <pos> and total frequency among all POSes behind.
		//////////////////////////////////////////////////////////////////////////
		double GetP_Backward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& backward) const;

		//////////////////////////////////////////////////////////////////////////
		///Compute the possibility of <pattern> in grammar sense.
		//////////////////////////////////////////////////////////////////////////
		double ComputePossibility(const DataCollection::GrammarPattern& pattern) const;
	private:
		void Initialize();
		std::vector<GrammarAttribute> InputGrammaPatterns(std::string filename);
		void AddPatternToTree(const DataCollection::GrammarPattern& pattern);

		//////////////////////////////////////////////////////////////////////////
		///Initialize <_wPattern> and <_wLocal>.
		//////////////////////////////////////////////////////////////////////////
		void InitializeWeights();

		void WriteWeights(const double wPattern, const double wLocal);
		//////////////////////////////////////////////////////////////////////////
		///Read weights from file.
		//////////////////////////////////////////////////////////////////////////
		void ReadWeights();

		void ReadGrammarLocal();

		vector<GrammarSet::Sen_Gra> InputGraSamples(string file) const;

		void ExtractGrammarLocalDistribution();

		int GetMaxID() const;
		int FindPatternIndex(const DataCollection::GrammarPattern& pattern);

		//////////////////////////////////////////////////////////////////////////
		///Get the sum of frequencies of all grammar patterns.
		//////////////////////////////////////////////////////////////////////////
		Math::MyInt GetTotalFrequency() const;

		//////////////////////////////////////////////////////////////////////////
		///Compute confidence of <pattern> considering confidence of each POS with local grammar analysis.
		//////////////////////////////////////////////////////////////////////////
		double ComputeP_GrammarLocal(const DataCollection::PartOfSpeech& curPos, const DataCollection::PartOfSpeech& forwardPos, const DataCollection::PartOfSpeech& backwardPos) const;
		
		//////////////////////////////////////////////////////////////////////////
		///Compute confidence of <curPOS> when its previous POS is <forwardPos> and its next POS is <backwardPos>.
		///The returned value is 0 to 1.
		//////////////////////////////////////////////////////////////////////////
		double ComputeP_GrammarLocalAnalysis(const DataCollection::GrammarPattern& pattern) const;

		//////////////////////////////////////////////////////////////////////////
		///Compute the weights of possibilities of grammar patterns and possibilities of local grammar.
		///Such weights make each possibility of grammar structure close to one as possible.
		//////////////////////////////////////////////////////////////////////////
		void ComputeWeights(const vector<double>& patternP, const vector<double>& localP,
			double& wPattern, double& wLocal) const;

		//////////////////////////////////////////////////////////////////////////
		///Compute the deviation of grammar possibility.
		///<patternP> are possibilities of grammar patterns.
		///<localP> are possibilities of local grammar structure.
		///<wPattern> is the weight of <patternP>, <wLocal> is the weight of <localP>.
		//////////////////////////////////////////////////////////////////////////
		double ComputeDeviation(const vector<double>& patternP, const vector<double>& localP,
			const double wPattern, const double wLocal) const;

		//////////////////////////////////////////////////////////////////////////
		///Compute possibility of component of grammar pattern.
		//////////////////////////////////////////////////////////////////////////
		double ComputePossibilityGrammarPattern(const DataCollection::GrammarPattern& pattern,const Math::MyInt totalFreq) const;
	};
}


