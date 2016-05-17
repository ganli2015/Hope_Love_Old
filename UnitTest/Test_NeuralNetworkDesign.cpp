#include "StdAfx.h"
#include "Test_NeuralNetworkDesign.h"

#include "../Neural Network Design/Neuron.h"
#include "../Neural Network Design/TransferFunctions.h"
#include "../Neural Network Design/Network.h"
#include "../Neural Network Design/Perceptron.h"
#include "../Neural Network Design/ADALINE.h"
#include "../Neural Network Design/MultilayerNetwork.h"
#include "../Neural Network Design/CompetitiveNetwork.h"
#include "../Neural Network Design/Neuron_compet.h"

#include "../Neural Network Design/MultiNet_MOBP.h"

#include "../Mathmatic/Vector.h"
#include "../Mathmatic/iMatrix.h"
#include "../Mathmatic/MathTool.h"

#include "../CommonTools/IOFunction.h"
#include "../CommonTools/CommonStringFunction.h"

using namespace Math;
using namespace NeuralNetwork::TransferFunction;
using namespace CommonTool;
using namespace NeuralNetwork;


double ComputeDeviation( const shared_ptr<iDataArray> array1,const shared_ptr<iDataArray> array2 );
double g(double x);
shared_ptr<NeuralNetwork::iDataArray> ToDataArray( const double val[], const int n );

TEST(DISABLED_Test_NeuralNetworkDesign,PerceptronNetwork1)
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

TEST(DISABLED_Test_NeuralNetworkDesign,PerceptronNetwork2)
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

TEST(DISABLED_Test_NeuralNetworkDesign,ADALINENetwork)
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

TEST(Test_NeuralNetworkDesign,MultilayerNetwork)
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

	ASSERT_TRUE(res->Same(t1));
}

TEST(DISABLED_Test_NeuralNetworkDesign,CompetitiveNetwork)
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

TEST(DISABLED_Test_NeuralNetworkDesign,Connectivity)
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
	int interDim=2;
	shared_ptr<iNeuron> W1(new Neuron(CreateRandomMatrix(4,interDim)));
	W1->SetFun(CreateTransferFunction(Purelin));
	shared_ptr<iNeuron> W2(new Neuron(CreateRandomMatrix(interDim,4)));
	W2->SetFun(CreateTransferFunction(Purelin));

	MultilayerNetwork multilayerNetwork(4,4);
	multilayerNetwork.SetMyNeuron(0,W1);
	multilayerNetwork.SetMyNeuron(1,W2);

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
	try
	{
		ASSERT_TRUE(SameVec(o3->GetVector(),o3Expect));
	}
	catch(...)
	{
		double deviation=Math::ComputeDeviation(o3Expect,o3->GetVector());
		throw;
	}

	//{0,1,2,3}
	ConcoleDisplay(o3->GetVector());
}

TEST(DISABLED_Test_NeuralNetworkDesign,SearchingParameter)
{
	double pp1[4]={1,2,0,0},
		tt1[4]={0,1,2,0},
		pp2[4]={0,1,2,0},
		tt2[4]={0,0,1,2};

	shared_ptr<iDataArray> p1=ToDataArray(pp1,4);
	shared_ptr<iDataArray> t1=ToDataArray(tt1,4);
	shared_ptr<iDataArray> p2=ToDataArray(pp2,4);
	shared_ptr<iDataArray> t2=ToDataArray(tt2,4);

	MultilayerNetwork multilayerNetwork(4,4);
	multilayerNetwork.SetMyData(p1,t1);
	multilayerNetwork.SetMyData(p2,t2);

	for (double j=0;j<1;j+=0.1)
	{
		multilayerNetwork.SetLearningRate(j);
		cout<<j<<endl;

		for (double i=0;i<1;i+=0.1)
		{
			shared_ptr<MultiNet_MOBP> trainImp(new MultiNet_MOBP());
			Test_NeuralNetworkDesign::SetMomentumCoefficient(trainImp,i);
			Test_NeuralNetworkDesign::SetTrainImp(multilayerNetwork,trainImp);

			shared_ptr<iNeuron> W1(new Neuron(CreateRandomMatrix(4,4)));
			W1->SetFun(CreateTransferFunction(Purelin));
			multilayerNetwork.SetMyNeuron(0,W1);

			multilayerNetwork.Training();

			cout<<ToString(i)<<" "<<multilayerNetwork.GetInteationCount()<<endl;

		}
	}	
}

