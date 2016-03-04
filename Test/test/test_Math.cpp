#include "StdAfx.h"
#include "test_Math.h"
#include "DataPrepareFunctions.h"
#include "Vector.h"
#include "iMatrix.h"
#include "FindSequence.h"
using namespace std;
using namespace Math;

Test_Math::Test_Math(void)
{
}


Test_Math::~Test_Math(void)
{
}

void Test_Math::RunTest()
{
	Vector vec1(GenerateContinuousNumber(1,5));
	Vector vec2(GenerateContinuousNumber(2,6));
	Vector vec3(GenerateContinuousNumber(3,7));
	vector<Vector> matvec;
	matvec.push_back(vec1);
	matvec.push_back(vec2);
	matvec.push_back(vec3);

	Matrix mat(matvec);
	Vector leftvec(GenerateContinuousNumber(0,4));
	Vector rightvec(GenerateContinuousNumber(4,6));

	Vector leftMulti=leftvec*mat;
	Vector rightMulti=mat*rightvec;



	int a[9]={1,2,6,3,7,8,9,3,2};
	int b[7]={2,9,5,3,3,8,3};
	vector<int> avec=Tovector(a,9);
	vector<int> bvec=Tovector(b,7);
	vector<int> lcs;
	FindLongestCommonSubsequence(avec,bvec,lcs);
	vector<vector<int>> cs;
	FindAllCommonSubsequence(avec,bvec,cs);


	bool match=IsMatch("了的","的空间发生了的就分是了的金佛山");
	int matchCount=MatchCount("了的","的空间发生了的就分是了的金的请哦呜为IE青浦区的快捷方式佛山");
	int matchCount2=MatchCount("的金的请哦呜","的空间发生了的就分是了的金的请哦呜为IE青浦区的快捷方式佛山");

}
