#include "XItem.h"
#include "XUseful.h"

XItem::XItem(XWidget *parent)
{
	this->parent = parent;
	font=NULL;
	font_color=0x000000ff;
	
	margin_L=10;
	margin_TB=3;
	
	setFont(NULL);
	curHeight();
}

void XItem::setText(string& text)
{
	this->text=text;
	//���ܿ�ȷ����仯
}

string& XItem::getText()
{
	return this->text;
}	

void XItem::setFontColor(Uint32 color)
{
	font_color=color;
}

void XItem::setMarginLeft(const int& left)
{
	margin_L=left;
}

void XItem::setMarginTB(const int& tb)
{
	margin_TB=tb;
	
	curHeight(); //���¼���H
}

void XItem::setFont(XFont *font)
{
	if(!share_font)
	{
		share_font = new XFont;
	}
	
	if(font)
		this->font=font;
	else 
		this->font = share_font;
	
	curHeight(); //���¼���H	
}

int XItem::getItemMinWidth()
{
	int w=0;
	
	return font->getFontWidth(text.c_str());
}

const Uint16& XItem::getHeight()
{
	return widget_rect.h;
}

XPoint XItem::getPosition()
{
	XPoint point;
	
	point.x=widget_rect.x;
	point.y=widget_rect.y;
	
	return point;
}

void XItem::show()
{
	SDL_UpdateRects(screen,1,&widget_rect);
}

XRect XItem::getEffective()
{
	XRect lRect;
	
	return lRect;
}

//******************************************************************

void XItem::setLocation(Uint16 x,Uint16 y)
{
	widget_rect.x=x;
	widget_rect.y=y;
	
}

void XItem::setWidth(const int& w)
{
	widget_rect.w=w;
	
}

void XItem::curHeight()
{	
	widget_rect.h=font->getFontHeight()+2*margin_TB;
}

void XItem::draw(Uint32 &divider_color,Uint32& bg)
{
	XRectF rectF={widget_rect.x,widget_rect.y,widget_rect.w+widget_rect.x,widget_rect.y+widget_rect.h};
	
	boxColor(screen,rectF.x1+1,rectF.y1+1,rectF.x2-1,rectF.y2-1,bg);
	font->displayFont(text.c_str(),font_color,widget_rect,margin_L);
	
	separatorLine(screen,divider_color,widget_rect.x,rectF.x2,rectF.y2);
}


/****************************************************/
//���ܣ�����Item
//������pdc ...
//     type�ǻ������ͣ�1.SECTION�ǻ������� ��2.ALL����Item����
//     divider_color�Ƿָ�����ɫ
//     isBg �Ƿ񻭱���ɫ
//˵�������rect����item������������ȡ����Ч��
/****************************************************/

void XItem::paint(XDC *pdc,ITEM_TYPE type,Uint32 &divider_color,Uint32& bg)
{
	SDL_Rect eff_rect; //��Ч��rect
	
	
	if(widget_rect.y >= pdc->rect->y+pdc->rect->h || widget_rect.y+widget_rect.h <= pdc->rect->y) //���item��DC�ⷵ��
	{
		return ;
	}
	
	switch(type)
	{
		case SECTION:
			{
				eff_rect.y=widget_rect.y;
				eff_rect.h=widget_rect.h;
				if(widget_rect.y < pdc->rect->y )
				{
					eff_rect.y=pdc->rect->y;
					eff_rect.h=widget_rect.y+widget_rect.h-eff_rect.y;
				}
				
				if(widget_rect.y+widget_rect.h > pdc->rect->y+pdc->rect->h)
				{
					eff_rect.h=pdc->rect->y+ pdc->rect->h -eff_rect.y;
						
				}
				
				eff_rect.x=widget_rect.x;
				eff_rect.w=widget_rect.w;
				
				//������...
				boxColor(screen,eff_rect.x+1,eff_rect.y+1,
						eff_rect.x+eff_rect.w-1,eff_rect.y+eff_rect.h,bg);
				
				font->displaySection(text.c_str(),font_color,
					widget_rect,eff_rect,margin_L);
				separatorLine(screen,divider_color,eff_rect.x,eff_rect.x+eff_rect.w,eff_rect.y+eff_rect.h);
			}
			break;
		case ALL:
			{
				boxColor(screen,widget_rect.x,widget_rect.y+1,
						widget_rect.x+widget_rect.w,widget_rect.y+widget_rect.h,bg);
				font->displayFont(text.c_str(),font_color,widget_rect,margin_L);		
				
				separatorLine(screen,divider_color,widget_rect.x,widget_rect.x+widget_rect.w,widget_rect.y+widget_rect.h);		
			}
			break;
	}
	
}

