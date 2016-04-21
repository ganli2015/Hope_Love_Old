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
        
        //与<chara>或<word>同根的词的数量，只记向前的。
        //比如概念集里只有“天”“天空”“天上”这三个词语，那么“天”的Count_ForwardAdjWord就等于3.
        //而“天空”的Count_ForwardAdjWord就等于1.
		int Count_ForwardAdjWord(const shared_ptr<DataCollection::Character> chara) const;
        int Count_ForwardAdjWord(const shared_ptr<DataCollection::Word> word) const;
        //找出相邻的前向词。
        //比如概念集里只有“天”“天空”“天空空”这三个词语，那么“天”的<forAdjword>就是“天”“天空”“天空空”，
        //而“天空”的<forAdjword>就是“天空”“天空空”.
		void GetForwardAdjWord(const shared_ptr<DataCollection::Character> chara,std::vector<std::string>& forAdjword) const;
		void GetForwardAdjWord(const shared_ptr<DataCollection::Word> word,std::vector<std::string>& forAdjword) const;
		void GetForwardAdjWord(const shared_ptr<DataCollection::Character> chara,std::vector<DataCollection::Word>& forAdjword) const;
		void GetForwardAdjWord(const shared_ptr<DataCollection::Word> word,std::vector<DataCollection::Word>& forAdjword) const;
        //最大的同根词的长度。
        //比如概念集里只有“天”“天空”“天空空”这三个词语，那么“天”和“天空”的MaxLength_AdjacentWord都等于3。
		int MaxLength_AdjacentWord(const shared_ptr<DataCollection::Character> chara) const;
		int MaxLength_AdjacentWord(const shared_ptr<DataCollection::Word> word) const;
		int MaxLength_WordWithHead(const shared_ptr<DataCollection::Character> headChara) const;

		//得到已知的所有词性的<word>。
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
		//获得me的后一个词性是forward的概率.
		double GetP_Forward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& forward) const;
		//获得me的前一个词性是backward的概率.
		double GetP_Backward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& backward) const;

		//Concept Interact Table Related Functions
// 		void BuildConceptInteractTable(const shared_ptr<Concept> fromConcept,const shared_ptr<Concept> toConcept);
// 		std::vector<pair<shared_ptr<Concept>,shared_ptr<Concept>>> GetAllInteractPairs() const;
// 		void ClearConceptInteractTable();

		//Concept React System Functions
		vector<ConceptChainProperty> React(const shared_ptr<ConceptChain> chain);

		
	};
}


