#pragma once
#include "InOut.h"

namespace NeuralNetwork
{
	namespace TransferFunction
	{
		enum fun_type
		{
			Hardlim=0,
			Hardlims,
			Purelin,
			Satlin,
			Satlins,
			Logsig,
			Tansig,
			Poslin,
			Compet,
			DoubleCompet
		};

		class _NEURALNETWORKDESIGNINOUT fun
		{
		public:
			fun(){};
			virtual ~fun(){};

			double Value(double x)
			{
				return this->operator()(x);
			}
			virtual double operator()(double)=0;
			virtual fun_type Type()=0;
			virtual double D1(double val) const =0;
		};

		std::tr1::shared_ptr<fun> _NEURALNETWORKDESIGNINOUT CreateTransferFunction(const fun_type type);

		class _NEURALNETWORKDESIGNINOUT hardlim:public fun
		{
		public:
			hardlim(){};
			~hardlim(){};
			virtual double operator()(double);
			virtual fun_type Type(){return Hardlim;}
			virtual double D1(double val) const;
		};

		class _NEURALNETWORKDESIGNINOUT hardlims:public fun
		{
		public:
			hardlims(){};
			~hardlims(){};
			virtual double operator()(double);
			virtual fun_type Type(){return Hardlims;}
			virtual double D1(double val) const;
		};

		class _NEURALNETWORKDESIGNINOUT purelin:public fun
		{
		public:
			purelin(){};
			~purelin(){};
			virtual double operator()(double);
			virtual fun_type Type(){return Purelin;}
			virtual double D1(double val) const;
		};

		class _NEURALNETWORKDESIGNINOUT satlin:public fun
		{
		public:
			satlin(){};
			~satlin(){};
			virtual double operator()(double);
			virtual fun_type Type(){return Satlin;}
			virtual double D1(double val) const;
		};

		class _NEURALNETWORKDESIGNINOUT satlins:public fun
		{
		public:
			satlins(){};
			~satlins(){};
			virtual double operator()(double);
			virtual fun_type Type(){return Satlins;}
			virtual double D1(double val) const;
		};

		class _NEURALNETWORKDESIGNINOUT logsig:public fun
		{
		public:
			logsig(){};
			~logsig(){};
			virtual double operator()(double val);
			virtual fun_type Type(){return Logsig;}
			virtual double D1(double val) const;
		};

		class _NEURALNETWORKDESIGNINOUT tansig:public fun
		{
		public:
			tansig(){};
			~tansig(){};
			virtual double operator()(double);
			virtual fun_type Type(){return Tansig;}
			virtual double D1(double val) const;
		};

		class _NEURALNETWORKDESIGNINOUT poslin:public fun
		{
		public:
			poslin(){};
			~poslin(){};
			virtual double operator()(double);
			virtual fun_type Type(){return Poslin;}
			virtual double D1(double val) const;
		};

		class _NEURALNETWORKDESIGNINOUT compet:public fun
		{
			std::vector<double> _vec;
			double _maxval;
		public:
			compet(){};
			~compet(){};
			virtual double operator()(double);
			virtual double D1(double val) const;
			virtual fun_type Type(){return Compet;};

			void SetInput( const std::vector<double> vec );
		};

		class _NEURALNETWORKDESIGNINOUT double_compet:public fun
		{
			std::vector<double> _vec;
			double _maxval;
			double _secondMax;
		public:
			double_compet(){};
			~double_compet(){};
			virtual double operator()(double);
			virtual double D1(double val) const;
			virtual fun_type Type(){return DoubleCompet;};

			void SetInput( const std::vector<double> vec );
		};
	}
}
