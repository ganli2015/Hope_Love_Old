#include "StdAfx.h"
#include "MultilayerNetwork.h"
#include "iNeuron.h"
#include "DataArray.h"
#include "Errors.h"

#include "../Mathmatic/Vector.h"
#include "../Mathmatic/iMatrix.h"

namespace NeuralNetwork
{
	using namespace Math;

	MultilayerNetwork::MultilayerNetwork( const int i, const int j ):_learningRate(0.1),_i(i),_j(j)
	{

	}


	void MultilayerNetwork::SetMyNeuron( const int index,const shared_ptr<iNeuron>& myNeuron )
	{
		SetNeuron(index,myNeuron);
	}

	TrainResult MultilayerNetwork::Training()
	{
		TrainResult result=Success;

		int iteration(0);//max iteration number
		vector<double> prev_errors;
		train_MultiNetwork mytrain(_neurons,_learningRate);
		do 
		{
			mytrain.SetNeuronState(false);
			mytrain.ClearDeviations();
			mytrain=for_each(_mydata.begin(),_mydata.end(),mytrain);

			vector<double> cur_errors=mytrain.GetSampleDeviations();
			if(!prev_errors.empty())
			{
				if(ErrorConverge(prev_errors,cur_errors,_tol))
				{
					result=DeviationConverge;
					break;
				}
			}
			prev_errors=cur_errors;

			if(++iteration>_maxiter)
			{
				result=Max_Reached;
				break;
			}
		} while (mytrain.NeuronChanged());//If the neuron is changed after one iteration, process the proto patterns again to make sure that all errors are zero!

		_neurons=mytrain.GetResult();
		hasTrained=true;
		return result;
	}


	void train_MultiNetwork::operator()( shared_ptr<typename Network::MyData> mydata )
	{
		shared_ptr<iDataArray> proto=mydata->proto;
		shared_ptr<iDataArray> expec=mydata->expec;
		//shared_ptr<iDataArray> tmpoutput=ForwardPropagation(proto,_myNeurons);

		vector<shared_ptr<iDataArray>> n; //Transformed data derived by each neuron BEFORE using transfer function.
		vector<shared_ptr<iDataArray>> a; //Actual input data BEFORE transformed.
		shared_ptr<iDataArray> actualOut;
		ComputeActualOutAndIntermediateData(proto,actualOut,n,a);

		shared_ptr<iDataArray> ee=expec->Subtract(actualOut);
		_deviations.push_back(ee->Norm());

		if(ee->AllZero())//if the error array is zeroes
			return;
		
		BackwardPropagation(ee,n,a);
	}

	void train_MultiNetwork::BackwardPropagation(const shared_ptr<iDataArray> ee,
		const vector<shared_ptr<iDataArray>>& n, 
		const vector<shared_ptr<iDataArray>>& a )
	{
		DataArray e=*dynamic_pointer_cast<DataArray>(ee);

		//Backward Propagation
		MyNeurons::reverse_iterator neo_backward=_myNeurons.rbegin();
		vector<shared_ptr<iDataArray>>::const_reverse_iterator n_it=n.rbegin(),
			a_it=a.rbegin();
		shared_ptr<iDataArray> s_m_next;//s_m+1, the (m+1)th sensitivity
		shared_ptr<Matrix> mat_next;//W_m+1, the (m+1)th matrix
		for (;neo_backward!=_myNeurons.rend(),n_it!=n.rend(),a_it!=a.rend()
			;++neo_backward,++n_it,++a_it)
		{
			shared_ptr<iNeuron> tmpNeu=neo_backward->second;
			shared_ptr<TransferFunction::fun> myFun(tmpNeu->GetTransferFun());//transfer function
			shared_ptr<iDataArray> n_m(*n_it);//n_m, the (m)th transformed data
			shared_ptr<iDataArray> a_m_prev(*a_it);//a_m-1, the (m-1)th output data 
			shared_ptr<iDataArray> s_m(new DataArray(tmpNeu->GetOutputDimension()));//s_m, the (m)th sensitivity

			ComputeSensitivity(neo_backward,myFun,e,n_m,s_m,s_m_next,mat_next);
			AdjustNeuron(s_m,a_m_prev,tmpNeu);

			neuron_changed=true;
		}
	}

