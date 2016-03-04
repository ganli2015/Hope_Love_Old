#pragma once
#include "Stdafx.h"
#include "InOut.h"



namespace Math
{
	class Vector;
}

namespace NeuralNetwork
{

	class _NEURALNETWORKDESIGNINOUT iDataArray
	{
	public:
		iDataArray(void);
		virtual ~iDataArray(void);

		virtual unsigned int Dimension() const =0;

		virtual const Math::Vector GetArray() const =0;

		virtual const std::vector<double>& GetVector() const =0;

		virtual double Norm()=0;

		virtual void Set_ithVal(int i,double val)=0;

		virtual double Get_ithVal(int i) const =0 ;

		//If all element in DataArray are zero, return true.
		virtual bool AllZero()=0;

		virtual std::shared_ptr<iDataArray> Subtract(const std::shared_ptr<iDataArray> val)=0;
	};

}

