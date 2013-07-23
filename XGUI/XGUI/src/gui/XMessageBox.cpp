#include "XMessageBox.h"
#include "XHBoxLayout.h"
#include "XUseful.h"


#define FONT_MAX_WIDTH      280
#define FONT_MAX_HEIGHT     200
#define FONT_SEPARATOR      2
#define FONT_MARGIN_V       10
#define FONT_MARGIN_H       10

XMessageBox::XMessageBox()
{
	setSize(120,90);	          //�Ի�����С��С
	setBackground(0xb9d2ffaa);
	
	title_color=0xffffffff;
	
	hlayout=NULL;
}

XMessageBox::~XMessageBox()
{
	if(hlayout)
		delete hlayout;
}

void XMessageBox::addButton(XButton *button)
{
	hlayout->addWidget(button);
}

/*��ʾ�û����ṩ��string
* ���裺
* 1.��ťID��0 2.��Ϣ������
* 3.��ԭ��root�滻�����ڵĶԻ��򣬲�����ԭ����root
* 4.���� 5.ִ����Ϣѭ��XApplication::run()
* 6.���ذ�ťID
*/

ID XMessageBox::show(string title,string text,BUTTON_TYPE type)
{
	button_id =ID_NONE;
	
	if(!hlayout)
	{	
		hlayout = new XHBoxLayout;
		if(!hlayout)
		{	
			LOG("XMessageBox: don't new memory\n");	
		}
	}
	
	switch(type)
	{
		case ID_OK:
		{
			//...
		}	
		break;
		case ID_CANCLE:	
		{	
			
		}
		break;
		
		case ID_OKCANCLE:
		{
			ok.setText("OK");
			cancel.setText("cancel");
			
			hlayout->addWidget(&ok);
			hlayout->addWidget(&cancel);
			
			ok.setMouseListener(this);
			cancel.setMouseListener(this);
			
			this->setLayout(hlayout);
		}
	}

//����
	saveData();
	
	init(text,title);
	
	paint(title,text);
	
	XApplication::PollMessage();
	
	resumeData();
	
	delete hlayout;
	hlayout=NULL;
	return button_id;
}

//�رնԻ���
void XMessageBox::close()
{
	X_Event event;
	event.type=X_QUIT;
	XAbstractWidget::sendSystemMsg(&event);
	
	event.type=X_UPDATE;
	XAbstractWidget::sendSystemMsg(&event);
}

//*********************˽��*************************
void XMessageBox::saveData()
{
/**************************************************/
/*             ����X_RESUME��Ϣ���Իָ��������         */
/**************************************************/
	X_Event event;
	event.type=X_RESUME;
	XAbstractWidget::sendSystemMsg(&event);
	XApplication::PollMessage();	
	
	old_root =XAbstractWidget::getRoot();
	old_focus=(XWidget  *)XAbstractWidget::focus_widget;
	
	XAbstractWidget::setRoot(this);
	XAbstractWidget::setFocusWidget(NULL);
	
}
void XMessageBox::resumeData()
{
	XAbstractWidget::setRoot(old_root);
	XAbstractWidget::setFocusWidget(old_focus);
	
}
bool XMessageBox::responseEvent(X_Event *event)
{
	/***************��ֹ���ղ��ý��յ���Ϣ*****************/
	if(widget_state==X_ORIGINAL)
		widget_state=X_ACTIVE;
	else
		hlayout->responseEvent(event);

	return false;
}

