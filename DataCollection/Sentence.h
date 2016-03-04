#pragma once
#include "InOut.h"
#include "GrammardSentence.h"
#include "StructuredSentence.h"

namespace DataCollection
{
	class Character;
	class Word;
	class GrammarPattern;
	
	class RawSentence
	{
		std::vector<shared_ptr<Character>> _raw;
	public:
		RawSentence();
		~RawSentence();
		RawSentence(std::vector<shared_ptr<Character>> vec);
		RawSentence(std::string val);

		std::vector<shared_ptr<Character>> GetRawSentence() const;

	};

	class SegmentedSentence
	{
		std::vector<shared_ptr<DataCollection::Word>> _seg;
	public:
		SegmentedSentence();
		~SegmentedSentence();
		SegmentedSentence(const std::vector<shared_ptr<DataCollection::Word>> vec);

		std::vector<shared_ptr<Word>> Get() const ; 

	};



	class _DATACOLLECTIONINOUT Sentence
	{
		RawSentence _rawSentence;
		std::vector<SegmentedSentence> _segmented;// several ways of segmentation.
		std::vector<GrammardSentence> _grammard;
		vector<StructuredSentence> _structured;
	public:
		Sentence(void);
		~Sentence(void);
		Sentence(std::vector<shared_ptr<Character>> val);
		Sentence(std::string val);

		std::vector<shared_ptr<Character>> GetRawSentence() const;

		void AddSegmented(const std::vector<shared_ptr<DataCollection::Word>> vec);
		size_t Count_Segmented() const {return _segmented.size();}
		std::vector<shared_ptr<Word>> GetSegmented(const unsigned int i) const;

		void AddGrammard(const std::vector<shared_ptr<DataCollection::Word>> vec);
		size_t Count_Grammard() const {return _grammard.size();}
		std::vector<shared_ptr<Word>> GetGrammard(const unsigned int i) const;
		void BuildGrammarAssociation(const int i,const std::vector<GrammarPattern>& patterns);
		//��õ�i_thGra���﷨���ӵĵ�i_thWord��word���﷨ƥ����Ϣ��associatedIndexes���﷨ģʽƥ�����ż��ϣ�associatedPatterns����Ӧ��ģʽ������vectorһһ��Ӧ��		
		void GetAssociationInfo(const int i_thGra,const int i_thWord,vector<vector<int>>& associatedIndexes,vector<GrammarPattern>& associatedPatterns);
		unsigned int GrammarWordCount(const unsigned int i);

		//�趨��i���﷨�����еĵ�i_word��word�͵�j_word��word��intensity��
		void SetWordIntensity(const unsigned int i,const unsigned int i_word,const unsigned int j_word,double intensity);
		double GetWordIntensity(const unsigned int i,const unsigned int i_word,const unsigned int j_word);

	};

	
}

