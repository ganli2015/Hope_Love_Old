#pragma once
#include "InOut.h"
#include <fstream>

//#include "../Mathmatic/iMatrix.h"

namespace Math
{
	class Matrix;
	class Vector;
}

namespace NeuralNetwork
{
	class iDataArray;
	class iNeuron;
	using namespace std;

	//TypeList for data struct below.
	struct data_types
	{
		typedef iDataArray ProtoPattern;
		typedef iDataArray ActualOutput;
		typedef iDataArray Expectation;
	};
	
	//A struct including three types, first for prototype(input of network), second for actual output
	//of network, and third for expected output of prototype.
	struct TestSample: public data_types
	{
		shared_ptr<ProtoPattern> proto;
		shared_ptr<ActualOutput> actual;
		shared_ptr<Expectation> expec;
	};

	enum TrainResult
	{
		Success,
		Max_Reached,
		DeviationConverge
	};

	//Base of network
	class _NEURALNETWORKDESIGNINOUT Network : public MyObject
	{
	public:
		Network();
		virtual ~Network(){}

		typedef TestSample MyData;
		typedef MyData::ProtoPattern ProtoPattern;
		typedef MyData::ActualOutput ActualOutput;
		typedef MyData::Expectation Expectation;

		virtual TrainResult Training()=0;
		virtual void SetMaxIterationCount(const int val){_maxiter=val;}
		virtual shared_ptr<ActualOutput> GetResult(const shared_ptr<ProtoPattern>& in);
		bool ErrorConverge(const vector<double>& prev,const vector<double>& cur, const double tol);

		//Input Training data.
		void SetMyData(const shared_ptr<ProtoPattern>& proto, const shared_ptr<Expectation>& expec=NULL );

		virtual int GetOutputDimension() const =0;
		virtual int GetInputDimension() const =0;

		int GetInteationCount() const { return _curInteationCount; }
		void SetInteationCount(int val) { _curInteationCount = val; }

		//ÔÝ²»Êä³ö_mydata
		void Write(const string filename) const;
		void Read(const string filename);
	private:
		void OutputMatrix(const Math::Matrix& mat,std::ofstream& out) const;
		std::pair<int,Math::Matrix> InputMatrix(std::ifstream& in) const;
		void OutputVec(const Math::Vector& vec,std::ofstream& out) const;
		Math::Vector InputVec(const int dimension,std::ifstream& in) const;
	protected:
		//Set or change the nth neuron. n counts from 0!
		void SetNeuron(int n,shared_ptr<iNeuron> neuron);

	protected:
		std::vector<shared_ptr<MyData>> _mydata;
		std::map<int,shared_ptr<iNeuron>> _neurons;
		bool hasTrained;
		int _maxiter;
		int _curInteationCount;
		double _tol;

	};

	
	



	
}
