/*�Ի���*/
#ifndef __XDIALOG_H
#define __XDIALOG_H

#include "XWidget.h"
#include "XButton.h"
#include "XHBoxLayout.h"
#include "XMouseListener.h"

typedef enum
{
	CHILD=0x1,
	POP  =0x2,	
	TITLE=0x4
}XDIALOGSTYLE;

class XDialog: public XWidget,public XMouseListener
{
public:
	XDialog();
	~XDialog();
	
	void create(int style);
	void setTitleBG(Uint32 color);// ���ñ�������ɫ
	void setTitle(string text);
	void setMinSize(int w,int h);
	int  doModal();           //����ģʽ�Ի���
	void showWindow(bool nShow);    //��ģʽ�Ի��򣬵�������ΪPOP�Ի���
	void move(int x,int y);
	bool isModal();
protected:	
	void erase();
	virtual void exit();
	virtual void onInit();
	virtual void paint(); //��Ϊpop���
	virtual void onPaint(Uint16 msg);
	virtual void draw();
	virtual bool responseEvent(X_Event *event);
	virtual bool focusEvent(X_Event *event);
	virtual void onSize(int w,int h);
	virtual void onPosition(int x,int y);
	virtual void localUpdate(XRectF& pRect,XObject *pObject);
	
	virtual void mousePressed(X_Event *event,const ID id);
	virtual void mouseReleased(X_Event *event,const ID id);
	virtual void mouseEntered(X_Event *event,const ID id);
private:
	virtual void findOverridingWidget(XRect& pRect,XObject *pObject);
	virtual void computeLayout();
private:

	XWidget         *pOldRoot;
	XLayout         *pTitleLayout;    
	string          m_StrTitleText;
	unsigned int    m_style;
	
	bool           m_bIsPress;
	bool           m_bDisplay;
	
	XSize          m_MinSize;
	XRectF         m_TitleRectF;
	XPoint         m_pointClick;
	
	XButton        m_BtnClose;
	Uint32         m_TitleColor;
	
};

#endif

