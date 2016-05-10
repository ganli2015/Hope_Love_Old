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
	static void TestExtractConceptChains();

	static ConceptPair GenerateBasePair(const string con1,const string con2);
	static vector<string> GenerateChain(const string str1,const string str2);
	static vector<string> GenerateChain(const string str1,const string str2,const string str3);
	static vector<string> GenerateChain(const string str1,const string str2,const string str3,const string str4);

	
};

