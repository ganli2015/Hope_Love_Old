#include "StdAfx.h"
#include "Neuron_compet.h"

namespace NeuralNetwork
{
	using namespace TransferFunction;

	

	Neuron_compet::Neuron_compet( const int i, const int j ):Neuron(i,j)
	{
		shared_ptr<TransferFunction::fun> transferfun(new compet());
		Neuron::SetFun(transferfun);
	}

	Neuron_compet::Neuron_compet( const int i, const int j,double val ):Neuron(i,j,val)
	{
		shared_ptr<TransferFunction::fun> transferfun(new compet());
		Neuron::SetFun(transferfun);
	}

	Neuron_compet::Neuron_compet(const std::vector<std::vector<double>> val,double bias):Neuron(val,bias)
	{
		shared_ptr<TransferFunction::fun> transferfun(new compet());
		Neuron::SetFun(transferfun);
	}

	Neuron_compet::Neuron_compet(const std::vector<Math::Vector>& val,double bias):Neuron(val,bias)
	{
		shared_ptr<TransferFunction::fun> transferfun(new compet());
		Neuron::SetFun(transferfun);
	}
	
	Neuron_compet:: Neuron_compet(const Math::Matrix& val,double bias):Neuron(val,bias)
	{
		shared_ptr<TransferFunction::fun> transferfun(new compet());
		Neuron::SetFun(transferfun);
	}

	Neuron_compet::Neuron_compet(const Neuron_compet& neuron):Neuron(neuron)
	{

	}

	shared_ptr<iDataArray> Neuron_compet::Transfer( const shared_ptr<iDataArray>& val ) const
	{
		assert(GetTransferFun()!=NULL);

		vector<double> vec(val->GetVector());
		shared_ptr<compet> transferfun=dynamic_pointer_cast<compet>(GetTransferFun());
		transferfun->SetInput(vec);
		int j=val->Dimension();
		std::vector<double> newvec(j);
		for (int n=0;n<j;++n)
		{
			newvec[n]=transferfun->Value(vec[n]);
		}
		return shared_ptr<DataArray>(new DataArray(newvec));
	}

	void Neuron_compet::SetFun( const shared_ptr<TransferFunction::fun> fun )
	{
		return;
	}

	shared_ptr<iNeuron> Neuron_compet::Copy()
	{
		return NULL;
	}

}

