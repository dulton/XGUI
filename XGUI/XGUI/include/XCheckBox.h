#ifndef _XCHECKBOX_H
#define _XCHECKBOX_H

#include "XWidget.h"
#include "XWidgetListener.h"


class XCheckBox:public XWidget
{
public:
	XCheckBox();
	
	void setColor(Uint32 color); //�߿���ɫ��������ɫ
	void setText(const string& text);
	string& getText();
	void setChecked(bool checked);
	bool getChecked();
	
	void addWidgetListener(XWidgetListener *widget);
private:
	virtual void draw();
	virtual void onInit();
	virtual void paint();
	virtual void onPaint(Uint16 msg);
	
	virtual void localUpdate(XRectF& pRect,XObject *pObject);
	virtual void onSize(int w,int h);   //����������֮�����
	virtual void onPosition(int x,int y);
private:
	XRect  button_rect; //��ť��
	XRect  text_rect;   //�ı���
	
	XWidgetListener *widget_listener; //���������
		
	string text;
	Uint32 box_color;
	bool   checked;
};

#endif
