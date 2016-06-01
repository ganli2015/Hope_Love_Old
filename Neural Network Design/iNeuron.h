#pragma once
#include "Stdafx.h"
#include "InOut.h"

#include "TransferFunctions.h"

namespace Math
{
	class Vector;
	class Matrix;
}

namespace NeuralNetwork
{
	using namespace std;

	namespace TransferFunction
	{
		class fun;
		enum fun_type;
	}

	class iDataArray;

	class _NEURALNETWORKDESIGNINOUT iNeuron : public Obj<iNeuron>
	{
	public:
		iNeuron(void);
		~iNeuron(void);

		virtual std::shared_ptr<iDataArray> Process(const std::shared_ptr<iDataArray> array) const =0;

		virtual void Set_jthColumn(int n, const Math::Vector vec) =0;
		virtual Math::Vector Get_jthColumn(int n) const  =0;

		virtual void SetBias(const Math::Vector vec) =0;
		virtual void Set_jthBias(int n,const double val) =0; 
		virtual Math::Vector GetBias() const =0;
		virtual void SetElem(const int row,const int col, const double val)=0;

		virtual unsigned int GetInputDimension()=0;
		virtual unsigned int GetOutputDimension()=0;

		virtual TransferFunction::fun_type GetFunType() const =0;
		virtual bool SameType(const std::shared_ptr<iNeuron> neo) const =0;
		virtual void SetFun(const std::shared_ptr<TransferFunction::fun> fun) =0;
		virtual bool Same(const std::shared_ptr<iNeuron> neo,const double tol=1e-6)=0;

		virtual shared_ptr<iDataArray> TransformData(const shared_ptr<iDataArray>& val) const =0;
		virtual shared_ptr<iDataArray> Transfer(const shared_ptr<iDataArray>& val) const =0;

		virtual shared_ptr<TransferFunction::fun> GetTransferFun() const =0;
		virtual Math::Matrix GetMatrix() const =0;

		virtual shared_ptr<iNeuron> Copy()=0;
	};

	shared_ptr<iDataArray> ForwardPropagation( const shared_ptr<iDataArray> in ,const std::map<int,shared_ptr<iNeuron>>& neurons);

}



