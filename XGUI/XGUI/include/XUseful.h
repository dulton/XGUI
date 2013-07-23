#ifndef _XUSEFUL_H
#define _XUSEFUL_H

#include"XUtils.h"

/*�꿪��*/

#define DEBUG
#define USE_MOUSE
#define USE_KEYBOARD
//#define USE_TS


void BoxCenter(XRect *src,XRect *dst);

void ModifyAlpha1(Uint32* color,float percent);
/*�޸�������ɫ��͸����,color������������0xffffffff*/
void ModifyAlpha(XColor *color,float percent);

/*������ɫ��͸���ȣ�color������������0xffffff*/
void SetAlpha(XColor *color,float percent);

//�Ƿ�������͸��
bool isAlpha(Uint32& color);

//�ָ���
void separatorLine(SDL_Surface  *surface,Uint32 color,int x1,int x2,int y);

#ifdef DEBUG
#   define LOG(x) (printf("%s\n",x))
#else
#   define LOG(x) ((void) 0)
#endif


#define JUDGE_MOUSE_BEGIN \
if(event->motion->x < widget_rect.x+widget_rect.w && \
	event->motion->x >widget_rect.x && \
	event->motion->y <widget_rect.y+widget_rect.h &&\
	event->motion->y > widget_rect.y)\
{

#define JUDGE_MOUSE_END }

#define JUDGEMOUSE(event,rect)\
	event->motion->x < rect.x+rect.w && \
	event->motion->x > rect.x && \
	event->motion->y < rect.y+rect.h &&\
	event->motion->y > rect.y


#define JUDGEMOUSE1(event,rectF)\
	event->motion->x < rectF.x2 && \
	event->motion->x > rectF.x1 && \
	event->motion->y < rectF.y2 &&\
	event->motion->y > rectF.y1

#endif

