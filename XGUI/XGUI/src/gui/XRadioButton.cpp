#include "XRadioButton.h"

/*  _________
// |_o__text_|
*/
#define BUTTON_H_MARGIN 3 //��ť������BOXˮƽ����
#define BUTTON_V_MARGIN 6 //��ť������BOX��ֱ����

XRadioButton* XRadioButton::pCurrentChecked=NULL;

XRadioButton::XRadioButton()
{
	setText("Radio");
	
	if(!pCurrentChecked)
		pCurrentChecked=this;
	
	m_BoderColor = 0x6e86ffff;
	setBackground(0xffffff00);
	mFontColor=0x00;
}

XRadioButton::~XRadioButton()
{
	
}

bool XRadioButton::isChecked()
{
	if(pCurrentChecked == this) 
		return true;
	else
		return false;
}

void XRadioButton::setChecked(bool checked)
{
	if(run_state)
	{
		pCurrentChecked->resumeRidioButton();
		pCurrentChecked=this;
		onPaint(X_UPDATE);
	}
}
void XRadioButton::setText(const string& text)
{
	int   w,h;
	mStrText=text;
	
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
string& XRadioButton::getText()
{
	return mStrText;
}
void XRadioButton::setFontColor(Uint32& color)
{
	mFontColor=color;
}

void XRadioButton::setMarginColor(Uint32& color)
{
	m_BoderColor = color;
}

/////////////////////////////////////////////////

void XRadioButton::draw()
{
	onDrawBackground(widget_rectF);
	
	if(pCurrentChecked == this)
	{
		//��ť
		circleColor(screen,button_rect.x+button_rect.w/2,button_rect.y+button_rect.h/2,
					button_rect.h/2,m_BoderColor); //button		
				
		filledCircleColor(screen,button_rect.x+button_rect.w/2,button_rect.y+button_rect.h/2,
					button_rect.h/4,m_BoderColor);	
				
		//�ı�
		font->displayFont(mStrText.c_str(),mFontColor,text_rect);
	}else
	{
		//��ť
		circleColor(screen,button_rect.x+button_rect.w/2,button_rect.y+button_rect.h/2,
					button_rect.h/2,m_BoderColor);
		
		//�ı�
		font->displayFont(mStrText.c_str(),mFontColor,text_rect);			
	}
}

void XRadioButton::resumeRidioButton()
{
	setClipRect(widget_rect);
	
	//�ػ��Ƹ����
	if(lucency && parent)
	{
		parent->drawParent(widget_rectF,this);
	}
	
	onDrawBackground(widget_rectF);	
	//��ť
	circleColor(screen,button_rect.x+button_rect.w/2,button_rect.y+button_rect.h/2,
				button_rect.h/2,m_BoderColor);
	//�ı�
	font->displayFont(mStrText.c_str(),mFontColor,text_rect);	
		
	showWidget();
	cleanClipRect();
}

void XRadioButton::onInit()
{
	XWidget::onInit();
}

void XRadioButton::onPaint(Uint16 msg)
{
	if(msg == X_PAINT)
	{
		draw();
		//�����	
		if(layout)
			layout->drawChild(widget_rectF,this);
			
	}else if(msg == X_UPDATE)
	{
		paint();		
	}else if(msg == X_BUTTONUP)
	{
		setChecked(true);
	}
}

void XRadioButton::onSize(int w,int h)
{
	XWidget::onSize(w,h);
	
	changSize();
}
void XRadioButton::onPosition(int x,int y)
{
	XWidget::onPosition(x,y);
	changSize();
}
void XRadioButton::changSize()
{
	button_rect.x = widget_rect.x+BUTTON_H_MARGIN;
	button_rect.y = widget_rect.y+BUTTON_V_MARGIN;
	
	text_rect.x = widget_rect.w+widget_rect.x -text_rect.w;
	text_rect.y = widget_rect.y+BUTTON_V_MARGIN;
	
}

void XRadioButton::localUpdate(XRectF& pRect,XObject *pObject)
{
	if(pObject == this || !visible)
	{	
		return ;
	}
	
	draw();
}
