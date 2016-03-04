#include "StdAfx.h"
#include <typeinfo>

#include "CompetitiveNetwork.h"
#include "TransferFunctions.h"
#include "Neuron_compet.h"
#include "Errors.h"
#include "../Mathmatic/iMatrix.h"

namespace NeuralNetwork
{
	using namespace TransferFunction;

	int find_nonzero_index(const shared_ptr<iDataArray> array);

	CompetitiveNetwork::~CompetitiveNetwork(void)
	{
	}

	void CompetitiveNetwork::SetMyNeuron( const shared_ptr<MyNeuron>& myNeuron )
	{
		shared_ptr<fun> myfun(new compet());
		myNeuron->SetFun(myfun);
		SetNeuron(0,myNeuron);
	}

	TrainResult CompetitiveNetwork::Training()
	{
		TrainResult result=Success;

		int iteration(0);//max iteration number
		train_CompetitiveNetwork mytrain(_neurons[0],_learningRate);
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

// 	shared_ptr<Network::ActualOutput> CompetitiveNetwork::GetResult( const shared_ptr<Network::ProtoPattern>& in )
// 	{
// 		Math::Matrix mat=_neurons[0]->GetMatrix();
// 		shared_ptr<iNeuron> neu(new Neuron(mat));
// 		neu->SetFun(shared_ptr<fun>(new purelin));
// 		SetNeuron(0,neu);
// 		return ForwardPropagation(in,_neurons);
// 	}


	void train_CompetitiveNetwork::operator()( shared_ptr<typename Network::MyData> mydata )
	{
		shared_ptr<iDataArray> proto=mydata->proto;
		shared_ptr<iDataArray> tmpoutput=_myneuron->Process(proto);
		int dominant_index=find_nonzero_index(tmpoutput);
		Math::Vector vec_wj=_myneuron->Get_jthColumn(dominant_index);
		shared_ptr<iDataArray> cur_wj(new DataArray(vec_wj));//w_j_q-1
		shared_ptr<iDataArray> ee=proto->Subtract(cur_wj);//p-w_j_q-1

		if(!ee->AllZero())//if the error array is not zeroes
			welltrained=false;
		else return;

		Math::Vector e=ee->GetArray();

		//w_j_q=w_j_q-1+alpha*a_i_q*(p-w_j_q-1)
		Math::Vector newColum=vec_wj+_learningRate*e;
		_myneuron->Set_jthColumn(dominant_index,newColum);

		neuron_changed=true;
	}

	int find_nonzero_index(const shared_ptr<iDataArray> array)
	{
		for (unsigned int i=0;i<array->Dimension();++i)
		{
			if(Math::DoubleCompare(array->Get_ithVal(i),0)!=0)
			{
				return i;
			}
		}
		assert(false&&"error in computing the competitive function!");
		throw runtime_error("error in computing the competitive function!");
	}
}

