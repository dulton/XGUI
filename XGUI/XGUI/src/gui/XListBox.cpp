#include "XListBox.h"

XListBox* XListBox::pList=NULL;
XItem*    XListBox::pItem=NULL;

#define   SELECT_ITEM_COLOR 0xb2b3ffff
#define   DEFUIT_ITEM_COLOR 0xffffffff

XListBox::XListBox()
{
	top_item=NULL;
	bottom_item=NULL;
	
	top_position=0;
	bottom_position=0;
	
	setBackground(0xffffffff);
	
	divider_color= 0x0000ffff;
	item_color=0xffffffff;
	
	indexListener=NULL;
	
	index=-1;
	
	setSize(50,50);
	setVVariable(true);
	setHVariable(true);
	
}
XListBox::~XListBox()
{
	int i=0;
	list_item.begin();
	
	if(list_item.getCount() !=0)
	{
		delete list_item.takeFirst();
	}
	
	for(i=1;i<list_item.getCount();++i)
	{
		delete list_item.next();
	}
}

void XListBox::addItem(string text)
{
	XItem *pItem = new XItem;
	
	pItem->setText(text);
	list_item.append(pItem);
	
	if(run_state == true)
	{
		pItem->setWidth(widget_rect.w);
	}
}

void XListBox::addItem(XItem& item)
{
	
	XItem *pItem = new XItem;
	memcpy(pItem,&item,sizeof(XItem));
	
	list_item.append(pItem);
	
	if(run_state == true)
	{
		pItem->setWidth(widget_rect.w);
	}
	
}

/**********************************************/
//1.���ɾ��������������ʾ��item...
//2����֮...
/**********************************************/
void XListBox::removeItem(int item)
{
	int top_index= list_item.indexOf(list_item.takeFirst());
	int bottom_index= list_item.indexOf(list_item.takeLast() );
	
	if(bottom_index == -1) return ;
	
	list_item.remove(index);
	if(top_index <= item && item <=bottom_index) 
	{
		//reDraw();
	}
	
	changSize(); //�ܳ���
}

void XListBox::removeAll()
{
	
}

void XListBox::setLeftMargin()
{
	
}
void XListBox::setDividerLine(Uint32 color)
{
	divider_color=color;
}
void XListBox::addIndexlistener(XIndexListener *listener)
{
	indexListener=listener;
}

int&  XListBox::CurrentIndex()
{
	return index;
}
void XListBox::setItmeColor(Uint32 color)
{
	item_color=color;
}
/////////////////////////////////˽��/////////////////////////////////////

void XListBox::onInit()
{
	XWidget::onInit();
}

void XListBox::setItemWidth()
{
	XItem *item;
	
	list_item.begin();
	
	if(!list_item.isEmpty()){
			list_item.takeFirst()->setWidth(widget_rect.w);
		while(list_item.isNext())
		{
			item=list_item.next();
			item->setWidth(widget_rect.w);
		}
	}
}

void XListBox::initDraw()
{
	int h=0;
	int i=0;
	
	widget_state = X_PRESSED;
	top_position=widget_rect.y; //����item��y1����
	XPOSITION pos = list_item.getHeadPosition();

	onDrawBackground(widget_rectF);
	
	//��item
	if( !list_item.isEmpty())
	{
		top_item=list_item.getNext(pos);
		h=top_item->getHeight();
		
		top_item->setLocation(widget_rect.x,widget_rect.y);
		top_item->draw(divider_color,item_color);
		
		while(!pos.isEmpty())
		{
			bottom_item=list_item.getNext(pos);
			bottom_item->setLocation(widget_rect.x,widget_rect.y+h);
			h+=bottom_item->getHeight();
			
			bottom_item->draw(divider_color,item_color);
			
			if(h>= widget_rect.h)
			{
				break;
			}
		}
		bottom_position=h+widget_rect.y; //�ײ�item��y2����
	}
	
	//��Border
	rectangleColor(screen,widget_rectF.x1,widget_rectF.y1,widget_rectF.x2,widget_rectF.y2,0x7991c9ff);
	vScrollbar.paint();
}

