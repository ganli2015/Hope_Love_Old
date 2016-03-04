#include "StdAfx.h"
#include "TestClass.h"

#include "Neuron.h"
#include "TransferFunctions.h"
#include "Network.h"
#include "Perceptron.h"
#include "ADALINE.h"
#include "MultilayerNetwork.h"
#include "CompetitiveNetwork.h"
#include "Neuron_compet.h"

#include "../Mathmatic/Vector.h"
#include "../Mathmatic/iMatrix.h"
#include "../Mathmatic/MathTool.h"

#include "../CommonTools/IOFunction.h"

using namespace Math;
using namespace NeuralNetwork::TransferFunction;
using namespace CommonTool;

namespace NeuralNetwork
{
	TestClass::TestClass(void)
	{
	}


	TestClass::~TestClass(void)
	{
	}

	void TestClass::RunTest()
	{
		Vector vec1(GenerateContinuousNumber(1,5));
		Vector vec2(GenerateContinuousNumber(2,6));
		Vector vec3(GenerateContinuousNumber(3,7));
		vector<Vector> matvec;
		matvec.push_back(vec1);
		matvec.push_back(vec2);
		matvec.push_back(vec3);

		Matrix mat(matvec);
		//1 2 3
		//2 3 4
		//3 4 5
		//4 5 6
		//5 6 7

		shared_ptr<DataArray> array(new DataArray(vec1*0.1));
		//(0.1,0.2,0.3,0.4,0.5)
		Neuron neuron(mat,5);
		neuron.SetFun(shared_ptr<logsig>(new logsig));

		shared_ptr<iDataArray> array2(neuron.Process(array));

// 		RunTest_PerceptronNetwork();
// 		RunTest_ADALINENetwork();
// 		RunTest_MultiNetwork();
// 		RunTest_CompetitiveNetwork();
		RunTest_Connectivity();
	}

	void TestClass::RunTest_PerceptronNetwork()
	{
		{
			//{p1={1,2},t1=1} {p2={-1,2},t2=0} {p3={0,-1},t3=0}

			vector<double> vec1;
			vector<double> vec2;
			vector<double> vec3;
			vec1.push_back(1);
			vec1.push_back(2);
			vec2.push_back(-1);
			vec2.push_back(2);
			vec3.push_back(0);
			vec3.push_back(-1);
			shared_ptr<DataArray> p1(new DataArray(vec1));
			shared_ptr<DataArray> p2(new DataArray(vec2));
			shared_ptr<DataArray> p3(new DataArray(vec3));

			vector<double> vec11;
			vector<double> vec22;
			vector<double> vec33;
			vec11.push_back(1);
			vec22.push_back(0);
			vec33.push_back(0);
			shared_ptr<DataArray> t1(new DataArray(vec11));
			shared_ptr<DataArray> t2(new DataArray(vec22));
			shared_ptr<DataArray> t3(new DataArray(vec33));

			typedef iNeuron MyNeoron;
			double col1[2]={1.0,-0.8};
			vector<double> vcol1=Tovector(col1,2);
			shared_ptr<MyNeoron> neo(new Neuron(2,1));
			neo->Set_jthColumn(0,ToVector(col1,2));
			//		neo->SetFun(shared_ptr<hardlim>());
			Perceptron perceptron(2,1);
			perceptron.SetMyData(p1,t1);
			perceptron.SetMyData(p2,t2);
			perceptron.SetMyData(p3,t3);
			perceptron.SetMyNeuron(neo);
			perceptron.Training();
		}

		{
			double a1[3]={1,-1,-1},
				a2[3]={1,1,-1},
				a3[1]={0},
				a4[1]={1},
				a5[3]={0.5,-1,-0.5},
				a6[1]={0.5};
			shared_ptr<iDataArray> p1(ToDataArray(a1,3));
			shared_ptr<iDataArray> p2(ToDataArray(a2,3));
			shared_ptr<iDataArray> t1(ToDataArray(a3,1));
			shared_ptr<iDataArray> t2(ToDataArray(a4,1));

			typedef iNeuron MyNeoron;
			shared_ptr<MyNeoron> neo(new Neuron(3,1));
			neo->Set_jthColumn(0,ToVector(a5,3));
			neo->Set_jthBias(0,0.5);
			Perceptron perceptron(3,1);
			perceptron.SetMyData(p1,t1);
			perceptron.SetMyData(p2,t2);
			perceptron.SetMyNeuron(neo);
			perceptron.Training();
			shared_ptr<iDataArray> r1=perceptron.GetResult(p1);
			shared_ptr<iDataArray> r2=perceptron.GetResult(p2);
		}

		//{
		double a1[2]={1,1},
			a2[2]={1,2},
			a3[2]={2,-1},
			a4[2]={2,0},
			a5[2]={-1,2},
			a6[2]={-2,1},
			a7[2]={-1,-1},
			a8[2]={-2,-2},
			tt1[2]={0,0},
			tt2[2]={1,0},
			tt3[2]={0,1},
			tt4[2]={1,1};
		shared_ptr<iDataArray> p1(ToDataArray(a1,2)),
			p2(ToDataArray(a2,2)),
			p3(ToDataArray(a3,2)),
			p4(ToDataArray(a4,2)),
			p5(ToDataArray(a5,2)),
			p6(ToDataArray(a6,2)),
			p7(ToDataArray(a7,2)),
			p8(ToDataArray(a8,2)),
			t1(ToDataArray(tt1,2)),
			t2(ToDataArray(tt2,2)),
			t3(ToDataArray(tt3,2)),
			t4(ToDataArray(tt4,2));
		typedef iNeuron MyNeoron;

		shared_ptr<MyNeoron> neo(new Neuron(2,2));

		Perceptron perceptron(2,2);
		perceptron.SetMyData(p1,t1);
		perceptron.SetMyData(p2,t1);
		perceptron.SetMyData(p3,t2);
		perceptron.SetMyData(p4,t2);
		perceptron.SetMyData(p5,t3);
		perceptron.SetMyData(p6,t3);
		perceptron.SetMyData(p7,t4);
		perceptron.SetMyData(p8,t4);

		perceptron.SetMyNeuron(neo);
		perceptron.Training();
		shared_ptr<iDataArray> r1=perceptron.GetResult(p1);
		shared_ptr<iDataArray> r2=perceptron.GetResult(p2);
		shared_ptr<iDataArray> r3=perceptron.GetResult(p3);
		shared_ptr<iDataArray> r4=perceptron.GetResult(p4);
		shared_ptr<iDataArray> r5=perceptron.GetResult(p5);
		shared_ptr<iDataArray> r6=perceptron.GetResult(p6);
		shared_ptr<iDataArray> r7=perceptron.GetResult(p7);
		shared_ptr<iDataArray> r8=perceptron.GetResult(p8);
		//}



	}

