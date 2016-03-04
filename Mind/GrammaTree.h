#pragma once
#include "InOut.h"
//#include "../DataCollection/Word.h"
#include <set>

namespace DataCollection
{
	class GrammarPattern;
}

namespace Mind
{
	class GrammaTreeNode
	{
		std::map<int,shared_ptr<GrammaTreeNode>> _children;//key value (int)is the _val of each child
		int _val;
		int _grammaID;

		void GetAllGrammaIDs(std::set<int>& ids) const;
		void GetAllGrammaPatterns(const shared_ptr<GrammaTreeNode> node, std::vector<std::vector<int>>& patterns) const;
	public:
		GrammaTreeNode(int val);
		~GrammaTreeNode(void);

		friend class GrammaTree;

		void AppendChild(int val);
		void SetGrammaID(const int ID) {_grammaID=ID;};
		void GetAllGrammaPatterns(std::vector<DataCollection::GrammarPattern>& patterns) const;
		void GetAllGrammaIDs(std::vector<int>& ids) const;
		int GetGrammarID(const DataCollection::GrammarPattern pattern) const;
	};

	class GrammaTree
	{
		shared_ptr<GrammaTreeNode> _root;

	public:
		GrammaTree(void);
		~GrammaTree();
		GrammaTree(int rootval);

		void AppendGramma(const DataCollection::GrammarPattern pattern);
		
		std::vector<DataCollection::GrammarPattern> GetAllGrammaPatterns() const;
		std::vector<int> GetAllGrammaIDs() const;
		int GetGrammarID(const DataCollection::GrammarPattern pattern) const;
	};
}


