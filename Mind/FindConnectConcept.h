#pragma once
#include "InOut.h"
#include "CommonFunction.h"

namespace Mind
{
	class Concept;

	class FindConnectConcept
	{
	private:

		enum SearchDir
		{
			Forward,
			Backward
		};
		multimap<string,int> _existedIdentity;//��¼�Ѿ������Concept
		shared_ptr<Concept> _initialConcept;

	public:
		FindConnectConcept(void);
		~FindConnectConcept(void);

		vector<shared_ptr<Concept>> FindForward(const shared_ptr<Concept> concept);
		vector<shared_ptr<Concept>> FindBackward(const shared_ptr<Concept> concept);
	private: 
		//��¼�Ѿ��ҵ���Concept
		void Record(const shared_ptr<Concept> concept);
		bool ConceptExist(const shared_ptr<Concept> concept) const;
		void Recursive_Find(const shared_ptr<Concept> concept,const SearchDir dir, vector<shared_ptr<Concept>>& connectConcepts);
	};
}


