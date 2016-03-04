#pragma once
#include "InOut.h"
#include "Network.h"

namespace NeuralNetwork
{
	class fun;

	//i,j count from 1.
	class _NEURALNETWORKDESIGNINOUT Perceptron: public Network
	{
	public:
		Perceptron(const int i,const int j);
		~Perceptron(){}

		typedef iNeuron MyNeuron;

		//Set the Neuron whose input dimension is i and output dimension is j.
		//The transfer function used is HardLim!
		void SetMyNeuron(const shared_ptr<MyNeuron>& myNeuron);

		TrainResult Training();

		virtual int GetOutputDimension() const {return _j;};
		virtual int GetInputDimension() const {return _i;};

	private:

		const int _i;
		const int _j;

	};

	//Function Object:
	//perceptron training
	class train_perceptron
	{
		typedef Perceptron::MyNeuron MyNeuron;
		shared_ptr<typename MyNeuron> _myneuron;
		bool welltrained;
		bool neuron_changed;
	public:
		train_perceptron(const shared_ptr<MyNeuron> myNeuron):_myneuron(myNeuron),welltrained(true),neuron_changed(false){}
		~train_perceptron(){}

		shared_ptr<typename MyNeuron> GetResult()const {return _myneuron;};
		//Whether all errors are zero
		bool TrainFinished()const {return welltrained;}
		//Whether the neuron is changed after one iteration
		bool NeuronChanged() const {return neuron_changed;}
		void SetNeuronState(bool changestate){neuron_changed=changestate;}

		void operator()(shared_ptr<typename Network::MyData>  mydata);
	};
}