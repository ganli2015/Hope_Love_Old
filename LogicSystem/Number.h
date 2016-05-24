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
		static int ArbNum;
		static string TypeName;

		int _id;

	public:
		Number(void){ ++ArbNum; };
		~Number(void){};

		static shared_ptr<Number> Create();

		virtual bool Match(const shared_ptr<T> con) const ;
		virtual string GetString() const;
	};

	template<class T>
	int Number<T>::ArbNum=0;

	template<class T>
	string Number<T>::TypeName=typeid(T).name();

	template<class T>
	shared_ptr<Number<T>> Number<T>::Create()
	{
		return shared_ptr<Number>(new Number());
	}

	template<class T>
	bool Number<T>::Match( const shared_ptr<T> con ) const
	{
		if(typeid(Mind::iConcept).name()==TypeName)
		{
			//Check whether the forward concepts of <con> exists 数字 concept.
			vector<shared_ptr<Mind::iConcept>> forward=con->GetForwardConcepts();
			for (unsigned int i=0;i<forward.size();++i)
			{
				if(forward[i]->GetString()=="数字")
				{
					return true;
				}
			}

			return false;
		}
		else
			throw runtime_error("Not implemented!!");
	}

// 	template<>
// 	bool Number<Mind::iConcept>::Match( const shared_ptr<Mind::iConcept> con ) const;
// 	{
// 		//Check whether the forward concepts of <con> exists 数字 concept.
// 		vector<shared_ptr<Mind::iConcept>> forward=con->GetForwardConcepts();
// 		for (unsigned int i=0;i<forward.size();++i)
// 		{
// 			if(forward[i]->GetString()=="数字")
// 			{
// 				return true;
// 			}
// 		}
// 
// 		return false;
// 	}

	template<class T>
	string LogicSystem::Number<T>::GetString() const
	{
		return "Num"+CommonTool::ToString(_id);
	}

}


