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
	size_t found = str.find_first_of(splitTag, startIndex);//查找分割点的序号
	while (found != string::npos)
	{
		res.push_back(string(str.begin() + startIndex, str.begin() + found));
		startIndex = found + 1;//更新下个起点
		found = str.find_first_of(splitTag, startIndex);
	}
	res.push_back(string(str.begin() + startIndex, str.end()));//弹入最后一段

	return res;
}

string UnicodeToAscii(const wstring& wstr) {
	// 预算-缓冲区中多字节的长度    
	int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	// 给指向缓冲区的指针变量分配内存    
	char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
	// 开始向缓冲区转换字节    
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
		if (wch == 0x000D) // 判断回车  
		{
			strLineAnsi = UnicodeToAscii(wstrLine);
			wstrLine.erase(0, wstrLine.size() + 1);
			index += 4; // 跳过回车符和行开头符  

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
