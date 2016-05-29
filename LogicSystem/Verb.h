#pragma once
#include "InOut.h"
#include "../MindInterface/iSymbol.h"
#include "../CommonTools/CommonStringFunction.h"
#include "../DataCollection/Word.h"

namespace LogicSystem
{
	///Verb presents any verb word.
	template<class T>
	class Verb : public iSymbol<T>
	{
		static int VerbNum;

		int _id;

	public:
		Verb(void){ ++VerbNum; };
		~Verb(void){};

		static shared_ptr<Verb> Create();

		virtual bool Match(const shared_ptr<T> con) const ;
		virtual string GetString() const;
		virtual void BindReferredObject(const shared_ptr<T> obj) ;
	};

	template<class T>
	int LogicSystem::Verb<T>::VerbNum=0;

	template<class T>
	string LogicSystem::Verb<T>::GetString() const
	{
		return "Verb"+CommonTool::ToString(_id);
	}

	template<class T>
	bool Verb<T>::Match( const shared_ptr<T> sym ) const
	{
		if(sym->GetPartOfSpeech()==DataCollection::Verb)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template<class T>
	void Verb<T>::BindReferredObject(const shared_ptr<T> obj) 
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
	shared_ptr<Verb<T>> Verb<T>::Create()
	{
		return shared_ptr<Verb>(new Verb());
	}


}