#pragma once
#include "InOut.h"
#include "GrammaPattern.h"
#include <map>


namespace DataCollection
{
	class Word;

	class _DATACOLLECTIONINOUT GrammardSentence
	{
	public:
		struct GraAssoInfo
		{
			vector<int> indexes;//表示该GrammarPattern所对应的可能的序列，用每个word的序号来表示
			GrammarPattern pattern;
		};

	private:
		std::vector<shared_ptr<DataCollection::Word>> _gra;
		multimap<int,GraAssoInfo> _graInfoSet; //int表示word在_gra里的序号，GraAssoInfo储存了包含该word的GrammarPattern，以及该GrammarPattern所对应的可能序列。
	public:
		GrammardSentence();
		~GrammardSentence();
		GrammardSentence(const std::vector<shared_ptr<DataCollection::Word>> vec);

		std::vector<shared_ptr<Word>> Get() const ; 
		int WordCount() const {return _gra.size();}

		bool BuildGrammarAssociation(const vector<GrammarPattern>& grammarPatterns);

		//获得序号i的word的语法匹配信息，associatedIndexes是语法模式匹配的序号集合，associatedPatterns是相应的模式，两者vector一一对应。
		void GetAssociationInfo(const unsigned int i,vector<vector<int>>& associatedIndexes,vector<GrammarPattern>& associatedPatterns);
	private:
		bool GetIndexOfMatchedPattern(const GrammarPattern& patternRaw,const GrammarPattern& patternMatch,vector<vector<int>>& indexes);
		void GetIndexOfMatchedPattern(const GrammarPattern& patternRaw,const GrammarPattern& patternMatch,const unsigned int rawStartIndex,const unsigned int matchStartIndex,vector<vector<int>>& indexes);
		void ClassifyGrammarInfoSet(multimap<int,GraAssoInfo>& graInfoSet,const vector<vector<int>>& indexes,const GrammarPattern& pattern);
	};
}

