#ifndef _XITEM_H
#define _XITEM_H

#include "XAbstractWidegt.h"

class XWidget;

typedef enum
{
	SECTION,
	ALL
}ITEM_TYPE;

class XItem:public XAbstractWidget
{
public:
	XItem(XWidget *parent=NULL);	
	void setText(string& text);
	string& getText();
	void setFontColor(Uint32 color);
	void setMarginLeft(const int& left);   //��������
	void setMarginTB(const int& tb);       //�������¼��
	void setFont(XFont *font);             //��������
	void setWidth(const int& w);           //���ÿ��
	int  getItemMinWidth();
	const Uint16& getHeight();
	XPoint getPosition();
	
	void setIcon();                // �ȴ����...
	XRect getEffective();          //�õ���Ч����
	void show();
private:
	
	bool focusEvent(X_Event *event){return false;}
	void setLocation(Uint16 x,Uint16 y);//����λ��
	
	//����û��
	void curHeight();                   //����H
	
	//������������Ҳ��ˢ�µ���Ļ
	void paint(Uint32 &divider_color,Uint32& bg);
	//����ͱ���һ�𻭳������ǲ�ˢ�µ���Ļ
	void paintAll(Uint32 &divider_color,Uint32& bg);
	//������ĳһ��ʱ���ã��˺�����ˢ�µ���Ļ����֪ͨ��������ػ���
	void paintUpdate(Uint32 &divider_color,Uint32& bg);
	//���ػ�ĳһ���ǵ��ô˺�������ĳһ���п��ܲ�����ȫ��
	SDL_Rect paint(XDC *pdc,Uint32 &divider_color,Uint32& bg);
	//��������...
	void paint(XDC *pdc,ITEM_TYPE type,Uint32 &,Uint32&);
	
	void draw(Uint32 &divider_color,Uint32& bg);
	
	virtual void onPaint(Uint16 msg);
	virtual void localUpdate(XRectF& pRect,XObject *pObject){};
	virtual void onSize(int w,int h);
	virtual void onPosition(int x,int y);
private:
		
	string text;
	Uint32 font_color;
	
	Uint8  margin_L;     //���� 
	Uint8  margin_TB;    //�ϱ߼����±߼��
	
	XFont *font;
	XWidget *parent;
	
	friend class XListBox;
	friend class XPopMenu;
};

#endif
