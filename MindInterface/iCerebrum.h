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
	class iLogicKnowledge;
}

namespace Mind
{
	class iConcept;
	class iConceptChain;
	class iConceptInteractTable;
	struct Identity;
	struct ConceptChainProperty;
	struct DescMatchedConceptInfo;

	//////////////////////////////////////////////////////////////////////////
	///iCerebrum is the central component of AI.
	///It contains almost all data of knowledge that AI knows.
	///Knowledge include concepts about words, grammar of sentence,experimental reaction of environment and logical knowledge.
	///It provide APIs of knowledge above.
	///
	///iCerebrum is singleton and there is only one iCerebrum during runtime of application.
	//////////////////////////////////////////////////////////////////////////
	class _MINDINTERFACEINOUT iCerebrum
	{
		static iCerebrum* _instance;

	public:
		virtual ~iCerebrum(){}

		//////////////////////////////////////////////////////////////////////////
		///Get the unique instance of iCerebrum.
		//////////////////////////////////////////////////////////////////////////
		static iCerebrum* Instance();
		static void SetInstance(iCerebrum* val);
		//////////////////////////////////////////////////////////////////////////
		///Delete the unique instance.
		static void KillInstance();
		//////////////////////////////////////////////////////////////////////////
		///Check whether there is an instance.
		//////////////////////////////////////////////////////////////////////////
		static bool Empty();

		virtual void SetLogicKnowledge(LogicSystem::iLogicKnowledge* val) =0;

		//Concept Related Functions
		
		//////////////////////////////////////////////////////////////////////////
		///Check whether <me> knows the word of <str>
		//////////////////////////////////////////////////////////////////////////
		virtual bool IsInMind(const std::string str) const=0;
		virtual bool IsInMind(const shared_ptr<DataCollection::Word> word) const=0;

		//////////////////////////////////////////////////////////////////////////
		///Get the max length of the word which start with character <headChara>.
		//////////////////////////////////////////////////////////////////////////
		virtual int MaxLength_WordWithHead(const shared_ptr<DataCollection::Character> headChara) const=0;

		//////////////////////////////////////////////////////////////////////////
		///Get all words whose string is the same as <word>.
		//////////////////////////////////////////////////////////////////////////
		virtual std::vector<shared_ptr<DataCollection::Word>> GetAllKindsofWord(const shared_ptr<DataCollection::Word> word) const=0;
		//////////////////////////////////////////////////////////////////////////
		///Get all words whose POS is <pos>.
		//////////////////////////////////////////////////////////////////////////
		virtual vector<shared_ptr<DataCollection::Word>> GetAllWordsOfPOS(const DataCollection::PartOfSpeech pos) const=0;

		//////////////////////////////////////////////////////////////////////////
		///Get the concept of the <word>.
		///POS of the returned concept is the same with <word>.
		///As for one certain word there may be several concepts with the same POS, the returned concept is just one of them.
		//////////////////////////////////////////////////////////////////////////
		virtual shared_ptr<iConcept> GetConcept(const shared_ptr<DataCollection::Word> word) const =0;
		//////////////////////////////////////////////////////////////////////////
		///Get the concept according to <identity>.
		//////////////////////////////////////////////////////////////////////////
		virtual shared_ptr<iConcept> GetConcept(const Identity identity) const =0;
		//////////////////////////////////////////////////////////////////////////
		///Get concepts that <concept> depends on.
		//////////////////////////////////////////////////////////////////////////
		virtual vector<shared_ptr<iConcept>> SearchForwardConcepts(const shared_ptr<iConcept> concept) const=0;
		//////////////////////////////////////////////////////////////////////////
		///Get concepts that depend on <concept>.
		//////////////////////////////////////////////////////////////////////////
		virtual vector<shared_ptr<iConcept>> SearchBackwardConcepts(const shared_ptr<iConcept> concept) const=0;

