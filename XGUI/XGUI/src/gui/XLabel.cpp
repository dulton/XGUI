#include "XLabel.h"

#define LABEL_H_MARGIN 8 //����text������߿�ˮƽ����
#define LABEL_V_MARGIN 6 //����text������߿���ֱ����

XLabel::XLabel()
{
	is_underLine=false;
	
	screen=NULL;
	font_color=0x000000ff;
	
	setBackground(0xffffff00);
	
	string str="hell,world";
	setText(str);
}
void XLabel::setFontColor(Uint32 color)
{
	font_color=color;
}
void XLabel::setText(string text)
{
	int   w,h;
	
	this->text=text;
	font->getFontSize(text.c_str(),&w,&h);
	
	if(w<=0 || h < 0)
	{
		w=LABEL_H_MARGIN;
		h=0;
	}
	
	w+=1;
	
	//������ڵ㲻�ǲ�����������ô�����к�text�����仯�������²���
	
	if(parent)
		setSize(w,h);
	else
		setLayoutSize(w,h);
}

void XLabel::setUnderLine(bool underLine)
{
	is_underLine=underLine;
}
/************************************************/
void XLabel::onInit()
{
	XWidget::onInit();
}
void XLabel::draw()
{
	onDrawBackground(widget_rectF);
		
	if(is_underLine)
		font->displayFontUnder(text.c_str(),font_color,widget_rect,true);
	else
		font->displayFont(text.c_str(),font_color,widget_rect,true);	
}

void XLabel::onPaint(Uint16 msg)
{
	if(msg == X_PAINT)
	{
		draw();
		
		//�����	
		//if(layout)
		//	layout->drawChild(widget_rectF,this);
			
	}else if(msg == X_UPDATE)
	{
		setClipRect(widget_rect);
		
		//�ػ��Ƹ����
		if(lucency && parent)
		{
			parent->drawParent(widget_rectF,this);
		}
		
		draw();	
		//�����
		//if(layout)	
		//	layout->drawChild(widget_rectF,this);
		
		showWidget();	
		cleanClipRect();		
	}
}

void XLabel::localUpdate(XRectF& pRect,XObject *pObject)
{
	if(pObject == this || !visible)
		return ;
		
	this->draw();
}
