#include "Stdafx.h"
#include "Number.h"

#include "../MindInterface/CommonFunction.h"

using namespace Mind;

namespace LogicSystem
{
	template<>
	bool Number<Mind::iConcept>::Match( const shared_ptr<Mind::iConcept> con ) const
	{
		//Check whether the forward concepts of <con> exists ÕûÊý concept.
		vector<shared_ptr<Mind::iConcept>> forward=con->GetBase();
		for (unsigned int i=0;i<forward.size();++i)
		{
			if(forward[i]->GetString()==_integerStr)
			{
				return true;
			}
		}

		return false;
	}


	template<>
	bool LogicSystem::Number<Mind::iConcept>::ToInt( int& out ) const
	{
		out=1;
		string oneStr="Ò»";

		shared_ptr<iConcept> integerCon=GetReferredObject();
		if(integerCon==NULL)
		{
			return false;
		}
		string conStr=integerCon->GetString();
		//Iterate until reach zero
		while(conStr!=oneStr)
		{
			//Find an integer concept that <integerCon> depends on.
			vector<shared_ptr<iConcept>> forward=integerCon->GetForwardConcepts();
			integerCon=CommonFunction::FindIntegerConcept(forward);
			if(integerCon==NULL)
			{
				return false;
			}

			conStr=integerCon->GetString();
			++out;
		}

		return true;
	}


}
