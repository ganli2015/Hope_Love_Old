#include "StdAfx.h"
#include "Perceptron.h"
#include "TransferFunctions.h"
#include "Neuron.h"
#include "Errors.h"

namespace NeuralNetwork
{
	using namespace TransferFunction;

	NeuralNetwork::Perceptron::Perceptron( const int i,const int j ) :_i(i),_j(j)
	{

	}

	void NeuralNetwork::Perceptron::SetMyNeuron( const shared_ptr<MyNeuron>& myNeuron )
	{
		shared_ptr<TransferFunction::fun> myfun(new hardlim());
		myNeuron->SetFun(myfun);
		SetNeuron(0,myNeuron);
	}

	TrainResult NeuralNetwork::Perceptron::Training()
	{
		TrainResult result=Success;

		int iteration(0);//max iteration number
		//for_each(_mydata.begin(),_mydata.end(),initialize<i,j,MyNeuron>(myNeuron));//initialize actual output for computing the first errors.
		train_perceptron mytrain(_neurons[0]);
		do 
		{
			mytrain.SetNeuronState(false);
			mytrain=for_each(_mydata.begin(),_mydata.end(),mytrain);

			if(++iteration>_maxiter)
			{
				result=Max_Reached;
				break;
			}

		} while (mytrain.NeuronChanged());//If the neuron is changed after one iteration, process the proto patterns again to make sure that all errors are zero!

		_neurons[0]=mytrain.GetResult();
		hasTrained=true;
		return result;
	}

	void train_perceptron::operator()( shared_ptr<typename Network::MyData> mydata )
	{
		shared_ptr<iDataArray> proto=mydata->proto;
		shared_ptr<iDataArray> expec=mydata->expec;
		shared_ptr<iDataArray> tmpoutput=_myneuron->Process(proto);
		shared_ptr<iDataArray> ee=expec->Subtract(tmpoutput);

		if(!ee->AllZero())//if the error array is not zeroes
			welltrained=false;
		else return;

		DataArray e=*dynamic_pointer_cast<DataArray>(ee);

		//Wi_new=Wi_old+Ei*P
		for (unsigned int n=0;n<_myneuron->GetOutputDimension();++n)
		{
			Math::Vector newColumn=_myneuron->Get_jthColumn(n)+e[n]*(proto->GetArray());
			_myneuron->Set_jthColumn(n,newColumn);
			double newbias=_myneuron->GetBias().Get_ithVal(n)+e[n];
			_myneuron->Set_jthBias(n,newbias);
		}

		neuron_changed=true;
	}

}


