#pragma once
#include "PublicHeader.h"
#include "../ReactionAnalysisAlgorithm/SentenceTypeDetermination.h"

namespace Mind
{
	class iConcept;
	class iConceptChain;
}

namespace DataCollection
{
	class Sentence;
}

typedef pair<shared_ptr<Mind::iConcept>,shared_ptr<Mind::iConcept>> ConceptPair;

struct Param_SentenceTypeDetermination
{
	shared_ptr<DataCollection::Sentence> sentence;
	SentenceTypeDetermination::Type type;
	shared_ptr<DataCollection::Sentence> questionPart;
};

class Test_SentenceTypeDetermination : public::testing::TestWithParam<Param_SentenceTypeDetermination>
{
public:
	Test_SentenceTypeDetermination() 
	{
		
	};
	~Test_SentenceTypeDetermination() {};

	static vector<Param_SentenceTypeDetermination> GenerateSamples();

private:

};



