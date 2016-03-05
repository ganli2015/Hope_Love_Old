#include "StdAfx.h"
#include "iMatrix.h"

namespace Math
{
	Math::Matrix::Matrix( const int i, const int j ) :_i(i),_j(j)
	{
		_m.assign(j,Vector(i));
	}

	Math::Matrix::Matrix( const std::vector<std::vector<double>> val ) :_i(val[0].size()),_j(val.size())
	{
		assert(val.size()==_j);
		_m.clear();
		for (std::vector<std::vector<double>>::const_iterator it=val.begin();it!=val.end();++it)
		{
			assert(it->size()==_i);
			Vector vec(*it);
			_m.push_back(vec);
		}
	}

	Math::Matrix::Matrix( const std::vector<Vector>& val ) :_i(val[0].Dimension()),_j(val.size())
	{
		for (unsigned int i=0;i<val.size();++i)
		{
			assert(val[i].Dimension()==_i);
		}
		_m=val;
	}

	Math::Matrix::Matrix( const Matrix& mat ) :_i(mat.Rows()),_j(mat.Columns())
	{
		_m=mat._m;
	}

	Math::Matrix::~Matrix( void )
	{

	}

	Math::Vector Math::Matrix::nthColumn( unsigned int col ) const
	{
		assert(col<=_m.size() && col>=0);return _m[col];
	}

	Math::Vector Math::Matrix::nthRow( unsigned int row ) const
	{
		std::vector<double> rowvec(_j);
		transform(_m.begin(),_m.end(),rowvec.begin(),get_nthElemOfVector(row));
		return Vector(rowvec);
	}

	void Math::Matrix::SetElem( int row,int col,double val )
	{
		assert(row<=_i&&col<=_j);
		Vector vec=nthColumn(col);
		vec.Set_ithVal(row,val);
		_m[col]=vec;
	}

	double Math::Matrix::GetElem( int row,int col ) const
	{
		return nthColumn(col)[row];
	}

	void Math::Matrix::Set_jthColumn( int n, Vector vec )
	{
		assert(n<_j);_m[n]=vec;
	}

	Math::Vector Math::Matrix::Multiply( const Vector& right ) const
	{
		assert(right.Dimension()==_j);
		Vector result(_i);
		for (int t=0;t<_i;++t)
		{
			result.Set_ithVal(t,nthRow(t)*right);
		}
		return result;
	}

	Matrix& Math::Matrix::operator=( const Matrix& mat )
	{
		assert(mat.Columns()==_j && mat.Rows()==_i);
		_m.clear();
		for (int t=0;t<_j;++t)
		{
			Vector tmpvec=mat.nthColumn(t);
			_m.push_back( tmpvec );
		}
		return *this;
	}

	Vector  operator*(const Matrix& mat,const Vector& vec)
	{
		return mat.Multiply(vec);
	}

	Vector  operator*(const Vector& vec,const Matrix& mat)
	{
		assert(vec.Dimension()==mat.Rows());
		int j=mat.Columns();
		Vector result(j);
		for (int t=0;t<j;++t)
		{
			result.Set_ithVal(t,mat.nthColumn(t)*vec);
		}
		return result;
	}

	bool Matrix::Same( const Matrix& mat,const double tol/*=1e-6*/ ) const
	{
		if(_i!=mat._i || _j!=mat._j)
		{
			return false;
		}

		for (unsigned int i=0;i<_m.size();++i)
		{
			if(!_m[i].Same(mat._m[i],tol))
			{
				return false;
			}
		}

		return true;
	}

	unsigned int Matrix::Columns() const
	{
		return (size_t)_j;
	}

	unsigned int Matrix::Rows() const
	{
		return (size_t)_i;
	}

	Matrix operator+( const Matrix& left,const Matrix& right )
	{
		Check(left.Rows()==right.Rows());
		Check(left.Columns()==right.Columns());

		Matrix res(left.Rows(),left.Columns());

		for (unsigned int i=0;i<left.Columns();++i)
		{
			Vector resColumn=left.nthColumn(i)+right.nthColumn(i);
			res.Set_jthColumn(i,resColumn);
		}

		return res;
	}

	Matrix& Matrix::operator+=( const Matrix& right )
	{
		Check(Rows()==right.Rows());
		Check(Columns()==right.Columns());

		for (unsigned int i=0;i<Columns();++i)
		{
			Vector resColumn=nthColumn(i)+right.nthColumn(i);
			Set_jthColumn(i,resColumn);
		}

		return *this;
	}

	Matrix Matrix::Negate() const
	{
		Matrix res(Rows(),Columns());

		for (unsigned int i=0;i<Columns();++i)
		{
			res.Set_jthColumn(i,_m[i].Negate());
		}

		return res;
	}

	Matrix operator*( const Matrix& left,const double& right )
	{
		Matrix res(left);
		for (unsigned int i=0;i<res.Columns();++i)
		{
			Vector newCol=res.nthColumn(i)*right;
			res.Set_jthColumn(i,newCol);
		}

		return res;
	}


	Matrix operator/( const Matrix& left,const double& right )
	{
		Check(DoubleCompare(right,0)!=0);

		Matrix res(left);
		for (unsigned int i=0;i<res.Columns();++i)
		{
			Vector newCol=res.nthColumn(i)/right;
			res.Set_jthColumn(i,newCol);
		}

		return res;
	}

}




