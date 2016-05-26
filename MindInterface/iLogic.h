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
	class iDeduceResult;

	///iLogic contains functions about logic manipulation.
	class _MINDINTERFACEINOUT iLogic: public MyObject
	{
	public:
		iLogic(void);
		~iLogic(void);

		///Check whether <conclusion> can be deduced by <condition>.
		///<condition> should have been analyzed!
		virtual LogicResult Determine(const shared_ptr<iExpression> condition,const shared_ptr<iExpression> conclusion) =0;

		///Deduce results from <condition>.
		virtual vector<shared_ptr<iDeduceResult>> Deduce(const shared_ptr<iExpression> condition) =0;

		///Deduce results from <condition> repeatedly until the results converge.
		virtual vector<shared_ptr<iDeduceResult>> FinalDeduce(const shared_ptr<iExpression> condition) =0;
	};
}


