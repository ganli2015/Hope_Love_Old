#pragma once
#include "InOut.h"
#include "../MindInterface/iCerebrum.h"


namespace DataCollection
{
	class Character;
	class Word;
	class GrammarPattern;
	class WordRelationTable;
	enum PartOfSpeech;
}

namespace LogicSystem
{
	class iLogicKnowledge;
}

namespace Mind
{
	class iConcept;
	class ConceptSet;
	class GrammarSet;
	class ConceptInteractTableContainer;
	class ConceptReactSystem;
	class iConceptChain;
	struct Identity;
	struct ConceptChainProperty;

	class _MINDINOUT Cerebrum : public iCerebrum
	{
		static Cerebrum* _instance;
		
		ConceptSet* _conceptset;
		GrammarSet* _grammaset;
		ConceptInteractTableContainer* _conceptInteractTableContainer;
		ConceptReactSystem* _conceptReactSystem;
		LogicSystem::iLogicKnowledge* _logicKnowledge;

		Cerebrum(void);
		void PostInitialize();
	public:
		static Cerebrum* Instance();
		virtual ~Cerebrum();

		void SetLogicKnowledge(LogicSystem::iLogicKnowledge* val){_logicKnowledge=val;}

		//Concept Related Functions
		virtual bool IsInMind(const std::string str) const;
		virtual bool IsInMind(const shared_ptr<DataCollection::Word> word) const;
        
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
		virtual std::vector<shared_ptr<DataCollection::Word>> GetAllKindsofWord(const shared_ptr<DataCollection::Word> word) const;
		virtual vector<shared_ptr<DataCollection::Word>> GetAllWordsOfPOS(const DataCollection::PartOfSpeech pos) const;

		void MakeConceptConnection(const shared_ptr<DataCollection::Word> from,const shared_ptr<DataCollection::Word> to);
		virtual shared_ptr<iConcept> GetConcept(const shared_ptr<DataCollection::Word> word) const ;
		virtual shared_ptr<iConcept> GetConcept(const Identity identity) const;
		virtual vector<shared_ptr<iConcept>> SearchForwardConcepts(const shared_ptr<iConcept> concept) const;
		virtual vector<shared_ptr<iConcept>> SearchBackwardConcepts(const shared_ptr<iConcept> concept) const;

		virtual vector<shared_ptr<iConcept>> FindConceptWithMatchedDisc(const shared_ptr<iConceptInteractTable> description) const ;
		virtual void FindConceptWithMatchedDisc(const shared_ptr<iConceptInteractTable> description, vector<DescMatchedConceptInfo>& matchedInfos) const;

		virtual int BaseConceptCount() const ;

		//Grammar Related Functions
		//搜索<pattern>所包含的子pattern.
		virtual std::vector<DataCollection::GrammarPattern> ContainSubsequence(const DataCollection::GrammarPattern& pattern) const;
		//搜索包含<pattern>的pattern.
		virtual std::vector<DataCollection::GrammarPattern> ContainedSubsequence(const DataCollection::GrammarPattern& pattern) const;
		virtual int CountOfSubsequence(const DataCollection::GrammarPattern& pattern) const;
		virtual int GetFreqencyofPattern(const DataCollection::GrammarPattern& pattern) const;
		virtual void IncreasePatternFreqency(const DataCollection::GrammarPattern& pattern);
		vector<DataCollection::GrammarPattern> GrammarPatternSortByFrequency() const ;
		//获得me的后一个词性是forward的概率.
		virtual double GetP_Forward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& forward) const;
		//获得me的前一个词性是backward的概率.
		virtual double GetP_Backward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& backward) const;

		virtual double ComputePossibility(const DataCollection::GrammarPattern& pattern) const ;

		//Concept React System Functions
		virtual vector<ConceptChainProperty> React(const shared_ptr<iConceptChain> chain);

		//LogicKnowledge related functions
		virtual vector<shared_ptr<LogicSystem::iDeduceResult>> Deduce(const shared_ptr<LogicSystem::iExpression> expre) const;
		virtual vector<shared_ptr<LogicSystem::iDeduceResult>> Deduce(const shared_ptr<iConceptInteractTable> conceptTable) const ;
		virtual void AddLogicStatement(const shared_ptr<LogicSystem::iLogicStatement> statement) ;

	};
}


