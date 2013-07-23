//�����˵�,��һ����̬���

#ifndef __XPOPMENU_H
#define __XPOPMENU_H

#include "XArray.h"
#include "XAbstractWidegt.h"
#include "XItem.h"

class XPopMenu:public XAbstractWidget
{
public:
	XPopMenu();
	~XPopMenu();
	
	void addItem(string text);
	void addItem(XItem& item);
	//popmenu���Բ���ɾ��item
	void removeItem(int item);
	void setMarginLeft(const int& left);
	
	//����item������ɫ
	void setItmeColor(Uint32 color);
	//���÷ָ�����ɫ
	void setDividerLine(Uint32 color);
	// ��ӷָ��ߣ��������ò�ͬ�ķָ��� ...ûʵ��
	void setDividerLine(); 
	
	void setPosition(int x,int y);
	void setMaxSize(int w,int h);
	
	//false��ʾ��true����ʾ
	void show(bool nShow);
protected:
	
	//���ñ���
	virtual void onDrawBackground(XRectF& rectF);
	virtual void onSize(int w,int h);
	virtual void onPosition(int x,int y);
	virtual void localUpdate(XRectF& pRect,XObject *pObject);
	
	bool responseEvent(X_Event *event);
	bool focusEvent(X_Event *event); //���������Ϊ�������ʱ��Ӧ�¼�
	
private:
	void update(){}
	void changSize();
	//����
	void paint();
	void erase();
	XItem * selectIndex(X_Event *event);
private:
	
	bool           run_state;
	int            m_indexTop; //��ʾ���������item
	
	XSize          m_MaxSize;

	XArray<XItem*> m_array; //item����
	Uint16         m_left; //item��߱߾�
	Uint32         m_itemBGColor;
	Uint32         m_dividerColor;
	
	static XItem *pSelectItem;    //�Ѿ�ѡ�е�Item
};

#endif
