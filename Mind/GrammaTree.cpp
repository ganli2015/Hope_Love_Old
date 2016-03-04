#include "StdAfx.h"
#include "GrammaTree.h"

#include "../DataCollection/GrammaPattern.h"

using namespace std;
namespace Mind
{
	GrammaTreeNode::GrammaTreeNode( int val ):_val(val),_grammaID(-1)
	{

	}


	GrammaTreeNode::~GrammaTreeNode(void)
	{
	}

	void GrammaTreeNode::AppendChild( int val )
	{
		shared_ptr<GrammaTreeNode> node(new GrammaTreeNode(val));
		_children[val]=node;
	}

	void GrammaTreeNode::GetAllGrammaIDs( std::set<int>& ids ) const
	{
		if(_grammaID!=-1)
		{
			ids.insert(_grammaID);
		}

		for (map<int,shared_ptr<GrammaTreeNode>>::const_iterator it=_children.begin();it!=_children.end();++it)
		{
			it->second->GetAllGrammaIDs(ids);
		}
	}

	void GrammaTreeNode::GetAllGrammaIDs( std::vector<int>& ids ) const
	{
		set<int> ids_set;
		GetAllGrammaIDs(ids_set);
		ids.clear();
		ids.insert(ids.end(),ids_set.begin(),ids_set.end());
	}

	class pushfrontval
	{
		int _val;

	public:
		pushfrontval(const int val):_val(val){}
		~pushfrontval(){}

		vector<int> operator()(const vector<int> vec)
		{
			vector<int> newvec;
			newvec.push_back(_val);
			newvec.insert(newvec.end(),vec.begin(),vec.end());
			return newvec;
		}
	};

	void GrammaTreeNode::GetAllGrammaPatterns(const shared_ptr<GrammaTreeNode> node,  std::vector<vector<int>>& patterns ) const
	{
		map<int,shared_ptr<GrammaTreeNode>> children=node->_children;

		if(children.empty())
		{
			vector<int> pattern;
			pattern.push_back(node->_val);
			patterns.push_back(pattern);
			return;
		}

	    vector<vector<int>> child_pattern;
		for (map<int,shared_ptr<GrammaTreeNode>>::const_iterator it=children.begin();it!=children.end();++it)
		{
			//vector<vector<int>> tmp_pattern;
			GetAllGrammaPatterns(it->second,child_pattern);
			//child_pattern.insert(child_pattern.end(),tmp_pattern.begin(),tmp_pattern.end());
		}
		//patterns.clear();
		transform(child_pattern.begin(),child_pattern.end(),back_inserter(patterns),pushfrontval(node->_val));
	}

	DataCollection::GrammarPattern ToGrammaPattern(const vector<int>& vec)
	{
		vector<DataCollection::PartOfSpeech> pattern_enum;
		pattern_enum.reserve(vec.size());
		for (unsigned int i=0;i<vec.size();++i)
		{
			pattern_enum.push_back((DataCollection::PartOfSpeech)vec[i]);
		}
		return DataCollection::GrammarPattern(pattern_enum);
	}

	void GrammaTreeNode::GetAllGrammaPatterns( std::vector<DataCollection::GrammarPattern>& patterns ) const
	{
		vector<std::vector<int>> patterns_vec;
		shared_ptr<GrammaTreeNode> root(new GrammaTreeNode(*this));
		GetAllGrammaPatterns(root,patterns_vec);
		patterns.clear();
		transform(patterns_vec.begin(),patterns_vec.end(),back_inserter(patterns),ToGrammaPattern);

	}

	int GrammaTreeNode::GetGrammarID( const DataCollection::GrammarPattern pattern ) const
	{
		vector<DataCollection::PartOfSpeech> pos= pattern.GetPattern();
		if(pos.empty()) return -1;
		if(pos[0]!=_val) return -1;

		shared_ptr<GrammaTreeNode> curNode(new GrammaTreeNode(*this));
		for (unsigned int i=1;i<pos.size();++i)
		{
			if(curNode->_children.find(pos[i])==curNode->_children.end())
			{
				return -1;
			}
			else
			{
				curNode=curNode->_children[pos[i]];
			}
			
		}

		assert(curNode->_grammaID>=0);


		return curNode->_grammaID;
	}


	GrammaTree::GrammaTree( void ):_root(NULL)
	{

	}

	GrammaTree::GrammaTree( int rootval ):_root(shared_ptr<GrammaTreeNode>(new GrammaTreeNode(rootval)))
	{

	}

	GrammaTree::~GrammaTree()
	{

	}

	void GrammaTree::AppendGramma( const DataCollection::GrammarPattern pattern )
	{
		vector<DataCollection::PartOfSpeech> gra_seq_enum=pattern.GetPattern();
		vector<int> gra_seq;
		gra_seq.reserve(gra_seq_enum.size());
		for (unsigned int i=0;i<gra_seq_enum.size();++i)
		{
			gra_seq.push_back((int)gra_seq_enum[i]);
		}

		if(gra_seq.empty()) return;
		double rootval=gra_seq[0];
		if(_root->_val!=rootval)
		{
			assert(false && "The pattern is not matched!");
			return;
		}
		if(gra_seq.size()==1) return;//if there is only one element, do not modify the gramma ID of the root.

		shared_ptr<GrammaTreeNode> curNode=_root;//track the node which is being operated.
		for (unsigned int i=1;i<gra_seq.size();++i)
		{
			std::map<int,shared_ptr<GrammaTreeNode>> &children=curNode->_children;
			int index=gra_seq[i];
			if(children.find(index)==children.end())//if there is no corresponding index ,create a child.
			{
				shared_ptr<GrammaTreeNode> newnode(new GrammaTreeNode(index));
				children[index]=newnode;
			}
			curNode=children[index];
		}

		curNode->_grammaID=pattern.GetID();

	}

	std::vector<DataCollection::GrammarPattern> GrammaTree::GetAllGrammaPatterns() const
	{
		vector<DataCollection::GrammarPattern> patterns;
		_root->GetAllGrammaPatterns(patterns);
		return patterns;
	}

	std::vector<int> GrammaTree::GetAllGrammaIDs() const
	{
		vector<int> ids;
		_root->GetAllGrammaIDs(ids);
		return ids;
	}

	int GrammaTree::GetGrammarID( const DataCollection::GrammarPattern pattern ) const
	{
		return _root->GetGrammarID(pattern);
	}

	

	
	
	

}
