#include "StdAfx.h"
#include "iNeuron.h"

namespace NeuralNetwork
{
	iNeuron::iNeuron(void)
	{
	}


	iNeuron::~iNeuron(void)
	{
	}

	shared_ptr<iDataArray> ForwardPropagation( const shared_ptr<iDataArray> in ,const std::map<int,shared_ptr<iNeuron>>& neurons)
	{
		typedef std::map<int,shared_ptr<iNeuron>> Neuron_map;

		shared_ptr<iDataArray> prevOutput(in);
		Neuron_map::const_iterator neu_it=neurons.begin();
		for (;neu_it!=neurons.end();++neu_it)
		{
			prevOutput=neu_it->second->Process(prevOutput);
		}

		//assert(prevOutput->Dimension()==GetOutputDimension());
		return prevOutput;
	}
}

