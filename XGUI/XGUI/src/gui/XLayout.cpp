/*
*���еĲ��ֹ������Ļ���
*���ֹ������ȳ䵱�����ְ��ݲ���
*/

#include "XLayout.h"
#include "XAbstractWidegt.h"

XLayout::XLayout()
{
	v_v_num=-1;
	h_v_num=-1;
	min_h=0;
	min_h=0;
	
	//Ĭ���ǲ�����
	h_dock=false;
	v_dock=false;
	
	parent = NULL;
	style = NONE;


/*	m_intHLeftDock = 0;
	m_intHRightDock = 0;
	m_intVTopDock =0;
	m_intVBottomDock = 0;*/
}

XLayout::~XLayout()
{
	list_int.begin();
	
	if( !list_int.isEmpty())
	{
		delete list_int.takeFirst();
		
		while(list_int.isNext())
		{
			delete list_int.next();
		}
	}
}
/*
*����ò����������������߲��ֹ�����������ֵ�������
*���ԾͲ���Ҫȥ����Ƿ���ֵ���
*/
void XLayout::addWidget(XWidget  *widget)
{
	XLYContainer *pContainer;
	
	list_widget.append(widget);
	
	widget->parent=this;  //��������widget�ĸ��ڵ�
	
	pContainer = new XLYContainer;
	pContainer->type = WIDGET;
	pContainer->pObject = widget;
	
	list_int.append(pContainer);
}
//&&ע�⣺�����һ�������ӵ��������������������Ƿ��������Ƿ��Ѽ������
//        �����ӵ��������������Ҳ�������

void XLayout::addLayout(XLayout *layout)
{	
	XLYContainer *pContainer;
	
	list_layout.append(layout);
	
	layout->setParent(this,LAYOUT); //��������layout�ĸ��ڵ�
	
	pContainer = new XLYContainer;
	pContainer->type = LAYOUT;
	pContainer->pObject = layout;
	list_int.append(pContainer);
}

void XLayout::addSpace()
{
	XLYContainer *pContainer;
	
	pContainer = new XLYContainer;	
	pContainer->type = SPACE;
	pContainer->pObject = NULL;
	
	list_int.append(pContainer);
}

void XLayout::insert(int index)
{
	
}

void XLayout::remove(XWidget  *widget)
{
	
}

void XLayout::remove(XLayout  *layout)
{
	
}

void XLayout::remove(int index)
{
	
}

void XLayout::removeAll()
{
	
}

void XLayout::setSize(int w,int h)
{
	if(w < 0) w=0;
	if(h < 0) h=0;
		
	rect.w=w;
	rect.h=h;
}
/*
void XLayout::setHLeftDock(Uint16 dock)
{
	m_intHLeftDock = dock;
}
void XLayout::setHRightDock(Uint16 dock)
{
	m_intHRightDock = dock;
}
void XLayout::setVTopDock(Uint16 dock)
{
	m_intVTopDock = dock;
}
void XLayout::setVBottomDock(Uint16 dock)
{
	m_intVBottomDock = dock;
}
void XLayout::setMargin(Uint16 dock)
{
	m_intMargin = dock;
}
*/
void XLayout::setLaction(int x,int y)
{
	rect.x=x;
	rect.y=y;
}
#include <string.h>
void XLayout::setRect(XRect *rect)
{
	memcpy(&(this->rect),rect,sizeof(XRect));
}

XRect XLayout::getRect()
{
	return rect;
}
XRect XLayout::getMinRect()
{
	XRect swap_rect=rect;
	
	swap_rect.w = min_w;
	swap_rect.h = min_h;
	
	return swap_rect;
}
void XLayout::setParent(XObject* parent,Uint8 style)
{
	this->style = style;
	this->parent=parent;
	
}

LAYOUT_PARENT_STYLE XLayout::getParent(XObject *parent)
{
	parent=this->parent;
	return (LAYOUT_PARENT_STYLE)style;
}

XWidget* XLayout::getWidgetParent()
{
	if(style == WIDGET)
	{
		return (XWidget*)parent;
	}else if(style == LAYOUT)
	{
		return ((XLayout *)parent)->getWidgetParent();
	}
	
	return NULL;
}

