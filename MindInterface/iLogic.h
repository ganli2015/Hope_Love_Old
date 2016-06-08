#pragma once
#include "InOut.h"

namespace Mind
{
	class iConceptInteractTable;
}

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
	class iReduceResult;

	///iLogic contains functions about logic manipulation.
	class _MINDINTERFACEINOUT iLogic: public Obj<iLogic>
	{
	public:
		iLogic(void);
		~iLogic(void);

		///Check whether <conclusion> can be deduced by <condition>.
		///<condition> should have been analyzed!
		virtual LogicResult Determine(const shared_ptr<iExpression> condition,const shared_ptr<iExpression> conclusion) const =0;

		///Deduce results from <condition>.
		///If only part of <condition> can deduce something , 
		///then the result includes deduction result from that part as well as the other original part.
		virtual vector<shared_ptr<iDeduceResult>> Deduce(const shared_ptr<iExpression> condition) const =0;
		
		///Deduce results from <condition> repeatedly until the results converge.
		virtual vector<shared_ptr<iDeduceResult>> FinalDeduce(const shared_ptr<iExpression> condition) const =0;

		///Reduce <conceptTable> to a simpler one.
		virtual vector<shared_ptr<iReduceResult>> Reduce(const shared_ptr<Mind::iConceptInteractTable> conceptTable) const =0;
	};
}


