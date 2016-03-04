#pragma once
#include "InOut.h"

namespace Math
{
	enum state_sequence
	{
		none,
		up,
		left,
		diagonal
	};

	//算法导论，P210
	_MATHMATICINOUT void FindLongestCommonSubsequence
		(const std::vector<int>& seq1, 
		const std::vector<int>& seq2,
		std::vector<int>& common_seq);

	_MATHMATICINOUT void FindAllCommonSubsequence
		(const std::vector<int>& seq1, 
		const std::vector<int>& seq2,
		std::vector<std::vector<int>>& common_seqs);

	//算法导论，P570
	_MATHMATICINOUT bool IsMatch(string P,string T);

	_MATHMATICINOUT int MatchCount(string P,string T);

	vector<int> ComputePrefixFunction(string P);

	void ConstructSequenceTable(const std::vector<int>& seq1, 
		const std::vector<int>& seq2,state_sequence **b);

	void PrintLCS
		( state_sequence **b,const std::vector<int>& seq,
		const int i_start, const int j_start,
		const int i_end,const int j_end, 
		std::vector<int>& out);

	template<class T>
	bool IsSubsequence(const std::vector<T>& sub, const std::vector<T>& full)
	{
		if(sub.empty()) return true;
		if(full.empty()) return false;

		unsigned int subIndex(0);
		T curElem=sub[subIndex];
		for (unsigned int i=0;i<full.size();++i)
		{
			if(curElem==full[i])
			{
				if(++subIndex<sub.size())
				{
					curElem=sub[subIndex];
				}
				else
				{
					return true;
				}
			}
		}

		return false;
	}

	//val是一个有序序列，val的每个元素val[i]是个无序序列。遍历每个val[i]的每个元素，获得有序序列的所有组合方式。
	template<class T>
	class GetAllCombinations
	{
	public:
		static vector<vector<T>> Get(const vector<vector<T>>& val)
		{
			vector<vector<T>> res;
			Recursive(0,val,res);
			return res;
		}

	private:
		static void Recursive(const unsigned int index, const vector<vector<T>>& in, vector<vector<T>>& out)
		{
			if(index>=in.size()) return;

			vector<T> curElem=in[index];

			vector<vector<T>> newout;
			for (unsigned int i=0;i<curElem.size();++i)
			{
				if(out.empty())//对于第一次递归，只需要添加in的第一列到out中
				{
					vector<T> newSeq;
					newSeq.push_back(curElem[i]);
					newout.push_back(newSeq);
				}
				else//在之前已经创建的组合的基础上添加当前元素，组合的个数会乘以curElem.size()倍（除了0）。
				{
					for (unsigned int j=0;j<out.size();++j)
					{
						vector<T> newSeq=out[j];
						newSeq.push_back(curElem[i]);
						newout.push_back(newSeq);
					}
				}
			}

			out=newout;
			//对下一列递归
			Recursive(index+1,in,out);
		}
	};

	//seq是一个有序序列，寻找该有序序列的所有子序列，子序列不一定是连续的，但是是有序的。
	template<class T>
	class GetAllSubSequence
	{
	public:
		static vector<vector<T>> Get(const vector<T>& seq)
		{
			vector<vector<T>> res;
			for (unsigned int i=1;i<=seq.size();++i)
			{
				vector<vector<T>> subs;
				FindSubSequence(seq,i,0,subs);
				res.insert(res.end(),subs.begin(),subs.end());
			}

			return res;
		}
	private:
		static void FindSubSequence(const vector<T>& raw,const unsigned int length,const unsigned int startIndex,vector<vector<T>>& out)
		{
			if(raw.size()-startIndex<length) return;
			if(length<=0) return;

			out.clear();
			for (unsigned int i=startIndex;i<raw.size();++i)
			{			
				//从raw的第i+1到结尾处，寻找长度等于length-1的子序列。
				vector<vector<T>> subsubs;
				FindSubSequence(raw,length-1,i+1,subsubs);

				if(length==1)//如果长度等于1，subsubs必然是空的，所以特殊处理。
				{
					vector<T> sub;
					sub.push_back(raw[i]);
					out.push_back(sub);
					continue;
				}

				//把当前的元素和子结构里的length-1长度的子序列连接起来，形成长度为length的子序列。
				for (unsigned int j=0;j<subsubs.size();++j)
				{
					vector<T> sub;
					sub.reserve(length);
					sub.push_back(raw[i]);
					sub.insert(sub.end(),subsubs[j].begin(),subsubs[j].end());

					out.push_back(sub);
				}
			}
		}
	};
}