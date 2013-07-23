/*
* ��������ĸ���
* ��������������齨��ͬ������
* ���ɽ�XWidget��Ϊ�ֲ������������ͷ���Ļָ��
*/

#ifndef _XWIDGET_H
#define _XWIDGET_H

#include "XAbstractWidegt.h"
#include "XLayout.h"
#include "XUseful.h"

class XLayout;
class XAbstractWidget;
class XVBoxLayout;
class XHBoxLayout;

class XWidget:public XAbstractWidget
{
public:
	XWidget(int w,int h);
	XWidget();
	~XWidget();
	
	/*
	*Ϊ���ֹ��������������С
	*���Ը��߲��ֹ��������ı��С��ֻ����λ��
	*/
	void setLayout(XLayout *layout);
	void setFont(XFont *font);
	
	/*
	*��ʾ����
	*/
	void show();
	void hide();
	
	void setVisible(bool visible);
	//�������ID
	const ID getId();
	/*
	*���ñ���ɫ
	*�ڶ��������Ǹ�������ñ���ͼƬ
	*/
	void setBackground(Uint32 color);
	const Uint32& getBackground();
	
	//�õ����ڵ�
	XLayout*	getParent();
	XLayout*	getLayout();
	
	//���²���
	void reLayout();
	void update();
	
	bool isChild(XWidget *pObject);
	
	/*
	*��������Ĳ���
	*����ǰ: ���ÿ������ô�С����������λ��û����
	*���ֺ�: ��������λ�úʹ�С�����ǲ��ܳ�������
	*/
	void setSize(int w,int h);
	void setLaction(int x,int y);
	
	void setRect(XRect* rect);
	Uint8 getWidgetState();
		
public:	
	/*�������ṩһ�ּ��������С�ķ���
	*����ֵ�����true�����Ȳ��ɱ�
	*����ֵfalse�����ȿɱ�
	*/
	virtual bool isVVariable(){
		
		return vVariable;
	}
	virtual bool isHVariable()
	{
		return hVariable;
	}
	/*
	*�����㷨
	*/
	virtual void computeLayout();
	virtual void setVVariable(bool variable); 
	virtual void setHVariable(bool variable); 
	
	/*�ֱ���ˮƽ����ֱ�ɱ�����ܵõ��Ķ��ⳤ��*/
	static int v_variable;
	static int h_variable;
	/*Ĭ��BOX��BOX�߾�*/
	static int h_margin;
	static int v_margin;
	
protected:
	
	virtual bool responseEvent(X_Event *event);
	//�������Ϊ���������ʱ����Ӧ�¼�����
	virtual bool focusEvent(X_Event *event);
	
	/*�ɸ��Ǻ���*/
	virtual void reDrawRect(const XRect& rect);
	virtual void onSize(int w,int h);   //����������֮�����
	virtual void onPosition(int x,int y);
	virtual bool onCloseWindowEvent();
	
	virtual void draw();
	virtual void paint();
	virtual void onPaint(Uint16 msg);
	virtual void onInit();
	virtual void onDrawBackground(XRectF& rectF);
	/**
	*���ұ�������ǵ���������ػ������Ǽ��ػ���������ӽڵ�
	*/
	virtual void findOverridingWidget(XRect& pRect,XObject *pObject);
	virtual void drawParent(XRectF& pRect,XObject *pObject);
	virtual void drawChild(XRectF& pRect,XObject *pObject);
	virtual void localUpdate(XRectF& pRect,XObject *pObject);
	
	virtual bool devEvent(X_Event *event);
	
	XSurface* getScreen();
	XFont     *font;         //�����������
	
	
	Uint32    background_color;    //������ɫ
	XLayout   *parent;             //���ڵ�
	XLayout   *layout;  //�����Ƕ�벼��
	
/*
*ʵ�ֳ������ӿ�
*�Լ������⹫���Ľӿ�
*/
private:
		
	/*�õ����������С��С���������к����²���*/
	virtual XRect getMinRect(); 
	

private:

	bool              hVariable; //ˮƽ�ɱ�
	bool              vVariable;  //��ֱ�ɱ�
	                 
	static void*       clone;    //��¡ĳһ�����Ա�ָ�
	
	friend class XFont;
	friend class XLayout;
	friend class XApplication;
	friend class XHBoxLayout;
	friend class XVBoxLayout;
};

#endif

