#include "StdAfx.h"
#include "CommonFunction.h"
#include "Concept.h"
#include "ConceptInteractTable.h"

namespace Mind
{
	namespace CommonFunction
	{

		void AppendToInteractTable( const vector<shared_ptr<Concept>>& from,const vector<shared_ptr<Concept>>& to,shared_ptr<ConceptInteractTable> table )
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

		int IndexOf( const vector<shared_ptr<Concept>>& concepts,const shared_ptr<Concept> concept )
		{
			class IsSameWith
			{
				shared_ptr<Concept> _val;
			public:
				IsSameWith(const shared_ptr<Concept> val):_val(val){};
				~IsSameWith(){}

				bool operator()(const shared_ptr<Concept> val)
				{
					if(CommonFunction::IsSameConcept(_val,val))
					{
						return true;
					}
					else
						return false;
				}
			};

			vector<shared_ptr<Concept>>::const_iterator iter=find_if(concepts.begin(),concepts.end(),IsSameWith(concept));
			if(iter==concepts.end())
			{
				return -1;
			}
			else
			{
				return distance(concepts.begin(),iter);
			}
		}


		bool IsSameConcept( const shared_ptr<Concept> left,const shared_ptr<Concept> right )
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

		void WriteConcepts(const vector<shared_ptr<Concept>>& vec,ofstream& out )
		{
			for (unsigned int j=0;j<vec.size();++j)
			{
				out<<vec[j]->GetString()<<" ";
			}
			out<<endl;
		}

		bool SameConcept::operator()( const shared_ptr<Concept> val )
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

