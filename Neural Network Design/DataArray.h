#pragma once
#include "Stdafx.h"
#include "InOut.h"
#include "iDataArray.h"

#include "../Mathmatic/Vector.h"
#include "../Mathmatic/MathTool.h"

// namespace Math
// {
// 	class Vector;
// }

namespace NeuralNetwork
{
// 	template<unsigned int n>
// 	class _NEURALNETWORKDESIGNINOUT iDataArray
// 	{
// 	public:
// 		iDataArray(){}
// 		~iDataArray(){}
// 
// 		unsigned int Dimension() const=0;
// 	};

	class _NEURALNETWORKDESIGNINOUT DataArray: public iDataArray
	{
		std::shared_ptr<Math::Vector> _vec;
		const int _n;
	public:
		DataArray(int i);
		~DataArray(){}

		explicit DataArray(const Math::Vector& vec);

		explicit DataArray(const std::vector<double>& vec);

		DataArray(const DataArray& data);

		unsigned int Dimension() const {return (unsigned int)_n;}

		const Math::Vector GetArray() const {return *_vec;}

		const std::vector<double>& GetVector() const ;

		double Norm();

		void Set_ithVal(int i,double val);

		double Get_ithVal(int i) const;

		//If all element in DataArray are zero, return true.
		bool AllZero();

		std::shared_ptr<iDataArray> Subtract(const std::shared_ptr<iDataArray> val);

		DataArray& operator=(const DataArray& data);

		//Read only
		double operator[](unsigned int i) const;

		virtual bool Same(const std::shared_ptr<iDataArray> val);
	};

	DataArray operator-(const DataArray& left, const DataArray& right);

	DataArray operator+(const DataArray& left, const DataArray& right);
}