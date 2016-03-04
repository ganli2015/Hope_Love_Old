#include "StdAfx.h"
#include <algorithm>
#include "TransferFunctions.h"

#include "../CommonTools/CommonCompareFunction.h"

#include "../Mathmatic/MathTool.h"

namespace NeuralNetwork
{
	namespace TransferFunction
	{
		using Math::e;

		std::tr1::shared_ptr<fun> _NEURALNETWORKDESIGNINOUT CreateTransferFunction( const fun_type type )
		{
			shared_ptr<fun> res;
			switch(type)
			{
			case Hardlim:
				{
					res=shared_ptr<fun>(new hardlim());
					break;
				}
			case Hardlims:
				{
					res=shared_ptr<fun>(new hardlims());
					break;
				}
			case Purelin:
				{
					res=shared_ptr<fun>(new purelin());
					break;
				}
			case Satlin:
				{
					res=shared_ptr<fun>(new satlin());
					break;
				}
			case Satlins:
				{
					res=shared_ptr<fun>(new satlins());
					break;
				}
			case Logsig:
				{
					res=shared_ptr<fun>(new logsig());
					break;
				}
			case Tansig:
				{
					res=shared_ptr<fun>(new tansig());
					break;
				}
			case Poslin:
				{
					res=shared_ptr<fun>(new poslin());
					break;
				}
			case Compet:
				{
					res=shared_ptr<fun>(new compet());
					break;
				}
			default:
				{
					throw runtime_error("Error in CreateTransferFunction!");
				}
			}

			return res;
		}

		double hardlim::operator()( double x)
		{
			if(x>=0)
				return 1;
			else return 0;
		}

		double hardlim::D1( double val ) const
		{
			//assert(val!=0.0);
			return 0.0;
		}


		double hardlims::operator()( double x)
		{
			if(x>=0)
				return 1;
			else return -1;
		}

		double hardlims::D1( double val ) const
		{
			assert(val!=0.0);
			return 0.0;
		}


		double purelin::operator()( double x)
		{
			return x;
		}

		double purelin::D1( double val ) const
		{
			return 1.;
		}


		double satlin::operator()( double x)
		{
			if(x>1)
				return 1;
			else if(x<0)
				return 0;
			else return x;
		}

		double satlin::D1( double val ) const
		{
			assert(val!=0 && val!=1);
			if(val<1 && val>0)
				return 1.0;
			else return 0.0;
		}


		double satlins::operator()( double x)
		{
			if(x>1)
				return 1;
			else if(x<-1)
				return -1;
			else return x;
		}

		double satlins::D1( double val ) const
		{
			assert(val!=-1 && val!=1);
			if(val<1 && val>-1)
				return 1.0;
			else return 0.0;
		}


		double logsig::operator()( double x)
		{
			return 1/(1+pow(e,-x));
		}

		double logsig::D1( double val ) const
		{
			return pow(e,-val)/pow(pow(e,-val)+1,2.0);
		}


		double tansig::operator()( double x)
		{
			return (pow(e,x)-pow(e,-x))/(pow(e,x)+pow(e,-x));
		}

		double tansig::D1( double val ) const
		{
			return 1.0-pow(pow(e,val)-pow(e,-val),2)/pow(pow(e,val)+pow(e,-val),2);
		}


		double poslin::operator()( double x)
		{
			if(x>=0)
				return x;
			else return 0;
		}

		double poslin::D1( double val ) const
		{
			//assert(val!=0);
			if(val>0)
				return 1.0;
			else return 0.0;
		}


		double compet::operator()( double val)
		{
			assert(!_vec.empty()&&"set input first!");
			std::vector<double>::iterator it=std::find_if(_vec.begin(),_vec.end(),CommonTool::comp_samedouble(val));
			if(it==_vec.end())
			{
				assert(false&&"invalid value");
				throw std::runtime_error("invalid input value");
			}
			if(Math::DoubleCompare(val,_maxval)==0)
				return 1.0;
			else return 0.0;
		}

		double compet::D1( double val ) const
		{
			assert(false&&"no derivative!");
			throw std::runtime_error("no derivative!");
		}

		void compet::SetInput( const std::vector<double> vec )
		{
			assert(!vec.empty());
			_vec=vec;
			_maxval=*max_element(_vec.begin(),_vec.end());
		}


		double double_compet::operator()( double val)
		{
			assert(!_vec.empty()&&"set input first!");
			std::vector<double>::iterator it=std::find_if(_vec.begin(),_vec.end(),CommonTool::comp_samedouble(val));
			if(it==_vec.end())
			{
				assert(false&&"invalid value");
				throw std::runtime_error("invalid input value");
			}
			if(Math::DoubleCompare(val,_maxval)==0 || Math::DoubleCompare(val,_secondMax)==0)
				return 1.0;
			else return 0.0;
		}

		double double_compet::D1( double val ) const
		{
			assert(false&&"no derivative!");
			throw std::runtime_error("no derivative!");
		}

		void double_compet::SetInput( const std::vector<double> vec )
		{
			assert(!vec.empty());
			_vec=vec;
			sort(_vec.begin(),_vec.end());

			_maxval=_vec.back();
			if(vec.size()>1)
			{
				_secondMax=_vec[_vec.size()-2];
			}
			else
			{
				_secondMax=_maxval;
			}
		}
	}
}


