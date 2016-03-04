#include "StdAfx.h"
#include "BaseConcept.h"
#include "ConceptReactSystem.h"
#include "Concept.h"
#include "ConceptSet.h"
#include "ConceptChain.h"
#include "FilePath.h"
#include "Cerebrum.h"

#include "../CommonTools/CommonStringFunction.h"

#include "../Mathmatic/Rand.h"
#include "../Mathmatic/Vector.h"
#include "../Mathmatic/FindSequence.h"

#include "../Neural Network Design/DataArray.h"
#include "../Neural Network Design/Neuron.h"
#include "../Neural Network Design/TransferFunctions.h"
#include "../Neural Network Design/MultilayerNetwork.h"
#include "../Neural Network Design/ADALINE.h"
#include "../Neural Network Design/Errors.h"

#define _ReadFile

using namespace Math;
using namespace NeuralNetwork;
namespace Mind
{
	ConceptReactSystem::ConceptReactSystem(ConceptSet* val):ioTag('&'),conceptTag('#'),idStrTag(' '),_conceptSet(val)
	{
		Initialize();
	}

	ConceptReactSystem::~ConceptReactSystem(void)
	{
	}

	void ConceptReactSystem::Initialize()
	{
#ifdef _ReadFile
		InitNetworkFromFile();
#else
		BasicTrainNetwork();
#endif // _ReadFile
	}

	void ConceptReactSystem::InitNetworkFromFile()
	{
		int dimension=_conceptSet->BaseConceptCount();
		shared_ptr<MultilayerNetwork> multiNetwork(new MultilayerNetwork(dimension,dimension));
		_network=multiNetwork;
		_network->Read(GetHopeLoveMindPath()+ConceptReactorNetworkFilename);
	}

	void ConceptReactSystem::BasicTrainNetwork()
	{
		ifstream in(GetHopeLoveMindPath()+ConceptReactor_InitialFilename);

		vector<DataInfo> dataInfos;
		string str;
		while(getline(in,str))
		{
			vector<string> i_o=CommonTool::SplitString(str,ioTag);
			if(i_o.size()!=2)
			{
				throw logic_error("Error in ConceptReactSystem::Initialize");
			}

			shared_ptr<ConceptChain> chain_i=ParseChain(i_o[0]);
			shared_ptr<ConceptChain> chain_o=ParseChain(i_o[1]);
			DataInfo info;
			info.input=chain_i;
			info.expect=chain_o;
			dataInfos.push_back(info);
		}

		Train(dataInfos);

		_network->Write(GetHopeLoveMindPath()+"network.txt");
	}

	shared_ptr<ConceptChain> ConceptReactSystem::ParseChain( const string str ) const
	{
		vector<shared_ptr<Concept>> conceptVec;
		//解析为多个Identity
		vector<string> conceptStr=CommonTool::SplitString(str,conceptTag);
		for (unsigned int i=0;i<conceptStr.size();++i)
		{
			//解析每个Identity
			vector<string> split=CommonTool::SplitString(conceptStr[i],idStrTag);

			if(split.size()!=2)
			{
				throw logic_error("Error in ParseChain");
			}

			shared_ptr<Concept> concept=_conceptSet->GetConceptPtr(CommonFunction::TransformToIdentity(split[0],split[1]));
			conceptVec.push_back(concept);
		}

		return shared_ptr<ConceptChain>(new ConceptChain(conceptVec));
	}


