#pragma once
#include "InOut.h"
#include "ConceptChain.h"

namespace NeuralNetwork
{
	class iDataArray;
	class iNeuron;
	class Network;
}

namespace Mind
{
	class ConceptSet;

	class ConceptReactSystem
	{
	private:
		struct DataInfo
		{
			shared_ptr<ConceptChain> input;
			shared_ptr<ConceptChain> expect;
		};
		struct ConceptInfo
		{
			//根据神经网络转化计算出来的向量序号对应的Concept。
			shared_ptr<Concept> concept;
			//根据神经网络转化计算出来的向量序号对应的数值。
			double arrayComponent;
		};

		const char ioTag;
		const char conceptTag;
		const char idStrTag;

		ConceptSet* _conceptSet;
		shared_ptr<NeuralNetwork::Network> _network;
	public:
		ConceptReactSystem(ConceptSet* val);
		~ConceptReactSystem(void);

		vector<ConceptChainProperty> React(const shared_ptr<ConceptChain> chain);

	private:
		void Initialize();
		void InitNetworkFromFile();
		void BasicTrainNetwork();

		shared_ptr<ConceptChain> ParseChain(const string str) const;
		shared_ptr<NeuralNetwork::iDataArray> ToDataArray(const shared_ptr<ConceptChain> chain) const;

		void Train(const vector<DataInfo>& dataInfos);
		shared_ptr<NeuralNetwork::iNeuron> ConceptReactSystem::InitNeuron(const int dimension);
		double ConceptReactSystem::ComputeStandardDeviation(const DataInfo& data,shared_ptr<NeuralNetwork::Network> network);

		//找出array中小于等于upVal同时大于等于lowVal的数值，并且根据该数值的序号查找相应的Concept
		vector<ConceptReactSystem::ConceptInfo> ExtractConceptInfo(const shared_ptr<NeuralNetwork::iDataArray> array,
			const double upVal,const double lowVal);
		vector<vector<ConceptReactSystem::ConceptInfo>> ExtractConceptInfoSequence(const shared_ptr<NeuralNetwork::iDataArray> array);
		void NormalizeConfidence(vector<ConceptChainProperty>& vec);

	private:
		class GenerateChainProperties
		{
			vector<ConceptChainProperty> _result;
		public:
			void operator()(const vector<ConceptInfo>& combination);
			vector<ConceptChainProperty> GetResult(){return _result;}
		};
	};

	
}


