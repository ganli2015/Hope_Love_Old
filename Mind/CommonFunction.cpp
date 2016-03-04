#include "StdAfx.h"
#include "CommonFunction.h"
#include "Concept.h"
#include "ConceptInteractTable.h"

#include <fstream>
#include <sstream>

#include "../CommonTools/CommonStringFunction.h"

#include "../DataCollection/Word.h"
#include "../DataCollection/DataBaseProcessorTool.h"

using namespace DataCollection;

namespace Mind
{
	namespace CommonFunction
	{
		vector<Connection_Info> InputConnectionFromFile( string filename )
		{
			ifstream in(filename);
			vector<Connection_Info> res;
			string str;
			while(getline(in,str))
			{
				vector<string> split=CommonTool::SplitString(str,' ');

				if(split.size()<2)
				{
					throw logic_error("Error in InputConnectionFromFile");
				}

				Connection_Info connnection_info;
				//��ȡ��ǰ��word��id
				connnection_info.me=TransformToIdentity(split[0],split[1]);

				if(split.size()==2)//û��ConceptEdge�ͼ����¸�ѭ��
				{
					res.push_back(connnection_info);
					continue;
				}

				//��ȡEdge
				int index=2;//��ʼ���������string
				while(true)
				{
					if(split[index]!="to")
					{
						throw runtime_error("Error in InputConnectionFromFile");
					}
					else
					{
						index++;
					}

					//��ȡ������word����id
					Edge_Info edge_info;
					edge_info.to=TransformToIdentity(split[index],split[index+1]);
					index+=2;

					//��ȡ���δ�
					vector<string>::iterator find_next_to=find(split.begin()+index,split.end(),"to");
					if(distance(split.begin()+index,find_next_to)%2!=0)//string�ĸ���������ż������Ϊword��id���ǳɶԳ���
					{
						throw runtime_error("Error in InputConnectionFromFile");
					}
					vector<Identity> modifications;
					for (vector<string>::iterator it=split.begin()+index;it!=find_next_to;it+=2)
					{
						modifications.push_back(TransformToIdentity(*it,*(it+1)));
					}
					edge_info.modifications=modifications;

					connnection_info.edge_infos.push_back(edge_info);

					if(find_next_to==split.end())
					{
						break;
					}

					index+=distance(split.begin()+index,find_next_to);//�ƶ�index����һ��to��λ�á�
				}

				res.push_back(connnection_info);
			}

			return res;
		}

		

		Mind::Identity TransformToIdentity( const string idStr,const string wordStr )
		{
			stringstream ss(idStr);//ԭ��string����������ת��

			int id_me;
			ss>>id_me;
// 			if(!ss.good())
// 			{
// 				throw runtime_error("Error in TransformToWordID");
// 			}
			Identity me;
			me.id=id_me;
			me.str=wordStr;

			return me;
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

		void WriteConcepts(const vector<shared_ptr<Concept>>& vec,ofstream& out )
		{
			for (unsigned int j=0;j<vec.size();++j)
			{
				out<<vec[j]->GetString()<<" ";
			}
			out<<endl;
		}

		

	}
}
