#ifndef _XFONT_H
#define _XFONT_H

#include "XObject.h"
#include "XUtils.h"
#include "XApplication.h"

typedef enum
{
	
	

}FONT_TYPE;


class XFont:public XObject
{
public:
	XFont();
	~XFont();
	void setSize(int size);
	void setFontType(FONT_TYPE type);
	void setFontColor(Uint32 color); //��ʱûʹ��...
	
	void getFontSize(const char *text,int *w,int *h);
	int  getFontHeight();
	int  getFontWidth(const char *text);
	
/************************���漸������˵��**********************/
// 1.��һ������:����(x,y)����Ϊ��׼��ʾ�ַ���
// 2.�ڶ�������:��text��ʾ��outside�м�,left���-1����ʾ���м䣬���򰴸����ı߾�
// 3.����������:ͬ2,������text������»���
// 4.���ĸ�����:��text����outside�ϱߺ������ʾ
// 5.���������:��text�����һ���ַ�Ϊ��׼������Outside������ʾ
// 6.����������:��text�Ե�һ���ַ�Ϊ��׼������outside������ʾ
// 7.���߸�����:����text,��ʾ��outside���ϲ���effside
// 8.�ڰ˸�����:����text,��ʾeffSide����
/**********************************************************/
	void displayFont(const char *text,int color,int x,int y);
	void displayFont(const char *text,int color,const XRect& outside,const int& left=-1);
	void displayFontUnder(const char *text,int color,const XRect& outside,bool left=false);
	void display(const char *text,int color,const XRect& outside); 
	void displayRight(const char *text,int color,const XRect& outside);
	void displayLeft(const char *text,int color,const XRect& outside);
	
	void displayTop(const char *text,int color,const XRect& outside,const XRect& effSide);
	void displaySection(const char *text,int color,const XRect& outside,const XRect& effSide,
				const int& left=-1);
	
	//���ܻᳬ��outside������ͨ��setClipRect���ÿ�д��Ļ����
	void fastDisplayFont(const char *text,int color,const XRect& outside,const int& left);
	
	/*�����ʹ��Ĭ������⣬�����ֶ��ͷ�*/
	void freeFont();
private:
	bool init();	
private:

	/*���˴���һ��Ĭ��ttfָ���ԭ���ǣ�����һ��ttfʵ��̫�ķ��ڴ���
	  �������ʹ��Ĭ���ֿ⣬���Թ���һ��ttf
	*/
	static TTF_Font  *dafult_font;
	static int       dafult_size;
	Uint32           font_color;
	
	Uint16     font_size;
	TTF_Font  *font;
	char      *font_name;
	
	friend class XApplication;
};


#endif
