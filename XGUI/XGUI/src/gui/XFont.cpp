#include "XFont.h"
#include "XWidget.h"

TTF_Font  * XFont::dafult_font=NULL;
int XFont::dafult_size =13;

XFont::XFont()
{
	font = NULL;
	font_size  = dafult_size;
	
	font_name ="/XGUI/fonts/simfang.ttf";
	init();
}

XFont::~XFont()
{
	/*��������������ڴ棬�ͷŵ�*/
	if(dafult_font != font)
		TTF_CloseFont(font);
}

bool XFont::init()
{

	if(!dafult_font)
	{
		dafult_font = TTF_OpenFont(font_name,font_size);
		if(!dafult_font)
		{	
			LOG(SDL_GetError());
			return false;
		}
	}
	
	font = dafult_font;
	
	return true;
}

void XFont::setFontColor(Uint32 color)
{
	this->font_color = color;
}

/*
*��С�����ã��������Ĭ�������ͷ���ǰ��
*/
void XFont::setSize(int size)
{
	font_size = size;
	/*������������С��Ĭ�������С��ȣ���ôʹ��Ĭ�������*/		
	if(dafult_size == size)
	{
		font = dafult_font;
		return ;
	}
	
	/*��������������ڴ棬�ͷŵ�*/
	if(dafult_font != font)
		TTF_CloseFont(font);
	
	font=TTF_OpenFont(font_name,font_size);
	if(!font)
	{	
		LOG(SDL_GetError());
		return ;
	}
}

/*
* ���fontΪNULL����֤��û�г�ʼ���ֿ�
* ��ô����Ĭ�ϴ�С����
*/
void XFont::getFontSize(const char *text,int *w,int *h)
{
	if(this->font != NULL && strlen(text))
	{	
		TTF_SizeUTF8(this->font,text,w,h);
		return ;
	}
	
	*w =0;
	*h =0;
}

int XFont::getFontHeight()
{
	if(font)
	{
		return TTF_FontHeight(font);
	}
	return 0;
}
int  XFont::getFontWidth(const char *text)
{
	int w=0;
	int h=0;

	if(this->font != NULL && strlen(text))
	{	
		TTF_SizeUTF8(this->font,text,&w,&h);
		
	}
	
	return w;	
}

