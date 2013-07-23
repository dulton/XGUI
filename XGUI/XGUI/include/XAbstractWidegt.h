/*
*���������ĳ�����
*/

#ifndef _XABSTRACTWIDGET_H
#define _XABSTRACTWIDGET_H

#include "XUtils.h"
#include "XObject.h"
#include "XEventType.h"
#include "XMouseListener.h"
#include "XUseful.h"
#include "XFont.h"
#include "XList.h"
#include "XKeyListener.h"

class XLayout;
class XWidget;

class XAbstractWidget:public XObject
{
public:
	XAbstractWidget();
	bool isFocus();
	
	/*�õ�������ڴ�С*/
	XRect getRect();
	/* �õ��������*/
	XRectF getRectF();
	
	//���������ˢ�´���������ҷ����ػ���Ϣ,����������֮�����
	void showWidget(); 
	void show(XRectF& pRect);
	void show(XRect rect);
	void showFillScreen();
	
	//���ÿ�д������
	void setClipRect(XRect rect);
	void cleanClipRect();
	XRect getClipRect();
	void setPreClipRect(); //�����ϴ�����clip������
	
	bool match(XRectF& rectF);
	
	static void setFirstRoot(XAbstractWidget *root);
	static void setRoot(XAbstractWidget  *root);
	static XWidget* getRoot();
	static void setFocusWidget(XAbstractWidget  *focus);
	//�ڶ����������Է���ϵͳ��Ϣ,ͨ����Ϣ���зַ���ȥ
	static void sendSystemMsg(X_Event *user);
	//������ϲ�����������Tooltip
	static void addGlobalHigh(XAbstractWidget  *global);
	//����²����������dialog
	static void addGlobalLow(XAbstractWidget  *global);
	static void removeGlobalHigh(XAbstractWidget  *global);
	static void removeGlobalLow(XAbstractWidget  *global);

	//ȫ������¼���ѯ
	static bool globalPoll(X_Event *event);
	//ˢ��root�ϲ��������
	static void updateAllGlobal(XAbstractWidget  *pObject);
	static void updateGlobalHighUp(XAbstractWidget  *global,XRectF& RectF);     //ˢ�����ϲ��������
	static void updateGlobalHighDown(XAbstractWidget  *global,XRectF& RectF);  //ˢ�����ϲ��������
	static void updateGlobalLowUp(XAbstractWidget  *global,XRectF& RectF);     //ˢ���²���������
	static void updateGlobalLowDown(XAbstractWidget  *global,XRectF& RectF);   //ˢ���²���������

#ifdef USE_MOUSE	
	void setMouseListener(XMouseListener *mouse); //�������¼�����
#endif	

#ifdef USE_KEYBOARD
	void setKeyListener(XKeyListener *key);
#endif
//�ɸ��Ǻ���	
	/*
	*�¼���Ӧ����
	*���е��������ʵ������ӿ�
	*����ֵΪbool��������һ���¼�����֮���Ƿ����ö���
	*/
	virtual bool responseEvent(X_Event *event);
	//�������Ϊ���������ʱ����Ӧ�¼�����
	virtual bool focusEvent(X_Event *event)=0;
	virtual bool devEvent(X_Event *event);
	
	//��Ӧ�÷������ӦΪ��Щ���û�м��뵽Layout������
	virtual void setLayoutRect(XRect* rect);
	virtual void setLayoutSize(Uint16 w,Uint16 h);
	
	/**
	*���ұ�������ǵ���������ػ������Ǽ��ػ���������ӽڵ�
	*/	
	virtual void findOverridingWidget(XRect& pRect,XObject *pObject){}
	
	//�ػ����������
	virtual void drawChild(XRectF& pRect,XObject *pObject);
	virtual void drawParent(XRectF& pRect,XObject *pObject);
	virtual void localUpdate(XRectF& pRect,XObject *pObject)=0;
	
	virtual void mouseLPressEvent(X_Event *event){  onPaint(X_BUTTONDOWN); }
	virtual void mouseLReleaseEvent(X_Event *event){ onPaint(X_BUTTONUP); }
	virtual void mouseMPressEvent(X_Event *event){}
	virtual void mouseMReleaEvent(X_Event *event){}
	virtual void mouseRPressEvent(X_Event *event){}
	virtual void mouseRReleaseEvent(X_Event *event){}
	virtual void mouseWheelDown(X_Event *event){}
	virtual void mouseWheelUp(X_Event *event){}
	
	virtual void mouseEnterEvent(X_Event *event){}
	virtual void mouseLeaveEvent(X_Event *event){}
	
	virtual void keydownEvent(X_Event *event){}
	virtual void keyReleaseEvent(X_Event *event){}
	
	virtual void touchScreenPressEvent(X_Event *event){}
	virtual void touchScreenReleaseEvent(X_Event *event){}
	
	//�뿪����
	virtual void focusLeave();
	//���뽹�� 
	virtual void focusEnter();
	virtual void loseFocus();
	
	//��ʼ�����õĺ������˺����ڲ����Ժ󱻵���
	virtual void onInit();
	//erase
	virtual void onPaint(Uint16 msg);
	
	//����������֮����ã��ȵ���onSize,�ٵ��õ�onPosition
	virtual void onSize(int w,int h)
	{
		widget_rectF.x2=widget_rect.x+w;
		widget_rectF.y2=widget_rect.y+h;
		
	}   
	virtual void onPosition(int x,int y)
	{	
		widget_rectF.x1=x;
		widget_rectF.y1=y;
	} 
	
	/*
	*��ʱ��
	*/
	SDL_TimerID setTimer(unsigned int interval);
	void removeTimer(SDL_TimerID timerID);
	virtual void onTiemer();
	
	XSize getWindowSize();
	
protected:
	//�����λ��
	XRect  widget_rect;
	XRectF widget_rectF;
	//�������λ��
	XPoint centerPoint;
	
	bool 	  visible;       //����Ƿ�ɼ�
	bool      lucency;       //�Ƿ�͸��
	bool      run_state;     
	Uint8     widget_state;  //�������״̬������,����,��ͣ
	
	static XSurface 	*screen;  //SDL surface
	static XFont      *share_font; //�������Ĭ������
	static XRect      preClipRect;

	static XAbstractWidget  *root_widget;
	static XAbstractWidget  *focus_widget;
	static XAbstractWidget  *first_root;

	static XList<XAbstractWidget* > m_listHigh;
	static XList<XAbstractWidget* > m_listLow;
	static XList<XAbstractWidget* > m_listPollLow;

#ifdef USE_MOUSE		
	XMouseListener *mouse_listener; //����¼�
#endif

#ifdef USE_KEYBOARD
	XKeyListener  *key_listener;
#endif
};

#endif
