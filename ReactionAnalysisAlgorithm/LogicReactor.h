#pragma once
#include "InOut.h"


namespace LogicSystem
{
	class iExpression;
}

namespace DataCollection
{
	class Sentence;
	class Word;
}

namespace Mind
{
	class iConceptChain;
}

///It is designed for temporary.
///Check sentence to analyze its logic component and make some reaction.
class _REACTIONANALYSISALGORITHMINOUT LogicReactor
{
	class LogicPattern
	{
		///Pattern to satisfy
		shared_ptr<Mind::iConceptChain> _pattern;
		///Indexes for <_pattern> that construct an potential expression.
		vector<int> _expressionIndex;
	public:
		LogicPattern(const shared_ptr<Mind::iConceptChain> val):_pattern(val){}
		~LogicPattern(){}

		void SetExpressionIndex(const vector<int> val){_expressionIndex=val;}

		bool Satify(const shared_ptr<Mind::iConceptChain> chain,shared_ptr<LogicSystem::iExpression>& expressionForLogic);
	};

	shared_ptr<LogicPattern> _logicPattern;

public:
	LogicReactor(void);
	~LogicReactor(void);

	///Check whether <sen> contain logic expression and  output the result.
	bool ContainLogicExpression(const shared_ptr<DataCollection::Sentence> sen, shared_ptr<LogicSystem::iExpression>& expression) const;

	shared_ptr<DataCollection::Sentence> Analyze(const shared_ptr<LogicSystem::iExpression> expre) const;

private:
	///Convert sentence to the concept chain and get all sub chains.
	vector<shared_ptr<Mind::iConceptChain>> ConvertToSubChains(const shared_ptr<DataCollection::Sentence> sen) const;

	void InitLogicPattern();
};

