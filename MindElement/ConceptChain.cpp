#include "StdAfx.h"
#include "ConceptChain.h"

#include "../MindInterface/iConcept.h"

namespace Mind
{
	ConceptChain::ConceptChain(void)
	{
	}

	ConceptChain::ConceptChain( const vector<shared_ptr<iConcept>>& val ):_chain(val.begin(),val.end())
	{

	}


	ConceptChain::~ConceptChain(void)
	{
	}

	vector<shared_ptr<iConcept>> ConceptChain::GetConceptVec() const
	{
		return vector<shared_ptr<iConcept>>(_chain.begin(),_chain.end());
	}

	void ConceptChain::Append( const shared_ptr<iConceptChain> chain )
	{
		vector<shared_ptr<iConcept>> vec=chain->GetConceptVec();
		_chain.insert(_chain.end(),vec.begin(),vec.end());
	}

	shared_ptr<iConceptChain> ConceptChain::Copy() const
	{		
		shared_ptr<ConceptChain> res(new ConceptChain(GetConceptVec()));

		return res;
	}

	bool ConceptChain::Same( const shared_ptr<iConceptChain> chain ) const
	{
		Sequence otherSeq=chain->GetConceptVec();
		Sequence mySeq=GetConceptVec();

		for (Sequence::const_iterator it1=mySeq.begin(),it2=otherSeq.begin();
			it1!=mySeq.end(),it2!=otherSeq.end();++it1,++it2)
		{
			if(!(*it1)->Same(*it2))
			{
				return false;
			}
		}

		return true;
	}

	bool ConceptChain::IsPartChainOf( const shared_ptr<iConceptChain> parentChain ) const
	{
		vector<shared_ptr<iConcept>> P=GetConceptVec();
		vector<shared_ptr<iConcept>> T=parentChain->GetConceptVec();

		unsigned int n=T.size();
		unsigned int m=P.size();
		vector<int> pi=ComputePrefixFunction(P);

		int q=0;
		for (unsigned int i=0;i<n;++i)
		{
			while(q>0 && !P[q]->Same(T[i]))
			{
				q=pi[q-1];
			}
			if(P[q]->Same(T[i]))
			{
				q++;
			}

			if(q==m)
			{
				return true;
			}
		}

		return false;
	}

	vector<int> ConceptChain::ComputePrefixFunction( const vector<shared_ptr<iConcept>> P) const
	{
		vector<int> res;
		int m=P.size();
		res.reserve(m);

		res.push_back(0);
		int k=0;
		for(int q=1;q<m;++q)
		{
			while(k>0 && !P[k]->Same(P[q]))
			{
				k=res[k-1];
			}
			if(P[k]->Same(P[q]))
			{
				k++;
			}
			res.push_back(k);
		}

		return res;
	}

	bool ConceptChain::IsSubSequenceOf( const shared_ptr<iConceptChain> parentChain ) const
	{
		vector<shared_ptr<iConcept>> sub=GetConceptVec();
		vector<shared_ptr<iConcept>> full=parentChain->GetConceptVec();

		if(sub.empty()) return true;
		if(full.empty()) return false;

		unsigned int subIndex(0);
		shared_ptr<iConcept> curElem=sub[subIndex];
		for (unsigned int i=0;i<full.size();++i)
		{
			if(curElem->Same(full[i]))
			{
				if(++subIndex<sub.size())
				{
					curElem=sub[subIndex];
				}
				else
				{
					return true;
				}
			}
		}

		return false;
	}

	bool ConceptChain::Contain( const shared_ptr<iConcept> concept ) const
	{
		for (list<shared_ptr<iConcept>>::const_iterator it=_chain.begin();it!=_chain.end();++it)
		{
			if(concept->Same(*it))
			{
				return true;
			}
		}

		return false;
	}

}

