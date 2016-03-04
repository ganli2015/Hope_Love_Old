#pragma once
#include "Stdafx.h"
#include "InOut.h"

#include "DataArray.h"
#include "Neuron.h"

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


	class _NEURALNETWORKDESIGNINOUT Neuron_compet : public Neuron
	{
	public:
		Neuron_compet(const int i, const int j);
		~Neuron_compet(){}
		Neuron_compet(const int i, const int j,double val);
		explicit Neuron_compet(const std::vector<std::vector<double>> val,double bias=0);
		explicit Neuron_compet(const std::vector<Math::Vector>& val,double bias=0);

		explicit Neuron_compet(const Math::Matrix& val,double bias=0);
		Neuron_compet(const Neuron_compet& neuron);

		virtual shared_ptr<iDataArray> Transfer(const shared_ptr<iDataArray>& val) const ;

		virtual shared_ptr<iNeuron> Copy();
	private:

		virtual void SetFun(const shared_ptr<TransferFunction::fun> fun);
	};



}

