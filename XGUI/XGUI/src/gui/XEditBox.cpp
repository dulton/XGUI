#include "XEditBox.h"

////////////////////////////////////////////////////////////

#define COURSOR_WIDTH 1

BCursor static_cursor;

Uint32 callback(Uint32 interval, void *param)
{
	static_cursor.paint();
	
	return interval;
}
BCursor::BCursor()
{
	clone_creen=NULL;
	screen=NULL;
	visible=true;
	state=false;
	height=17;
	cursor_color = 0x000000ff;
}
BCursor::~BCursor()
{
	if(clone_creen)
		free(clone_creen);
}
/*
*1.������λ�õ�ʱ�����ȿ�¡��λ�õ���ʾ��Ϣ
*2.��stop��ʱ�������괦����ʾ״̬�����
*/
void BCursor::run()
{
	m_timerId=SDL_AddTimer(500,callback,NULL);
	state=true;
}
void BCursor::stop()
{
	SDL_RemoveTimer(m_timerId);
	state=false;
	resume();
}

void BCursor::setLocation(Uint16 x,Uint16 y)
{
	Uint16 i;
	void *p_screen;
	void *p_clone;
	
	if(!screen)
	{	
		LOG("BCursor: screen is NULL\n");
		return ;
	}
	
	this->x=x;
	this->y=y;	
	
	if(clone_creen){
		free(clone_creen);
		clone_creen=NULL;
	}
	
	p_clone=clone_creen = malloc(COURSOR_WIDTH* height* screen->format->BytesPerPixel);
	if(clone_creen == NULL)
	{
		LOG("BCursor: �޷������ڴ�");
		return ;
	} 
	
	switch(screen->format->BytesPerPixel)
	 {
	 	case 2:
	 	for(i=y;i<y + height; ++i)
	 	{
	 		
	 		p_screen=((Uint16 *)screen->pixels) + (i * screen->w +x);
	 		memcpy(p_clone,p_screen,COURSOR_WIDTH*2);	
	 		
	 		p_clone =(Uint16 *)p_clone+COURSOR_WIDTH;
	 	} 		
	 	break;
	 	case 4:
	 		
	 	for(i=y;i<y + height; ++i)
	 	{
	 		p_screen=((Uint32 *)screen->pixels) + (i* screen->w +x);
	 		memcpy(p_clone,p_screen,COURSOR_WIDTH*4);	
	 		
	 		p_clone =(Uint32 *)p_clone+COURSOR_WIDTH;
	 	}
	}
}
Uint16 BCursor::getX()
{
	return this->x;
}

void BCursor::setHeight(Uint16 h)
{
	height=h;
}
void BCursor::add(XSurface *screen)
{
	this->screen=screen;
}

void BCursor::setCursorColor(Uint32 color)
{
	this->cursor_color =color;
}
bool BCursor::getState()
{
	return state;
}
void BCursor::resume()
{
	Uint16 current_height;
	int  i;
	void *p_screen;
	void *p_clone = clone_creen;
	
	if(!clone_creen)
		return ;
	
	current_height=y+height; //����y2���꣬������ѭ����ʱ���ظ�����
	
	switch(screen->format->BytesPerPixel)
	{
	 	case 2:
	 	for(i=y;i<current_height; ++i)
	 	{
	 		p_screen=((Uint16 *)screen->pixels) + (i * screen->w +x);
	 		memcpy(p_screen,p_clone,COURSOR_WIDTH*2);	
	 		
	 		p_clone =(Uint16 *)p_clone+COURSOR_WIDTH;
	 	} 		
	 	break;
	 	case 4:
	 	for(i=y;i<current_height; ++i)
	 	{
	 		p_screen=((Uint32 *)screen->pixels) + (i* screen->w +x);
	 		memcpy(p_screen,p_clone,COURSOR_WIDTH*4);	
	 		
	 		p_clone =(Uint32 *)p_clone+COURSOR_WIDTH;

	 	}
	 	
	 	break;
	}
	SDL_UpdateRect(screen,x,y,COURSOR_WIDTH,height);
}

void BCursor::paint()
{	
	if(screen){
		
		if(visible){
			
			vlineColor(screen,x,y,y+height-1,cursor_color);
			SDL_UpdateRect(screen,x,y,COURSOR_WIDTH,height);
			visible=false;
			
		}else
		{	
			resume();
			visible=true;
		}
	}
}
//////////////////////////////////////////////////////////

#define BUTTON_H_MARGIN 5 //text����BOXˮƽ����
#define BUTTON_V_MARGIN 6 //text����BOX��ֱ����

/*************************˵��****************************/
//1.�������������������Ϊ�������������ȥ�������Ϣ�������ô�
/*******************************************************/

