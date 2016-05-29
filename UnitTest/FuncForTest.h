#pragma once
#include "PublicHeader.h"

namespace Mind
{
	class iConcept;
	class iConceptChain;
	class iConceptInteractTable;
}

class InitCerebrum:public testing::Test
{
	int _initObjectCount;
protected:
	virtual void SetUp();
	virtual void TearDown();
};

class AddPatternToCerebrum:public testing::Test
{
	int _initObjectCount;
protected:
	virtual void SetUp();
	virtual void TearDown();
};

namespace FuncForTest
{
	const string TestSampleDir="TestSample\\";

	shared_ptr<Mind::iConcept> SimpleConcept(const string str);

	bool PairSameWithTable(const vector<pair<string,string>>& expect,const shared_ptr<Mind::iConceptInteractTable> table);

	bool SameTable(const shared_ptr<Mind::iConceptInteractTable> left,const shared_ptr<Mind::iConceptInteractTable> right);

	bool SameChainVec(const vector<vector<string>>& expect, const vector<shared_ptr<Mind::iConceptChain>>& result);

	bool SameChain(const vector<string>& expect,const shared_ptr<Mind::iConceptChain> res);

	void DisplayChains(const vector<shared_ptr<Mind::iConceptChain>>& chains);

	void DisplayConceptTable(const shared_ptr<Mind::iConceptInteractTable> table);

	///Add a grammar pattern to cerebrum.
	///Pattern is Numeral,Adjective,Preposition,Numeral.
	void AddGrammarPatternToCerebrum();

	shared_ptr<Mind::iConcept> GetConcept(const string str,const int id);

	template<class T>
	bool ContainSameElements(const vector<vector<T>>& v1,const vector<vector<T>>& v2)
	{
		if(v1.size()!=v2.size()) return false;

		vector<vector<T>> v2Copy=v2;
		for (unsigned int i=0;i<v1.size();++i)
		{
			bool exist=false;
			int existIndex=-1;
			for (unsigned int j=0;j<v2Copy.size();++j)
			{
				if(ContainSameElements(v1[i],v2Copy[j]))
				{
					exist=true;
					existIndex=j;
					break;
				}
			}

			if(!exist)
			{
				return false;
			}
			else
			{
				v2Copy.erase(v2Copy.begin()+existIndex);
			}
		}

		return true;
	}

	template<class T>
	bool ContainSameElements(const vector<T>& v1,const vector<T>& v2)
	{
		if(v1.size()!=v2.size())
		{
			return false;
		}

		for (unsigned int i=0;i<v1.size();++i)
		{
			if(v1[i]!=v2[i])
			{
				return false;
			}
		}

		return true;
	}
}