TEST(Test_NeuralNetworkDesign,MOBP)
{
	double pp1[4]={1,2,0,0},
		tt1[4]={0,1,2,0},
		pp2[4]={0,1,2,0},
		tt2[4]={0,0,1,2};

	shared_ptr<iDataArray> p1=ToDataArray(pp1,4);
	shared_ptr<iDataArray> t1=ToDataArray(tt1,4);
	shared_ptr<iDataArray> p2=ToDataArray(pp2,4);
	shared_ptr<iDataArray> t2=ToDataArray(tt2,4);

	MultilayerNetwork multilayerNetwork(4,4);
	multilayerNetwork.SetMyData(p1,t1);
	multilayerNetwork.SetMyData(p2,t2);

	shared_ptr<MultiNet_MOBP> trainImp(new MultiNet_MOBP());
	Test_NeuralNetworkDesign::SetTrainImp(multilayerNetwork,trainImp);

	shared_ptr<iNeuron> W1(new Neuron(CreateRandomMatrix(4,4)));
	W1->SetFun(CreateTransferFunction(Purelin));
	multilayerNetwork.SetMyNeuron(0,W1);

	multilayerNetwork.Training();

	ASSERT_TRUE(t1->Same(multilayerNetwork.GetResult(p1)));
	ASSERT_TRUE(t2->Same(multilayerNetwork.GetResult(p2)));
}

double g(double x)
{
	return 1+sin(PI*x/4);
}

shared_ptr<NeuralNetwork::iDataArray> ToDataArray( const double val[], const int n )
{
	return shared_ptr<DataArray>(new DataArray(Tovector(val,n)));
}

double ComputeDeviation( const shared_ptr<iDataArray> array1,const shared_ptr<iDataArray> array2 )
{
	return Math::ComputeDeviation(array1->GetVector(),array2->GetVector());
}

void Test_NeuralNetworkDesign::SetMomentumCoefficient( shared_ptr<MultiNet_MOBP> mobp,double val )
{
	mobp->SetMomentumCoefficient(val);
}

void Test_NeuralNetworkDesign::SetTrainImp( MultilayerNetwork& network, shared_ptr<NeuralNetwork::MultilayerNetworkTrainImp> imp )
{
	network.SetTrainImp(imp);
}