	void train_MultiNetwork::AdjustNeuron(const shared_ptr<iDataArray> s_m,
		const shared_ptr<iDataArray> a_m_prev,
		shared_ptr<iNeuron> tmpNeu)
	{
		assert(tmpNeu->GetOutputDimension()==s_m->Dimension());
		for (int n=0;n<tmpNeu->GetOutputDimension();++n)
		{
			Math::Vector newColumn=tmpNeu->Get_jthColumn(n)-_learningRate*s_m->Get_ithVal(n)*(a_m_prev->GetArray());//W_m_j_new=W_m_j_old-alpha*s_m_j*a_m-1
			tmpNeu->Set_jthColumn(n,newColumn);
			double newbias=tmpNeu->GetBias().Get_ithVal(n)-_learningRate*s_m->Get_ithVal(n);//b_m_new=b_m_old-alpha*s_m
			tmpNeu->Set_jthBias(n,newbias);
		}
	}

	void train_MultiNetwork::ComputeSensitivity(const MyNeurons::reverse_iterator& neo_backward,
		const shared_ptr<TransferFunction::fun> myFun,
		const DataArray& e,
		const shared_ptr<iDataArray> n_m,
		shared_ptr<iDataArray> s_m,
		shared_ptr<iDataArray>& s_m_next,
		shared_ptr<Matrix>& mat_next)
	{
		shared_ptr<iNeuron> tmpNeu=neo_backward->second;
		if(neo_backward==_myNeurons.rbegin())
		{
			for (unsigned int i=0;i<e.Dimension();++i)
			{
				double s_i=-2*e[i]*myFun->D1(n_m->Get_ithVal(i));//s_m_i=-2*e_i*df(n_m_i)
				s_m->Set_ithVal(i,s_i);
			}
			s_m_next=s_m;
			mat_next=shared_ptr<Matrix>(new Matrix(tmpNeu->GetMatrix()));
		}
		else
		{
			assert(s_m_next!=NULL);
			assert(n_m->Dimension()==tmpNeu->GetOutputDimension());
			for (int i=0;i<tmpNeu->GetOutputDimension();++i)
			{
				double D1_i=myFun->D1(n_m->Get_ithVal(i));
				Vector w_i=mat_next->nthRow(i);
				Vector s_m_next_v(s_m_next->GetArray());
				double s_i=(D1_i*w_i)*s_m_next_v;//s_m_i=df(n_m_i)*(W_m+1_i)*(s_m+1)
				s_m->Set_ithVal(i,s_i);
			}
			s_m_next=s_m;
			mat_next=shared_ptr<Matrix>(new Matrix(tmpNeu->GetMatrix()));
		}
	}

	void train_MultiNetwork::ComputeActualOutAndIntermediateData(const shared_ptr<iDataArray> proto,
		shared_ptr<iDataArray>& actualOut,
		vector<shared_ptr<iDataArray>>& n,
		vector<shared_ptr<iDataArray>>& a)
	{
		shared_ptr<iDataArray> tmpoutput=proto; //a temp output data After using transfer function.
		MyNeurons::iterator neo_forward=_myNeurons.begin();
		for (;neo_forward!=_myNeurons.end();++neo_forward)
		{
			a.push_back(tmpoutput);
			shared_ptr<iDataArray> n_m=neo_forward->second->TransformData(tmpoutput);
			n.push_back(n_m);
			tmpoutput=neo_forward->second->Transfer(n_m);
		}
		assert(n.size()==_myNeurons.size() && a.size()==_myNeurons.size());

		actualOut=tmpoutput;
	}

}
