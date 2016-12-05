#include "StdAfx.h"
#include "MyInt.h"


namespace Math
{
	const int MyInt::_power=9;
	const int MyInt::_maxLowHigh=999999999;

	MyInt::MyInt(void):_low(0),_high(0)
	{
	}

	MyInt::MyInt( const int val ):_low(val),_high(0)
	{
		CarryOver();
	}


	MyInt::MyInt(const long val)
	{
		_low = val;
		_high = 0;
		if (val >= 0)
		{
			CarryOver_Long(val);
		}
		else
		{
			GoBack_Long(val);
		}
	}

	MyInt::~MyInt(void)
	{
	}

	MyInt& MyInt::operator++()
	{
		if(_low==_maxLowHigh)
		{
			_low=0;
			++_high;
		}
		else
		{
			++_low;
		}

		CheckMe(*this);

		return *this;
	}

	MyInt MyInt::operator++( int )
	{
		MyInt tmp(*this);
		++*this;

		return tmp;
	}

	void MyInt::CheckMe(const MyInt& me)
	{
		Check(me._low<=_maxLowHigh && me._high<=_maxLowHigh);
		Check(me._low>=0 );
	}

	MyInt& MyInt::operator--()
	{
		if(_low==0)
		{
			--_high;
			_low=_maxLowHigh;
		}
		else
		{
			--_low;
		}

		CheckMe(*this);

		return *this;
	}

	Math::MyInt MyInt::operator--( int )
	{
		MyInt tmp(*this);
		--*this;

		return tmp;
	}

	void MyInt::CarryOver()
	{
		if(_low<=_maxLowHigh) return;

		while(_low>_maxLowHigh)
		{
			_low-=_maxLowHigh+1;
			++_high;
		}
	}

	void MyInt::GoBack()
	{
		if(_low>=0) return;

		while(_low<0)
		{
			_low+=_maxLowHigh+1;
			--_high;
		}

		CheckMe(*this);
	}

	void MyInt::CarryOver_Long(const long val)
	{
		if (val <= _maxLowHigh) return;

		long low = val;
		int high = _high;
		if (low <= _maxLowHigh) return;

		while (low > _maxLowHigh)
		{
			low -= _maxLowHigh + 1;
			++high;
		}

		_low = low;
		_high = high;
	}

	void MyInt::GoBack_Long(const long val)
	{
		if (val >= 0) return;

		long low = val;
		int high = _high;
		while (low < 0)
		{
			low += _maxLowHigh + 1;
			--high;
		}

		_low = low;
		_high = high;
	}

	void MyInt::operator+=(const MyInt& right)
	{
		_low+=right._low;
		_high+=right._high;
		CarryOver();
		CheckMe(*this);
	}

	void MyInt::operator+=( const int& right )
	{
		_low+=right;
		CarryOver();
		CheckMe(*this);
	}

	void MyInt::operator-=( const MyInt& right )
	{
		_low-=right._low;
		_high-=right._high;
		GoBack();
		CheckMe(*this);
	}

	void MyInt::operator-=( const int& right )
	{
		_low-=right;
		GoBack();
		CheckMe(*this);
	}

	double MyInt::GetDouble() const
	{
		return _high*pow(10.,_power)+_low;
	}

	int MyInt::GetInt() const
	{
		return (int)GetDouble();
	}

	double operator/( const MyInt& left,const MyInt& right )
	{
		return left.GetDouble()/right.GetDouble();
	}

	MyInt operator-( const int& left,const MyInt& right )
	{
		return MyInt(left)-right;
	}

	MyInt operator-( const MyInt& left,const int right )
	{
		return left-MyInt(right);
	}

	MyInt operator-( const MyInt& left,const MyInt& right )
	{
		MyInt res;
		res._low=left._low-right._low;
		res._high=left._high-right._high;
		res.GoBack();

		return res;
	}

	MyInt operator+( const MyInt& left,const MyInt& right )
	{
		MyInt res;
		res._low=left._low+right._low;
		res._high=left._high+right._high;
		res.CarryOver();
		
		return res;
	}

	MyInt operator+( const MyInt& left,const int right )
	{
		return left+MyInt(right);
	}

	MyInt operator+( const int& left,const MyInt& right )
	{
		return MyInt(left)+right;
	}

}

