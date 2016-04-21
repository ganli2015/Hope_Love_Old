#include "StdAfx.h"
#include "ChainGenerator.h"
#include "ExtractConceptChains.h"

#include "../Mind/Cerebrum.h"
#include "../MindElement/Concept.h"
#include "../MindElement/ConceptChain.h"
#include "../MindElement/ConceptInteractTable.h"
#include "../Mind/CommonFunction.h"

#include "../Mathmatic/Rand.h"

#include <iostream>

using namespace Mind;

ChainGenerator::ChainGenerator(void):_brain(Cerebrum::Instance())
{
}


ChainGenerator::~ChainGenerator(void)
{
}

void ChainGenerator::Generate(const shared_ptr<Mind::ConceptInteractTable> interactTable)
{
	vector<ConceptPair> allPairs=interactTable->GetAllRelations();
	vector<shared_ptr<ConceptChain>> allChains=ExtractConceptChains::Extract(allPairs);
	RemoveSameChain(allChains);

#ifdef _DEBUG
	CheckDuplicatedConceptInChains(allChains);
	//DisplayChains(allChains);
#endif // _DEBUG

	_reactChains=ChainReact(allChains);
}

void ChainGenerator::DisplayChains( const vector<shared_ptr<ConceptChain>>& chains ) const
{
	for (unsigned int i=0;i<chains.size();++i)
	{
		vector<shared_ptr<Concept> > concepts=chains[i]->GetConceptVec();
		for (unsigned int j=0;j<concepts.size();++j)
		{
			cout<<concepts[j]->GetString()<<" ";
		}
		cout<<endl;
	}
}

void ChainGenerator::RemoveSameChain( vector<shared_ptr<ConceptChain>>& chains ) const
{
	vector<shared_ptr<ConceptChain>> removedChains;

	for (unsigned int i=0;i<chains.size();++i)
	{
		shared_ptr<ConceptChain> curChain=chains[i];

		bool duplicated=false;
		for (unsigned int j=i+1;j<chains.size();++j)
		{
			if(chains[j]->Same(curChain))
			{
				duplicated=true;
			}
		}

		if(!duplicated)
		{
			removedChains.push_back(curChain);
		}
	}

	chains=removedChains;
}

void ChainGenerator::CheckDuplicatedConceptInChains( const vector<shared_ptr<Mind::ConceptChain>>& chains ) const
{
	for (unsigned int i=0;i<chains.size();++i)
	{
		vector<shared_ptr<Concept>> vec=chains[i]->GetConceptVec();
		for (unsigned int j=0;j<vec.size();++j)
		{
			if(find_if(vec.begin()+j+1,vec.end(),CommonFunction::SameConcept(vec[j]))!=vec.end())
			{
				throw runtime_error("DuplicatedConceptInChains!");
			}
		}
	}
}

vector<ConceptChainProperty> ChainGenerator::ChainReact( const vector<shared_ptr<ConceptChain>>& chains ) const
{
	vector<ConceptChainProperty> res;

	ofstream out("DebugInfo//ChainReact.txt");
	for (unsigned int i=0;i<chains.size();++i)
	{
		vector<ConceptChainProperty> properties=_brain->React(chains[i]);
		if(properties.empty()) continue;
		OutputChainProperty(chains[i],properties,out);

		//vector<shared_ptr<ConceptChain>> selected=RandomSelectChains(properties);
		res.insert(res.end(),properties.begin(),properties.end());
	}

	return res;
}

void ChainGenerator::OutputChainProperty( const shared_ptr<Mind::ConceptChain> chain,const vector<Mind::ConceptChainProperty>& properties,ofstream& out ) const
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

vector<shared_ptr<Mind::ConceptChain>> ChainGenerator::RandomSelectChains( const vector<Mind::ConceptChainProperty>& chainProperties ) const
{
	vector<shared_ptr<Mind::ConceptChain>> res;
	for (unsigned int i=0;i<chainProperties.size();++i)
	{
		if(Math::Rand::RandTrue(chainProperties[i].confidence))
		{
			res.push_back(chainProperties[i].chain);
		}
	}

	return res;
}

