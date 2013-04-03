#pragma once
#include "stdafx.h"
#include <string>
#include <fstream>
using namespace std;
typedef vector<CString>     VECCSTRING;
typedef vector<int>         VECINT;
class CStringTransform
{
public:
	CStringTransform()
	{

	}
	~CStringTransform()
	{

	}
    wstring m_wstr;
	char * m_str;
	string m_sstr;
	string GetCurTimes()
	{
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		CString times;
		times.Format(_T("%4d-%02d-%02d %02d:%02d:%02d"),sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond); 
		string lasttime=CStringtostring(times);
		return lasttime;
	}
	//将string类型转换wstring类型
	//返回转换后的数据
	wstring string2wstring(string str)  
	{  
		wstring result;  
		//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
		int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), int(str.size()), NULL, 0);  

		WCHAR* pBuffer = new WCHAR[len + 1];  

		//多字节编码转换成宽字节编码  
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), int(str.size()), pBuffer, len);  

		//添加字符串结尾  
		pBuffer[len] = '\0';             

		//删除缓冲区并返回值  
		result.append(pBuffer);  
		delete[] pBuffer;  

		return result;  
	} 

	//将wstring类型转换string类型
	//返回转换后的数据
	string wstring2string(wstring wstr)  
	{  
		string result;  

		//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
		int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.size()), NULL, 0, NULL, NULL);  
		char* buffer = new char[len + 1];  

		//宽字节编码转换成多字节编码  
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.size()), buffer, len, NULL, NULL);  
		buffer[len] = '\0';  

		//删除缓冲区并返回值  
		result.append(buffer);  
		delete[] buffer;  

		return result;  
	} 

	//编码类型转换
	//返回转换后的数据
	string EncodeUtf8(wstring in) 
	{ 
		string s(in.length()*3+1,' '); 
		size_t len = ::WideCharToMultiByte(CP_UTF8, 0, 
			in.c_str(), int(in.length()), 
			&s[0], int(s.length()), 
			NULL, NULL); 
		s.resize(len); 

		return s; 
	} 

	//将编码类型转换
	//返回转换后的数据
	wstring DecodeUtf8(string in) 
	{ 
		if (in=="")
		{
			return _T("");
		}
		std::wstring s(in.length(), _T(' ')); 
		size_t len = ::MultiByteToWideChar(CP_UTF8, 0, 
			in.c_str(), int(in.length()), &s[0], int(s.length())); 

		s.resize(len); 
		return s; 
	} 

	//主要用于使用char*时将字符串转换为CString
	//返回转换后的数据
	CString CharToCstring(char *p)
	{ 
		CString str;
		if (p==NULL)
		{
			return str;
		}
		wstring tes=string2wstring(p);

		str.Format(_T("%s"),tes.c_str());

		return str;
	}

	//将CString或者是char*转换为宽字符
	//返回转换后的数据
	char* CStringToChar(CString str)
	{
		wchar_t *wp=str.GetBuffer(str.GetLength());
		string  st=wstring2string(wp);
		char *p=(char *)st.c_str();

		return p;
	}

	string CStringtostring(CString str)
	{
		if (str==_T(""))
		{
			return "";
		}
		wchar_t *wp=str.GetBuffer(str.GetLength());
		string  st=wstring2string(wp);

		return st;

	}

	CString  stringToCstring(string str)
	{
		wstring wstr=string2wstring(str);
		CString cstr;
		cstr.Format(_T("%s"),wstr.c_str());		
		return cstr;
	}
	//从服务器接受数据后将字符进行转换
	CString GetUTF8(char *p)
	{
		if(p==NULL)
			return _T("");

		CString strName;
		wstring tes=DecodeUtf8(p);
		strName.Format(_T("%s"),tes.c_str());

		return strName;

	}

	string GetUTFs8(string str)
	{
		if (str=="")
		{
			return "";
		}
		char *p=(char *)str.c_str();
		CString cstr=GetUTF8(p);
		return CStringtostring(cstr);
	}

	string StubToLocal(char *res)
	{
		if (res==NULL)
		{
			return "";
		}
		//将返回值转换为宽字符
		wstring m_utf = DecodeUtf8(res);
		//将宽字符转换为string
		string p = wstring2string(m_utf);
		//在界面显示文字信息

		return p;
	}

	//转换为传输数据
	string LocalToStub(string str)
	{
		if (str=="")
			return "";
		m_str=NULL;
		CString cstr=stringToCstring(str);
		wchar_t *p=cstr.GetBuffer(cstr.GetLength());
		m_sstr=EncodeUtf8(p);
		//cstr.ReleaseBuffer();
		return m_sstr;
	}

	CString stupStringToCstring(string str)
	{
		if (str=="")
		{
			return _T("");
		}
		return GetUTF8((char *)str.c_str());
	}
	string GetDecode(CString str)
	{
		if (str=="")
			return "";
		wchar_t *p=str.GetBuffer(str.GetLength());
		string lstr=EncodeUtf8(p);

		return lstr;
	}

	//转换字符串为double型
	double todouble(string s)
	{
		double res=0;
		try
		{
			int flag=0,xs=0,ws=0;
			int jc=1;
			for(int i=0;i<int(s.size());i++)
			{
				if(s[i]=='.')
				{
					flag=1;
					continue;
				}
				if(flag==0)
				{
					res*=10;
					res+=s[i]-'0';
				}
				else
				{
					ws++;
					xs*=10;
					xs+=s[i]-'0';
				}
			}
			for(int j=0;j<ws;j++)
			{
				jc*=10;
			}
			res+=xs*1.0/jc;

		}catch(exception e)
		{
			res= 0;
		}

		return res;
	}


	string&   replace_all(string&   str,const   string&   old_value,const   string&  new_value)   
	{   
		while(true)   {   
			string::size_type   pos(0);   
			if(   (pos=str.find(old_value))!=string::npos   )   
				str.replace(pos,old_value.length(),new_value);   
			else   break;   
		}   
		return   str;   
	}  


	string&   replace_all_distinct(string&   str,const   string&   old_value,const   string&   new_value)   
	{   
		for(string::size_type   pos(0);   pos!=string::npos;   pos+=new_value.length())   {   
			if(   (pos=str.find(old_value,pos))!=string::npos   )   
				str.replace(pos,old_value.length(),new_value);   
			else   break;   
		}   
		return   str;   
	}   

	BOOL HaveLimiChar(CString str,CString npos)
	{	
		int pos=str.Find(npos,0);
		if (pos>-1 && pos<str.GetLength())
		{
			return TRUE;
		}
		return FALSE;
	}

	//按指定分隔符截取字符串 
	vector<string> split(string src,string tokens)
	{
		vector<string> vect;
		int nend=0;    
		int nbegin=0;    
		while(nend != -1)    
		{    
			nend = int(src.find_first_of(tokens, nbegin));    
			if(nend == -1)    
				vect.push_back(src.substr(nbegin, src.length()-nbegin));    
			else   
				vect.push_back(src.substr(nbegin, nend-nbegin));    
			nbegin = nend + 1;    
		}  
		return vect;

	}

	string  getSqlIds(vector<string> ids)
	{
		string id="";
		int num=int(ids.size());
		for( int i = 0; i < num; i++ )//v.size() 表示vector存入元素的个数
		{

			if(i == ids.size()-1){
				if(ids[i]!="")
				{
					id=id+"'"+ids[i]+"'"; //把每个元素存放到id里面去
				}
				else
				{
					id=id+"''"; //把每个元素存放到id里面去
				}

			}
			else
			{
				id=id+"'"+ids[i]+"',";
				//把每个元素存放到id里面去
			}


		}
		return id;
	}

	bool ReadNewByPath( void** p,unsigned long & count, std::string strPath )
	{
		std::ifstream istrm(strPath.c_str(), std::ios::binary | std::ios::in | std::ios::ate , 0x40);
		if(!istrm)
			return false;
		count = istrm.tellg();
		std::string ext = strPath.substr(strPath.rfind('.') == std::string::npos ? strPath.length() : strPath.rfind('.') + 1);
		int add = 0;
		if(ext == "xml")
			add = 1;
		*p = new char[count+add];
		istrm.seekg(0,std::ios::beg);
		istrm.read((char*)*p,count);
		istrm.close();
		return true;
	}

};