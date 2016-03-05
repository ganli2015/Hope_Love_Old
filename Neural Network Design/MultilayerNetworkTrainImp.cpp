#include "StdAfx.h"
#include "MultilayerNetworkTrainImp.h"

#include <fstream>

namespace NeuralNetwork
{
	MultilayerNetworkTrainImp::MultilayerNetworkTrainImp(void):_out("DebugInfo//Network Object Function.txt")
	{
	}


	MultilayerNetworkTrainImp::~MultilayerNetworkTrainImp(void)
	{
	}

	void MultilayerNetworkTrainImp::OutputDebugInfo() 
	{
		_out<<_obj<<endl;
	}

}

