#include "StdAfx.h"
#include "RelationNode.h"


namespace LogicSystem
{
	RelationNode::RelationNode(void):_andTag("&&"),_orTag("||")
	{
	}


	RelationNode::~RelationNode(void)
	{
	}

	std::string RelationNode::GetString() const
	{
		string res="";

		for (unsigned int i=0;i<_subRelations.size();++i)
		{
			res+='(';
			res+=_subRelations[i]->GetString();
			res+=')';

			if(i!=_subRelations.size()-1)
			{
				if(_state==And)
				{
					res+=_andTag;
				}
				else
				{
					res+=_orTag;
				}
			}
		}

		return res;
	}

	bool RelationNode::Satisfy( const shared_ptr<iExpression> expre ) const
	{
		return false;
	}

}

