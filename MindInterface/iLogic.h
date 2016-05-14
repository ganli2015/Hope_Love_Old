#pragma once
#include "InOut.h"

namespace LogicSystem
{
	enum LogicResult
	{
		True,
		False,
		Unknown
	};

	class iExpression;

	///iLogic contains functions about logic manipulation.
	class _MINDINTERFACEINOUT iLogic: public MyObject
	{
		shared_ptr<iLogic> _instance;
		
	public:
		iLogic(void);
		~iLogic(void);

		shared_ptr<iLogic> GetInstance() const { return _instance; }
		void SetInstance(const shared_ptr<iLogic> val) { _instance = val; }

		///Check whether <conclusion> can be deduced by <condition>.
		///<condition> should have been analyzed!
		virtual LogicResult Determine(const shared_ptr<iExpression> condition,const shared_ptr<iExpression> conclusion) =0;
	};
}


