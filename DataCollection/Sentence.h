#pragma once
#include "InOut.h"
#include "GrammardSentence.h"
#include "StructuredSentence.h"

namespace DataCollection
{
	class Character;
	class Word;
	class GrammarPattern;
	
	//�Ӿ��ӣ�ֻ����һ����ϱ����ţ����š���ţ�
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


	//��ʾһ�������ľ��ӣ����԰���������
	class _DATACOLLECTIONINOUT Sentence
	{
		//�����Ӿ��ӵ���Ϣ�������Ͼ䷽ʽ���﷨��������ʹ���֮�������ǿ��.
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

// 		std::vector<RawSentence> _punctured;//�������ŷֿ����Ӿ���.
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
		//����<patterns>�����Ӿ���subsentence�����﷨��ϵ.
		void BuildGrammarAssociation(const std::vector<GrammarPattern>& patterns);
		//����Ӿ���subsentence�еĵ�i_thWord��word���﷨ƥ����Ϣ��associatedIndexes���﷨ģʽƥ�����ż��ϣ�associatedPatterns����Ӧ��ģʽ������vectorһһ��Ӧ��		
		void GetAssociationInfo(const int i_thWord,vector<vector<int>>& associatedIndexes,vector<GrammarPattern>& associatedPatterns);
		unsigned int GrammarWordCount();

		//�趨�Ӿ���subsentence�еĵ�i_word��word�͵�j_word��word��intensity��
		void SetWordIntensity(const unsigned int i_word,const unsigned int j_word,double intensity);
		double GetWordIntensity(const unsigned int i_word,const unsigned int j_word);


	private:
		bool SearchSubInfo(const string str,int& infoIndex) const;
	};

	
}

