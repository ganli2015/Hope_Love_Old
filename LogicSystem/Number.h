#pragma once
#include "InOut.h"
#include "../MindInterface/iSymbol.h"
#include "../MindInterface/iConcept.h"
#include "../CommonTools/CommonStringFunction.h"

namespace LogicSystem
{
	///A Number represents an integer in a logic system.
	template<class T>
	class Number : public iSymbol<T>
	{
		static int NumNum;
		static string _integerStr;

		int _id;

	public:
		Number(void){ ++NumNum; };
		~Number(void){};

		static shared_ptr<Number> Create();

		virtual bool Match(const shared_ptr<T> con) const ;
		virtual string GetString() const;
		virtual void BindReferredObject(const shared_ptr<T> obj) ;

		///Transform to a integer if possible.
		///Currently only support positive integers!
		bool ToInt(int& out) const;

	private:
	};

	template<class T>
	string LogicSystem::Number<T>::_integerStr="ÕûÊý";

	///Specialize for iConcept
	template<>
	bool _LOGICSYSTEMINOUT Number<Mind::iConcept>::Match( const shared_ptr<Mind::iConcept> con ) const;

	template<>
	bool _LOGICSYSTEMINOUT Number<Mind::iConcept>::ToInt( int& out ) const;

	template<class T>
	int Number<T>::NumNum=0;

	template<class T>
	shared_ptr<Number<T>> Number<T>::Create()
	{
		return shared_ptr<Number>(new Number());
	}

	template<class T>
	void Number<T>::BindReferredObject(const shared_ptr<T> obj) 
	{
		if(obj==NULL)
		{
			_referredObj=NULL;
			return;
		}

		if(Match(obj))
		{
			_referredObj=obj;
		}
	}

	template<class T>
	string LogicSystem::Number<T>::GetString() const
	{
		return "Num"+CommonTool::ToString(_id);
	}

}


