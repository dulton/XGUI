//��ѡ��ť

#ifndef _XRIDIOBUTTON_H
#define _XRIDIOBUTTON_H

#include "XWidget.h"

class XRadioButton:public XWidget
{
public:
	XRadioButton();
	~XRadioButton();
	
	bool isChecked();
	void setChecked(bool checked);
	void setText(const string& text);
	string& getText();
	
	void setMarginColor(Uint32& color);
	void setFontColor(Uint32& color);
	
private:

	virtual void draw();
	virtual void onInit();
	virtual void onPaint(Uint16 msg);
	virtual void onSize(int w,int h);
	virtual void onPosition(int x,int y);
	virtual void localUpdate(XRectF& pRect,XObject *pObject);
	//�ָ�
	virtual void resumeRidioButton();
	
	void  changSize();
private:
	string mStrText;
	XRect  button_rect; //��ť��
	XRect  text_rect;   //�ı���
	
	Uint32 mFontColor;
	Uint32 m_BoderColor;
		
	static XRadioButton* pCurrentChecked;
};

#endif
