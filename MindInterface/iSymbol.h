#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;
}

namespace LogicSystem
{
	//iSymbol is a logic symbol.It is a fundamental element in a logic expression.
	template<class T>
	class _MINDINTERFACEINOUT iSymbol: public MyObject
	{
	protected:
		shared_ptr<T> _referredObj;

	public:
		iSymbol(void) {};
		virtual ~iSymbol(void) {};

		virtual bool Match(const shared_ptr<T> con) const =0;
		virtual string GetString() const =0;

		///Bind <me> with <obj> that <me> is referring to.
		virtual void BindReferredObject(const shared_ptr<T> obj) 
		{
			_referredObj=obj;
		}

		virtual shared_ptr<T> GetReferredObject() const 
		{
			return _referredObj;
		}
		///Check whether <me> and <other> refer to the same thing.
		virtual bool SameReferring(const shared_ptr<iSymbol<T>> other)
		{
			if(GetReferredObject()==NULL || other->GetReferredObject()==NULL)
			{
				assert(GetReferredObject()==NULL || other->GetReferredObject()==NULL);

				return false;
			}

			return GetReferredObject()->Same(other->GetReferredObject());
		}
	};



}


