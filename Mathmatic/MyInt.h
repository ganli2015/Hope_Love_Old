#pragma once
#include "InOut.h"

namespace Math
{
	//���Ա�ʾ��Int����߱�ʾ��1e18.
	class _MATHMATICINOUT MyInt : public Obj<MyInt>
	{
		int _low;
		int _high;

		const static int _maxLowHigh;
		const static int _power;

	public:
		MyInt(void);
		~MyInt(void);
		MyInt(const int val);

		MyInt& operator++();
		MyInt operator++(int);

		MyInt& operator--();
		MyInt operator--(int);

		_MATHMATICINOUT friend MyInt operator+(const MyInt& left,const MyInt& right);
		_MATHMATICINOUT friend MyInt operator+(const MyInt& left,const int right);
		_MATHMATICINOUT friend MyInt operator+(const int& left,const MyInt& right);
		void operator+=(const MyInt& right);
		void operator+=(const int& right);

		_MATHMATICINOUT friend MyInt operator-(const MyInt& left,const MyInt& right);
		_MATHMATICINOUT friend MyInt operator-(const MyInt& left,const int right);
		_MATHMATICINOUT friend MyInt operator-(const int& left,const MyInt& right);
		void operator-=(const MyInt& right);
		void operator-=(const int& right);

		_MATHMATICINOUT friend double operator/(const MyInt& left,const MyInt& right);

		double GetDouble() const;
		int GetInt() const;

	private: 
		//�鿴me��û�г����Ͻ�.
		static void CheckMe(const MyInt& me);
		
		void CarryOver();
		void GoBack();
	};
}