// Test_NeuralNetworkDesign::Test_NeuralNetworkDesign(void)
// {
// }
// 
// 
// Test_NeuralNetworkDesign::~Test_NeuralNetworkDesign(void)
// {
// }
// 
// void Test_NeuralNetworkDesign::RunTest()
// {
// 	// 		RunTest_PerceptronNetwork();
// 	// 		RunTest_ADALINENetwork();
// 	RunTest_MultiNetwork();
// 	// 		RunTest_CompetitiveNetwork();
// 	//		RunTest_Connectivity();
// 	RunTest_MOBP();
// 	//		RunTest_MOBP_SearchingParameter();
// }
// 
// void Test_NeuralNetworkDesign::RunTest_PerceptronNetwork()
// {
// 	{
// 		//{p1={1,2},t1=1} {p2={-1,2},t2=0} {p3={0,-1},t3=0}
// 
// 		vector<double> vec1;
// 		vector<double> vec2;
// 		vector<double> vec3;
// 		vec1.push_back(1);
// 		vec1.push_back(2);
// 		vec2.push_back(-1);
// 		vec2.push_back(2);
// 		vec3.push_back(0);
// 		vec3.push_back(-1);
// 		shared_ptr<DataArray> p1(new DataArray(vec1));
// 		shared_ptr<DataArray> p2(new DataArray(vec2));
// 		shared_ptr<DataArray> p3(new DataArray(vec3));
// 
// 		vector<double> vec11;
// 		vector<double> vec22;
// 		vector<double> vec33;
// 		vec11.push_back(1);
// 		vec22.push_back(0);
// 		vec33.push_back(0);
// 		shared_ptr<DataArray> t1(new DataArray(vec11));
// 		shared_ptr<DataArray> t2(new DataArray(vec22));
// 		shared_ptr<DataArray> t3(new DataArray(vec33));
// 
// 		typedef iNeuron MyNeoron;
// 		double col1[2]={1.0,-0.8};
// 		vector<double> vcol1=Tovector(col1,2);
// 		shared_ptr<MyNeoron> neo(new Neuron(2,1));
// 		neo->Set_jthColumn(0,ToVector(col1,2));
// 		//		neo->SetFun(shared_ptr<hardlim>());
// 		Perceptron perceptron(2,1);
// 		perceptron.SetMyData(p1,t1);
// 		perceptron.SetMyData(p2,t2);
// 		perceptron.SetMyData(p3,t3);
// 		perceptron.SetMyNeuron(neo);
// 		perceptron.Training();
// 	}
// 
// 	{
// 		double a1[3]={1,-1,-1},
// 			a2[3]={1,1,-1},
// 			a3[1]={0},
// 			a4[1]={1},
// 			a5[3]={0.5,-1,-0.5},
// 			a6[1]={0.5};
// 		shared_ptr<iDataArray> p1(ToDataArray(a1,3));
// 		shared_ptr<iDataArray> p2(ToDataArray(a2,3));
// 		shared_ptr<iDataArray> t1(ToDataArray(a3,1));
// 		shared_ptr<iDataArray> t2(ToDataArray(a4,1));
// 
// 		typedef iNeuron MyNeoron;
// 		shared_ptr<MyNeoron> neo(new Neuron(3,1));
// 		neo->Set_jthColumn(0,ToVector(a5,3));
// 		neo->Set_jthBias(0,0.5);
// 		Perceptron perceptron(3,1);
// 		perceptron.SetMyData(p1,t1);
// 		perceptron.SetMyData(p2,t2);
// 		perceptron.SetMyNeuron(neo);
// 		perceptron.Training();
// 		shared_ptr<iDataArray> r1=perceptron.GetResult(p1);
// 		shared_ptr<iDataArray> r2=perceptron.GetResult(p2);
// 	}
// 
// 	//{
// 	double a1[2]={1,1},
// 		a2[2]={1,2},
// 		a3[2]={2,-1},
// 		a4[2]={2,0},
// 		a5[2]={-1,2},
// 		a6[2]={-2,1},
// 		a7[2]={-1,-1},
// 		a8[2]={-2,-2},
// 		tt1[2]={0,0},
// 		tt2[2]={1,0},
// 		tt3[2]={0,1},
// 		tt4[2]={1,1};
// 	shared_ptr<iDataArray> p1(ToDataArray(a1,2)),
// 		p2(ToDataArray(a2,2)),
// 		p3(ToDataArray(a3,2)),
// 		p4(ToDataArray(a4,2)),
// 		p5(ToDataArray(a5,2)),
// 		p6(ToDataArray(a6,2)),
// 		p7(ToDataArray(a7,2)),
// 		p8(ToDataArray(a8,2)),
// 		t1(ToDataArray(tt1,2)),
// 		t2(ToDataArray(tt2,2)),
// 		t3(ToDataArray(tt3,2)),
// 		t4(ToDataArray(tt4,2));
// 	typedef iNeuron MyNeoron;
// 
// 	shared_ptr<MyNeoron> neo(new Neuron(2,2));
// 
// 	Perceptron perceptron(2,2);
// 	perceptron.SetMyData(p1,t1);
// 	perceptron.SetMyData(p2,t1);
// 	perceptron.SetMyData(p3,t2);
// 	perceptron.SetMyData(p4,t2);
// 	perceptron.SetMyData(p5,t3);
// 	perceptron.SetMyData(p6,t3);
// 	perceptron.SetMyData(p7,t4);
// 	perceptron.SetMyData(p8,t4);
// 
// 	perceptron.SetMyNeuron(neo);
// 	perceptron.Training();
// 	shared_ptr<iDataArray> r1=perceptron.GetResult(p1);
// 	shared_ptr<iDataArray> r2=perceptron.GetResult(p2);
// 	shared_ptr<iDataArray> r3=perceptron.GetResult(p3);
// 	shared_ptr<iDataArray> r4=perceptron.GetResult(p4);
// 	shared_ptr<iDataArray> r5=perceptron.GetResult(p5);
// 	shared_ptr<iDataArray> r6=perceptron.GetResult(p6);
// 	shared_ptr<iDataArray> r7=perceptron.GetResult(p7);
// 	shared_ptr<iDataArray> r8=perceptron.GetResult(p8);
// 	//}
// 
// 
// 
// }
// 
// void Test_NeuralNetworkDesign::RunTest_ADALINENetwork()
// {
// 	double a1[3]={1,-1,-1},
// 		a2[3]={1,1,-1},
// 		tt1[1]={-1},
// 		tt2[2]={1};
// 	shared_ptr<iDataArray> p1(ToDataArray(a1,3)),
// 		p2(ToDataArray(a2,3));
// 	shared_ptr<iDataArray> t1(ToDataArray(tt1,1)),
// 		t2(ToDataArray(tt2,1));
// 
// 	typedef ADALINE::MyNeuron MyNeuron;
// 	shared_ptr<MyNeuron> neo(new Neuron(3,1));
// 
// 	ADALINE adaline(3,1);
// 	adaline.SetMyNeuron(neo);
// 	adaline.SetMyData(p1,t1);
// 	adaline.SetMyData(p2,t2);
// 	adaline.Training();
// 
// 	shared_ptr<iDataArray> r1=adaline.GetResult(p1);
// 	shared_ptr<iDataArray> r2=adaline.GetResult(p2);
// 
// }
// 
// double g(double x)
// {
// 	return 1+sin(PI*x/4);
// }
// 
// void Test_NeuralNetworkDesign::RunTest_MultiNetwork()
// {
// 	double a1[1]={1},
// 		tt1[1]={g(1)},
// 		w1_1[1]={-0.27},
// 		w1_2[1]={-0.41},
// 		b1[2]={-0.48,-0.13},
// 		w2[2]={0.09,-0.17},
// 		b2[1]={0.48};
// 	shared_ptr<iDataArray> p1=ToDataArray(a1,1);
// 	shared_ptr<iDataArray> t1=ToDataArray(tt1,1);
// 
// 	shared_ptr<iNeuron> W1(new Neuron(1,2));
// 	shared_ptr<iNeuron> W2(new Neuron(2,1));
// 
// 	shared_ptr<TransferFunction::logsig> fun_logsig(new logsig);
// 	shared_ptr<TransferFunction::purelin> fun_purelin(new purelin);
// 
// 	W1->Set_jthColumn(0,ToVector(w1_1,1));
// 	W1->Set_jthColumn(1,ToVector(w1_2,1));
// 	W1->SetBias(ToVector(b1,2));
// 	W1->SetFun(fun_logsig);
// 	W2->Set_jthColumn(0,ToVector(w2,2));
// 	W2->SetBias(ToVector(b2,1));
// 	W2->SetFun(fun_purelin);
// 
// 	MultilayerNetwork multilayerNetwork(1,1);
// 
// 	multilayerNetwork.SetMyData(p1,t1);
// 	multilayerNetwork.SetMyNeuron(0,W1);
// 	multilayerNetwork.SetMyNeuron(1,W2);
// 	multilayerNetwork.Training();
// 	multilayerNetwork.SetLearningRate(0.8);
// 
// 	shared_ptr<iDataArray> res=multilayerNetwork.GetResult(p1);
// 
// 	Check(res->Same(t1));
// }
// 
// void Test_NeuralNetworkDesign::RunTest_CompetitiveNetwork()
// {
// 	double a1[2]={-0.1961,0.9806},
// 		a2[2]={0.1961,0.9806},
// 		a3[2]={0.9806,0.1961},
// 		a4[2]={0.9806,-0.1961},
// 		a5[2]={-0.5812,-0.8137},
// 		a6[2]={-0.8137,-0.5812},
// 		w1[2]={0.7071,-0.7071},
// 		w2[2]={0.7071,0.7071},
// 		w3[2]={-1,0};
// 
// 	shared_ptr<iDataArray> p1=ToDataArray(a1,2);
// 	shared_ptr<iDataArray> p2=ToDataArray(a2,2);
// 	shared_ptr<iDataArray> p3=ToDataArray(a3,2);
// 	shared_ptr<iDataArray> p4=ToDataArray(a4,2);
// 	shared_ptr<iDataArray> p5=ToDataArray(a5,2);
// 	shared_ptr<iDataArray> p6=ToDataArray(a6,2);
// 
// 	shared_ptr<iNeuron> W1(new Neuron_compet(2,3));
// 	W1->Set_jthColumn(0,ToVector(w1,2));
// 	W1->Set_jthColumn(1,ToVector(w2,2));
// 	W1->Set_jthColumn(2,ToVector(w3,2));
// 
// 	CompetitiveNetwork competitiveNetwork(2,3);
// 
// 	competitiveNetwork.SetMyNeuron(W1);
// 	competitiveNetwork.SetMyData(p1);
// 	competitiveNetwork.SetMyData(p2);
// 	competitiveNetwork.SetMyData(p3);
// 	competitiveNetwork.SetMyData(p4);
// 	competitiveNetwork.SetMyData(p5);
// 	competitiveNetwork.SetMyData(p6);
// 
// 	competitiveNetwork.SetLearningRate(0.5);
// 	competitiveNetwork.Training();
// 	shared_ptr<iDataArray> r1=competitiveNetwork.GetResult(p1);
// 	shared_ptr<iDataArray> r2=competitiveNetwork.GetResult(p2);
// 	shared_ptr<iDataArray> r3=competitiveNetwork.GetResult(p3);
// 	shared_ptr<iDataArray> r4=competitiveNetwork.GetResult(p4);
// 	shared_ptr<iDataArray> r5=competitiveNetwork.GetResult(p5);
// 	shared_ptr<iDataArray> r6=competitiveNetwork.GetResult(p6);
// 
// }
// 
// shared_ptr<NeuralNetwork::iDataArray> Test_NeuralNetworkDesign::ToDataArray( const double val[], const int n )
// {
// 	return shared_ptr<DataArray>(new DataArray(Tovector(val,n)));
// }
// 
// void Test_NeuralNetworkDesign::RunTest_Connectivity()
// {
// 	double pp1[4]={1,2,0,0},
// 		tt1[4]={0,1,2,0},
// 		pp2[4]={0,1,2,0},
// 		tt2[4]={0,0,1,2};
// 
// 	shared_ptr<iDataArray> p1=ToDataArray(pp1,4);
// 	shared_ptr<iDataArray> t1=ToDataArray(tt1,4);
// 	shared_ptr<iDataArray> p2=ToDataArray(pp2,4);
// 	shared_ptr<iDataArray> t2=ToDataArray(tt2,4);
// 
// 	//shared_ptr<iNeuron> W1(new Neuron(CreateRandomMatrix(4,4)));
// 	int interDim=2;
// 	shared_ptr<iNeuron> W1(new Neuron(CreateRandomMatrix(4,interDim)));
// 	W1->SetFun(CreateTransferFunction(Purelin));
// 	shared_ptr<iNeuron> W2(new Neuron(CreateRandomMatrix(interDim,4)));
// 	W2->SetFun(CreateTransferFunction(Purelin));
// 
// 	MultilayerNetwork multilayerNetwork(4,4);
// 	multilayerNetwork.SetMyNeuron(0,W1);
// 	multilayerNetwork.SetMyNeuron(1,W2);
// 
// 	multilayerNetwork.SetMyData(p1,t1);
// 	multilayerNetwork.SetMyData(p2,t2);
// 	multilayerNetwork.SetLearningRate(0.15);
// 	multilayerNetwork.Training();
// 
// 	double sigma1=ComputeDeviation(t1,multilayerNetwork.GetResult(p1));
// 	double sigma2=ComputeDeviation(t2,multilayerNetwork.GetResult(p2));
// 
// 	double pp3[4]={1,2,3,0};
// 	shared_ptr<iDataArray> p3=ToDataArray(pp3,4);
// 
// 	shared_ptr<iDataArray> o3=multilayerNetwork.GetResult(p3);
// 
// 	vector<double> o3Expect;
// 	o3Expect.push_back(0.00000000000000000);
// 	o3Expect.push_back(0.33333447557466112);
// 	o3Expect.push_back(2.0000026939557554);
// 	o3Expect.push_back(2.6666674856128672);
// 	try
// 	{
// 		Check(SameVec(o3->GetVector(),o3Expect));
// 	}
// 	catch(...)
// 	{
// 		double deviation=Math::ComputeDeviation(o3Expect,o3->GetVector());
// 		throw;
// 	}
// 
// 	//{0,1,2,3}
// 	ConcoleDisplay(o3->GetVector());
// }
// 
// double Test_NeuralNetworkDesign::ComputeDeviation( const shared_ptr<iDataArray> array1,const shared_ptr<iDataArray> array2 )
// {
// 	return Math::ComputeDeviation(array1->GetVector(),array2->GetVector());
// }
// 
// void Test_NeuralNetworkDesign::RunTest_MOBP_SearchingParameter( )
// {
// 	double pp1[4]={1,2,0,0},
// 		tt1[4]={0,1,2,0},
// 		pp2[4]={0,1,2,0},
// 		tt2[4]={0,0,1,2};
// 
// 	shared_ptr<iDataArray> p1=ToDataArray(pp1,4);
// 	shared_ptr<iDataArray> t1=ToDataArray(tt1,4);
// 	shared_ptr<iDataArray> p2=ToDataArray(pp2,4);
// 	shared_ptr<iDataArray> t2=ToDataArray(tt2,4);
// 
// 	MultilayerNetwork multilayerNetwork(4,4);
// 	multilayerNetwork.SetMyData(p1,t1);
// 	multilayerNetwork.SetMyData(p2,t2);
// 
// 	for (double j=0;j<1;j+=0.1)
// 	{
// 		multilayerNetwork.SetLearningRate(j);
// 		cout<<j<<endl;
// 
// 		for (double i=0;i<1;i+=0.1)
// 		{
// 			shared_ptr<MultiNet_MOBP> trainImp(new MultiNet_MOBP());
// 			trainImp->SetMomentumCoefficient(i);
// 			multilayerNetwork.SetTrainImp(trainImp);
// 
// 			shared_ptr<iNeuron> W1(new Neuron(CreateRandomMatrix(4,4)));
// 			W1->SetFun(CreateTransferFunction(Purelin));
// 			multilayerNetwork.SetMyNeuron(0,W1);
// 
// 			multilayerNetwork.Training();
// 
// 			cout<<ToString(i)<<" "<<multilayerNetwork.GetInteationCount()<<endl;
// 
// 		}
// 	}	
// }
// 
// void Test_NeuralNetworkDesign::RunTest_MOBP()
// {
// 	double pp1[4]={1,2,0,0},
// 		tt1[4]={0,1,2,0},
// 		pp2[4]={0,1,2,0},
// 		tt2[4]={0,0,1,2};
// 
// 	shared_ptr<iDataArray> p1=ToDataArray(pp1,4);
// 	shared_ptr<iDataArray> t1=ToDataArray(tt1,4);
// 	shared_ptr<iDataArray> p2=ToDataArray(pp2,4);
// 	shared_ptr<iDataArray> t2=ToDataArray(tt2,4);
// 
// 	MultilayerNetwork multilayerNetwork(4,4);
// 	multilayerNetwork.SetMyData(p1,t1);
// 	multilayerNetwork.SetMyData(p2,t2);
// 
// 	shared_ptr<MultiNet_MOBP> trainImp(new MultiNet_MOBP());
// 	multilayerNetwork.SetTrainImp(trainImp);
// 
// 	shared_ptr<iNeuron> W1(new Neuron(CreateRandomMatrix(4,4)));
// 	W1->SetFun(CreateTransferFunction(Purelin));
// 	multilayerNetwork.SetMyNeuron(0,W1);
// 
// 	multilayerNetwork.Training();
// 
// 	Check(t1->Same(multilayerNetwork.GetResult(p1)));
// 	Check(t2->Same(multilayerNetwork.GetResult(p2)));
// }




