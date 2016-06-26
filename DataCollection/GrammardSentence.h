#pragma once
#include "InOut.h"
#include "GrammaPattern.h"
#include <map>


namespace DataCollection
{
	class Word;

	///GrammardSentence contains information of POS of words and their association of them.
	///Words in GrammardSentence have definite POS instead of unknown or ambiguous.
	class _DATACOLLECTIONINOUT GrammardSentence : public Obj<GrammardSentence>
	{
	public:
		///GraAssoInfo contains information about grammar pattern and its relation with GrammardSentence.
		///<indexes> is indexes of words in <me> which form a grammar pattern <pattern>.
		struct GraAssoInfo
		{
			vector<int> indexes;
			GrammarPattern pattern;
		};

	private:
		std::vector<shared_ptr<DataCollection::Word>> _gra;
		///Key is the index of one word in GrammardSentence.
		///Value is grammar association information of the word..
		multimap<int,GraAssoInfo> _graInfoSet;
	public:
		GrammardSentence();
		~GrammardSentence();
		GrammardSentence(const std::vector<shared_ptr<DataCollection::Word>> vec);

		///Get all words of <me>.
		std::vector<shared_ptr<Word>> Get() const ; 
		///Get the size of sentence of <me>.
		int WordCount() const {return _gra.size();}

		///Build grammar association of <me>.
		///<grammarPatterns> are grammar patterns for reference.
		///When <me> contains grammar patterns incorporated in <grammarPatterns>,
		///association related to these grammar patterns will be built.
		bool BuildGrammarAssociation(const vector<GrammarPattern>& grammarPatterns);

		///Get grammar association of the word of the index <i>.
		///Each of <associatedIndexes> is indexes of words with corresponding grammar pattern in <associatedPatterns>.
		///<associatedIndexes> and <associatedPatterns> are one-to-one.
		void GetAssociationInfo(const unsigned int i,vector<vector<int>>& associatedIndexes,vector<GrammarPattern>& associatedPatterns);
	private:
		bool GetIndexOfMatchedPattern(const GrammarPattern& patternRaw,const GrammarPattern& patternMatch,vector<vector<int>>& indexes);
		void GetIndexOfMatchedPattern(const GrammarPattern& patternRaw,const GrammarPattern& patternMatch,const unsigned int rawStartIndex,const unsigned int matchStartIndex,vector<vector<int>>& indexes);
		void ClassifyGrammarInfoSet(multimap<int,GraAssoInfo>& graInfoSet,const vector<vector<int>>& indexes,const GrammarPattern& pattern);
	};
}

