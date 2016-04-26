#include "StdAfx.h"
#include "TestClass.h"
#include "Cerebrum.h"

#include "../MindElement/Concept.h"
#include "../MindElement/CommonFunction.h"
#include "../MindElement/ConceptInteractTable.h"

#include "../Neural Network Design/CompetitiveNetwork.h"
#include "../Neural Network Design/Neuron_compet.h"

#include "../CommonTools/IOFunction.h"

#include "../Mathmatic/Vector.h"
#include "../Mathmatic/FindSequence.h"
#include "../Mathmatic/MathTool.h"

#include "../DataCollection/GrammardSentence.h"
#include "../DataCollection/DataBaseProcessorTool.h"
#include "../DataCollection/Word.h"
#include "../DataCollection/GrammaPattern.h"


using namespace std;
using namespace Math;
using namespace CommonTool;
using namespace NeuralNetwork;
using namespace DataCollection;


namespace Mind
{
	TestClass::TestClass(void)
	{
	}


	TestClass::~TestClass(void)
	{
	}

	void TestClass::RunTest()
	{
		Test_ConceptDeepInteraction();
		Test_BuildGrammarAssociation();
	}

	void TestClass::Test_BuildGrammarAssociation()
	{
		vector<PartOfSpeech> pos;
		pos.push_back(PartOfSpeech(1));
		pos.push_back(PartOfSpeech(2));
		pos.push_back(PartOfSpeech(2));
		pos.push_back(PartOfSpeech(4));
		pos.push_back(PartOfSpeech(2));
		pos.push_back(PartOfSpeech(3));
		pos.push_back(PartOfSpeech(5));
		pos.push_back(PartOfSpeech(2));
		pos.push_back(PartOfSpeech(4));
		pos.push_back(PartOfSpeech(5));
		vector<shared_ptr<Word>> words;
		for (unsigned int i=0;i<pos.size();++i)
		{
			words.push_back(DataBaseProcessorTool::GetParticularWord("我",pos[i]));
		}

		vector<PartOfSpeech> pos1;
		pos1.push_back(PartOfSpeech(2));
		pos1.push_back(PartOfSpeech(4));
		vector<PartOfSpeech> pos2;
		pos2.push_back(PartOfSpeech(1));
		pos2.push_back(PartOfSpeech(2));
		pos2.push_back(PartOfSpeech(3));
		vector<PartOfSpeech> pos3;
		pos3.push_back(PartOfSpeech(3));
		pos3.push_back(PartOfSpeech(4));
		vector<PartOfSpeech> pos4;
		pos4.push_back(PartOfSpeech(4));
		pos4.push_back(PartOfSpeech(5));
		GrammarPattern pattern1(pos1);
		pattern1.SetID(0);
		GrammarPattern pattern2(pos2);
		pattern2.SetID(1);
		GrammarPattern pattern3(pos3);
		pattern3.SetID(2);
		GrammarPattern pattern4(pos4);
		pattern4.SetID(3);

		vector<GrammarPattern> patterns;
		patterns.push_back(pattern1);
		patterns.push_back(pattern2);
		patterns.push_back(pattern3);
		patterns.push_back(pattern4);

		GrammardSentence gs(words);
		gs.BuildGrammarAssociation(patterns);



	}

	void TestClass::Test_ConceptDeepInteraction()
	{
		Cerebrum* brain=Cerebrum::Instance();
		{
			Identity iden1;
			iden1.id=0;
			iden1.str="爱";
			shared_ptr<iConcept> from=brain->GetConcept(iden1);
			Identity iden2;
			iden2.id=0;
			iden2.str="你";
			shared_ptr<iConcept> to=brain->GetConcept(iden2);

			shared_ptr<ConceptInteractTable> table=from->DeepInteractWith(to);

			vector<pair<string,string>> expect;
			expect.push_back(make_pair("大","程度"));
			expect.push_back(make_pair("程度","好感"));
			expect.push_back(make_pair("好感","对方"));
			expect.push_back(make_pair("大","好感"));

			Check(PairSameWithTable(expect,table));
		}

		{
			Identity iden1;
			iden1.id=0;
			iden1.str="不";
			shared_ptr<iConcept> from=brain->GetConcept(iden1);
			Identity iden2;
			iden2.id=0;
			iden2.str="老";
			shared_ptr<iConcept> to=brain->GetConcept(iden2);

			shared_ptr<ConceptInteractTable> table=from->DeepInteractWith(to);

			vector<pair<string,string>> expect;
			expect.push_back(make_pair("否定","年龄"));
			expect.push_back(make_pair("大","年龄"));

			Check(PairSameWithTable(expect,table));
		}
	}

	bool TestClass::PairSameWithTable( const vector<pair<string,string>>& expect,const shared_ptr<ConceptInteractTable> table )
	{
		class FindRelation
		{
			pair<string,string> _p;
		public: 
			FindRelation(const pair<string,string> p):_p(p){}
			~FindRelation(){}

			bool operator()(const pair<shared_ptr<iConcept>,shared_ptr<iConcept>> conceptPair)
			{
				if(conceptPair.first->GetString()==_p.first && conceptPair.second->GetString()==_p.second)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};

		vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> relations=table->GetAllRelations();
		for (unsigned int i=0;i<expect.size();++i)
		{
			if(find_if(relations.begin(),relations.end(),FindRelation(expect[i]))==relations.end())
			{
				return false;
			}
		}

		return true;
	}

}

