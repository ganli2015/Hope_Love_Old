#pragma  once
#include "InOut.h"

namespace DataCollection
{
	class Character;
	class Word;
	class GrammarPattern;
	enum PartOfSpeech;
}

namespace LogicSystem
{
	class iExpression;
	class iRelation;
	class iDeduceResult;
	class iLogicStatement;
}

namespace Mind
{
	class iConcept;
	class iConceptChain;
	struct Identity;
	struct ConceptChainProperty;

	class _MINDINTERFACEINOUT iCerebrum
	{
		static iCerebrum* _instance;

	public:
		virtual ~iCerebrum(){}

		static iCerebrum* Instance();
		static void SetInstance(iCerebrum* val);
		static void KillInstance();

		//Concept Related Functions
		virtual bool IsInMind(const std::string str) const=0;
		virtual bool IsInMind(const shared_ptr<DataCollection::Word> word) const=0;

		virtual int MaxLength_WordWithHead(const shared_ptr<DataCollection::Character> headChara) const=0;

		///Get all words whose string is the same as <word>.
		virtual std::vector<shared_ptr<DataCollection::Word>> GetAllKindsofWord(const shared_ptr<DataCollection::Word> word) const=0;
		virtual vector<shared_ptr<DataCollection::Word>> GetAllWordsOfPOS(const DataCollection::PartOfSpeech pos) const=0;

		virtual shared_ptr<iConcept> GetConcept(const shared_ptr<DataCollection::Word> word)=0;
		virtual shared_ptr<iConcept> GetConcept(const Identity identity)=0;
		virtual vector<shared_ptr<iConcept>> SearchForwardConcepts(const shared_ptr<iConcept> concept) const=0;
		virtual vector<shared_ptr<iConcept>> SearchBackwardConcepts(const shared_ptr<iConcept> concept) const=0;

		//Grammar Related Functions
		//搜索<pattern>所包含的子pattern.
		virtual std::vector<DataCollection::GrammarPattern> ContainSubsequence(const DataCollection::GrammarPattern& pattern) const=0;
		//搜索包含<pattern>的pattern.
		virtual std::vector<DataCollection::GrammarPattern> ContainedSubsequence(const DataCollection::GrammarPattern& pattern) const=0;
		virtual int CountOfSubsequence(const DataCollection::GrammarPattern& pattern) const=0;
		virtual int GetFreqencyofPattern(const DataCollection::GrammarPattern& pattern) const=0;
		virtual void IncreasePatternFreqency(const DataCollection::GrammarPattern& pattern) =0;
		//获得me的后一个词性是forward的概率.
		virtual double GetP_Forward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& forward) const=0;
		//获得me的前一个词性是backward的概率.
		virtual double GetP_Backward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& backward) const=0;

		//Concept React System Functions
		virtual vector<ConceptChainProperty> React(const shared_ptr<iConceptChain> chain)=0;

		//LogicKnowledge related functions
		virtual vector<shared_ptr<LogicSystem::iDeduceResult>> Deduce(const shared_ptr<LogicSystem::iExpression> expre) const =0;
		virtual void AddLogicStatement(const shared_ptr<LogicSystem::iLogicStatement> statement) =0;
	};
}