#include "StdAfx.h"
#include "CommonFunction.h"
#include "../MindElement/Concept.h"
#include "../MindElement/ConceptInteractTable.h"
#include "ConceptSet.h"
#include "../MindElement/ConceptChain.h"
#include "Cerebrum.h"
#include "../MindElement/BaseConcept.h"

#include <fstream>
#include <sstream>

#include "../CommonTools/CommonStringFunction.h"

#include "../DataCollection/Word.h"
#include "../DataCollection/DataBaseProcessorTool.h"
#include "../DataCollection/GrammaPattern.h"

#include "../Neural Network Design/DataArray.h"

using namespace DataCollection;
using namespace Math;
using namespace NeuralNetwork;

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
				//读取当前的word和id
				connnection_info.me=TransformToIdentity(split[0],split[1]);

				if(split.size()==2)//没有ConceptEdge就继续下个循环
				{
					res.push_back(connnection_info);
					continue;
				}

				//读取Edge
				int index=2;//开始遍历后面的string
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

					//读取依赖的word及其id
					Edge_Info edge_info;
					edge_info.to=TransformToIdentity(split[index],split[index+1]);
					index+=2;

					//读取修饰词
					vector<string>::iterator find_next_to=find(split.begin()+index,split.end(),"to");
					if(distance(split.begin()+index,find_next_to)%2!=0)//string的个数必须是偶数，因为word和id总是成对出现
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

					index+=distance(split.begin()+index,find_next_to);//移动index到下一个to的位置。
				}

				res.push_back(connnection_info);
			}

			return res;
		}

		

		Mind::Identity TransformToIdentity( const string idStr,const string wordStr )
		{
			stringstream ss(idStr);//原来string与其他类型转换

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

		shared_ptr<NeuralNetwork::iDataArray> ToDataArray( const shared_ptr<ConceptChain> chain , const ConceptSet* conceptSet)
		{
			//初始化，所有元素等于0
			shared_ptr<iDataArray> res(new DataArray(conceptSet->BaseConceptCount()));

			vector<shared_ptr<iConcept>> conceptSequence=chain->GetConceptVec();
			for (unsigned int i=0;i<conceptSequence.size();++i)
			{
				shared_ptr<BaseConcept> base=dynamic_pointer_cast<BaseConcept>(conceptSequence[i]);
				if(base==NULL)
				{
					throw runtime_error("Error in ToDataArray");
				}

				res->Set_ithVal(base->GetBaseId(),i+1);
			}

			return res;
		}

		double ComputeP_GrammarLocalAnalysis( const DataCollection::GrammarPattern& pattern )
		{
			Cerebrum* brain=Cerebrum::Instance();

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

		double _MINDINOUT ComputeP_GrammarLocal( const PartOfSpeech& curPos,const PartOfSpeech& forwardPos,const PartOfSpeech& backwardPos )
		{
			Cerebrum* brain=Cerebrum::Instance();

			double p_cur_for=brain->GetP_Forward(curPos,forwardPos);
			double p_cur_back=brain->GetP_Backward(curPos,backwardPos);
			double p_for_cur=brain->GetP_Backward(forwardPos,curPos);
			double p_back_cur=brain->GetP_Forward(backwardPos,curPos);


			return (p_cur_for*p_for_cur+p_cur_back*p_back_cur)/2;
		}

	}
}
