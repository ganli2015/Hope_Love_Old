#pragma once
#include "InOut.h"
#include "../MindElement/ConceptChain.h"

namespace NeuralNetwork
{
	class iDataArray;
	class iNeuron;
	class Network;
}

namespace Mind
{
	class ConceptSet;
	class iConcept;

	class ConceptReactSystem : public Obj<ConceptReactSystem>
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
			shared_ptr<iConcept> concept;
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

		vector<ConceptChainProperty> React(const shared_ptr<iConceptChain> chain);

	private:
		void Initialize();
		void InitNetworkFromFile();
		void BasicTrainNetwork();
		///Check whether <baseConceptCount> is the same as the input dimension of network in file <in>.
		///Only consider the input dimension of the first neuron.
		bool SameInputDimension(const int baseConceptCount, ifstream& in);

		shared_ptr<ConceptChain> ParseChain(const string str) const;

		void Train(const vector<DataInfo>& dataInfos);
		shared_ptr<NeuralNetwork::iNeuron> ConceptReactSystem::InitNeuron(const int i,const int j);
		double ConceptReactSystem::ComputeStandardDeviation(const DataInfo& data,shared_ptr<NeuralNetwork::Network> network);

		void NormalizeConfidence(vector<ConceptChainProperty>& vec);

	private:
		
	};

	
}


