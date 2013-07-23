/*
*���еĲ��ֹ������Ļ���
*���ֹ������ȳ䵱�����ְ��ݲ���
*/

#ifndef _XLAYOUT_H
#define _XLAYOUT_H

#include "XList.h"
#include "XUtils.h"
#include "XObject.h"
#include "XWidget.h"

typedef enum 
{
	LAYOUT,
	WIDGET,
	SPACE,
	NONE	
}LAYOUT_PARENT_STYLE;


typedef struct
{
	Uint8   type;	
	XObject *pObject;
		
}XLYContainer;


class XWidget;

class XLayout:public XObject
{
public:
	
	XLayout();
	~XLayout();
	
	void addWidget(XWidget  *widget);
	void addLayout(XLayout *layout);
	void addSpace();
	//�����Ǹ��ڼ���ǰ��
	void insert(int index);
	
	void remove(XWidget  *widget);
	void remove(XLayout  *layout);
	void remove(int index);
	
	void removeAll(); //�����⣬ע��...
	/*
	*�������е�������߲��ַ���λ�õĽӿ�
	*����̳�ʵ��������
	*/
	virtual void computeLayout()=0;
	
	/*
	*����ˮƽ�ɱ�����������ֱ�ɱ�����������   ��ʹ�Ǵ��ڷ����仯��Ŀ����С�߶ȺͿ���ǲ���仯��
	*��һ�����������õ�BOXˮƽ��С���
	*�ڶ������������õ�BOX��ֱ��С�߶�
			W
		_________
		|
	H	|
		|
	*/
	virtual int getHVariableCount(int *w,bool cal=false)=0;
	virtual int getVVariableCount(int *h,bool cal=false)=0;
	
	/*�ֱ��Ƿ���ˮƽ����ֱBOX���������(�����ӽڵ�)*/
	virtual int getHCount()=0;
	virtual int getVCount()=0;
	
	void setHDock(bool dock){this->h_dock =dock;}
	void setVDock(bool dock){this->v_dock =dock;}
	/*
	void setHLeftDock(Uint16 dock);    //ˮƽ��߾�
	void setHRightDock(Uint16 dock);   //ˮƽ�ұ߾�
	void setVTopDock(Uint16 dock);     //ˮƽ��߾�
	void setVBottomDock(Uint16 dock);  //ˮƽ�ұ߾�
	void setMargin(Uint16 dock);       //�����ı߾�
	*/
	void compute(int *h_margin,int *v_margin,int *h_variable,int *v_variable);
	void findOverridingWidget(XRect& pRect,XObject *pObject);
	void drawChild(XRectF& pRect,XObject *pObject);
	void drawParent(XRectF& pRect,XObject *pObject);
	
	/*
	*���ò��ֵ�λ��
	*/
	void  setLaction(int x,int y);
	void  setSize(int w,int h);
	
	void setRect(XRect *rect);
	
	//���ز����������ڵĴ�С��λ��
	XRect getRect();
	//���ز���������С��С��λ��
	XRect getMinRect();	
	
	bool isChild(XObject *pObject);
	
	/*
	*�ַ��¼�
	*/
	bool responseEvent(X_Event *event);
	void update();
	void init();	
	void setParent(XObject* parent,Uint8 style); //���ò��ֵĸ��ڵ�
	//���ظ��ڵ����ͣ�����parent�Ǹ��ڵ����ָ��
	LAYOUT_PARENT_STYLE getParent(XObject* parent); 
	XWidget  *getWidgetParent(); // �õ�Widget�����


protected:
	
	int      v_v_num;    //��ֱ�ɱ��������
	int      h_v_num;   //ˮƽ�ɱ��������
	Uint16   min_h;
	Uint16   min_w;
	
	XRect  rect;
	
	/*
	*��һ�����������
	*�ڶ����ǲ�������
	*/
	
	XList<XWidget  *>   list_widget;
	XList<XLayout  *>   list_layout;
	
	//XList<Uint8>          list_int;
	XList<XLYContainer *>  list_int;
	
	bool                h_dock; //�Ƿ���
	bool                v_dock; //�Ƿ���
/*	
	Uint16          m_intHLeftDock;    //ˮƽ��߾�
	Uint16          m_intHRightDock;   //ˮƽ�ұ߾�
	
	Uint16          m_intVTopDock;     //ˮƽ��߾�
	Uint16          m_intVBottomDock;  //ˮƽ�ұ߾�

	Uint32          m_intMargin;       //�����ı߾�
	*/
	Uint8           style;   //���ڵ����ͣ���������(��������ָ��XWidget*, XLayout *)�ĺô�����֤��ֻ��һ�����ڵ�
	XObject  		*parent; //���ڵ㣬�����ǲ���������Ҳ������XWidget
};

#endif


