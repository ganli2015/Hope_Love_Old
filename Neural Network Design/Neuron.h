#pragma once
#include "Stdafx.h"
#include "InOut.h"

#include "DataArray.h"
#include "iNeuron.h"

#include "../Mathmatic/iMatrix.h"
#include "../Mathmatic/Vector.h"

namespace NeuralNetwork
{
	using namespace std;

	namespace TransferFunction
	{
		class fun;
		enum fun_type;
	}


	class _NEURALNETWORKDESIGNINOUT Neuron : public iNeuron
	{
		Math::Matrix _mat;
		Math::Vector _bias;
		shared_ptr<TransferFunction::fun> _transferfun;

		const int _i;
		const int _j;
	public:
		Neuron(const int i, const int j);
		~Neuron(){}
		Neuron(const int i, const int j,double val);
		explicit Neuron(const std::vector<std::vector<double>> val,double bias=0);
		explicit Neuron(const std::vector<Math::Vector>& val,double bias=0);

		explicit Neuron(const Math::Matrix& val,double bias=0);
		Neuron(const Neuron& neuron);

// 		std::shared_ptr<iDataArray> Process(const std::shared_ptr<iDataArray> array) const
// 		{
// 			shared_ptr<DataArray> val=dynamic_pointer_cast<DataArray<_i>>(array);
// 			DataArray<_j> res=Process(*val);
// 			return shared_ptr<DataArray<_j>>(res);
// 		}

		virtual shared_ptr<iDataArray> Process(const shared_ptr<iDataArray> val) const;

		virtual int GetInputDimension();
		virtual int GetOutputDimension();

		virtual void Set_jthColumn(int n, const Math::Vector vec);
		virtual Math::Vector Get_jthColumn(int n) const;

		virtual void SetBias(const Math::Vector vec) ;
		virtual void Set_jthBias(int n,const double val);
		virtual Math::Vector GetBias() const;
		virtual void SetElem(const int row,const int col, const double val);

		virtual TransferFunction::fun_type GetFunType()const;
		virtual bool SameType(const shared_ptr<iNeuron> neo) const;
		virtual bool Same(const std::shared_ptr<iNeuron> neo,const double tol=1e-6);

		virtual void SetFun(const shared_ptr<TransferFunction::fun> fun);

		virtual shared_ptr<iDataArray> TransformData(const shared_ptr<iDataArray>& val) const;

		virtual shared_ptr<iDataArray> Transfer(const shared_ptr<iDataArray>& val) const ;

		virtual shared_ptr<TransferFunction::fun> GetTransferFun() const ;
		virtual Math::Matrix GetMatrix() const ;

		virtual shared_ptr<iNeuron> Copy();

	private:
		//Linear transform input data according to weight matrix. 

	};



}