		//////////////////////////////////////////////////////////////////////////
		///Find a concept which has the same meaning with the concept pairs in  <description>.
		//////////////////////////////////////////////////////////////////////////
		virtual vector<shared_ptr<iConcept>> FindConceptWithMatchedDisc(const shared_ptr<iConceptInteractTable> description) const = 0;
		//////////////////////////////////////////////////////////////////////////
		///Find a concept which has the same meaning with the concept pairs in  <description>.
		///Output information fo matched concept.
		//////////////////////////////////////////////////////////////////////////
		virtual void FindConceptWithMatchedDisc(const shared_ptr<iConceptInteractTable> description, vector<DescMatchedConceptInfo>& matchedInfos) const = 0;

		//////////////////////////////////////////////////////////////////////////
		///Return the number of base concepts.
		//////////////////////////////////////////////////////////////////////////
		virtual int BaseConceptCount() const =0;

		//Grammar Related Functions
		
		//////////////////////////////////////////////////////////////////////////
		///Search all grammar patterns which are sub patterns of <pattern>.
		//////////////////////////////////////////////////////////////////////////
		virtual std::vector<DataCollection::GrammarPattern> ContainSubsequence(const DataCollection::GrammarPattern& pattern) const=0;
		//////////////////////////////////////////////////////////////////////////
		///Search all grammar patterns of which <pattern> is a sub grammar pattern.
		//////////////////////////////////////////////////////////////////////////
		virtual std::vector<DataCollection::GrammarPattern> ContainedSubsequence(const DataCollection::GrammarPattern& pattern) const=0;
		
		//////////////////////////////////////////////////////////////////////////
		///Return the number of sub grammar patterns that <pattern> contains.
		//////////////////////////////////////////////////////////////////////////
		virtual int CountOfSubsequence(const DataCollection::GrammarPattern& pattern) const=0;
		
		//////////////////////////////////////////////////////////////////////////
		///Get the usage frequency of <pattern>.
		//////////////////////////////////////////////////////////////////////////
		virtual int GetFreqencyofPattern(const DataCollection::GrammarPattern& pattern) const=0;
		
		//////////////////////////////////////////////////////////////////////////
		///Increase of the usage frequency of <pattern> by one.
		//////////////////////////////////////////////////////////////////////////
		virtual void IncreasePatternFreqency(const DataCollection::GrammarPattern& pattern) =0;
		
		//////////////////////////////////////////////////////////////////////////
		///Get possibility in cases that POS of current word is <me> and POS of next word is <forward>.
		//////////////////////////////////////////////////////////////////////////
		virtual double GetP_Forward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& forward) const=0;
		//////////////////////////////////////////////////////////////////////////
		///Get possibility in cases that POS of current word is <me> and POS of previous word is <backward>.
		//////////////////////////////////////////////////////////////////////////
		virtual double GetP_Backward(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& backward) const=0;

		//Concept React System Functions
		
		//////////////////////////////////////////////////////////////////////////
		///Get reaction information of the input concept chain <chain>.
		///The input chain should constitue of base concepts and the returned chain constitutes of base concepts as well.
		//////////////////////////////////////////////////////////////////////////
		virtual vector<ConceptChainProperty> React(const shared_ptr<iConceptChain> chain)=0;

		//LogicKnowledge related functions
		
		//////////////////////////////////////////////////////////////////////////
		///Deduce from <expre> using logical knowledge.
		//////////////////////////////////////////////////////////////////////////
		virtual vector<shared_ptr<LogicSystem::iDeduceResult>> Deduce(const shared_ptr<LogicSystem::iExpression> expre) const =0;
		virtual vector<shared_ptr<LogicSystem::iDeduceResult>> Deduce(const shared_ptr<iConceptInteractTable> conceptTable) const =0;
		virtual void AddLogicStatement(const shared_ptr<LogicSystem::iLogicStatement> statement) =0;
	};

	///Some information of concept that is matched with some description.
	struct DescMatchedConceptInfo
	{
		shared_ptr<iConcept> matchedConcept;
		shared_ptr<iConcept> toConcept;//The to concept of <matchedConcept> with corresponding description.
	};
}
