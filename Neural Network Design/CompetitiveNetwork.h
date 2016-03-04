#pragma once
#include "Stdafx.h"
#include "InOut.h"
#include "Network.h"

namespace NeuralNetwork
{
	class _NEURALNETWORKDESIGNINOUT CompetitiveNetwork : public Network
	{
	public:
		CompetitiveNetwork(const int i, const int j):_learningRate(0.1),_i(i),_j(j){};
		~CompetitiveNetwork(void);

		typedef  iNeuron MyNeuron;

		//Set the Neuron whose input dimension is i and output dimension is j.
		//The transfer function used is Compet!
		void SetMyNeuron(const shared_ptr<MyNeuron>& myNeuron);

		void SetLearningRate(const double val){_learningRate=val;}

		TrainResult Training();

		virtual int GetOutputDimension() const {return _j;};
		virtual int GetInputDimension() const {return _i;};

		//virtual shared_ptr<Network::ActualOutput> GetResult(const shared_ptr<Network::ProtoPattern>& in);

	private:
		double _learningRate;
		const int _i;
		const int _j;
	};



	//Function Object:
	//CompetitiveNetwork training
	class train_CompetitiveNetwork
	{
		typedef CompetitiveNetwork::MyNeuron MyNeuron;
		shared_ptr<typename MyNeuron> _myneuron;
		double _learningRate;
		bool welltrained;
		bool neuron_changed;
	public:
		train_CompetitiveNetwork(const shared_ptr<MyNeuron> myNeuron,const double learnrate):
		  _myneuron(myNeuron),_learningRate(learnrate),
			  welltrained(true),neuron_changed(false){}
		  ~train_CompetitiveNetwork(){}

		  shared_ptr<typename MyNeuron> GetResult()const {return _myneuron;};
		  //Whether all errors are zero
		  bool TrainFinished()const {return welltrained;}
		  //Whether the neuron is changed after one iteration
		  bool NeuronChanged() const {return neuron_changed;}
		  void SetNeuronState(bool changestate){neuron_changed=changestate;}

		  void operator()(shared_ptr<typename Network::MyData>  mydata);
	};
}