XEditBox::XEditBox()
{
	textListener=NULL;
	start_pointer=0;
	cursor_addr=0;
	cursor_postion=0;
	text="�༭��...";
	
	setBackground(0xffffffff);
	init();
}

void XEditBox::setText(string text)
{
	this->text = text;
}

string& XEditBox::getText()
{
	return text;
}
void XEditBox::setFontColor(Uint32 color)
{
	font_color =color;
}
void XEditBox::setBoxColor(Uint32 color)
{
	box_color = color;
}
void XEditBox::init()
{
	int h;
	if(font)
	{
		h=font->getFontHeight();
		
		setSize(80,h+2*BUTTON_V_MARGIN);
	}
	box_color  = 0x424fffff;
	font_color = 0x000000ff;
}

//******************************************
void XEditBox::draw()
{
	char *p=(char *)text.c_str();
	//����
	onDrawBackground(widget_rectF);
	rectangleColor(screen,widget_rect.x,widget_rect.y,widget_rectF.x2,widget_rectF.y2,box_color);
	
	if(widget_state == X_RELEASED)
	{
		//��ʾ�����벿��
		if(cursor_postion>0)
		{
			SDL_Rect rect={widget_rect.x+2,text_rect.y,cursor_postion,text_rect.h};
			string str;
		
			str.append(p,start_pointer,cursor_addr);
		
			font->displayRight(str.c_str(),font_color,rect);	
		}
		
		// ��ʾ����Ұ벿��
		if(widget_rect.w-cursor_postion>0){
			string str;
			SDL_Rect rect={cursor_postion+text_rect.x,text_rect.y,
						widget_rect.w-cursor_postion-2,text_rect.h};
			str.append(p,cursor_addr,strlen(p) - cursor_addr);
	
			font->displayLeft(str.c_str(),font_color,rect);
		}
	}else if(widget_state == X_ORIGINAL)
	{
		text_rect.x=widget_rect.x+2;
		text_rect.y=(widget_rect.h - font->getFontHeight())/2+widget_rect.y;
		
		text_rect.w=widget_rect.w-3;
		
		text_rect.h=widget_rect.h;
		font->display(text.c_str(),font_color,text_rect);	
	}
	
}

void XEditBox::onInit()
{
	XWidget::onInit();
	
	static_cursor.add(screen);
}

void XEditBox::onPaint(Uint16 msg)
{
	if(msg == X_PAINT)
	{
		draw();
			
	}else if(msg == X_UPDATE )
	{
		paint();	
	}
}
void XEditBox::mouseLPressEvent(X_Event *event)
{
	cursor_addr=computeCursor(event->motion->x); //������
}

void XEditBox::mouseLReleaseEvent(X_Event *event)
{
	
}

void XEditBox::keydownEvent(X_Event *event)
{
	switch(event->key->keysym.sym)
	{
		case SDLK_LEFT:
			
			CursorLeftMove();
		break;				
		case SDLK_RIGHT:
			CursorRightMove();
		break;
		
		case SDLK_BACKSPACE:
			{
				deleteFont();
				onPaint(X_UPDATE);
			}
		break;
		
	}
	
	if(event->key->keysym.sym <=126 && event->key->keysym.sym>=32)
	{
		char ch[2]="\n";
		
		*ch=event->key->keysym.sym;
		text.insert(cursor_addr,1,event->key->keysym.sym);
		cursor_addr++;
		cursor_postion+=font->getFontWidth(ch);
		if(cursor_postion> widget_rect.w-3)
		{
			cursor_postion = widget_rect.w-4;
			
		}
		
		static_cursor.resume();
		static_cursor.setLocation(text_rect.x+cursor_postion,widget_rect.y+5);
		static_cursor.paint();
		
		onPaint(X_UPDATE);
	}
}


/**********************˵��***************/
//1.�������ã���������x���������Ӧ�������λ��
//2.������x ����x����
//3.����ֵ������������ڵڼ����ֽ�
/****************************************/

