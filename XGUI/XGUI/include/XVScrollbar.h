//ˮƽ������

#ifndef _XVSEPARATOR_H
#define _XVSEPARATOR_H

#include "XAbstractWidegt.h"


class XListBox;

class XVScrollbar:public XAbstractWidget
{
public:
	XVScrollbar();
	void setBgColor(Uint32 color);
	void setWidth(int& w);
private:

	void setLayoutRect(XRect* rect){}
	void setLayoutSize(Uint16 w,Uint16 h){}
	
	void update(){}
	bool responseEvent(X_Event *event){ return false;}
	bool focusEvent(X_Event *event){return false;}
	
	XRect* getRect();
	//����������������
	void setRect(XRect& rect); //���ṩ�������ÿ��
	void setParentLength(int& length);//����������ĳ���
	
	void setScrollbarBottom(); //��scrollbar���õ�������
	void setScrollbarTop();    //��scrollbar���õ�������
	
	int getScrollbarTopLength();
	int getScrollbarBottomLength();
	
	void computeScrollbar();//���㻬��ĳ���
	void move(int& length);//��������������ĳ���,������λ��,���õ��������������Rect
	void paint();
	
	void drawChild(XRectF& pRect,XObject *pObject){};
	void drawParent(XRectF& pRect,XObject *pObject){};
	void localUpdate(XRectF& pRect,XObject *pObject);
private:
	Uint32 BgColor;//���鱳��ɫ
	
	bool   run_state;
	Uint16 scrollbar_position;//�����λ��
	int    parentMoveLength;  //��������ƶ��ľ���
	int    parent_length;     //��������ĳ���
	
	XRect  scrollbar_rect;
	
	float  scale; //���黬��һ�����ص㣬���������ʵ�ʹ����೤
	
	friend class XListBox;
};

#endif