void XListBox::draw()
{
	XItem *Item;
	XPOSITION pos = list_item.find(top_item);
	
	//������
	onDrawBackground(widget_rectF);
	
	while(!pos.isEmpty())
	{	
		Item=list_item.getNext(pos);
		Item->draw(divider_color,item_color);
		if(bottom_item == Item)
		{	
			break;
		}
	}
	//����ѡ����
	if(pList== this && pItem)
	{
		Uint32 color = (Uint32)SELECT_ITEM_COLOR;
		pItem->draw(divider_color,color);
	}
	//������
	vScrollbar.paint();
	//�߿�
	rectangleColor(screen,widget_rect.x,widget_rect.y,widget_rectF.x2,widget_rectF.y2,0x7991c9ff);
}


void XListBox::compute(int MoveLength)
{
	int   MoveScrollbar; //����Ӧ�������ľ���
	int   h;
	int   swap_length=0;
	bool mark=true; //������ǣ���Ҫ�ǽ��item���������Ҳ�޷��ﵽMoveLength�ĳ���
	
	if(bottom_position < widget_rectF.y2) //������һ��item
	{
		return ;	
	}
	
	if(MoveLength < 0  ) //���Ϲ���
	{	
		MoveLength=-MoveLength; //��MoveLength�������
		swap_length= bottom_position - widget_rectF.y2; //item����Ĳ���
		
		list_item.begin();
		list_item.setPosition(bottom_item);
		list_item.next();
		
		if(swap_length >= MoveLength) //�����ʾ�����һ������Ѿ�������MoveLength
		{
			bottom_position=bottom_position-MoveLength; //������������ʾ��item��Y2����
			h=bottom_item->getPosition().y-MoveLength;  //�������ײ�Item��y����
			
			MoveScrollbar=MoveLength;
			mark=false;
		}else{
			h=swap_length;
			while(list_item.isNext())
			{
				bottom_item=list_item.next();
				h+=bottom_item->getHeight();
				if(h >= MoveLength)
				{
					mark=false;
					break;
				}
			}
			if(mark==false)
			{	
				MoveScrollbar=MoveLength;
				h= widget_rectF.y2-(bottom_item->getHeight()-(h-MoveLength));
				bottom_position=h+bottom_item->getHeight();  //������������ʾ��item��Y2����
			}else
			{
				MoveScrollbar=vScrollbar.getScrollbarBottomLength();
				h=widget_rectF.y2-bottom_item->getHeight();
				bottom_position=widget_rectF.y2;
			}
		}
		
		bottom_item->setLocation(widget_rect.x,h);
		while(list_item.isPrevious())
		{
			top_item=list_item.previous();
			
			h=h-top_item->getHeight();
			top_item->setLocation(widget_rect.x,h);
			
			if(h<= widget_rect.y)
			{
				top_position=h;
				break;
			}
		}
		top_position=h; //����item��y1����
		vScrollbar.move(MoveScrollbar);//����������	
	}
	else if(MoveLength >= 0 ) //���¹���
	{
		list_item.begin();
		if(top_item == list_item.takeFirst()){}
		else{
			while(list_item.isNext())
			{
				if(list_item.next() == top_item) break;
			}
		}
		swap_length=widget_rect.y - top_position; //item����Ĳ���
		
		if(swap_length >= MoveLength)             //�����ʾ�����һ������Ѿ�������MoveLength
		{
			top_position=top_position+MoveLength; //������������ʾ��item��Y����
			h=top_position;
			
			MoveScrollbar=-MoveLength;
			mark=false;
		}else{
		
			h=swap_length;
			
			while(list_item.isPrevious())
			{
				top_item=list_item.previous();
				h+=top_item->getHeight();
				if(h >= MoveLength)
				{
					mark=false;
					break;
				}
			}
			
			if(mark==false)
			{	
				MoveScrollbar=-MoveLength;
				h=widget_rect.y-(h-MoveLength) ;//����top_item��y����
				top_position=h;
			}else
			{
				MoveScrollbar=-vScrollbar.getScrollbarTopLength();
				h=widget_rect.y;
				top_position=h;
			}
		}
		
		top_item->setLocation(widget_rect.x,h);
		h=h+top_item->getHeight();
		
		while(list_item.isNext())
		{
			bottom_item=list_item.next();
			
			bottom_item->setLocation(widget_rect.x,h);
			h=h+bottom_item->getHeight();
			
			if(h >= widget_rectF.y2)
			{
				break;
			}
		}
		
		bottom_position=h; //����item��y1����
		vScrollbar.move(MoveScrollbar);//����������	
	}
}