/*��ʼ����Ϣ���С
* �������
*/
void XMessageBox::init(string& text,string& title)
{
	int i=0;
	int w=0;
	int h=0;
	int layout_h=0;
	int layout_w=0;
	int widget_count_h=0;
	text_rect.h=0;
	
	XSize   size = this->getWindowSize();
	
	{
		widget_count_h=hlayout->getHVariableCount(&layout_w,true);
		hlayout->getVVariableCount(&layout_h,true);
		
		button_rect.h=layout_h;           //��ť���߶�
		
		/*
		*�������Ŀ��С�ڰ�ť�����,���������ȺͲ�������������
		*/
		if(widget_rect.w < layout_w+XWidget::h_margin*(widget_count_h+1) ) 
			widget_rect.w = layout_w+XWidget::h_margin*(widget_count_h+1); 
	}
	
	arry.split(text,'\n');
	for(;i<arry.getCount(); ++i)
	{
		font->getFontSize((char *)arry.getAt(i).c_str(),&w,&h);
		
		if(widget_rect.w < w) {
		   widget_rect.w=w;
		}
		text_rect.h+=h+FONT_SEPARATOR;
	}
	
	if(arry.getCount()==0)  //�����һ���ı�
	{
		font->getFontSize((char *)text.c_str(),&w,&h);
		
		if(widget_rect.w < w) {
		   widget_rect.w=w;
		}
		text_rect.h+=h+FONT_SEPARATOR;
	}
	
	text_rect.w=widget_rect.w;
	//������
	if(widget_rect.w > FONT_MAX_WIDTH- 2*FONT_MARGIN_H)                      
		widget_rect.w= FONT_MAX_WIDTH+ 2*FONT_MARGIN_H;
	else
	{
		widget_rect.w+= 2*FONT_MARGIN_H;
	}
	widget_rect.x = (size.w - widget_rect.w)/2;            //�����X����
	
	title_rect.h=font->getFontHeight()+XWidget::v_margin;  //�������߶�
	
	if(text_rect.h > FONT_MAX_HEIGHT-title_rect.h-button_rect.h-2*FONT_MARGIN_H) //�ı��Ŀ�Ȳ��ܳ��������
		text_rect.h =FONT_MAX_HEIGHT-title_rect.h-button_rect.h-2*FONT_MARGIN_H;
	
	
	widget_rect.y = (size.h - title_rect.h - text_rect.h - 2*FONT_MARGIN_H  - button_rect.h)/2; //�����Y����
	widget_rect.h = button_rect.h+text_rect.h+title_rect.h+2*FONT_MARGIN_H;
	
	
	//������
	title_rect.x=widget_rect.x;
	title_rect.w=widget_rect.w;
	title_rect.y=widget_rect.y;
	//�ı���
	text_rect.x=widget_rect.x+FONT_MARGIN_V;
	text_rect.y=widget_rect.y+title_rect.h+FONT_MARGIN_V;
	
	
	//��ť��
	button_rect.y=(widget_rect.y+widget_rect.h) -(layout_h+XWidget::v_margin);
	button_rect.x=widget_rect.x;
	button_rect.w=widget_rect.w;
	
	
	//��������������λ��
	hlayout->setRect(&button_rect);
	//��ʼ����
	hlayout->computeLayout();
}
bool XMessageBox::onCloseWindowEvent()
{
	
	return false;
}	

/*����"\n"
*"\n"��ʾ����
*/
/*   _______
*   |_______|    ������ 21
*   |       |   �ı���  36
*   |_______|
*   |_______|   ��ť��  33
*/

void XMessageBox::paint(string& title,string& text)
{
	int i;
	int x,y;   //��������������,��Ϊ�ദ�õ�������һ��ռ任ʱ��
	Uint32      color = getBackground();
	XSurface 	*screen=this->getScreen();
	
	XSize screen_size=getWindowSize();
	//boxColor(screen,0,0,screen_size.w,screen_size.h,0x8c8c8c77); //������ɻ�ɫ���Ա�ֱ����Ϣ�� 
	
	//������
	XRect font_rect; //��
	x=  widget_rect.w+widget_rect.x;
	y=  widget_rect.y+widget_rect.h;
	
	//�����
	roundedBoxColor(screen,widget_rect.x, widget_rect.y, x,
					widget_rect.y+title_rect.h,3,title_color); //������
	roundedBoxColor(screen,widget_rect.x, widget_rect.y+title_rect.h, x, y,3,color); //�ı���
	roundedRectangleColor(screen,widget_rect.x, widget_rect.y, x, y,3,0xd1d1d1ff); //����
	
	//����
	hlineColor(screen,widget_rect.x+3,x-3,y,0xffffffff); //
	
	//�ı���
	if(font){
		font->displayFont((char *)title.c_str(),0,title_rect); //����
		//�ı�
		
		if(arry.getCount() == 0)
		{
			font->displayFont((char *)text.c_str(),0,text_rect);
		}else{
			font_rect.x=widget_rect.x;
			font_rect.y=text_rect.y;
			font_rect.w=widget_rect.w; 
			font_rect.h=font->getFontHeight()+FONT_SEPARATOR;
		}
		for(i=0;i<arry.getCount(); ++i){
			
			font->displayFont((char *)arry.getAt(i).c_str(),0,font_rect);
			
			font_rect.y+=font->getFontHeight()+FONT_SEPARATOR;
		}
	}

	//��ť��
	hlayout->update();

	SDL_Flip(screen);
	//SDL_UpdateRect(screen,widget_rect.x,widget_rect.y,widget_rect.w+1,widget_rect.h+1);
	run_state=true; //���ñ��������״̬
}

void XMessageBox::mousePressed(X_Event *event,const ID id)
{
	//************
}

/*����Ϣ���˳���ʱ���˳���ѭ�������ػ�*/
void XMessageBox::mouseReleased(X_Event *event,const ID id)
{
	if(ok.equals((XObject *)id))
	{
		button_id = ID_OK;
	}else if(cancel.equals((XObject *)id))
	{
		button_id = ID_CANCLE;
	}
	
	event->type=X_WIDGETCLOSE;
	XAbstractWidget::sendSystemMsg(event);
	
	event->type=X_UPDATE;
	XAbstractWidget::sendSystemMsg(event);
	
}
void XMessageBox::mouseEntered(X_Event *event,const ID id)
{
	
	//*************
}

//*********************˽��*************************

