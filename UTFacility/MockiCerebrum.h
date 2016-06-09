#pragma once
#pragma warning(disable:4373)
#include "PublicHeader.h"
#include <gmock/gmock.h>

#include "../DataCollection/GrammaPattern.h"

#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/CommonFunction.h"
#include "../MindInterface/iConceptChain.h"

#include "../Mind/Cerebrum.h"

class ConceptTableCreator;
class ConceptCreator;


namespace Mind
{
	class _UTFACILITYINOUT MockiCerebrum : public iCerebrum
	{
	public:

		struct FindMatchConceptParam
		{
			string conceptTableStr;
			string matchedConceptStr;
			string toConceptStr;

			FindMatchConceptParam(const string table,const string matchedCon,const string toCon):
				conceptTableStr(table),matchedConceptStr(matchedCon),toConceptStr(toCon)
			{

			}
		};

	public:
		static Mind::MockiCerebrum* Create();

		///Create MockiCerebrum that designates the reduce result on the condition of <conceptTableStr>.
		void AddExpectCall_FindConceptWithMatchedDisc(const string conceptTableStr,
			const string matchedConceptStr,
			const string toConceptStr,
			const shared_ptr<ConceptTableCreator> tableCreator=NULL,
			const shared_ptr<ConceptCreator> conceptCreator=NULL);

		///Create MockiCerebrum that designates the reduce result.
		void AddExpectCall_FindConceptWithMatchedDisc(const vector<FindMatchConceptParam>& param,
			const shared_ptr<ConceptTableCreator> tableCreator=NULL,
			const shared_ptr<ConceptCreator> conceptCreator=NULL);

		///Add expect call for Deduce.
		///<inputTable> is input parameter , <outputResults> is the returned value.
		void AddExpectCall_Deduce(const string inputTable, const vector<string>& outputResults);
		void AddExpectCall_Deduce(const string inputTable, const string& outputResults);

		MOCK_METHOD1(SetLogicKnowledge,void(LogicSystem::iLogicKnowledge*));

		MOCK_CONST_METHOD1(IsInMind,bool(const string));
		MOCK_CONST_METHOD1(IsInMind,bool(const shared_ptr<DataCollection::Word>));
		MOCK_CONST_METHOD1(MaxLength_WordWithHead,int(const shared_ptr<DataCollection::Character>));

		MOCK_CONST_METHOD1(GetAllKindsofWord,std::vector<shared_ptr<DataCollection::Word>>(const shared_ptr<DataCollection::Word>));
		MOCK_CONST_METHOD1(GetAllWordsOfPOS,vector<shared_ptr<DataCollection::Word>>(const DataCollection::PartOfSpeech));

		MOCK_CONST_METHOD1(GetConcept,shared_ptr<iConcept>(const Identity identity));
		virtual shared_ptr<iConcept> GetConcept(const shared_ptr<DataCollection::Word> word) const 
		{
			throw runtime_error("Forbidden!");
		}

		MOCK_CONST_METHOD1(SearchForwardConcepts,vector<shared_ptr<iConcept>>(const shared_ptr<iConcept>));
		MOCK_CONST_METHOD1(SearchBackwardConcepts,vector<shared_ptr<iConcept>>(const shared_ptr<iConcept>));

		MOCK_CONST_METHOD1(ContainSubsequence,std::vector<DataCollection::GrammarPattern>(const DataCollection::GrammarPattern&));
		MOCK_CONST_METHOD1(ContainedSubsequence,std::vector<DataCollection::GrammarPattern>(const DataCollection::GrammarPattern&));
		MOCK_CONST_METHOD1(CountOfSubsequence,int(const DataCollection::GrammarPattern&));
		MOCK_CONST_METHOD1(GetFreqencyofPattern,int(const DataCollection::GrammarPattern&));
		MOCK_METHOD1(IncreasePatternFreqency,void(const DataCollection::GrammarPattern&));
		MOCK_CONST_METHOD2(GetP_Forward,double(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& forward));
		MOCK_CONST_METHOD2(GetP_Backward,double(const DataCollection::PartOfSpeech& me,const DataCollection::PartOfSpeech& backward));


		MOCK_METHOD1(React,vector<ConceptChainProperty>(const shared_ptr<iConceptChain> chain));

		MOCK_CONST_METHOD1(Deduce,vector<shared_ptr<LogicSystem::iDeduceResult>>(const shared_ptr<LogicSystem::iExpression> expre));
		MOCK_CONST_METHOD1(Deduce,vector<shared_ptr<LogicSystem::iDeduceResult>>(const shared_ptr<Mind::iConceptInteractTable> expre));

		MOCK_METHOD1(AddLogicStatement,void(const shared_ptr<LogicSystem::iLogicStatement> statement));

		virtual vector<shared_ptr<iConcept>> FindConceptWithMatchedDisc(const shared_ptr<iConceptInteractTable> description) const 
		{
			throw runtime_error("Forbidden!");
		}

		MOCK_CONST_METHOD2(FindConceptWithMatchedDisc,void(const shared_ptr<iConceptInteractTable> description, vector<DescMatchedConceptInfo>& matchedInfos));
	
	
	private:

		void AddFindMatchedConceptExpectCall(const string conceptTableStr, const string matchedConceptStr, 
			const string toConceptStr, const shared_ptr<ConceptTableCreator> tableCreator, const shared_ptr<ConceptCreator> conceptCreator);
	};
}


