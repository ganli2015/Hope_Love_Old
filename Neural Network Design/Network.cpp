#include "StdAfx.h"
#include "Network.h"
#include "iNeuron.h"
#include "Neuron.h"
#include "TransferFunctions.h"

#include "../Mathmatic/MathTool.h"
#include "../Mathmatic/iMatrix.h"
#include "../Mathmatic/Vector.h"

using namespace NeuralNetwork::TransferFunction;

namespace NeuralNetwork
{
	typedef TestSample MyData;
	typedef MyData::ProtoPattern ProtoPattern;
	typedef MyData::ActualOutput ActualOutput;
	typedef MyData::Expectation Expectation;

	NeuralNetwork::Network::Network() :hasTrained(false),_maxiter(100),_tol(1e-6)
	{

	}

	shared_ptr<ActualOutput> NeuralNetwork::Network::GetResult( const shared_ptr<ProtoPattern>& in )
	{
		return ForwardPropagation(in,_neurons);
	}

	void NeuralNetwork::Network::SetMyData( const shared_ptr<ProtoPattern>& proto, const shared_ptr<Expectation>& expec )
	{
		shared_ptr<MyData> mydata(new MyData());
		mydata->proto=proto;
		mydata->expec=expec;
		_mydata.push_back(mydata);
	}

	void NeuralNetwork::Network::SetNeuron( int n,shared_ptr<iNeuron> neuron )
	{
		assert(n>=0);
		//Confirm the correct output dimension and input dimension
		if(n==0)
		{
			if( _neurons.find(n+1)!=_neurons.end())
				assert(_neurons[n+1]->GetInputDimension()==neuron->GetOutputDimension());
		}
		else if(n==_neurons.rbegin()->first)
		{
			if( _neurons.find(n-1)!=_neurons.end())
				assert(_neurons[n-1]->GetOutputDimension()==neuron->GetInputDimension());
		}
		else
		{
			if( _neurons.find(n+1)!=_neurons.end())
				assert(_neurons[n+1]->GetInputDimension()==neuron->GetOutputDimension());
			if( _neurons.find(n-1)!=_neurons.end())
				assert(_neurons[n-1]->GetOutputDimension()==neuron->GetInputDimension());
		}	

		_neurons[n]=neuron;
	}

	bool Network::ErrorConverge( const vector<double>& prev,const vector<double>& cur, const double tol )
	{
		if(prev.size()!=cur.size())
		{
			throw runtime_error("Error in ErrorConverge");
		}

		for (unsigned int i=0;i<prev.size();++i)
		{
			if(Math::DoubleCompare(prev[i],cur[i],tol)!=0)
			{
				return false;
			}
		}

		return true;
	}

	void Network::Write( const string filename ) const
	{
		ofstream out(filename);

		out<<hasTrained<<" "<<_maxiter<<" "<<_tol<<endl;

		out<<_neurons.size()<<endl;
		for (map<int,shared_ptr<iNeuron>>::const_iterator it=_neurons.cbegin();it!=_neurons.cend();++it)
		{
			out<<(int)it->second->GetFunType()<<endl;
			out<<it->first<<" "<<it->second->GetInputDimension()<<" "<<it->second->GetOutputDimension()<<endl;

			Math::Matrix mat=it->second->GetMatrix();
			OutputMatrix(mat,out);
			out<<endl;
			OutputVec(it->second->GetBias().GetVector(),out);
			out<<endl;
		}
		
	}

	void Network::OutputMatrix( const Math::Matrix& mat,ofstream& out ) const
	{
		for (unsigned int i=0;i<mat.Columns();++i)
		{
			Math::Vector col=mat.nthColumn(i);
			OutputVec(col,out);
			out<<endl;
		}
	}

	void Network::Read( const string filename )
	{
		ifstream in(filename);

		in>>hasTrained;
		in>>_maxiter;
		in>>_tol;

		int neuCount;
		in>>neuCount;
		for (int i=0;i<neuCount;++i)
		{
			int funType;
			in>>funType;
			shared_ptr<fun> transferFun=CreateTransferFunction(fun_type(funType));

			pair<int,Math::Matrix> pair=InputMatrix(in);
			Math::Vector bias=InputVec(pair.second.Columns(),in);
			shared_ptr<iNeuron> neu(new Neuron(pair.second));
			neu->SetFun(transferFun);
			neu->SetBias(bias);
			_neurons.insert(make_pair(pair.first,neu));
		}
	}

	pair<int,Math::Matrix> Network::InputMatrix( std::ifstream& in ) const
	{
		//NeuronµÄ±àºÅ
		int index;
		in>>index;
		int inDim,outDim;
		in>>inDim>>outDim;

		Math::Matrix mat(inDim,outDim);
		for (int i=0;i<outDim;++i)
		{
			Math::Vector v=InputVec(inDim,in);
			mat.Set_jthColumn(i,v);
		}

		return make_pair(index,mat);
	}

	void Network::OutputVec( const Math::Vector& vec,std::ofstream& out ) const
	{
		for (unsigned int j=0;j<vec.Dimension();++j)
		{
			out<<vec[j]<<" ";
		}
	}

	Math::Vector Network::InputVec(const int dimension, std::ifstream& in ) const
	{
		Math::Vector v(dimension);
		for (int j=0;j<dimension;++j)
		{
			double val;
			in>>val;
			v.Set_ithVal(j,val);
		}

		return v;
	}

}


