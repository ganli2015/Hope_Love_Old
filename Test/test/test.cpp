// test.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include "Vector.h"
#include "iMatrix.h"
#include <vector>
#include <time.h>
#include <assert.h>
#include "test_Math.h"
#include "Test_NeuralNetwork.h"
#include "TestGramma.h"
#include "Test_ConceptSet.h"

//#include "APPLE.cpp"
using namespace std;

class A
{
	double a;

public:
	A(){cout<<"a"<<endl;}
	~A(){cout<<"aa"<<endl;}
	A(double val):a(val){}
	double& get(){return a;}
	virtual void set(double)=0;
};
class B:public A
{
	double a;
	double b;
	double c;
public:
	B(){cout<<"b"<<endl;}
	~B(){cout<<"bb"<<endl;}
	B(double val):b(val){}
	B(const B& bb)
	{
		b=bb.b;
	}
// 	B(const A& aa)
// 	{
// 		b=aa.get();
// 	}
	void set(double val)
	{
		b=val;
	}
};

int main(int argc, _TCHAR* argv[])
{
	map<int,string> amap;
// 	amap[3]="谁";
// 	amap[2]="是";
// 	amap[1]="我";

	//char a="我";
// 	char* a="临";
// 	int b=sizeof("哈");
// 	int c=sizeof(a)/sizeof(a[0]);
// 	int c2=strlen(a);
// 	char d=a[0];
// 	char d2=a[1];
// 	char d3=a[2];
// 	char d4=a[3];
// 	char d5=a[4];
// 	char d6=a[5];
// 	char d7=a[10];
// 	int e=(int)(a[0]);
// 	int e2=(int)a[1];
// 
// 
// 	for (int i=0;i<strlen(a);i+=2)
// 	{
// 		char list[3]={a[i],a[i+1]};
// 		char dddd[]={a[i]};
// 		int ccc=strlen(dddd);
// 		char* firstcode=new char(a[i]);
// 		int a1=strlen(firstcode);
// 		char* secondcode=new char(a[i+1]);
// 		strcat(firstcode,secondcode);
// 		int b=strlen(list);
// 	    int a=0;
// 	}

// 	string a("我");
// 	int b1=(int)a[0];
// 	int b2=(int)a[1];
// 	int c=a.size();
   // a.push_back(b);

// 	string a("我是？");
// 	//string::iterator it=find(a.begin(),a.end(),"？");
// 	int b=0;
	


// 	Test_Math::RunTest();
 	Test_NeuralNetwork::RunTest();
//    Test_Gramma::RunTest();
//	Test_ConceptSet::RunTest();
}

