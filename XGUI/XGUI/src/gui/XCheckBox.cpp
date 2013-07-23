#include "XCheckBox.h"

#define BUTTON_H_MARGIN 5 //��ť������BOXˮƽ����
#define BUTTON_V_MARGIN 6 //��ť������BOX��ֱ����

/****************˵��************************/
// 1.checkbox���Բ����ñ�����ɫ
// 2.��ť���жԺ��á��̡� ���������棬Ҳ������λͼ����
/******************************************/


XCheckBox::XCheckBox()
{
	widget_listener=NULL;
	checked =true;
	box_color = 0x000000ff;
	setText("check");
	
	setBackground(0xffffff00);
}
void XCheckBox::setText(const string& text)
{
	int   w,h;
	this->text =text;
	
	if(font)
	{
		font->getFontSize((char *)text.c_str(),&w,&h);
	
		if(w<0 || h < 0)
		{
			w=0;
			h=0;
		}
		button_rect.w=h; //��ť������Ϊ�������߶���ȵ�������
		button_rect.h=h;
		
		text_rect.w=w;  //�ı���
		text_rect.h=h;
		
		w +=2 * BUTTON_H_MARGIN + h;
		h +=2 * BUTTON_V_MARGIN;
		
		setSize(w,h);
	}
}
void XCheckBox::setChecked(bool checked)
{
	this->checked = checked;
	
	if(run_state ==true)
		this->draw();
}
void XCheckBox::setColor(Uint32 color)
{
	this->box_color = color;
}
bool XCheckBox::getChecked()
{
	return this->checked;
}

void XCheckBox::addWidgetListener(XWidgetListener *widget)
{
	this->widget_listener =widget;
}

//**********************************

void XCheckBox::draw()
{
	onDrawBackground(widget_rectF);
	
	if(checked == true)
	{
		rectangleColor(screen,button_rect.x,button_rect.y,button_rect.x+button_rect.w,
				button_rect.y+button_rect.h,box_color);
		
		font->displayFont("��",box_color,button_rect);
		font->displayFont(text.c_str(),box_color,text_rect);
	}else{
		rectangleColor(screen,button_rect.x,button_rect.y,button_rect.x+button_rect.w,
				button_rect.y+button_rect.h,box_color);
		font->displayFont(text.c_str(),box_color,text_rect);
	}
}

void XCheckBox::onInit()
{
	XWidget::onInit();
}

void XCheckBox::onPaint(Uint16 msg)
{
	if(msg == X_PAINT)
	{
		draw();
		//�����	
		if(layout)
			layout->drawChild(widget_rectF,this);
			
	}else if(msg == X_UPDATE )
	{
		paint();	
	}else if(msg == X_BUTTONUP)
	{
		if(checked)
			checked=false;
		else 
			checked=true;
			
		paint();
	}
}
void XCheckBox::paint()
{
	setClipRect(button_rect);
		
	//�ػ��Ƹ����
	if(lucency && parent)
	{
		parent->drawParent(widget_rectF,this);
	}
			
	//���Ʊ����
	draw();
	//�����
	if(layout)	
		layout->drawChild(widget_rectF,this);
	
	showWidget();	
	cleanClipRect();	
}


void XCheckBox::onSize(int w,int h)
{
	XWidget::onSize(w,h);
	
	button_rect.x = widget_rect.x+BUTTON_H_MARGIN;
	button_rect.y = widget_rect.y+BUTTON_V_MARGIN;
	
	text_rect.x = widget_rect.w+widget_rect.x -text_rect.w;
	text_rect.y = widget_rect.y+BUTTON_V_MARGIN;
}
void XCheckBox::onPosition(int x,int y)
{
	XWidget::onPosition(x,y);
	
	button_rect.x = widget_rect.x+BUTTON_H_MARGIN;
	button_rect.y = widget_rect.y+BUTTON_V_MARGIN;
	
	text_rect.x = widget_rect.w+widget_rect.x -text_rect.w;
	text_rect.y = widget_rect.y+BUTTON_V_MARGIN;
}
void XCheckBox::localUpdate(XRectF& pRect,XObject *pObject)
{
	if(pObject == this || !visible)
		return ;
	
	
	draw();
}
