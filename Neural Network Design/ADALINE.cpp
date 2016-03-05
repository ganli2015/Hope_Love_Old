#include "StdAfx.h"
#include "ADALINE.h"
#include "TransferFunctions.h"
#include "Neuron.h"
#include "Errors.h"

namespace NeuralNetwork
{

	using namespace TransferFunction;

	void NeuralNetwork::ADALINE::SetMyNeuron( const shared_ptr<MyNeuron>& myNeuron )
	{
		shared_ptr<fun> myfun(new purelin());
		myNeuron->SetFun(myfun);
		SetNeuron(0,myNeuron);
	}

	TrainResult NeuralNetwork::ADALINE::Training()
	{
		TrainResult result=Success;

		int iteration(0);//max iteration number
		//for_each(_mydata.begin(),_mydata.end(),initialize<i,j,MyNeuron>(myNeuron));//initialize actual output for computing the first errors.
		train_ADALINE mytrain(_neurons[0],_learningRate);
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


	void train_ADALINE::operator()( shared_ptr<typename Network::MyData> mydata )
	{
		neuron_changed=false;

		shared_ptr<iDataArray> proto=mydata->proto;
		shared_ptr<iDataArray> expec=mydata->expec;
		shared_ptr<iDataArray> tmpoutput=_myneuron->Process(proto);
		shared_ptr<iDataArray> ee=expec->Subtract(tmpoutput);

		if(ee->AllZero())//if the error array is zeroes
			return;

		DataArray e=*dynamic_pointer_cast<DataArray>(ee);

		//Wi_new=Wi_old+2*alpha*Ei*P
		//b_new=b_old+2*alpha*Ei
		for (unsigned int n=0;n<_myneuron->GetOutputDimension();++n)
		{
			Math::Vector newColumn=_myneuron->Get_jthColumn(n)+2*_learningRate*e[n]*(proto->GetArray());
			_myneuron->Set_jthColumn(n,newColumn);
			double newbias=_myneuron->GetBias().Get_ithVal(n)+2*_learningRate*e[n];
			_myneuron->Set_jthBias(n,newbias);
		}

		neuron_changed=true;
	}

}
