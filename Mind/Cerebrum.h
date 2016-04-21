#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Character;
	class Word;
	class GrammarPattern;
	class WordRelationTable;
	enum PartOfSpeech;
}

namespace Mind
{
	class Concept;
	class ConceptSet;
	class GrammarSet;
	class ConceptInteractTableContainer;
	class ConceptReactSystem;
	class ConceptChain;
	struct Identity;
	struct ConceptChainProperty;

	class _MINDINOUT Cerebrum
	{
		static Cerebrum* _instance;
		
		ConceptSet* _conceptset;
		GrammarSet* _grammaset;
		ConceptInteractTableContainer* _conceptInteractTableContainer;
		ConceptReactSystem* _conceptReactSystem;

		Cerebrum(void);
		~Cerebrum();
	public:
		static Cerebrum* Instance();


		//Concept Related Functions
		bool IsInMind(const std::string str) const;
		bool IsInMind(const shared_ptr<DataCollection::Word> word) const;
        
        //��<chara>��<word>ͬ���Ĵʵ�������ֻ����ǰ�ġ�
        //��������ֻ�С��족����ա������ϡ������������ô���족��Count_ForwardAdjWord�͵���3.
        //������ա���Count_ForwardAdjWord�͵���1.
		int Count_ForwardAdjWord(const shared_ptr<DataCollection::Character> chara) const;
        int Count_ForwardAdjWord(const shared_ptr<DataCollection::Word> word) const;
        //�ҳ����ڵ�ǰ��ʡ�
        //��������ֻ�С��족����ա�����տա������������ô���족��<forAdjword>���ǡ��족����ա�����տա���
        //������ա���<forAdjword>���ǡ���ա�����տա�.
		void GetForwardAdjWord(const shared_ptr<DataCollection::Character> chara,std::vector<std::string>& forAdjword) const;
		void GetForwardAdjWord(const shared_ptr<DataCollection::Word> word,std::vector<std::string>& forAdjword) const;
		void GetForwardAdjWord(const shared_ptr<DataCollection::Character> chara,std::vector<DataCollection::Word>& forAdjword) const;
		void GetForwardAdjWord(const shared_ptr<DataCollection::Word> word,std::vector<DataCollection::Word>& forAdjword) const;
        //����ͬ���ʵĳ��ȡ�
        //��������ֻ�С��족����ա�����տա������������ô���족�͡���ա���MaxLength_AdjacentWord������3��
		int MaxLength_AdjacentWord(const shared_ptr<DataCollection::Character> chara) const;
		int MaxLength_AdjacentWord(const shared_ptr<DataCollection::Word> word) const;
		int MaxLength_WordWithHead(const shared_ptr<DataCollection::Character> headChara) const;

		//�õ���֪�����д��Ե�<word>��
		std::vector<shared_ptr<DataCollection::Word>> GetAllKindsofWord(const shared_ptr<DataCollection::Word> word) const;
		vector<shared_ptr<DataCollection::Word>> GetAllWordsOfPOS(const DataCollection::PartOfSpeech pos) const;

		void MakeConceptConnection(const shared_ptr<DataCollection::Word> from,const shared_ptr<DataCollection::Word> to);
		shared_ptr<Concept> GetConcept(const shared_ptr<DataCollection::Word> word);
		shared_ptr<Concept> GetConcept(const Identity identity);
		vector<shared_ptr<Concept>> SearchForwardConcepts(const shared_ptr<Concept> concept) const;
		vector<shared_ptr<Concept>> SearchBackwardConcepts(const shared_ptr<Concept> concept) const;

		//Grammar Related Functions
		std::vector<DataCollection::GrammarPattern> ContainSubsequence(const DataCollection::GrammarPattern& pattern) const;
		std::vector<DataCollection::GrammarPattern> ContainedSubsequence(const DataCollection::GrammarPattern& pattern) const;
		int CountOfSubsequence(const DataCollection::GrammarPattern& pattern) const;
		int GetFreqencyofPattern(const DataCollection::GrammarPattern& pattern) const;
		void IncreasePatternFreqency(const DataCollection::GrammarPattern& pattern);
		vector<DataCollection::GrammarPattern> GrammarPatternSortByFrequency() const ;
		//���me�ĺ�һ��������forward�ĸ���.
		double GetP_Forward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& forward) const;
		//���me��ǰһ��������backward�ĸ���.
		double GetP_Backward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& backward) const;

		//Concept Interact Table Related Functions
// 		void BuildConceptInteractTable(const shared_ptr<Concept> fromConcept,const shared_ptr<Concept> toConcept);
// 		std::vector<pair<shared_ptr<Concept>,shared_ptr<Concept>>> GetAllInteractPairs() const;
// 		void ClearConceptInteractTable();

		//Concept React System Functions
		vector<ConceptChainProperty> React(const shared_ptr<ConceptChain> chain);

		
	};
}


