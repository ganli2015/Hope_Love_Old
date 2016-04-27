#include "StdAfx.h"
#include "ConceptReactSystem.h"
#include "../MindElement/BaseConcept.h"
#include "ConceptSet.h"
#include "../MindElement/ConceptChain.h"
#include "FilePath.h"
#include "Cerebrum.h"
#include "CommonFunction.h"
#include "ConceptReactImp.h"
#include "ConceptReactImp_1234.h"
#include "ConceptReactImp_1212.h"

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

#include "../MindInterface/iConcept.h"

#include <numeric>


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
#ifdef _Train_Initial_React_Network
		BasicTrainNetwork();
#else
		InitNetworkFromFile();
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

		_network->Write(GetHopeLoveMindPath()+ConceptReactorNetworkFilename);
	}

	shared_ptr<ConceptChain> ConceptReactSystem::ParseChain( const string str ) const
	{
		vector<shared_ptr<iConcept>> conceptVec;
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

			shared_ptr<iConcept> concept=_conceptSet->GetConceptPtr(CommonFunction::TransformToIdentity(split[0],split[1]));
			conceptVec.push_back(concept);
		}

		return shared_ptr<ConceptChain>(new ConceptChain(conceptVec));
	}

	void ConceptReactSystem::Train( const vector<DataInfo>& dataInfos )
	{
		if(dataInfos.empty()) return;

		int dimension=_conceptSet->BaseConceptCount();
//		int interDim=30;
		shared_ptr<iNeuron> neu1=InitNeuron(dimension,dimension);
//		shared_ptr<iNeuron> neu2=InitNeuron(interDim,dimension);

// 		int interDim=50;
// 		shared_ptr<iNeuron> neu1(new Neuron(dimension,interDim));
// 		neu1->SetBias(Vector(interDim,0));
// 		shared_ptr<TransferFunction::fun> fun_logsig(new TransferFunction::purelin);
// 		neu1->SetFun(fun_logsig);
// 		shared_ptr<iNeuron> neu2(new Neuron(interDim,dimension));
// 		neu2->SetBias(Vector(dimension,0));
// 		neu2->SetFun(fun_logsig);

		shared_ptr<MultilayerNetwork> multiNetwork(new MultilayerNetwork(dimension,dimension));
		multiNetwork->SetMyNeuron(0,neu1);
//		multiNetwork->SetMyNeuron(1,neu2);

		for (unsigned int i=0;i<dataInfos.size();++i)
		{
			shared_ptr<iDataArray> proto=CommonFunction::ToDataArray(dataInfos[i].input,_conceptSet);
			shared_ptr<iDataArray> expect=CommonFunction::ToDataArray(dataInfos[i].expect,_conceptSet);
			multiNetwork->SetMyData(proto,expect);
		}
		multiNetwork->SetLearningRate(0.9);
		multiNetwork->SetMaxIterationCount(200);

		TrainResult result=	multiNetwork->Training();

		if(result!=Success)
		{
			vector<double> residuals;
			for (unsigned int i=0;i<dataInfos.size();++i)
			{
				residuals.push_back(ComputeStandardDeviation(dataInfos[i],multiNetwork));
			}
			double objFun=accumulate(residuals.begin(),residuals.end(),0.);
		}

		_network=multiNetwork;
	}

	shared_ptr<iNeuron> ConceptReactSystem::InitNeuron(const int i,const int j)
	{
		double randDouble=Rand::GetRandDecimal();

		shared_ptr<iNeuron> neu(new Neuron(CreateRandomMatrix(i,j)));
		//对随机的行列初始化随机的数值。
// 		int initElemCount=dimension*dimension/4;
// 		for (int i=0;i<initElemCount;++i)
// 		{
// 			int randRow=Rand::GetRandInt(0,dimension-1);
// 			int randCol=Rand::GetRandInt(0,dimension-1);
// 			neu->SetElem(randRow,randCol,Rand::GetRandDecimal());
// 		}

		shared_ptr<TransferFunction::fun> transferFun(new TransferFunction::purelin);
		neu->SetFun(transferFun);

		return neu;
	}

	double ConceptReactSystem::ComputeStandardDeviation(const DataInfo& data,shared_ptr<Network> network)
	{
		shared_ptr<iDataArray> output=network->GetResult(CommonFunction::ToDataArray(data.input,_conceptSet));
		shared_ptr<iDataArray> residual=output->Subtract(CommonFunction::ToDataArray(data.expect,_conceptSet));
		return residual->Norm();
	}

	vector<ConceptChainProperty> ConceptReactSystem::React( const shared_ptr<iConceptChain> chain )
	{
		shared_ptr<ConceptReactImp> reactImp(new ConceptReactImp_1212(_network,_conceptSet));
		return reactImp->Perform(chain);
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

	

}