	void TestClass::RunTest_ADALINENetwork()
	{
		double a1[3]={1,-1,-1},
			a2[3]={1,1,-1},
			tt1[1]={-1},
			tt2[2]={1};
		shared_ptr<iDataArray> p1(ToDataArray(a1,3)),
			p2(ToDataArray(a2,3));
		shared_ptr<iDataArray> t1(ToDataArray(tt1,1)),
			t2(ToDataArray(tt2,1));

		typedef ADALINE::MyNeuron MyNeuron;
		shared_ptr<MyNeuron> neo(new Neuron(3,1));

		ADALINE adaline(3,1);
		adaline.SetMyNeuron(neo);
		adaline.SetMyData(p1,t1);
		adaline.SetMyData(p2,t2);
		adaline.Training();

		shared_ptr<iDataArray> r1=adaline.GetResult(p1);
		shared_ptr<iDataArray> r2=adaline.GetResult(p2);

	}

	double g(double x)
	{
		return 1+sin(PI*x/4);
	}

	void TestClass::RunTest_MultiNetwork()
	{
		double a1[1]={1},
			tt1[1]={g(1)},
			w1_1[1]={-0.27},
			w1_2[1]={-0.41},
			b1[2]={-0.48,-0.13},
			w2[2]={0.09,-0.17},
			b2[1]={0.48};
		shared_ptr<iDataArray> p1=ToDataArray(a1,1);
		shared_ptr<iDataArray> t1=ToDataArray(tt1,1);

		shared_ptr<iNeuron> W1(new Neuron(1,2));
		shared_ptr<iNeuron> W2(new Neuron(2,1));

		shared_ptr<TransferFunction::logsig> fun_logsig(new logsig);
		shared_ptr<TransferFunction::purelin> fun_purelin(new purelin);

		W1->Set_jthColumn(0,ToVector(w1_1,1));
		W1->Set_jthColumn(1,ToVector(w1_2,1));
		W1->SetBias(ToVector(b1,2));
		W1->SetFun(fun_logsig);
		W2->Set_jthColumn(0,ToVector(w2,2));
		W2->SetBias(ToVector(b2,1));
		W2->SetFun(fun_purelin);

		MultilayerNetwork multilayerNetwork(1,1);

		multilayerNetwork.SetMyData(p1,t1);
		multilayerNetwork.SetMyNeuron(0,W1);
		multilayerNetwork.SetMyNeuron(1,W2);
		multilayerNetwork.Training();
		multilayerNetwork.SetLearningRate(0.8);

		shared_ptr<iDataArray> res=multilayerNetwork.GetResult(p1);
	}

