#include "StdAfx.h"
#include "DataArray.h"
#include "../Mathmatic/Vector.h"

namespace NeuralNetwork
{
	using namespace std;

	DataArray::DataArray( int i ):_n(i),_vec(new Math::Vector(i))
	{

	}

	NeuralNetwork::DataArray::DataArray( const Math::Vector& vec ) :_vec(new  Math::Vector(vec)),_n(vec.Dimension())
	{

	}

	NeuralNetwork::DataArray::DataArray( const std::vector<double>& vec ) :_vec(new Math::Vector(vec)),_n(vec.size())
	{

	}

	NeuralNetwork::DataArray::DataArray( const DataArray& data ) :_n(data._n)
	{
		_vec=data._vec;
	}

	const std::vector<double>& DataArray::GetVector() const 
	{
		return _vec->GetVector();
	}

	double NeuralNetwork::DataArray::Norm()
	{
		return _vec->Norm();
	}

	void NeuralNetwork::DataArray::Set_ithVal( int i,double val )
	{
		_vec->Set_ithVal(i,val);
	}

	double NeuralNetwork::DataArray::Get_ithVal( int i ) const
	{
		return _vec->Get_ithVal(i);
	}

	bool NeuralNetwork::DataArray::AllZero()
	{
		for (int i=0;i<_n;++i)
		{
			if(Math::DoubleCompare(_vec->Get_ithVal(i),0)!=0)
				return false;
		}
		return true;
	}

	DataArray& NeuralNetwork::DataArray::operator=( const DataArray& data )
	{
		_vec=shared_ptr<Math::Vector>(new Math::Vector(data.GetArray()));
		return *this;
	}

	double DataArray::operator[](unsigned int i) const
	{
		return _vec->Get_ithVal(i);
	}

	std::shared_ptr<iDataArray> DataArray::Subtract( const std::shared_ptr<iDataArray> val )
	{
		std::shared_ptr<DataArray> right=dynamic_pointer_cast<DataArray>(val);
		return shared_ptr<iDataArray>(new DataArray(*this-*right));
	}

	bool DataArray::Same( const std::shared_ptr<iDataArray> val )
	{
		return GetArray().Same(val->GetArray());
	}



	NeuralNetwork::DataArray NeuralNetwork::operator-( const DataArray& left, const DataArray& right )
	{
		return DataArray(left.GetArray()-right.GetArray());
	}

	DataArray operator+(const DataArray& left, const DataArray& right)
	{
		return DataArray(left.GetArray()+right.GetArray());
	}
}


