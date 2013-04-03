////////////////////////////////////////////////////////////////////////////////
//      
//      ��������ת��
//      
//      File      : DataChange.h
//      Version   : 1.0
//      Comment   : ���ַ��Ͷ��ַ�֮���ת��
//                  �ַ�����֮���ת��
//      
//      Create at : 2011-08-31
//		Create by : liu  
//      
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include <string>
#include <fstream>
#include "../KUILib/Include/kscbase/kscres.h"
using namespace std;
typedef vector<CString>     VECCSTRING;
typedef vector<int>         VECINT;
class CDataChange
{
public:
	CDataChange()
	{

	}
	~CDataChange()
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
	//��string����ת��wstring����
	//����ת���������
	wstring string2wstring(string str)  
	{  
		wstring result;  
		//��ȡ��������С��������ռ䣬��������С���ַ�����  
		int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), int(str.size()), NULL, 0);  

		WCHAR* pBuffer = new WCHAR[len + 1];  

		//���ֽڱ���ת���ɿ��ֽڱ���  
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), int(str.size()), pBuffer, len);  

		//����ַ�����β  
		pBuffer[len] = '\0';             

		//ɾ��������������ֵ  
		result.append(pBuffer);  
		delete[] pBuffer;  

		return result;  
	} 

	CString getBirthdayMin(int age)
	{
		CTime tm=CTime::GetCurrentTime();
		int lyear = tm.GetYear()-age;
		CString year;
		year.Format(_T("%d"),lyear);
		return year+"-01-01";
	}

	CString getBirthdayMax(int age)
	{
		CTime tm=CTime::GetCurrentTime();
		int lyear = tm.GetYear()-age;
		CString year;
		year.Format(_T("%d"),lyear);
		return year+"-99-99";
	}

	//��wstring����ת��string����
	//����ת���������
	string wstring2string(wstring wstr)  
	{  
		string result;  

		//��ȡ��������С��������ռ䣬��������С�°��ֽڼ����  
		int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.size()), NULL, 0, NULL, NULL);  
		char* buffer = new char[len + 1];  

		//���ֽڱ���ת���ɶ��ֽڱ���  
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.size()), buffer, len, NULL, NULL);  
		buffer[len] = '\0';  

		//ɾ��������������ֵ  
		result.append(buffer);  
		delete[] buffer;  

		return result;  
	} 

	//��������ת��
	//����ת���������
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

	//����������ת��
	//����ת���������
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

	//��Ҫ����ʹ��char*ʱ���ַ���ת��ΪCString
	//����ת���������
	CString CharToCstring(char *p)
	{ 
		CString str="";
		if (p==NULL)
		{
			return str;
		}
		wstring tes=string2wstring(p);

		str.Format(_T("%s"),tes.c_str());

		return str;
	}

	//��CString������char*ת��Ϊ���ַ�
	//����ת���������
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
	//�ӷ������������ݺ��ַ�����ת��
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
		//������ֵת��Ϊ���ַ�
		wstring m_utf = DecodeUtf8(res);
		//�����ַ�ת��Ϊstring
		string p = wstring2string(m_utf);
		//�ڽ�����ʾ������Ϣ

		return p;
	}

	//ת��Ϊ��������
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

	//�ָ���
	CString getDelimiter()
	{
		return ";";
	}
	CString getDelimiterCStr(CString str,int startpos=0,int endpos=0)
	{
		if (startpos<str.GetLength()&& str!="")
		{
			int pos=str.Find(getDelimiter(),startpos);
			str=str.Mid(startpos,pos);

			return str;
		}
		return _T("");
	}

	//��÷ָ��ַ������ƶ�λ��
	int getDelimiterendPos(CString str,int startpos=0)
	{
		int pos=str.Find(getDelimiter(),startpos);
		return pos;
	}


	//��������
	//��������������
	//���أ�����Ŀǰʱ��ͳ������ڵõ��������С
	CString getAge( string s )
	{
		if(s=="")
		{
			return _T("");
		}
		if(s.length() <= 3)
		{
			return stringToCstring(s);
		}
		wstring wstr=string2wstring(s);
		CString str;
		str.Format(_T("%s"),wstr.c_str());	

		int endpos=str.Find(_T("-"),0);
		str=str.Mid(0,endpos);

		int birthDay=atoi(CStringtostring(str).c_str());
		time_t timer=time(NULL); 
		time(&timer); 
		string nowtime=ctime(&timer);

		CString nowTimes=stringToCstring(nowtime);
		nowTimes=nowTimes.Right(5);
		int nowyear=atoi(CStringtostring(nowTimes).c_str());

		int age=nowyear-birthDay;
		str.Format(_T("%d"),age);

		return str;
	}

	//ת������Ϊ����
	CString getBirthday(string age)
	{
		int age1= atoi((char *)age.c_str());
		CTime tm=CTime::GetCurrentTime();
		int lyear = tm.GetYear()-age1;
		int lmonth = tm.GetMonth();
		int lday = tm.GetDay();

		long t=GetTickCount();
		CString year,month,day;
		year.Format(_T("%d"),lyear);
		month.Format(_T("%d"),lmonth);
		day.Format(_T("%d"),lday);
		return year+"-"+month+"-"+day;
	}


	//ת���ַ���Ϊdouble��
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

	//��ָ���ָ�����ȡ�ַ��� 
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
		for( int i = 0; i < num; i++ )//v.size() ��ʾvector����Ԫ�صĸ���
		{

			if(i == ids.size()-1){
				if(ids[i]!="")
				{
					id=id+"'"+ids[i]+"'"; //��ÿ��Ԫ�ش�ŵ�id����ȥ
				}
				else
				{
					id=id+"''"; //��ÿ��Ԫ�ش�ŵ�id����ȥ
				}

			}
			else
			{
				id=id+"'"+ids[i]+"',";
				//��ÿ��Ԫ�ش�ŵ�id����ȥ
			}


		}
		return id;
	}

	HBITMAP GetMyImageByPath( const std::string& strID )
	{
		HBITMAP retval = NULL;
		void* pBuffer = NULL;
		unsigned long dwBuffer = 0;

		if(!ReadNewByPath(&pBuffer,dwBuffer,strID))
			return false;
		retval =KAppRes::Instance().LoadNewAnImage(pBuffer, dwBuffer);
		if (!retval)
		{
			KAppRes::Instance().FreeRawData(pBuffer);
		}
		return retval;
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