	void TestClass::RunTest_CompetitiveNetwork()
	{
		double a1[2]={-0.1961,0.9806},
			a2[2]={0.1961,0.9806},
			a3[2]={0.9806,0.1961},
			a4[2]={0.9806,-0.1961},
			a5[2]={-0.5812,-0.8137},
			a6[2]={-0.8137,-0.5812},
			w1[2]={0.7071,-0.7071},
			w2[2]={0.7071,0.7071},
			w3[2]={-1,0};

		shared_ptr<iDataArray> p1=ToDataArray(a1,2);
		shared_ptr<iDataArray> p2=ToDataArray(a2,2);
		shared_ptr<iDataArray> p3=ToDataArray(a3,2);
		shared_ptr<iDataArray> p4=ToDataArray(a4,2);
		shared_ptr<iDataArray> p5=ToDataArray(a5,2);
		shared_ptr<iDataArray> p6=ToDataArray(a6,2);

		shared_ptr<iNeuron> W1(new Neuron_compet(2,3));
		W1->Set_jthColumn(0,ToVector(w1,2));
		W1->Set_jthColumn(1,ToVector(w2,2));
		W1->Set_jthColumn(2,ToVector(w3,2));

		CompetitiveNetwork competitiveNetwork(2,3);

		competitiveNetwork.SetMyNeuron(W1);
		competitiveNetwork.SetMyData(p1);
		competitiveNetwork.SetMyData(p2);
		competitiveNetwork.SetMyData(p3);
		competitiveNetwork.SetMyData(p4);
		competitiveNetwork.SetMyData(p5);
		competitiveNetwork.SetMyData(p6);

		competitiveNetwork.SetLearningRate(0.5);
		competitiveNetwork.Training();
		shared_ptr<iDataArray> r1=competitiveNetwork.GetResult(p1);
		shared_ptr<iDataArray> r2=competitiveNetwork.GetResult(p2);
		shared_ptr<iDataArray> r3=competitiveNetwork.GetResult(p3);
		shared_ptr<iDataArray> r4=competitiveNetwork.GetResult(p4);
		shared_ptr<iDataArray> r5=competitiveNetwork.GetResult(p5);
		shared_ptr<iDataArray> r6=competitiveNetwork.GetResult(p6);

	}

	shared_ptr<NeuralNetwork::iDataArray> TestClass::ToDataArray( const double val[], const int n )
	{
		return shared_ptr<DataArray>(new DataArray(Tovector(val,n)));
	}

	void TestClass::RunTest_Connectivity()
	{
		double pp1[4]={1,2,0,0},
			tt1[4]={0,1,2,0},
			pp2[4]={0,1,2,0},
			tt2[4]={0,0,1,2};

		shared_ptr<iDataArray> p1=ToDataArray(pp1,4);
		shared_ptr<iDataArray> t1=ToDataArray(tt1,4);
		shared_ptr<iDataArray> p2=ToDataArray(pp2,4);
		shared_ptr<iDataArray> t2=ToDataArray(tt2,4);

		//shared_ptr<iNeuron> W1(new Neuron(CreateRandomMatrix(4,4)));
		shared_ptr<iNeuron> W1(new Neuron(4,4));
		W1->SetFun(CreateTransferFunction(Purelin));
		

		MultilayerNetwork multilayerNetwork(4,4);
		multilayerNetwork.SetMyNeuron(0,W1);
		multilayerNetwork.SetMyData(p1,t1);
		multilayerNetwork.SetMyData(p2,t2);
		multilayerNetwork.SetLearningRate(0.15);
		multilayerNetwork.Training();
		
		double sigma1=ComputeDeviation(t1,multilayerNetwork.GetResult(p1));
		double sigma2=ComputeDeviation(t2,multilayerNetwork.GetResult(p2));

		double pp3[4]={1,2,3,0};
		shared_ptr<iDataArray> p3=ToDataArray(pp3,4);

		shared_ptr<iDataArray> o3=multilayerNetwork.GetResult(p3);

		vector<double> o3Expect;
		o3Expect.push_back(0.00000000000000000);
		o3Expect.push_back(0.33333447557466112);
		o3Expect.push_back(2.0000026939557554);
		o3Expect.push_back(2.6666674856128672);
		Check(SameVec(o3->GetVector(),o3Expect));

		//{0,1,2,3}
		ConcoleDisplay(o3->GetVector());
	}

	double TestClass::ComputeDeviation( const shared_ptr<iDataArray> array1,const shared_ptr<iDataArray> array2 )
	{
		return Math::ComputeDeviation(array1->GetVector(),array2->GetVector());
	}

}

