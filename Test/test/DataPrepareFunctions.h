#pragma once
#include <vector>

namespace Math
{
	class Vector;
	class Matrix;
}
namespace NeuralNetwork
{
	class iDataArray;
}

using namespace std;

const double PI=3.1415926;

vector<double> GenerateContinuousNumber(int from,int to);
vector<double> Tovector(const double val[], const int n);
vector<int> Tovector(const int val[], const int n);
Math::Vector ToVector(const double val[], const int n);
shared_ptr<NeuralNetwork::iDataArray> ToDataArray(const double val[], const int n);
Math::Matrix CreateRandomMatrix(int i,int j);
double RandomDouble(int figure=10);
