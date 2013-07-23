/*
*�������һ���б��
*/

#ifndef _XLISTBOX_H
#define _XLISTBOX_H

#include "XWidget.h"
#include "XItem.h"
#include "XIndexListener.h"
#include "XVScrollbar.h"

class XVScrollbar;

class XListBox:public XWidget
{
public:
	XListBox();
	~XListBox();

	void addItem(string text);
	void addItem(XItem& item);
	void removeItem(int item);
	void removeAll();
	
	void setItmeColor(Uint32 color);
	void setDividerLine(Uint32 color);
	void addDividerLine(); // ��ӷָ��ߣ��������ò�ͬ�ķָ��� ...ûʵ��
	
	void addIndexlistener(XIndexListener *listener);
	void setLeftMargin();
	int&  CurrentIndex();//����ѡ�е�����
	
protected:
	
	XItem * selectIndex(X_Event *event);
	void setItemWidth(); //�����Ե�item���ÿ��
	
	void resumeItem(); //�ָ�item
	void setResumeItem(XListBox *list,XItem *item);//������Ҫ�ָ�Item��List
	void paintSelectItem(XItem *item);
	
	//�����ÿ��Item����λ��
	void compute(int MoveLength);
	virtual void initDraw(); //��ʼ������listbox
	virtual void draw();     //�ǳ���ʼ������
	virtual void onInit();
	virtual void onPaint(Uint16 msg);
	virtual void onSize(int w,int h);
	virtual void onPosition(int x,int y);
	virtual void changSize();//item���ܳ��ȱ仯��������ListBox��С�仯
	virtual void localUpdate(XRectF& pRect,XObject *pObject);
	
	virtual void mouseWheelDown(X_Event *event);
	virtual void mouseWheelUp(X_Event *event);
	virtual void mouseLPressEvent(X_Event *event);
private:
	
	XVScrollbar vScrollbar;//��ֱ������
	XIndexListener *indexListener;
	
	XList<XItem *> list_item;
	
	XItem *top_item;     //������ʾ��������item
	XItem *bottom_item;  //������ʾ�����һ��item
	
	int top_position;    //������ʾ��������item��Y1���� 
	int bottom_position; //������ʾ��������item��Y2����
	
	Uint32 divider_color;
	Uint32 item_color;
	
	int index;              //ѡ��Item������ֵ
	
	static XListBox *pList; //��Ҫ�ָ���List
	static XItem    *pItem;    //�Ѿ�ѡ�е�Item
 
};

/*

*bug: ���item�ĳ��������к����仯����ô�������Ͳ�����
*/

#endif

