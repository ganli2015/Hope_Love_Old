#pragma once
#include "InOut.h"
#include "CommonFunction.h"

namespace Mind
{
	class iConcept;

	class FindConnectConcept
	{
	private:

		enum SearchDir
		{
			Forward,
			Backward
		};
		multimap<string,int> _existedIdentity;//记录已经存入的Concept
		shared_ptr<iConcept> _initialConcept;

	public:
		FindConnectConcept(void);
		~FindConnectConcept(void);

		vector<shared_ptr<iConcept>> FindForward(const shared_ptr<iConcept> concept);
		vector<shared_ptr<iConcept>> FindBackward(const shared_ptr<iConcept> concept);
	private: 
		//记录已经找到的Concept
		void Record(const shared_ptr<iConcept> concept);
		bool ConceptExist(const shared_ptr<iConcept> concept) const;
		void Recursive_Find(const shared_ptr<iConcept> concept,const SearchDir dir, vector<shared_ptr<iConcept>>& connectConcepts);
	};
}