void XLayout::compute(int *h_margin,int *v_margin,int *h_variable,int *v_variable)
{
	int w=0;
	int h=0;
	int h_v=0; //ˮƽ�ɱ�����
	int v_v=0; //��ֱ�ɱ�����
	
	h_v=this->getHVariableCount(&w);
	v_v=this->getVVariableCount(&h);
	
	//�ܹ�ˮƽ�������
	int h_count=this->getHCount();
	int v_count=this->getVCount();
	
	if(h_v){
		*h_variable = (rect.w-w-XWidget::h_margin*(h_count+1) )/h_v;
	}
	if(v_v){
	
		*v_variable = (rect.h-h-XWidget::v_margin*(v_count+1) )/v_v;
	}
	
	if(!h_v){
		
		if(h_count){
			*h_margin= (rect.w-w)/(h_count+1);
		}
	}else
	{
		*h_margin=XWidget::h_margin;
	}
	
	if(!v_v)
	{
		if(v_count){
			*v_margin= (rect.h-h)/(v_count+1);
		}
	}else
	{
		*v_margin=XWidget::v_margin;
	}
}


/*���Ҳ����ж�Ӧ��������߲�������*/
bool XLayout::responseEvent(X_Event *event)
{
	XWidget *widget;
	XLayout *layout;
	
	XPOSITION  pos = list_widget.getHeadPosition();
	while(!pos.isEmpty())
	{
		widget = list_widget.getNext(pos);
		if( ((XAbstractWidget* )widget)->responseEvent(event) )
		{
			return true;
		}
	}
		
	pos = list_layout.getHeadPosition();
	while(!pos.isEmpty())
	{
		layout = list_layout.getNext(pos);
		if( layout->responseEvent(event) )
		{
			return true;
		}
	}
	return false;
}


void XLayout::init()
{
	//����߾�


	XPOSITION  pos = list_widget.getHeadPosition();
	while(!pos.isEmpty())
	{
		( (XAbstractWidget* )list_widget.getNext(pos))->onInit() ;
	}
		
	pos = list_layout.getHeadPosition();
	while(!pos.isEmpty())
	{
		 list_layout.getNext(pos)->init() ;
	}	
}
void XLayout::update()
{
	list_widget.begin();
	list_layout.begin();
	
	if(!list_widget.isEmpty() )
	{
		X_Event event;
		event.type = X_PAINT;
		
		( (XAbstractWidget*)list_widget.takeFirst() )->responseEvent(&event);
		
		while(list_widget.isNext())
		{	
			((XAbstractWidget*)list_widget.next())->responseEvent(&event);
		}
		
	}
	
	if(!list_layout.isEmpty())
	{
		list_layout.takeFirst()->update();
		
		while(list_layout.isNext())
		{	
			list_layout.next()->update();
		}
	}
	
}

void XLayout::findOverridingWidget(XRect& pRect,XObject *pObject)
{
	XPOSITION  pos = list_widget.getHeadPosition();
	while(!pos.isEmpty())
	{
		( (XAbstractWidget*)list_widget.getNext(pos) )->findOverridingWidget(pRect,pObject);
	}
	
	pos = list_layout.getHeadPosition();
	while(!pos.isEmpty())
	{
		list_layout.getNext(pos)->findOverridingWidget(pRect,pObject);		
	}
}


void XLayout::drawParent(XRectF& pRect,XObject *pObject)
{
	if(style == LAYOUT)
	{
		((XLayout *)parent)->drawParent(pRect,pObject);
	}else if(style == WIDGET)
	{	
		((XWidget *)parent)->drawParent(pRect,pObject);
	}
}

//�����ӽڵ��ʱ��Ӧ��ƥ���Ƿ񸲸�...
void XLayout::drawChild(XRectF& pRect,XObject *pObject)
{
	XPOSITION  pos = list_widget.getHeadPosition();
	while(!pos.isEmpty())
	{
		
		( (XAbstractWidget*)list_widget.getNext(pos) )->drawChild(pRect,pObject);
	}
	
	pos = list_layout.getHeadPosition();
	while(!pos.isEmpty())
	{
		list_layout.getNext(pos)->drawChild(pRect,pObject);		
	}
	
}

bool XLayout::isChild(XObject *pObject)
{
	XPOSITION  pos = list_widget.getHeadPosition();
	while(!pos.isEmpty())
	{
		if(pObject == list_widget.getNext(pos) )
			return true;
	}
		
	pos = list_layout.getHeadPosition();
	while(!pos.isEmpty())
	{
		if(list_layout.getNext(pos)->isChild(pObject))
				return true;
	}
	
	return false;
}


