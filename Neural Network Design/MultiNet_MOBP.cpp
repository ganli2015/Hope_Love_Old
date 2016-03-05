#include "StdAfx.h"
#include "MultiNet_MOBP.h"
#include "MultilayerNetwork.h"
#include "iDataArray.h"

#include "../Mathmatic/iMatrix.h"
#include "../Mathmatic/Vector.h"
#include "../Mathmatic/MathTool.h"

#define _Output_Network_Obj

using namespace Math;

namespace NeuralNetwork
{
	MultiNet_MOBP::MultiNet_MOBP(void):_momentumCoefficient(0.1),
		_objIncreaseLimit(0.04),
		_learnRateIncre(1.05),
		_learnRateDecre(0.7)
	{
		_obj=-1;
		_iterCount=0;
	}


	MultiNet_MOBP::~MultiNet_MOBP(void)
	{
	}

	void MultiNet_MOBP::Train( const vector<shared_ptr<Network::MyData>> mydata,train_MultiNetwork& myTrain )
	{
		_iterCount++;

		vector<vector<Math::Matrix>> deltaMat_Samples;
		vector<vector<Math::Vector>> deltaBias_Samples;
		vector<double> deviations;
		ComputeNeuronCorrection(mydata,myTrain,deltaMat_Samples,deltaBias_Samples,deviations);
		_deviations=deviations;

		if(deltaMat_Samples.empty())//收敛了
		{
			myTrain.SetNeuronState(false);
			return;
		}
		
		myTrain.SetNeuronState(true);

		vector<Matrix> meanDeltaMat=ComputeDeltaMatForLayers(deltaMat_Samples);
		vector<Vector> meanDeltaBias=ComputeDeltaBiasForLayers(deltaBias_Samples);
		vector<Matrix> filteredDeltaMat;
		vector<Vector> filteredDeltaBias;
		if(_prevDeltaBias.empty() || _prevDeltaMat.empty())
		{
			filteredDeltaMat=meanDeltaMat;
			filteredDeltaBias=meanDeltaBias;
		}
		else
		{
			ComputeMomentumCorrection(meanDeltaMat,meanDeltaBias,_prevDeltaMat,_prevDeltaBias,_momentumCoefficient,filteredDeltaMat,filteredDeltaBias);
		}

		double curObj=ComputeObjFun(deviations);
		AdjustParameters(curObj,_obj,_prevDeltaMat,_prevDeltaBias,myTrain,filteredDeltaMat,filteredDeltaBias,_momentumCoefficient);
		_obj=curObj;

		_prevDeltaMat=filteredDeltaMat;
		_prevDeltaBias=filteredDeltaBias;
		myTrain.AdjustNeuron(filteredDeltaMat,filteredDeltaBias);
		
#ifdef _Output_Network_Obj
		OutputDebugInfo();
#endif // _DEBUG
		
	}

	void MultiNet_MOBP::ComputeNeuronCorrection(const vector<shared_ptr<Network::MyData>> mydata,
		train_MultiNetwork& myTrain,
		vector<vector<Math::Matrix>>& deltaMat_Samples,
		vector<vector<Math::Vector>>& deltaBias_Samples,
		vector<double>& deviations)
	{
		class ComputeDeltaNeuron
		{
			train_MultiNetwork _train;
			vector<vector<Math::Matrix>> _deltaMats;//存放每个样本对neuron的修正，每个元素是一个样本对所有neuron的修正。
			vector<vector<Math::Vector>> _deltaBiases;
			vector<double> _errors;
		public:
			ComputeDeltaNeuron(train_MultiNetwork& myTrain):_train(myTrain){}
			~ComputeDeltaNeuron(){}

			void operator()(const shared_ptr<Network::MyData> mydata)
			{
				vector<Math::Matrix> deltaMat;
				vector<Math::Vector> deltaBias;
				shared_ptr<iDataArray> error;
				_train.ComputeDeltaNeuron(mydata,deltaMat,deltaBias,error);
				_errors.push_back(error->Norm());

				if(deltaBias.empty() || deltaMat.empty())
				{
					return;
				}

				_deltaMats.push_back(deltaMat);
				_deltaBiases.push_back(deltaBias);
			}

			vector<vector<Math::Matrix>> GetDeltaMat() const{return _deltaMats;}
			vector<vector<Math::Vector>> GetDeltaBias() const {return _deltaBiases;}
			vector<double> GetDeviations() const {return _errors;}
		};

		myTrain.SetNeuronState(false);
		myTrain.ClearDeviations();
		ComputeDeltaNeuron computeDeltaNeuron(myTrain);
		computeDeltaNeuron=for_each(mydata.begin(),mydata.end(),computeDeltaNeuron);

		deltaMat_Samples=computeDeltaNeuron.GetDeltaMat();
		deltaBias_Samples=computeDeltaNeuron.GetDeltaBias();
		deviations=computeDeltaNeuron.GetDeviations();
	}