void XFont::freeFont()
{
	/*����Ժ�����ʹ�ô��ֿ������ͷŵ�
	* ������������֣���Щ���ٷ����仯�ͷŵ�
	*/
	
	if(font != dafult_font)
		TTF_CloseFont(font);
}
void XFont::displayFont(const char *text,int color,int x,int y)
{
	SDL_Surface  *surface;
	XRect         inside={x,y,0,0};
	int           w,h;
	SDL_Color     this_color;
	
	if(!font){
		 
		 if(init()==false){ 
		 
		 	LOG("font: font  is NULL!");
		 	return ;
		 }
	}
	
	this_color.unused = 0x000000ff & color;
	this_color.b = (0x0000ff00 & color) >> 8;
	this_color.g = (0x00ff0000 & color) >>16;
	this_color.r =(0xff000000 & color) >> 24;
	
	surface=TTF_RenderUTF8_Blended(font,text,this_color);
	
	TTF_SizeUTF8(font,text,&w,&h);
	
	inside.w=w;
	inside.h=h;	
	
	SDL_BlitSurface(surface, &inside, XWidget::screen,&inside);
	SDL_FreeSurface(surface);	
	
}	
/*
* ������ rect �������ⲿ�Ŀ�ܴ�С��λ��
* ��������������ʾ��rect�м�
* ��һЩ�ж�ע���������˷�ʱ��
*/
void XFont::displayFont(const char *text,int color,const XRect& rect,const int& left)
{
	SDL_Surface  *surface;
	XRect         inside={0};
	XRect         outside={0};
	int           w,h;
	SDL_Color     this_color;

	if(!strlen(text)) return ; //if null return;
	/*
	if(!font ){
		 if(init()==false){ 
		 
		 	LOG("font: font  is NULL!");
		 	return ;
		 }
	}
	*/
	this_color.unused = 0x000000ff & color;
	this_color.b = (0x0000ff00 & color) >> 8;
	this_color.g = (0x00ff0000 & color) >>16;
	this_color.r =(0xff000000 & color) >> 24;
	
	surface=TTF_RenderUTF8_Blended(font,text,this_color);
	/*if(!surface)
	{
		LOG("font: ����ΪNULL\n");
		return ;
	}*/
	TTF_SizeUTF8(font,text,&w,&h);
	
	if(w>rect.w) w=rect.w; //��ʾ���ֲ��ܳ�����BOX
	if(h>rect.h) h=rect.h;
	
	inside.w=w;
	inside.h=h;
	
	outside.w=w;
	outside.h=h;
	
	if(left==-1)
		outside.x = (rect.w - w)/2 + rect.x; 
		
	else  {
		outside.x = rect.x+left;
		inside.w = (rect.x+rect.w)-outside.x;
	}
	
	outside.y = (rect.h - h)/2 + rect.y;//����rect.h������С��h�����Բ����ж�outside.y�ķ�Χ��,ͬ��rect.x
	
	SDL_BlitSurface(surface,&inside, XWidget::screen, &outside);
	
	SDL_FreeSurface(surface);	
}
void XFont::fastDisplayFont(const char *text,int color,const XRect& rect,const int& left)
{
	SDL_Surface  *surface;
	XRect         inside={0};
	XRect         outside={0};
	SDL_Color     this_color;

	if(!strlen(text)) return ; //if null return;
	
	this_color.b = (0x0000ff00 & color) >> 8;
	this_color.g = (0x00ff0000 & color) >>16;
	this_color.r =(0xff000000 & color) >> 24;
	
	surface=TTF_RenderUTF8_Blended(font,text,this_color);
	
	TTF_SizeUTF8(font,text,(int *)&inside.w,(int *)&inside.h);
	
	outside.w=rect.w;
	outside.h=rect.w;
	
	outside.x = rect.x+left;
	outside.y = (rect.h - outside.h)/2 + rect.y;
	
	SDL_BlitSurface(surface,&inside, XWidget::screen, &outside);
	
	SDL_FreeSurface(surface);

}
void XFont::displayFontUnder(const char *text,int color,const XRect& rect,bool left)
{
	SDL_Surface  *surface;
	XRect         inside={0};
	XRect         outside={0};
	int           w,h;
	SDL_Color     this_color;

	if(!strlen(text)) return ; //if null return;
	
	if(!font ){
		 if(init()==false){ 
		 
		 	LOG("font: font  is NULL!");
		 	return ;
		 }
	}
	
	this_color.unused = 0x000000ff & color;
	this_color.b = (0x0000ff00 & color) >> 8;
	this_color.g = (0x00ff0000 & color) >>16;
	this_color.r =(0xff000000 & color) >> 24;
	
	TTF_SetFontStyle(font,TTF_STYLE_UNDERLINE); //1.�����»���
	surface=TTF_RenderUTF8_Blended(font,text,this_color);
	if(!surface)
	{
		LOG("font: ����ΪNULL\n");
		return ;
	}
	TTF_SetFontStyle(font,TTF_STYLE_NORMAL);  //2.��ԭ
	
	TTF_SizeUTF8(font,text,&w,&h);
	
	if(w>rect.w) w=rect.w; //��ʾ���ֲ��ܳ�����BOX
	if(h>rect.h) h=rect.h;
	
	inside.w=w;
	inside.h=h;
	
	outside.w=w;
	outside.h=h;
	
	if(left==false)
		outside.x = (rect.w - w)/2 + rect.x; 
	else  outside.x = rect.x;
	
	outside.y = (rect.h - h)/2 + rect.y;//����rect.h������С��h�����Բ����ж�outside.y�ķ�Χ��,ͬ��rect.x
	
	SDL_BlitSurface(surface,&inside, XWidget::screen, &outside);
	
	SDL_FreeSurface(surface);
}

void XFont::display(const char *text,int color,const XRect& outside)
{
	SDL_Surface  *surface;
	SDL_Color     this_color;
	XRect         inside={0};
	
	
	if(!strlen(text)) return ; //if null return;
	
	if(!font ){
		 if(init()==false){ 
		 
		 	LOG("font: font  is NULL!");
		 	return ;
		 }
	}
	
	
	this_color.unused = 0x000000ff & color;
	this_color.b = (0x0000ff00 & color) >> 8;
	this_color.g = (0x00ff0000 & color) >>16;
	this_color.r =(0xff000000 & color) >> 24;
	
	surface=TTF_RenderUTF8_Blended(font,text,this_color);
	if(!surface)
	{
		LOG("font:����ΪNULL\n");
		return ;
	}
	
	inside.w=outside.w;
	inside.h=outside.h;
	
	SDL_BlitSurface(surface,&inside, XWidget::screen, (XRect *)&outside);
	SDL_FreeSurface(surface);
}

void XFont::displayRight(const char *text,int color,const XRect& outside)
{
	int w,h;
	SDL_Surface  *surface;
	SDL_Color     this_color;
	XRect         inside;
	
	
	if(!strlen(text)) return ; //if null return;
	
	if(!font ){
		 if(init()==false){ 
		 
		 	LOG("font: font  is NULL!");
		 	return ;
		 }
	}
	
	this_color.unused = 0x000000ff & color;
	this_color.b = (0x0000ff00 & color) >> 8;
	this_color.g = (0x00ff0000 & color) >>16;
	this_color.r =(0xff000000 & color) >> 24;
	
	surface=TTF_RenderUTF8_Blended(font,text,this_color);
	if(!surface)
	{
		LOG("font:����ΪNULL\n");
		return ;
	}
	
	TTF_SizeUTF8(font,text,&w,&h);
	
	inside.x=w-outside.w;
	inside.y=0;
	inside.w=outside.w;
	inside.h=outside.h;
	
	SDL_BlitSurface(surface,&inside, XWidget::screen, (XRect *)&outside);
	SDL_FreeSurface(surface);
}

