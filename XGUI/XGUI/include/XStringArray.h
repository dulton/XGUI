#ifndef  _XSTRINGARRAY_H
#define _XSTRINGARRAY_H

#include<iostream>
using namespace std;

typedef struct string_data
{
	string data;
	string_data *next;
		
}string_data;

class XStringArray
{
public:
	XStringArray();
	~XStringArray();
	string& getAt(int index);
	void split(string& src,char c);
	void split(string& src,int average);  //ƽ���� ����average��ÿ��string�зֳ���
	void append(string& str);
	void remove(int index);
	int  getCount();
	
	XStringArray& operator=(XStringArray &src);
private:
	
	string_data *head;
	string_data *s;
	
	int   count;
	static bool mark;  //�����
	
};


#endif

