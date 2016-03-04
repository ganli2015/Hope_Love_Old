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

	//�㷨���ۣ�P210
	_MATHMATICINOUT void FindLongestCommonSubsequence
		(const std::vector<int>& seq1, 
		const std::vector<int>& seq2,
		std::vector<int>& common_seq);

	_MATHMATICINOUT void FindAllCommonSubsequence
		(const std::vector<int>& seq1, 
		const std::vector<int>& seq2,
		std::vector<std::vector<int>>& common_seqs);

	//�㷨���ۣ�P570
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

	//val��һ���������У�val��ÿ��Ԫ��val[i]�Ǹ��������С�����ÿ��val[i]��ÿ��Ԫ�أ�����������е�������Ϸ�ʽ��
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
				if(out.empty())//���ڵ�һ�εݹ飬ֻ��Ҫ���in�ĵ�һ�е�out��
				{
					vector<T> newSeq;
					newSeq.push_back(curElem[i]);
					newout.push_back(newSeq);
				}
				else//��֮ǰ�Ѿ���������ϵĻ�������ӵ�ǰԪ�أ���ϵĸ��������curElem.size()��������0����
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
			//����һ�еݹ�
			Recursive(index+1,in,out);
		}
	};

	//seq��һ���������У�Ѱ�Ҹ��������е����������У������в�һ���������ģ�����������ġ�
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
				//��raw�ĵ�i+1����β����Ѱ�ҳ��ȵ���length-1�������С�
				vector<vector<T>> subsubs;
				FindSubSequence(raw,length-1,i+1,subsubs);

				if(length==1)//������ȵ���1��subsubs��Ȼ�ǿյģ��������⴦��
				{
					vector<T> sub;
					sub.push_back(raw[i]);
					out.push_back(sub);
					continue;
				}

				//�ѵ�ǰ��Ԫ�غ��ӽṹ���length-1���ȵ������������������γɳ���Ϊlength�������С�
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