void XFont::displayLeft(const char *text,int color,const XRect& outside)
{
	SDL_Surface  *surface;
	SDL_Color     this_color;
	XRect         inside;
	
	
	if(!strlen(text)) return ; //if null return;
	
	if(!font ){
		 if(init()==false){ 
		 
		 	LOG("font: font  is NULL!");
		 	return ;
		 }
	}
	
	this_color.unused = 0x000000ff & color;
	this_color.b = (0x0000ff00 & color) >> 8;
	this_color.g = (0x00ff0000 & color) >>16;
	this_color.r =(0xff000000 & color) >> 24;
	
	surface=TTF_RenderUTF8_Blended(font,text,this_color);
	if(!surface)
	{
		LOG("font:����ΪNULL\n");
		return ;
	}
	
	inside.x=0;
	inside.y=0;
	inside.w=outside.w;
	inside.h=outside.h;
	
	SDL_BlitSurface(surface,&inside, XWidget::screen, (XRect *)&outside);
	SDL_FreeSurface(surface);
}
void XFont::displayTop(const char *text,int color,const XRect& rect,const XRect& effSide)
{
	SDL_Surface  *surface;
	XRect         inside={0};
	XRect         outside={0};
	int           w,h;
	SDL_Color     this_color;

	if(!strlen(text)) return ; //if null return;
	
	if(!font ){
		 if(init()==false){ 
		 
		 	LOG("font: font  is NULL!");
		 	return ;
		 }
	}

	this_color.unused = 0x000000ff & color;
	this_color.b = (0x0000ff00 & color) >> 8;
	this_color.g = (0x00ff0000 & color) >>16;
	this_color.r =(0xff000000 & color) >> 24;
	
	surface=TTF_RenderUTF8_Blended(font,text,this_color);
	if(!surface)
	{
		LOG("font: ����ΪNULL\n");
		return ;
	}
	TTF_SizeUTF8(font,text,&w,&h);
	
	if(w>rect.w) w=rect.w; //��ʾ���ֲ��ܳ�����BOX
	if(h>rect.h) h=rect.h;
	
	inside.w=w;
	inside.h=h;
	
	outside.w=w;
	outside.h=h;
	
	
	outside.x = rect.x;
	outside.y = (rect.h - h)/2 + rect.y;//����rect.h������С��h�����Բ����ж�outside.y�ķ�Χ��,ͬ��rect.x
	
	if(outside.y < effSide.y)
	{
		inside.y=effSide.y-outside.y;
		outside.y=effSide.y;
	}
	
	SDL_BlitSurface(surface,&inside,  XWidget::screen, &outside);
	
	SDL_FreeSurface(surface);	
}

void XFont::displaySection(const char *text,int color,const XRect& rect,const XRect& effSide,
					const int& left)
{
	SDL_Surface  *surface;
	XRect         inside={0};
	XRect         outside={0};
	int           w,h;
	SDL_Color     this_color;
	
	if(!strlen(text)) return ; //if null return;
	
	if(!font ){
		 if(init()==false){ 
		 
		 	LOG("font: font  is NULL!");
		 	return ;
		 }
	}

	this_color.unused = 0x000000ff & color;
	this_color.b = (0x0000ff00 & color) >> 8;
	this_color.g = (0x00ff0000 & color) >>16;
	this_color.r =(0xff000000 & color) >> 24;
	
	surface=TTF_RenderUTF8_Blended(font,text,this_color);
	if(!surface)
	{
		LOG("font: ����ΪNULL\n");
		return ;
	}
	TTF_SizeUTF8(font,text,&w,&h);
	
	if(w>rect.w) w=rect.w; //��ʾ���ֲ��ܳ�����BOX
	if(h>rect.h) h=rect.h;
	
	inside.w=w;
	
	outside.w=w;
	outside.h=h;
	
	if(left==-1)
		outside.x = (rect.w - w)/2 + rect.x; 
	else  {
		outside.x = rect.x+left;
		inside.w = (rect.x+rect.w)-outside.x;
	}
	
	outside.y = (rect.h - h)/2 + rect.y;//����rect.h������С��h�����Բ����ж�outside.y�ķ�Χ��,ͬ��rect.x
	
	
	if(effSide.y+effSide.h < outside.y) //��ЧBOX��Y2< ����BOX��Y1
	{
		inside.h=0;
		
	}else{
		
		int y1= outside.y;           //����BOX��Y1����
		int y2= outside.y+outside.h; //����BOX��Y2����
		
		if(y1 < effSide.y)
		{
			y1=effSide.y;
		}
	
		if(y2 > effSide.y+effSide.h)
		{
			y2=effSide.y+effSide.h;
		
		}
		
		inside.y=y1-outside.y;
		inside.h=y2-y1;
	
		outside.y=y1;
		outside.h=inside.h;
	
		SDL_BlitSurface(surface,&inside, XWidget::screen, (SDL_Rect *)&outside);
	}
	
	SDL_FreeSurface(surface);	
}



