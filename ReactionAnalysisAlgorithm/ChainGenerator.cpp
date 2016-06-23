#include "StdAfx.h"
#include "ChainGenerator.h"
#include "ExtractConceptChains.h"

#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iConcept.h"
#include "../MindInterface/iConceptChain.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/CommonFunction.h"

#include "../Mind/CommonFunction.h"


#include "../Mathmatic/Rand.h"

#include <iostream>

using namespace Mind;

ChainGenerator::ChainGenerator(void):_brain(iCerebrum::Instance())
{
}


ChainGenerator::~ChainGenerator(void)
{
}

void ChainGenerator::Generate(const shared_ptr<Mind::iConceptInteractTable> interactTable)
{
	vector<ConceptPair> allPairs=interactTable->GetAllRelations();
	vector<shared_ptr<iConceptChain>> allChains=ExtractConceptChains::Extract(allPairs);
	CommonFunction::RemoveSameChain(allChains);

#ifdef _COUT_DEBUG_INFO
	CheckDuplicatedConceptInChains(allChains);
	//DisplayChains(allChains);
#endif // _DEBUG

	_reactChains=ChainReact(allChains);
}

void ChainGenerator::DisplayChains( const vector<shared_ptr<iConceptChain>>& chains ) const
{
	for (unsigned int i=0;i<chains.size();++i)
	{
		vector<shared_ptr<iConcept> > concepts=chains[i]->GetConceptVec();
		for (unsigned int j=0;j<concepts.size();++j)
		{
			cout<<concepts[j]->GetString()<<" ";
		}
		cout<<endl;
	}
}



void ChainGenerator::CheckDuplicatedConceptInChains( const vector<shared_ptr<Mind::iConceptChain>>& chains ) const
{
	for (unsigned int i=0;i<chains.size();++i)
	{
		vector<shared_ptr<iConcept>> vec=chains[i]->GetConceptVec();
		for (unsigned int j=0;j<vec.size();++j)
		{
			if(find_if(vec.begin()+j+1,vec.end(),CommonFunction::SameConcept(vec[j]))!=vec.end())
			{
				throw runtime_error("DuplicatedConceptInChains!");
			}
		}
	}
}

vector<ConceptChainProperty> ChainGenerator::ChainReact( const vector<shared_ptr<iConceptChain>>& chains ) const
{
	vector<ConceptChainProperty> res;

	//Compute react chains based on the data from Cerebrum.
	//Chains are experimental and each of them have some confidence which stores in <ConceptChainProperty>.
	ofstream out("DebugInfo//ChainReact.txt");
	for (unsigned int i=0;i<chains.size();++i)
	{
		vector<ConceptChainProperty> properties=_brain->React(chains[i]);
		if(properties.empty()) continue;
		OutputChainProperty(chains[i],properties,out);

		res.insert(res.end(),properties.begin(),properties.end());
	}

	return res;
}

void ChainGenerator::OutputChainProperty( const shared_ptr<Mind::iConceptChain> chain,const vector<Mind::ConceptChainProperty>& properties,ofstream& out ) const
{
	out<<"input chain: "<<endl;
	CommonFunction::WriteConcepts(chain->GetConceptVec(),out);
	out<<"output chains: "<<endl;
	for (unsigned int j=0;j<properties.size();++j)
	{
		CommonFunction::WriteConcepts(properties[j].chain->GetConceptVec(),out);
		out<<properties[j].confidence<<endl;
	}
	out<<endl;

}

vector<shared_ptr<Mind::iConceptChain>> ChainGenerator::RandomSelectChains( const vector<Mind::ConceptChainProperty>& chainProperties ) const
{
	vector<shared_ptr<Mind::iConceptChain>> res;
	for (unsigned int i=0;i<chainProperties.size();++i)
	{
		if(Math::Rand::RandTrue(chainProperties[i].confidence))
		{
			res.push_back(chainProperties[i].chain);
		}
	}

	return res;
}

