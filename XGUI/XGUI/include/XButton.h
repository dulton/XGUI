#ifndef _XBUTTON_H
#define _XBUTTON_H

#include "XWidget.h"
#include "XFont.h"

#define BUTTON_H_MARGIN 8
#define BUTTON_V_MARGIN 6

class XButton:public XWidget
{
public:
	XButton();
	
	void setText(char *text);
	void setFontColor(int color);
	
private:
	
	virtual void draw();
	virtual void onInit();
	virtual void onPaint(Uint16 msg);
	virtual void localUpdate(XRectF& pRect,XObject *pObject);
	//�뿪����
	virtual void focusLeave();
	//���뽹�� 
	virtual void focusEnter();
	
private:	
	char       *text;
	Uint32     font_color;
	
};


#endif

/**
* ��©�������ť�Ƿ�͸���ģ��ػ��Ʊ������ԣ�SDL_FillRect(screen,&rect,color);��
*/


