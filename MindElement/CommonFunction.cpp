#include "StdAfx.h"
#include "CommonFunction.h"
#include "ConceptInteractTable.h"

#include "../MindInterface/iConcept.h"
#include "../MindInterface/iConceptInteractTable.h"

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

	}
}

