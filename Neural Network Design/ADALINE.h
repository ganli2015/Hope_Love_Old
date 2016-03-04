#pragma once
#include "InOut.h"
#include "Network.h"

namespace NeuralNetwork
{
	class _NEURALNETWORKDESIGNINOUT ADALINE : public Network
	{
	public:
		ADALINE(const int i, const int j):_learningRate(0.1),_i(i),_j(j){}
		~ADALINE(){}

		typedef  iNeuron MyNeuron;

		//Set the Neuron whose input dimension is i and output dimension is j.
		//The transfer function used is PureLin!
		void SetMyNeuron(const shared_ptr<MyNeuron>& myNeuron);

		void SetLearningRate(const double val){_learningRate=val;}

		TrainResult Training();

		virtual int GetOutputDimension() const {return _j;};
		virtual int GetInputDimension() const {return _i;};

	private:

		double _learningRate;
		const int _i;
		const int _j;

	};


	//Function Object:
	//ADALINE training
	class train_ADALINE
	{
		typedef ADALINE::MyNeuron MyNeuron;
		shared_ptr<typename MyNeuron> _myneuron;
		double _learningRate;
		bool neuron_changed;

	public:
		train_ADALINE(const shared_ptr<MyNeuron> myNeuron,const double learnrate):
		  _myneuron(myNeuron),_learningRate(learnrate),neuron_changed(false){}
		~train_ADALINE(){}

		shared_ptr<typename MyNeuron> GetResult()const {return _myneuron;};
		//Whether all errors are zero
		//Whether the neuron is changed after one iteration
		bool NeuronChanged() const {return neuron_changed;}
		void SetNeuronState(bool changestate){neuron_changed=changestate;}

		void operator()(shared_ptr<typename Network::MyData>  mydata);
	};
}

