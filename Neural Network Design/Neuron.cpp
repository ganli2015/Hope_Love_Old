#include "StdAfx.h"
#include "Neuron.h"
#include "TransferFunctions.h"

namespace NeuralNetwork
{
	using namespace TransferFunction;

	Neuron::Neuron( const int i, const int j ) :_mat(i,j),_bias(j,0),_i(i),_j(j)
	{

	}

	Neuron::Neuron( const int i, const int j,double val ) :_mat(i,j),_bias(j,val),_i(i),_j(j)
	{

	}

	Neuron::Neuron( const std::vector<std::vector<double>> val,double bias/*=0*/ ) :_mat(val),_bias(val.size(),bias),
		_i(val[0].size()),_j(val.size())
	{

	}

	Neuron::Neuron( const std::vector<Math::Vector>& val,double bias/*=0*/ ) :_mat(val),_bias(val.size(),bias),
		_i(val[0].Dimension()),_j(val.size())
	{

	}

	Neuron::Neuron( const Math::Matrix& val,double bias/*=0*/ ) :_mat(val),_bias(val.Columns(),bias),
		_i(val.Rows()),_j(val.Columns())
	{

	}

	Neuron::Neuron( const Neuron& neuron ) :_i(neuron._i),_j(neuron._j),
		_mat(neuron._mat),_bias(neuron._bias)
	{
		_transferfun=neuron._transferfun;
	}

	shared_ptr<iDataArray> Neuron::Process( const shared_ptr<iDataArray> val ) const
	{
		
		shared_ptr<iDataArray> vec=TransformData(val);

		assert(vec->Dimension()==_j);
		//Use transfer function.
		return Transfer(vec);
	}

	unsigned int Neuron::GetInputDimension()
	{
		return _i;
	}

	unsigned int Neuron::GetOutputDimension()
	{
		return _j;
	}

	void Neuron::Set_jthColumn( int n, const Math::Vector vec )
	{
		assert(n<_j);
		_mat.Set_jthColumn(n,vec);
	}

	Math::Vector Neuron::Get_jthColumn( int n ) const
	{
		assert(n<_j);return _mat.nthColumn(n);
	}

	void Neuron::Set_jthBias( int n,const double val )
	{
		assert(n<_j);_bias.Set_ithVal(n,val);
	}

	void Neuron::SetElem( const int row,const int col, const double val )
	{
		_mat.SetElem(row,col,val);
	}

	Math::Vector Neuron::GetBias() const
	{
		return _bias;
	}

	TransferFunction::fun_type Neuron::GetFunType() const
	{
		return _transferfun->Type();
	}

	bool Neuron::SameType( const shared_ptr<iNeuron> neo ) const
	{
		if(_i==neo->GetInputDimension()
			&& _j==neo->GetOutputDimension()
			&& GetFunType()==neo->GetFunType())
			return true;
		else return false;
	}

	void Neuron::SetFun( const shared_ptr<fun> fun )
	{
		_transferfun=fun;
	}

	shared_ptr<iDataArray> Neuron::TransformData( const shared_ptr<iDataArray>& val ) const
	{
		Math::Vector input(val->GetArray());
		Math::Vector output(input*_mat+_bias);
		return shared_ptr<DataArray>(new DataArray(output));
	}

	shared_ptr<iDataArray> Neuron::Transfer( const shared_ptr<iDataArray>& val ) const
	{
		assert(_transferfun!=NULL);

		vector<double> vec(val->GetVector());
		std::vector<double> newvec(_j);
		for (int n=0;n<_j;++n)
		{
			newvec[n]=_transferfun->Value(vec[n]);
		}
		return shared_ptr<DataArray>(new DataArray(newvec));
	}

	shared_ptr<TransferFunction::fun> Neuron::GetTransferFun() const
	{
		return _transferfun;
	}

	Math::Matrix Neuron::GetMatrix() const
	{
		return _mat;
	}

	void Neuron::SetBias( const Math::Vector vec )
	{
		_bias=vec;
	}

	bool Neuron::Same( const std::shared_ptr<iNeuron> neo,const double tol/*=1e-6*/ )
	{
		if(_mat.Same(neo->GetMatrix(),tol) && _bias.Same(neo->GetBias(),tol))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	shared_ptr<iNeuron> Neuron::Copy()
	{
		shared_ptr<Neuron> res(new Neuron(_i,_j));
		res->_bias=_bias;
		res->_mat=_mat;
		res->_transferfun=_transferfun;

		return res;
	}



}