XItem * XListBox::selectIndex(X_Event *event)
{
	int length;
	XItem *item;
	int widget_rect_y2=widget_rect.y+widget_rect.h;
	XPOSITION pos = list_item.getHeadPosition();

	index=-1; //������ֵ��ֵΪ0
	
	if(list_item.isEmpty()) return NULL;
	
	index=0; //������ֵ��ֵΪ0
	list_item.begin();

	while (!pos.isEmpty())
	{
		if((item =list_item.getNext(pos)) == top_item) break;
		++index;
	}
	
	length=top_position;
	length += item->getHeight();
	
	if(length >= event->motion->y)
	{
		return item;
		
	}else{
	
		while(!pos.isEmpty())
		{
			index++;
			item=list_item.getNext(pos);
			length += item->getHeight();
			if(length >= event->motion->y)
			{	
				return item;
				break;	
			}
		}
	}
	
	return NULL;
}


void XListBox::paintSelectItem(XItem *item)
{
	XDC mDC;
	mDC.surface=screen;
	mDC.rect=&widget_rect;
	
	Uint32 color=SELECT_ITEM_COLOR;
	SDL_Rect lRect=item->paint(&mDC,divider_color,color);
	
	SDL_SetClipRect(screen,&lRect);
	vScrollbar.paint();
	SDL_SetClipRect(screen,NULL);
}

void XListBox::resumeItem()
{
	XDC mDC;
	mDC.surface=screen;
	mDC.rect=&widget_rect;
	
	if(pItem)
	{
		SDL_Rect lRect=pItem->paint(&mDC,divider_color,item_color);
		
		SDL_SetClipRect(screen,&lRect);
		
		vScrollbar.paint();
		SDL_UpdateRects(screen,1,&lRect);
		SDL_SetClipRect(screen,NULL);
	}
	
}

void XListBox::setResumeItem(XListBox *list,XItem *item)
{
	pList =list;
	pItem =item;
}

void XListBox::onSize(int w,int h)
{
	XWidget::onSize(w,h);
	
	setItemWidth();
	changSize();	
}

void XListBox::onPosition(int x,int y)
{
	XWidget::onPosition(x,y);
	
	if(run_state)
	{
		vScrollbar.setRect(widget_rect);
		vScrollbar.computeScrollbar();
	}
}
void XListBox::changSize()
{
	int item_w=0;
	list_item.begin();
	
	if(list_item.isEmpty()) return ;
		
	item_w=list_item.takeFirst()->getHeight();
	
	while(list_item.isNext())
	{
		item_w+=list_item.next()->getHeight();
	}
	
	vScrollbar.setRect(widget_rect);
	vScrollbar.setParentLength(item_w);
	vScrollbar.computeScrollbar();

}
void XListBox::mouseWheelDown(X_Event *event)
{
	compute(-6);
	onPaint(X_UPDATE);
	showWidget();
}

void XListBox::mouseWheelUp(X_Event *event)
{
	compute(6);
	onPaint(X_UPDATE);
	showWidget();
}

void XListBox::mouseLPressEvent(X_Event *event)
{
	XItem *item=selectIndex(event);
	if(item)
	{
		//1.�Ȼָ�ѡ�����item
		//2.�������ڵ�item
		//3.�������ڵ�item��

		if(pList){
			pList->resumeItem();
		}
		paintSelectItem(item);
		setResumeItem(this,item);
		if(indexListener)
		{
			indexListener->selectIndex(event,(ID)item,index);
		}
	}
}

void XListBox::onPaint(Uint16 msg)
{
	if(msg == X_PAINT)
	{
		draw();
		//�����	
		if(layout)
			layout->drawChild(widget_rectF,this);
		
	}else if(msg  == X_UPDATE)
	{
		paint();
	}
}

void XListBox::localUpdate(XRectF& pRect,XObject *pObject)
{
	if(pObject == this )
		return ;
	
	if(widget_state == X_ORIGINAL)
		initDraw();
	else
		draw();
}

