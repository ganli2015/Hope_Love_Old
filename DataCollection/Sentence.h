#pragma once
#include "InOut.h"
#include "GrammardSentence.h"
#include "StructuredSentence.h"

namespace DataCollection
{
	class Character;
	class Word;
	class GrammarPattern;
	
	//子句子，只包含一个间断标点符号（逗号、句号）
	class SubSentence
	{
		std::vector<shared_ptr<Character>> _raw;
	public:
		SubSentence();
		~SubSentence();
		SubSentence(std::vector<shared_ptr<Character>> vec);
		SubSentence(std::string val);

		std::vector<shared_ptr<Character>> GetRawSentence() const;
		std::string GetString() const;

	};

	class _DATACOLLECTIONINOUT SegmentedSentence
	{
		std::vector<shared_ptr<DataCollection::Word>> _seg;
	public:
		SegmentedSentence();
		~SegmentedSentence();
		SegmentedSentence(const std::vector<shared_ptr<DataCollection::Word>> vec);

		std::vector<shared_ptr<Word>> Get() const ; 

	};


	//表示一个完整的句子，可以包括标点符号
	class _DATACOLLECTIONINOUT Sentence
	{
		//储存子句子的信息，包括断句方式、语法分析结果和词语之间的作用强度.
		class SubSentenceInfo
		{
			std::string _str;
			shared_ptr<SubSentence> _punctured;
			
		public:
			SubSentenceInfo(const string str, const shared_ptr<SubSentence> sub):_str(str),_punctured(sub){}
			~SubSentenceInfo(){}

			shared_ptr<SubSentence> GetSentence() const {return _punctured;}
			string GetString() const {return _str;}
		};

		vector<shared_ptr<DataCollection::Character>> _raw;
		vector<SubSentenceInfo> _subInfos;
		shared_ptr<GrammardSentence> _grammard;
		shared_ptr<StructuredSentence> _structured;

// 		std::vector<RawSentence> _punctured;//被标点符号分开的子句子.
// 		std::vector<SegmentedSentence> _segmented;// several ways of segmentation.
// 		std::vector<GrammardSentence> _grammard;
// 		vector<StructuredSentence> _structured;
	public:
		Sentence(void);
		~Sentence(void);
		Sentence(std::vector<shared_ptr<Character>> val);
		Sentence(std::string val);

		string GetString() const;
		std::vector<shared_ptr<Character>> GetRawSentence() const;
		
		void AddSubSentence(const std::vector<shared_ptr<DataCollection::Character>> vec);
		void AddSubSentence(const string str);
		size_t Count_SubSentence() const;
		string GetSubSentence(const unsigned int i) const;

		void SetGrammard(const std::vector<shared_ptr<DataCollection::Word>> vec);
		std::vector<shared_ptr<Word>> GetGrammard() const;
		//根据<patterns>来对子句子subsentence建立语法联系.
		void BuildGrammarAssociation(const std::vector<GrammarPattern>& patterns);
		//获得子句子subsentence中的第i_thWord个word的语法匹配信息，associatedIndexes是语法模式匹配的序号集合，associatedPatterns是相应的模式，两者vector一一对应。		
		void GetAssociationInfo(const int i_thWord,vector<vector<int>>& associatedIndexes,vector<GrammarPattern>& associatedPatterns);
		unsigned int GrammarWordCount();

		//设定子句子subsentence中的第i_word个word和第j_word个word的intensity。
		void SetWordIntensity(const unsigned int i_word,const unsigned int j_word,double intensity);
		double GetWordIntensity(const unsigned int i_word,const unsigned int j_word);


	private:
		bool SearchSubInfo(const string str,int& infoIndex) const;
	};

	
}