int XEditBox::computeCursor(const int& x)
{
	int i=cursor_addr; //ָ�������ڵ�ַ
	int j=0;
	int cursor_width;
	int swap_x=0;
	int char_w=0;
	int xx=cursor_postion+text_rect.x; //�����ʵ������
	
	char *p=(char *)text.c_str();
	
	if(x< xx) 
	{	
		cursor_width=xx - x;
		
		for(;i>0;)
		{
			j=i;
			string x_str;
			
			if((*(p+i-1) & 0xff000000) >= 0x80000000) //����
			{
				i-=3;
				x_str.append(p,i,3);
				
			}else //Ӣ��
			{
				i-=1;
				x_str.append(p,i,1);
			}
			
			char_w= font->getFontWidth(x_str.c_str());
		
			if(cursor_width <=swap_x+char_w/2 && cursor_width >=swap_x)
			{
				cursor_width=swap_x;
				break;
			}else if(cursor_width>swap_x+char_w/2 && cursor_width <swap_x+char_w)
			{
				j=i;
				cursor_width=swap_x+char_w;
				break;	
			}
			swap_x +=char_w;
		}

		static_cursor.stop();
		static_cursor.setLocation(xx-cursor_width,widget_rect.y+5);
		
		cursor_postion-=cursor_width;
	}else if(x> xx)
	{
		cursor_width=x - xx;
		if(i>=strlen(p)) return cursor_addr;
		
		if(x> text_rect.x+cursor_postion+font->getFontWidth(text.c_str()+cursor_addr) )
		{
			static_cursor.stop();
			static_cursor.setLocation(text_rect.x+cursor_postion+font->getFontWidth(text.c_str()+cursor_addr),widget_rect.y+5);
			cursor_postion=cursor_postion+font->getFontWidth(text.c_str()+cursor_addr);
			j=strlen(p);
			
		}else{
			for(;i<strlen(p);)
			{
				j=i;
				string x_str;
				if(*(p+i) >0 ){
					x_str.append(p,i,1);
					++i; 
				}else{
					x_str.append(p,i,3);
					i+=3;
				}
			
				char_w= font->getFontWidth(x_str.c_str());
				
				if(cursor_width <=swap_x+char_w/2 && cursor_width >=swap_x)
				{
					cursor_width=swap_x;
					break;
				}else if(cursor_width>swap_x+char_w/2 && cursor_width <swap_x+char_w)
				{
					cursor_width=swap_x+char_w;
					j=i;
					break;	
				}
				swap_x +=char_w;
			}
			static_cursor.stop();
		
			static_cursor.setLocation(xx+cursor_width,widget_rect.y+5);
			cursor_postion+=cursor_width;
		}
		
		
	}else
	{
		j=cursor_addr;
	}
	
	static_cursor.paint();
	static_cursor.run();
	
	return j; 
}
void XEditBox::CursorRightMove()
{
	int i=cursor_addr;
	int char_w=0;
	char *p=(char *)text.c_str();
	
	if(cursor_addr>=strlen(p))
	{
		//��ֹԽ��
		return ;
	}
	
	string str;
	if(*(p+cursor_addr) >0 ){
		
		str.append(p,cursor_addr,1);
		++cursor_addr;
		
	}else{
	
		str.append(p,cursor_addr,3);
		cursor_addr+=3;
	}
	char_w= font->getFontWidth(str.c_str());	
	
	cursor_postion+=char_w;
	if(cursor_postion> widget_rect.w-3)
	{
		cursor_postion = widget_rect.w-4;
	}
	
	static_cursor.resume();
	static_cursor.setLocation(text_rect.x+cursor_postion,widget_rect.y+5);
	static_cursor.paint();

}
void XEditBox::CursorLeftMove()
{
	int i=0;
	int j=0;
	int char_w=0;
	char *p=(char *)text.c_str();
	
	if(cursor_addr<=0)
	{
		//��ֹԽ��
		return ;
	}
	
	string str;
	if((*(p+cursor_addr-1) & 0xff000000) >= 0x80000000)
	{
		
		str.append(p,cursor_addr-3,3);
		cursor_addr-=3;
	}
	else
	{
		str.append(p,cursor_addr-1,1);
		cursor_addr-=1;
	}
	
	char_w= font->getFontWidth(str.c_str());
	cursor_postion-=char_w;
	if(cursor_postion<0)
	{
		cursor_postion=0;
	}
			
	static_cursor.resume();
	static_cursor.setLocation(text_rect.x+cursor_postion,widget_rect.y+5);
	static_cursor.paint();

}
void XEditBox::deleteFont()
{
	char *p=(char *)text.c_str();
	string str;
	
	if(cursor_addr <=0) return ;
	
	if((*(p+cursor_addr-1) & 0xff000000) >= 0x80000000)
	{
		str.append(p,cursor_addr-3,3);
		
		text.erase(cursor_addr-3,3);
		cursor_addr-=3;
		cursor_postion-=font->getFontWidth(str.c_str());
		
	}else
	{
		
		str.append(p,cursor_addr-1,1);
		text.erase(cursor_addr-1,1);
		cursor_addr-=1;
		
		cursor_postion-=font->getFontWidth(str.c_str());
		
	}
	
	if(cursor_postion<1)
	{
		cursor_postion=1;
	}
	
	static_cursor.resume();
	static_cursor.setLocation(text_rect.x+cursor_postion,widget_rect.y+5);
	static_cursor.paint();
}

void XEditBox::localUpdate(XRectF& pRect,XObject *pObject)
{
	if(pObject == this || !visible)
		return ;
		
	draw();
}

