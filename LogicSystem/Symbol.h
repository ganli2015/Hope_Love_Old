#pragma once
#include "InOut.h"
#include "../MindInterface/iSymbol.h"

namespace LogicSystem
{
	///Symbol is a simple iSymbol that corresponds to one concept.
	template<class T>
	class Symbol : public iSymbol<T>
	{
		shared_ptr<T> _object;

	public:
		Symbol(void);
		virtual ~Symbol(void);
		///Set the unique content of <me>
		Symbol(const shared_ptr<T> obj);

		virtual bool Match(const shared_ptr<T> obj) const ;
		virtual string GetString() const ;
		///Only bind if <obj> is the same with the content of <me>.
		virtual void BindReferredObject(const shared_ptr<T> obj) ;
	};

	template<class T>
	Symbol<T>::Symbol(void)
	{
	}

	template<class T>
	Symbol<T>::Symbol( const shared_ptr<T> obj ):_object(obj)
	{
		_referredObj=obj;
	}


	template<class T>
	Symbol<T>::~Symbol(void)
	{
	}

	template<class T>
	bool Symbol<T>::Match( const shared_ptr<T> obj ) const
	{
		if(obj->Same(_object))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template<class T>
	std::string Symbol<T>::GetString() const
	{
		return _object->GetString();
	}

	template<class T>
	void Symbol<T>::BindReferredObject( const shared_ptr<T> obj )
	{
		if(obj==NULL) return;

		if(obj->Same(_object))
		{
			_referredObj=obj;
		}
	}

}


