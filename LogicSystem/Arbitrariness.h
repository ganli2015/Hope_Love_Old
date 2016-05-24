#pragma once
#include "InOut.h"
#include "../MindInterface/iSymbol.h"
#include "../CommonTools/CommonStringFunction.h"

namespace LogicSystem
{
	///An Arbitrariness indicates any valid iSymbol.
	template<class T>
	class Arbitrariness : public iSymbol<T>
	{
		static int ArbNum;

		int _id;

		friend class Test_iRelation;

	public:
		Arbitrariness(void);
		virtual ~Arbitrariness(void);

		static shared_ptr<Arbitrariness> Create();

		virtual bool Match(const shared_ptr<T> con) const ;
		virtual string GetString() const;

	};

	template<class T>
	int Arbitrariness<T>::ArbNum=0;

	template<class T>
	Arbitrariness<T>::Arbitrariness(void):_id(ArbNum)
	{
		++ArbNum;
	}


	template<class T>
	Arbitrariness<T>::~Arbitrariness(void)
	{
		//--ArbNum;
	}

	template<class T>
	bool Arbitrariness<T>::Match( const shared_ptr<T> con ) const
	{
		if(con!=NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template<class T>
	std::string Arbitrariness<T>::GetString() const
	{
		return "S"+CommonTool::ToString(_id);
	}

	template<class T>
	shared_ptr<Arbitrariness<T>> Arbitrariness<T>::Create()
	{
		return shared_ptr<Arbitrariness>(new Arbitrariness());
	}
}


