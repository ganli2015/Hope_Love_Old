#include "StdAfx.h"
#include "FindSequence.h"

using namespace std;

namespace Math
{
	_MATHMATICINOUT void FindLongestCommonSubsequence( const std::vector<int>& seq1, const std::vector<int>& seq2, std::vector<int>& common_seq )
	{
		unsigned int m=seq1.size();
		unsigned int n=seq2.size();
		state_sequence **b=new state_sequence *[m+1];
		ConstructSequenceTable(seq1,seq2,b);
		common_seq.clear();
		PrintLCS(b,seq1,0,0,m,n,common_seq);
	}

	void ConstructSequenceTable( const std::vector<int>& seq1, const std::vector<int>& seq2,state_sequence **b )
	{
		unsigned int m=seq1.size();
		unsigned int n=seq2.size();
		unsigned int **c;
		c=new unsigned int *[m+1];
		
		for (unsigned i=0;i<=m;++i)
		{
			c[i]=new unsigned int[n+1];
			b[i]=new state_sequence[n+1];
		}
		for(unsigned int row = 0;row <= m;row++) 
		{  
			c[row][0] = 0; 
			b[row][0] = none;
		}
		for(unsigned int col = 0;col <= n;col++) 
		{  
			c[0][col] = 0; 
			b[0][col] = none;
		}

		for (unsigned int i=1;i<=m;++i)
		{
			for (unsigned int j=1;j<=n;++j)
			{
				if(seq1[i-1]==seq2[j-1])
				{
					c[i][j]=c[i-1][j-1]+1;
					b[i][j]=diagonal;
				}
				else if(c[i-1][j]>=c[i][j-1])
				{
					c[i][j]=c[i-1][j];
					b[i][j]=up;
				}
				else
				{
					c[i][j]=c[i][j-1];
					b[i][j]=left;
				}
			}
		}
	}

	void PrintLCS( state_sequence **b,const std::vector<int>& seq, const int i_start, const int j_start, const int i_end,const int j_end, std::vector<int>& out )
	{
		if(i_end==i_start || j_end==j_start)
			return;

		if(b[i_end][j_end]==diagonal)
		{
			PrintLCS(b,seq,i_start,j_start,i_end-1,j_end-1,out);
			out.push_back(seq[i_end-1]);
		}
		else if(b[i_end][j_end]==up)
		{
			PrintLCS(b,seq,i_start,j_start,i_end-1,j_end,out);
		}
		else
		{
			PrintLCS(b,seq,i_start,j_start,i_end,j_end-1,out);
		}
	}

	_MATHMATICINOUT void FindAllCommonSubsequence( const std::vector<int>& seq1, const std::vector<int>& seq2, std::vector<std::vector<int>>& common_seqs )
	{
		unsigned int m=seq1.size();
		unsigned int n=seq2.size();
		state_sequence **b=new state_sequence *[m+1];
		ConstructSequenceTable(seq1,seq2,b);
		
		common_seqs.clear();
		for (unsigned int i=1;i<=m;++i)
		{
			for (unsigned int j=1;j<=n;++j)
			{
				if(b[i][j]==diagonal)
				{
					vector<int> commonSeq;
					PrintLCS(b,seq1,i-1,j-1,m,n,commonSeq);
					if(commonSeq.size()>1)
						common_seqs.push_back(commonSeq);
				}
			}
		}
	}

	_MATHMATICINOUT bool IsMatch( string P,string T )
	{
		unsigned int n=T.length();
		unsigned int m=P.length();
		vector<int> pi=ComputePrefixFunction(P);

		int q=0;
		for (unsigned int i=0;i<n;++i)
		{
			while(q>0 && P[q]!=T[i])
			{
				q=pi[q-1];
			}
			if(P[q]==T[i])
			{
				q++;
			}

			if(q==m)
			{
				return true;
			}
		}

		return false;
	}

	_MATHMATICINOUT int MatchCount( string P,string T )
	{
		unsigned int n=T.length();
		unsigned int m=P.length();
		vector<int> pi=ComputePrefixFunction(P);

		int q=0;
		int count(0);
		for (unsigned int i=0;i<n;++i)
		{
			while(q>0 && P[q]!=T[i])
			{
				q=pi[q-1];
			}
			if(P[q]==T[i])
			{
				q++;
			}

			if(q==m)
			{
				q=pi[q-1];
				count++;
			}
		}

		return count;
	}

	vector<int> ComputePrefixFunction( string P )
	{
		vector<int> res;
		int m=P.length();
		res.reserve(m);

		res.push_back(0);
		int k=0;
		for(int q=1;q<m;++q)
		{
			while(k>0 && P[k]!=P[q])
			{
				k=res[k-1];
			}
			if(P[k]==P[q])
			{
				k++;
			}
			res.push_back(k);
		}

		return res;
	}

	

}