	vector<Math::Matrix> MultiNet_MOBP::ComputeDeltaMatForLayers( const vector<vector<Math::Matrix>>& deltaMats ) const
	{
		Check(!deltaMats.empty());

		//遍历所有样本，计算对neuron修改的总数值。
		vector<Math::Matrix> deltaMat_layer;
		for (unsigned int i=0;i<deltaMats.size();++i)
		{
			vector<Matrix> deltaMats_oneSample=deltaMats[i];
			if(i==0)
			{				
				for (unsigned int j=0;j<deltaMats_oneSample.size();++j)
				{
					deltaMat_layer.push_back(deltaMats_oneSample[j]);
				}
			}
			else
			{
				for (unsigned int j=0;j<deltaMats_oneSample.size();++j)
				{
					deltaMat_layer[j]+=deltaMats_oneSample[j];
				}
			}
		}

		//除以总样本数求平均值。
		for (unsigned int i=0;i<deltaMat_layer.size();++i)
		{
			deltaMat_layer[i]=deltaMat_layer[i]/deltaMats.size();
		}

		return deltaMat_layer;
	}

	vector<Math::Vector> MultiNet_MOBP::ComputeDeltaBiasForLayers( const vector<vector<Math::Vector>>& deltaBiases ) const
	{
		Check(!deltaBiases.empty());

		vector<Math::Vector> deltaBias_layer;
		for (unsigned int i=0;i<deltaBiases.size();++i)
		{
			vector<Vector> deltaBias_oneSample=deltaBiases[i];
			if(i==0)
			{				
				for (unsigned int j=0;j<deltaBias_oneSample.size();++j)
				{
					deltaBias_layer.push_back(deltaBias_oneSample[j]);
				}
			}
			else
			{
				for (unsigned int j=0;j<deltaBias_oneSample.size();++j)
				{
					deltaBias_layer[j]+=deltaBias_oneSample[j];
				}
			}
		}

		//除以总样本数求平均值。
		for (unsigned int i=0;i<deltaBias_layer.size();++i)
		{
			deltaBias_layer[i]=deltaBias_layer[i]/deltaBiases.size();
		}

		return deltaBias_layer;
	}

	void MultiNet_MOBP::ComputeMomentumCorrection( 
		const vector<Math::Matrix>& curDeltaMat,
		const vector<Math::Vector>& curDeltaBias, 
		const vector<Math::Matrix>& prevDeltaMat, 
		const vector<Math::Vector>& prevDeltaBias, 
		const double& momentumCoefficient,
		vector<Math::Matrix>& filteredDeltaMat, vector<Math::Vector>& filteredDeltaBias )
	{
		Check(curDeltaMat.size()==curDeltaBias.size()==prevDeltaBias.size()==prevDeltaMat.size());

		filteredDeltaMat.clear();
		filteredDeltaBias.clear();

		double gamma=momentumCoefficient;
		for (unsigned int i=0;i<curDeltaMat.size();++i)
		{
			Matrix newMat=prevDeltaMat[i]*gamma+curDeltaMat[i]*(1-gamma);
			Vector newBias=prevDeltaBias[i]*gamma+curDeltaBias[i]*(1-gamma);

			filteredDeltaMat.push_back(newMat);
			filteredDeltaBias.push_back(newBias);
		}
	}

	double MultiNet_MOBP::ComputeObjFun( const vector<double>& devia )
	{
		double var=0.;

		for (unsigned int i=0;i<devia.size();++i)
		{
			var+=devia[i]*devia[i];
		}

		return var;
	}

	void MultiNet_MOBP::AdjustParameters( 
		const double curObj,
		const double prevObj, 
		const vector<Math::Matrix>& prevDeltaMat,
		const vector<Math::Vector>& prevDeltaBias,
		train_MultiNetwork& myTrain, 
		vector<Math::Matrix>& filteredDeltaMat, 
		vector<Math::Vector>& filteredDeltaBias, 
		double& momentumCoefficient )
	{
		if(_iterCount<=1)//第一次迭代不调整参数
		{
			return;
		}

		if(curObj/prevObj>(1+_objIncreaseLimit))//如果目标函数太大
		{
			//相当于取消上一次的改变
			filteredDeltaBias=ComputeNegateVector(prevDeltaBias);
			filteredDeltaMat=ComputeNegateMatrix(prevDeltaMat);
			//减小Learning Rate
			myTrain.SetLearningRate(myTrain.GetLearningRate()*_learnRateDecre);

			momentumCoefficient=0.;
		}
		else
		{
			if(DoubleCompare(momentumCoefficient,0)==0)
			{
				momentumCoefficient=0.2;
			}
		}

		if(curObj<prevObj)//目标函数比上一次小
		{
			//增加Learning Rate
			myTrain.SetLearningRate(myTrain.GetLearningRate()*_learnRateIncre);
		}

	}

}

