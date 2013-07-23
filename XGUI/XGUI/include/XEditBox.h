#ifndef _XEDITBOX_H
#define _XEDITBOX_H

#include "XWidget.h"
#include "XTextListener.h"

/***************˵��*******************/
// 1.BCursor �Ǳ༭�������Ĺ��
// 2.ע��������λ�õ�ʱ������ȴ���screen
// 3.�ڵ�һ��run֮ǰҪ�����ù���λ��
/*************************************/

class BCursor
{
public:
	BCursor();
	~BCursor();
	void run();
	void stop();
	void setLocation(Uint16 x,Uint16 y);
	Uint16 getX();
	void setHeight(Uint16 h);
	void add(XSurface *screen);
	void setCursorColor(Uint32 color);
	void paint();
	bool getState();
	void resume();
private:
	
	bool   state;
	bool   visible;
	Uint16 x,y;
	Uint16 height;
	Uint32 cursor_color;
	SDL_TimerID m_timerId;
	void       *clone_creen;
	XSurface 	*screen;
	
	XWidget *m_wParent;
};

class XEditBox:public XWidget
{
public:
	XEditBox();
	
	void setFontColor(Uint32 color);//����������ɫ
	void setBoxColor(Uint32 color);//������߿���ɫ
	void setText(string text);    
	string& getText();
	void setEdit(bool eidt); //�����Ƿ�ɱ༭  ��û��...
	void setPassword(bool password); //û��...
	//����ֻ���������� ...
	//����ֻ������Ӣ�� ...
	//�����Ƿ�ɱ༭...	
private:
	
	void init();
	int computeCursor(const int& x);
	void deleteFont();
	void CursorRightMove(); //�������һ���ַ�
	void CursorLeftMove();  //�������һ���ַ�
	
	virtual void draw();
	virtual void onInit();
	virtual void onPaint(Uint16 msg);
	virtual void mouseLPressEvent(X_Event *event);
	virtual void mouseLReleaseEvent(X_Event *event);
	virtual void localUpdate(XRectF& pRect,XObject *pObject);
	virtual void keydownEvent(X_Event *event);
	
private:
	
	int    start_pointer;  //�༭����ʾ��һ�����ֵĵ�ַ
	int    cursor_addr;    //�������λ��
	int    cursor_postion; //�����༭��ߵľ���
	
	Uint32 font_color;   //������ɫ
	Uint32 box_color;    //��߿���ɫ
	string text;         //�ı�����
	
	XPoint cursor_point; //�����Ĺ����������λ��
	XRect  text_rect;    //�ı�����С��λ��

	XTextListener *textListener; //�ı����������
	
	
	friend class BCursor;
};


extern BCursor static_cursor;

#endif

