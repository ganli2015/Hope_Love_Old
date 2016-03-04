#include "StdAfx.h"
#include "Test_ConceptSet.h"
#include "ConceptSet.h"

#include "../DataCollection/Word.h"

using namespace Mind;
using namespace DataCollection;

namespace Mind
{
	Test_ConceptSet::Test_ConceptSet(void)
	{
	}


	Test_ConceptSet::~Test_ConceptSet(void)
	{
	}

	void Test_ConceptSet::RunTest()
	{
// 		vector<shared_ptr<Word>> sample;
// 		sample.push_back(shared_ptr<Word>(new Word("aa")));
// 		sample.push_back(shared_ptr<Word>(new Word("bb")));
// 		sample.push_back(shared_ptr<Word>(new Word("cc")));
// 		sample.push_back(shared_ptr<Word>(new Word("dd")));
// 		sample.push_back(shared_ptr<Word>(new Word("ee")));
// 		sample.push_back(shared_ptr<Word>(new Word("ff")));
// 		sample.push_back(shared_ptr<Word>(new Word("gg")));
// 		sample.push_back(shared_ptr<Word>(new Word("hh")));
// 
// 
// 		ConceptSet conceptSet;
// 		for (unsigned int i=0;i<sample.size();++i)
// 		{
// 			conceptSet.AddConcept(sample[i]);
// 
// 		}
// 		conceptSet.MakeConnection(sample[1],sample[0]);
// 		conceptSet.MakeConnection(sample[1],sample[2]);
// 		conceptSet.MakeConnection(sample[2],sample[3]);
// 		conceptSet.MakeConnection(sample[3],sample[4]);
// 		conceptSet.MakeConnection(sample[4],sample[3]);
// 		conceptSet.MakeConnection(sample[4],sample[5]);
// 		conceptSet.MakeConnection(sample[5],sample[6]);
// 		conceptSet.MakeConnection(sample[6],sample[7]);
// 		conceptSet.MakeConnection(sample[4],sample[7]);
// 		conceptSet.MakeConnection(sample[6],sample[4]);
// 
// 		for (unsigned int i=0;i<8;++i)
// 		{
// 			Identity identity;
// 			identity.str=sample[i]->GetString();
// 			identity.id=0;
// 			vector<Concept> res=conceptSet.BreadthFirstSearch(identity);
// 			cout<<sample[i]->GetString()<<": "<<endl;
// 			for (unsigned int j=0;j<res.size();++j)
// 			{
// 				cout<<res[j].GetString()<<endl;
// 			}
// 		}
	}

}