SDL_Rect XItem::paint(XDC *pdc,Uint32 &divider_color,Uint32& bg)
{
	SDL_Rect eff_rect; //��Ч��rect
	
	if(widget_rect.y >= pdc->rect->y+pdc->rect->h || widget_rect.y+widget_rect.h <= pdc->rect->y) //���item��DC�ⷵ��
	{
		SDL_Rect eff_rect={0};
		return eff_rect;
	}
	
	eff_rect.y=widget_rect.y;
	eff_rect.h=widget_rect.h;
	if(widget_rect.y < pdc->rect->y )
	{
		eff_rect.y=pdc->rect->y;
		eff_rect.h=widget_rect.y+widget_rect.h-eff_rect.y;
	}
	
	if(widget_rect.y+widget_rect.h > pdc->rect->y+pdc->rect->h)
	{
		eff_rect.h=pdc->rect->y+ pdc->rect->h -eff_rect.y;
			
	}
	
	eff_rect.x=widget_rect.x;
	eff_rect.w=widget_rect.w;
	
	XRectF rectF={eff_rect.x,eff_rect.y,eff_rect.w+eff_rect.x,eff_rect.y+eff_rect.h};
	
	SDL_SetClipRect(screen,&eff_rect);
	//������...
	boxColor(screen,eff_rect.x+1,eff_rect.y+1,
			rectF.x2-1,rectF.y2-1,bg);
	
	font->displaySection(text.c_str(),font_color,
		widget_rect,eff_rect,margin_L);
	separatorLine(screen,divider_color,eff_rect.x,rectF.x2,rectF.y2);
	
	
	XAbstractWidget::show(rectF);	
	SDL_SetClipRect(screen,NULL);
	
	return eff_rect;
}

void XItem::paint(Uint32 &divider_color,Uint32& bg)
{
	Uint16 lX2=widget_rect.x+widget_rect.w;
	Uint16 lY2=widget_rect.y+widget_rect.h;
	
	font->displayFont(text.c_str(),font_color,widget_rect,margin_L);		
				
	separatorLine(screen,divider_color,widget_rect.x,lX2,lY2);
	
}

void XItem::paintAll(Uint32 &divider_color,Uint32& bg)
{
	XRectF rectF={widget_rect.x,widget_rect.y,widget_rect.w+widget_rect.x,widget_rect.y+widget_rect.h};
	
	boxColor(screen,rectF.x1+1,rectF.y1+1,rectF.x2-2,rectF.y2-1,bg);
	font->displayFont(text.c_str(),font_color,widget_rect,margin_L);		
				
	separatorLine(screen,divider_color,widget_rect.x,rectF.x2,rectF.y2);
}

void XItem::paintUpdate(Uint32 &divider_color,Uint32& bg)
{
	XRectF rectF={widget_rect.x,widget_rect.y,widget_rect.w+widget_rect.x,widget_rect.y+widget_rect.h};
	
	SDL_SetClipRect(screen,&widget_rect);
	
	boxColor(screen,rectF.x1+1,rectF.y1+2,rectF.x2-2,rectF.y2-2,bg);
	font->displayFont(text.c_str(),font_color,widget_rect,margin_L);		
				
	separatorLine(screen,divider_color,widget_rect.x,rectF.x2,rectF.y2);
	
	XAbstractWidget::show(rectF);
	SDL_SetClipRect(screen,NULL);
}

void XItem::onPaint(Uint16 msg)
{
	if(msg == X_PAINT)
	{
			
	}else if(msg  == X_UPDATE)
	{
			
	}
}

void XItem::onSize(int w,int h)
{
	widget_rectF.x2=widget_rect.x+w;
	widget_rectF.y2=widget_rect.y+widget_rect.h;
}
void XItem::onPosition(int x,int y)
{
	widget_rectF.x1=x;
	widget_rectF.y1=y;
}

