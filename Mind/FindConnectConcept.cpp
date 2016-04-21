#include "StdAfx.h"
#include "FindConnectConcept.h"
#include "../MindElement/Concept.h"

#include "../DataCollection/Word.h"

namespace Mind
{
	FindConnectConcept::FindConnectConcept(void)
	{
	}


	FindConnectConcept::~FindConnectConcept(void)
	{
	}

	vector<shared_ptr<Concept>> FindConnectConcept::FindForward( const shared_ptr<Concept> concept )
	{
		_existedIdentity.clear();

		_initialConcept=concept;
		vector<shared_ptr<Concept>> res;
		Record(concept);
		Recursive_Find(concept,Forward,res);

		return res;
	}

	vector<shared_ptr<Concept>> FindConnectConcept::FindBackward( const shared_ptr<Concept> concept )
	{
		_existedIdentity.clear();

		_initialConcept=concept;
		vector<shared_ptr<Concept>> res;
		Record(concept);
		Recursive_Find(concept,Backward,res);

		return res;
	}

	bool FindConnectConcept::ConceptExist( const shared_ptr<Concept> concept ) const
	{
		Identity identity;
		identity.str=concept->GetString();
		identity.id=concept->GetId();

		multimap<string,int>::const_iterator it_low=_existedIdentity.lower_bound(identity.str);
		if(it_low==_existedIdentity.end())
		{
			return false;
		}

		multimap<string,int>::const_iterator it_up=_existedIdentity.upper_bound(identity.str);
		while(it_low!=it_up)
		{
			if(it_low->second==identity.id)
			{
				return true;
			}
		}

		return false;
	}

	void FindConnectConcept::Record( const shared_ptr<Concept> concept )
	{
		string str=concept->GetString();
		int id=concept->GetId();

		_existedIdentity.insert(make_pair(str,id));
	}

	void FindConnectConcept::Recursive_Find( const shared_ptr<Concept> concept,const SearchDir dir, vector<shared_ptr<Concept>>& connectConcepts )
	{	
		if(!ConceptExist(concept))
		{
			connectConcepts.push_back(concept);
			Record(concept);
		}

		vector<shared_ptr<Concept>> adjConcepts;
		if(dir==Forward)
		{
			adjConcepts=concept->GetForwardConcepts();
		}
		else
		{
			adjConcepts=concept->GetBackwardConcepts();
		}

		for (unsigned int i=0;i<adjConcepts.size();++i)
		{
			//·ÀÖ¹±Õ»·
			if(adjConcepts[i]->Same(_initialConcept))
			{
				continue;
			}

			Recursive_Find(adjConcepts[i],dir,connectConcepts);
		}
	}


}

