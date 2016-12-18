#include "stdafx.h"
#include "CommonTools.h"
#include "windows.h" 


CommonTools::CommonTools()
{
}


CommonTools::~CommonTools()
{
}

vector<string> CommonTools::SplitString(const string& str, const char splitTag)
{
	vector<string> res;
	int startIndex = 0;
	size_t found = str.find_first_of(splitTag, startIndex);//���ҷָ������
	while (found != string::npos)
	{
		res.push_back(string(str.begin() + startIndex, str.begin() + found));
		startIndex = found + 1;//�����¸����
		found = str.find_first_of(splitTag, startIndex);
	}
	res.push_back(string(str.begin() + startIndex, str.end()));//�������һ��

	return res;
}

string UnicodeToAscii(const wstring& wstr) {
	// Ԥ��-�������ж��ֽڵĳ���    
	int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	// ��ָ�򻺳�����ָ����������ڴ�    
	char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
	// ��ʼ�򻺳���ת���ֽ�    
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
	string ret_str = pAssii;
	free(pAssii);
	return ret_str;
}


std::string CommonTools::Getline_UnicodeFile(ifstream& fin, size_t& index)
{
	wstring wstrLine = L"";
	string strLineAnsi = "";

	while (true)
	{
		fin.seekg(index, ios::beg);
		wchar_t wch;
		fin.read((char *)(&wch), 2);
		if (wch == 0x000D) // �жϻس�  
		{
			strLineAnsi = UnicodeToAscii(wstrLine);
			wstrLine.erase(0, wstrLine.size() + 1);
			index += 4; // �����س������п�ͷ��  

			break;
		}
		else
		{
			wstrLine.append(1, wch);
			index += 2;
		}
	}

	return strLineAnsi;
}
