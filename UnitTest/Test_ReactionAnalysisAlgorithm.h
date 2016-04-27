#pragma once
#include "PublicHeader.h"

namespace Mind
{
	class iConcept;
	class iConceptChain;
}

typedef pair<shared_ptr<Mind::iConcept>,shared_ptr<Mind::iConcept>> ConceptPair;

class Test_ReactionAnalysisAlgorithm
{
public:
	Test_ReactionAnalysisAlgorithm(void);
	~Test_ReactionAnalysisAlgorithm(void);

	static void RunTest();

private:
	static ConceptPair GenerateBasePair(const string con1,const string con2);
	static vector<string> GenerateChain(const string str1,const string str2,const string str3);
	static vector<string> GenerateChain(const string str1,const string str2,const string str3,const string str4);

	static bool SameChainVec(const vector<vector<string>>& expect, const vector<shared_ptr<Mind::iConceptChain>>& result);
	static bool SameChain(const vector<string>& expect,const shared_ptr<Mind::iConceptChain> res);
};

