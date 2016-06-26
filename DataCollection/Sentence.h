#pragma once
#include "InOut.h"
#include "GrammardSentence.h"
#include "StructuredSentence.h"

namespace DataCollection
{
	class Character;
	class Word;
	class GrammarPattern;
	
	//SubSentence contains only one of the puncture of end of the sentence.
	class SubSentence : public Obj<SubSentence>
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

	///SegmentedSentence indicates the segmentation structure of a certain sentence.
	///Words in SegmentedSentence are probably of no definite POS.
	class _DATACOLLECTIONINOUT SegmentedSentence : public Obj<SegmentedSentence>
	{
		std::vector<shared_ptr<DataCollection::Word>> _seg;
	public:
		SegmentedSentence();
		~SegmentedSentence();
		SegmentedSentence(const std::vector<shared_ptr<DataCollection::Word>> vec);

		std::vector<shared_ptr<Word>> Get() const ; 

	};


	//Sentence constitutes of several sub sentence, and may contain several punctures.
	class _DATACOLLECTIONINOUT Sentence : public Obj<Sentence>
	{
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


	public:
		Sentence(void);
		~Sentence(void);
		Sentence(std::vector<shared_ptr<Character>> val);
		Sentence(std::string val);

		string GetString() const;
		std::vector<shared_ptr<Character>> GetRawSentence() const;
		
		///Add a sub sentence which constitute of characters <vec>.
		void AddSubSentence(const std::vector<shared_ptr<DataCollection::Character>> vec);
		///Add a sub sentence which constitute of string <str>.
		void AddSubSentence(const string str);
		///Return the number sub sentences.
		size_t Count_SubSentence() const;
		///Get the ith sub sentences.
		string GetSubSentence(const unsigned int i) const;

		///Set grammar sentence whose words are <vec>.
		///Each word of <vec> should have definite POS.
		///There is only one grammar sentence in <me>.So when calling <SetGrammard>,the previous grammar sentence is covered.
		void SetGrammard(const std::vector<shared_ptr<DataCollection::Word>> vec);

		///Get words of grammar sentence.
		std::vector<shared_ptr<Word>> GetGrammard() const;
		shared_ptr<Word> GetGrammardWord(const unsigned int i) const;

		///Build grammar association of <me> according to <patterns>.
		void BuildGrammarAssociation(const std::vector<GrammarPattern>& patterns);

		///Get the association info of the <i_thWord>th word, including the associated indexes <associatedIndexes> and patterns related to them.
		///<associatedIndexes> and <associatedPatterns> are one-to-one mapping.
		void GetAssociationInfo(const int i_thWord,vector<vector<int>>& associatedIndexes,vector<GrammarPattern>& associatedPatterns);
		
		unsigned int GrammarWordCount() const;
		bool StructureAnalyzed() const {return _structured->Analyzed();}

		///Set the intensity of the <i_word>th and <j_word>th word.
		void SetWordIntensity(const unsigned int i_word,const unsigned int j_word,double intensity);
		double GetWordIntensity(const unsigned int i_word,const unsigned int j_word);


	private:
		bool SearchSubInfo(const string str,int& infoIndex) const;
	};

	
}

