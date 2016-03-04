#pragma once
#include "InOut.h"
#include "Network.h"

namespace Math
{
	class Matrix;
}

namespace NeuralNetwork
{
	namespace TransferFunction
	{
		class fun;
	}

	//i,j count from 1.
	class _NEURALNETWORKDESIGNINOUT MultilayerNetwork : public Network
	{
	public:
		MultilayerNetwork(const int i, const int j);
		~MultilayerNetwork(){}

		typedef std::map<int,shared_ptr<iNeuron>> MyNeurons;

		//Set the Neuron whose input dimension is s and output dimension is t.
		void SetMyNeuron(const int index,const shared_ptr<iNeuron>& myNeuron);

		TrainResult Training();

		void SetLearningRate(const double val){_learningRate=val;}

		virtual int GetOutputDimension() const {return _j;};
		virtual int GetInputDimension() const {return _i;};

	private:
		double _learningRate;
		const int _i;
		const int _j;
	};


	//Object Function:
	class iDataArray;
	class DataArray;
	class train_MultiNetwork
	{
		typedef MultilayerNetwork::MyNeurons MyNeurons;
		MyNeurons _myNeurons;
		double _learningRate;
		bool neuron_changed;
		
		vector<double> _deviations;
	public:
		train_MultiNetwork(const MyNeurons myNeuron,const double learnrate):
		  _myNeurons(myNeuron),_learningRate(learnrate),
			  neuron_changed(false){}

		~train_MultiNetwork(){}

		MyNeurons GetResult()const {return _myNeurons;};
		//Whether the neuron is changed after one iteration
		bool NeuronChanged() const {return neuron_changed;}
		void SetNeuronState(bool changestate){neuron_changed=changestate;}
		vector<double> GetSampleDeviations() const {return _deviations;}
		void ClearDeviations() {_deviations.clear();}

		void operator()(shared_ptr<typename Network::MyData>  mydata);

	private:
		void ComputeActualOutAndIntermediateData(const shared_ptr<iDataArray> proto,
			shared_ptr<iDataArray>& actualOut, 
			vector<shared_ptr<iDataArray>>& n, //Transformed data derived by each neuron BEFORE using transfer function.
			vector<shared_ptr<iDataArray>>& a );//Actual input data BEFORE transformed.
		void train_MultiNetwork::ComputeSensitivity(const MyNeurons::reverse_iterator& neo_backward, 
			const shared_ptr<TransferFunction::fun> myFun,
			const DataArray& e, 
			const shared_ptr<iDataArray> n_m, 
			shared_ptr<iDataArray> s_m, shared_ptr<iDataArray>& s_m_next, shared_ptr<Math::Matrix>& mat_next);
		void train_MultiNetwork::AdjustNeuron(const shared_ptr<iDataArray> s_m, const shared_ptr<iDataArray> a_m_prev, shared_ptr<iNeuron> tmpNeu);
		void train_MultiNetwork::BackwardPropagation(const shared_ptr<iDataArray> ee, const vector<shared_ptr<iDataArray>>& n, const vector<shared_ptr<iDataArray>>& a );
	};


	
}
