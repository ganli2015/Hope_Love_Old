#include "StdAfx.h"
#include "CommonFunction.h"

#include "iConceptInteractTable.h"
#include "iCerebrum.h"
#include "iConcept.h"
#include "iConceptInteractTable.h"
#include "iConceptChain.h"

#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/Word.h"

using namespace DataCollection;

namespace Mind
{
	namespace CommonFunction
	{

		void AppendToInteractTable( const vector<shared_ptr<iConcept>>& from,const vector<shared_ptr<iConcept>>& to,shared_ptr<iConceptInteractTable> table )
		{
			if(table==NULL) return;

			for (unsigned int i=0;i<from.size();++i)
			{
				for (unsigned int j=0;j<to.size();++j)
				{
					table->Add(from[i],to[j]);
				}
			}
		}

		int IndexOf( const vector<shared_ptr<iConcept>>& concepts,const shared_ptr<iConcept> concept )
		{
			class IsSameWith
			{
				shared_ptr<iConcept> _val;
			public:
				IsSameWith(const shared_ptr<iConcept> val):_val(val){};
				~IsSameWith(){}

				bool operator()(const shared_ptr<iConcept> val)
				{
					if(CommonFunction::IsSameConcept(_val,val))
					{
						return true;
					}
					else
						return false;
				}
			};

			vector<shared_ptr<iConcept>>::const_iterator iter=find_if(concepts.begin(),concepts.end(),IsSameWith(concept));
			if(iter==concepts.end())
			{
				return -1;
			}
			else
			{
				return distance(concepts.begin(),iter);
			}
		}


		bool IsSameConcept( const shared_ptr<iConcept> left,const shared_ptr<iConcept> right )
		{
			if(left->GetString()==right->GetString() && left->GetId()==right->GetId())
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void WriteConcepts(const vector<shared_ptr<iConcept>>& vec,ofstream& out )
		{
			for (unsigned int j=0;j<vec.size();++j)
			{
				out<<vec[j]->GetString()<<" ";
			}
			out<<endl;
		}

		bool SameConcept::operator()( const shared_ptr<iConcept> val )
		{
			if(val->Same(_me))
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void RemoveSameChain( vector<shared_ptr<iConceptChain>>& chains ) 
		{
			vector<shared_ptr<iConceptChain>> removedChains;

			for (unsigned int i=0;i<chains.size();++i)
			{
				shared_ptr<iConceptChain> curChain=chains[i];

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

		double ComputeP_GrammarLocalAnalysis( const DataCollection::GrammarPattern& pattern )
		{
			iCerebrum* brain=iCerebrum::Instance();

			vector<PartOfSpeech> poses=pattern.GetPattern();
			//去除标点
			for (vector<PartOfSpeech>::iterator it=poses.begin();it!=poses.end();)
			{
				if(*it==Puncture)
				{
					it=poses.erase(it);
				}
				else
				{
					++it;
				}
			}

			if(poses.size()<=1) return 0.;

			double res=0.;
			for (unsigned int i=0;i<poses.size();++i)
			{
				PartOfSpeech curPos=poses[i];
				if(i==0)//第一个词性只考虑与第二个词性之间的置信度.
				{
					double p_cur_for=brain->GetP_Forward(curPos,poses[i+1]);
					double p_for_cur=brain->GetP_Backward(poses[i+1],curPos);
					res+=p_for_cur*p_cur_for;
				}
				else if(i==poses.size()-1)//最后一个词性只考虑与倒数第二个之间的置信度.
				{
					double p_cur_back=brain->GetP_Backward(curPos,poses[i-1]);
					double p_back_cur=brain->GetP_Forward(poses[i-1],curPos);
					res+=p_back_cur*p_cur_back;
				}
				else
				{
					res+=ComputeP_GrammarLocal(curPos,poses[i+1],poses[i-1]);
				}
			}

			return res/poses.size();
		}

		double ComputeP_GrammarLocal( const PartOfSpeech& curPos,const PartOfSpeech& forwardPos,const PartOfSpeech& backwardPos )
		{
			iCerebrum* brain=iCerebrum::Instance();

			double p_cur_for=brain->GetP_Forward(curPos,forwardPos);
			double p_cur_back=brain->GetP_Backward(curPos,backwardPos);
			double p_for_cur=brain->GetP_Backward(forwardPos,curPos);
			double p_back_cur=brain->GetP_Forward(backwardPos,curPos);


			return (p_cur_for*p_for_cur+p_cur_back*p_back_cur)/2;
		}

		void OutputConceptPairs( const vector<MindType::ConceptPair>& pairs,ostream& out )
		{
			for (unsigned int i=0;i<pairs.size();++i)
			{
				out<<pairs[i].first->GetString();
				out<<" ";
				out<<pairs[i].second->GetString();
				out<<endl;
			}
		}

	}
}