	shared_ptr<NeuralNetwork::iDataArray> ConceptReactSystem::ToDataArray( const shared_ptr<ConceptChain> chain ) const
	{
		//初始化，所有元素等于0
		shared_ptr<iDataArray> res(new DataArray(_conceptSet->BaseConceptCount()));

		vector<shared_ptr<Concept>> conceptSequence=chain->GetConceptVec();
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

	void ConceptReactSystem::Train( const vector<DataInfo>& dataInfos )
	{
		if(dataInfos.empty()) return;

		int dimension=_conceptSet->BaseConceptCount();
		shared_ptr<iNeuron> neu=InitNeuron(dimension);

		shared_ptr<MultilayerNetwork> multiNetwork(new MultilayerNetwork(dimension,dimension));
		multiNetwork->SetMyNeuron(0,neu);

// 		shared_ptr<ADALINE> multiNetwork(new ADALINE(dimension,dimension));
// 		multiNetwork->SetMyNeuron(neu);

// 		shared_ptr<iNeuron> neu2=InitNeuron(dimension);
// 		shared_ptr<TransferFunction::purelin> fun_purelin(new TransferFunction::purelin);
// 		neu2->SetFun(fun_purelin);
// 		multiNetwork->SetMyNeuron(1,neu2);

		for (unsigned int i=0;i<dataInfos.size();++i)
		{
			shared_ptr<iDataArray> proto=ToDataArray(dataInfos[i].input);
			shared_ptr<iDataArray> expect=ToDataArray(dataInfos[i].expect);
			multiNetwork->SetMyData(proto,expect);
		}
		multiNetwork->SetLearningRate(0.03);
		multiNetwork->SetMaxIterationCount(200);

		TrainResult result=	multiNetwork->Training();

		if(result!=Success)
		{
			vector<double> residuals;
			for (unsigned int i=0;i<dataInfos.size();++i)
			{
				residuals.push_back(ComputeStandardDeviation(dataInfos[i],multiNetwork));
			}
		}

		_network=multiNetwork;
	}

	shared_ptr<iNeuron> ConceptReactSystem::InitNeuron(const int dimension)
	{
		double randDouble=Rand::GetRandDecimal();

		shared_ptr<iNeuron> neu(new Neuron(dimension,dimension));
		//对随机的行列初始化随机的数值。
// 		int initElemCount=dimension*dimension/4;
// 		for (int i=0;i<initElemCount;++i)
// 		{
// 			int randRow=Rand::GetRandInt(0,dimension-1);
// 			int randCol=Rand::GetRandInt(0,dimension-1);
// 			neu->SetElem(randRow,randCol,Rand::GetRandDecimal());
// 		}

		neu->SetBias(Vector(dimension,0));

		shared_ptr<TransferFunction::fun> fun_logsig(new TransferFunction::purelin);
		neu->SetFun(fun_logsig);

		return neu;
	}

	double ConceptReactSystem::ComputeStandardDeviation(const DataInfo& data,shared_ptr<Network> network)
	{
		shared_ptr<iDataArray> output=network->GetResult(ToDataArray(data.input));
		shared_ptr<iDataArray> residual=output->Subtract(ToDataArray(data.expect));
		return residual->Norm();
	}

	vector<ConceptChainProperty> ConceptReactSystem::React( const shared_ptr<ConceptChain> chain )
	{
		if(_network==NULL) return vector<ConceptChainProperty>();

		shared_ptr<iDataArray> input=ToDataArray(chain);
		shared_ptr<iDataArray> output=_network->GetResult(input);

		vector<vector<ConceptInfo>> conceptInfoSequence=ExtractConceptInfoSequence(output);
		//获得所有Concept序列的排列组合，每个组合的元素个数是相同的！
		vector<vector<ConceptInfo>> chainCombinations=GetAllCombinations<ConceptInfo>::Get(conceptInfoSequence);
		GenerateChainProperties generateResult;
		generateResult=for_each(chainCombinations.begin(),chainCombinations.end(),generateResult);

		vector<ConceptChainProperty> res= generateResult.GetResult();
		//NormalizeConfidence(res);

		return res;
	}

	vector<ConceptReactSystem::ConceptInfo> ConceptReactSystem::ExtractConceptInfo( const shared_ptr<iDataArray> array, const double upVal,const double lowVal )
	{
		vector<ConceptInfo> res;

		for (unsigned int i=0;i<array->Dimension();++i)
		{
			double component=array->Get_ithVal(i);
			if(component>upVal || component<=lowVal) continue;//不考虑超出界限的成分。

			//根据array的编号来获得Concept，因为array的第i个成分对应于id等于i的BaseConcept。
			shared_ptr<Concept> base=_conceptSet->GetBaseConcept(i);

			ConceptInfo info;
			info.concept=base;
			info.arrayComponent=component;
			res.push_back(info);
		}

		return res;
	}

	vector<vector<ConceptReactSystem::ConceptInfo>> ConceptReactSystem::ExtractConceptInfoSequence( const shared_ptr<iDataArray> array )
	{
		vector<vector<ConceptInfo>> conceptInfoSequence;
		//依次获得1、2、3、4...所对应的Concept以及数值，如果有个序号没有所对应的Concept，那么迭代终止。
		//这样保证了这个Concept序列是和自然数对应的。
		int seqIndex=1;
		while(true)
		{
			double validRegion=0.5;
			double upVal=seqIndex+validRegion;
			double lowVal=seqIndex-validRegion;

			vector<ConceptInfo> conceptInfos=ExtractConceptInfo(array,upVal,lowVal);
			if(conceptInfos.empty())
			{
				break;
			}

			conceptInfoSequence.push_back(conceptInfos);
			++seqIndex;
		}

		return conceptInfoSequence;
	}

	void ConceptReactSystem::NormalizeConfidence( vector<ConceptChainProperty>& vec )
	{
		vector<double> dev_unnormalized;
		dev_unnormalized.reserve(vec.size());
		for (unsigned int i=0;i<vec.size();++i)
		{
			dev_unnormalized.push_back(vec[i].confidence);
		}

		vector<double> dev_normalized=Normalized(dev_unnormalized);
		for (unsigned int i=0;i<dev_normalized.size();++i)
		{
			vec[i].confidence=dev_normalized[i];
		}
	}

	void ConceptReactSystem::GenerateChainProperties::operator()( const vector<ConceptInfo>& combination )
	{
		vector<shared_ptr<Concept>> conceptVec;
		conceptVec.reserve(combination.size());
		double variance=0.0;
		for (unsigned int i=0;i<combination.size();++i)
		{
			conceptVec.push_back(combination[i].concept);
			variance+=pow(combination[i].arrayComponent-(i+1),2);
		}

		ConceptChainProperty property;
		property.chain=shared_ptr<ConceptChain>(new ConceptChain(conceptVec));
		property.confidence=exp(-variance);
		_result.push_back(property);
	}

}
