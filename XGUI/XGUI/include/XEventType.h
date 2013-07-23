#ifndef _XEVENTTYPE_H
#define _XEVENTTYPE_H

#include "SDL/SDL.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
*�²����ϲ㷢��Ϣ
*����¼�����
*˫�������������ң����ƶ�
*������(ǰ��)
*/

//1--100�����������Ӧ��100֮���Ǹ��������Ӧ
typedef enum
{
	X_LOSE_FOCUS=1,
	X_KEYDOWN,
	X_KEYUP,
	X_MOUSEMOTION,	
	X_MOUSEBUTTONDOWN,
	X_MOUSEBUTTONUP,
	
	X_QUIT=12,        
	X_VIDEORESIZE=16, //���ڴ�С�ı�
	
	X_TSDOWN,   //����������
	X_TSUP,     //����������
	X_TSMOVE,    //�������ƶ�
	
	X_RESUME,
//���Ʊ���������
	X_RELAYOUT=100,        //���²���,����root�����ˢ�£������������ˢ��
	X_PAINT,               //ֻ�������,����root�����ˢ�£������������ˢ��

//start	
//����Ⱦ��������������������Ҫ�ػ��Ʊ���Ⱦ��������ˢ��	
	X_HIDE,                //������Ϣ
	X_UPDATE,              //���������ˢ��
	X_BUTTONDOWN,
	X_BUTTONUP,
	X_BUTTONENTER,
	X_BUTTONLEAVE,
//end	
	
	X_WIDGETCLOSE//root����˳�������MessegeBox	
		
}XEventType;

typedef enum
{
	X_BUTTON_LEFT=1,
	X_BUTTON_MIDDLE,
	X_BUTTON_RIGHT,
	X_BUTTON_WHEELUP,
	X_BUTTON_WHEELDOWN
	
}X_MouseType;


//���״̬
typedef enum
{
	X_ACTIVE,
	X_ORIGINAL,   //ԭʼ	     
	X_PRESSED,    //����
	X_RELEASED,
	X_CLICK,
	
}X_WIDGET_STATE;  


typedef enum
{
	ID_NONE,
	ID_OK,
	ID_CANCLE,
	ID_OKCANCLE
}BUTTON_TYPE;

typedef struct 
{
	Uint16 type;
	Uint16 mouse_type;
	SDL_MouseMotionEvent *motion;
	SDL_MouseButtonEvent *button;
	SDL_KeyboardEvent  *key;
	SDL_UserEvent      *user;
	
	
}X_Event;

#ifdef __cplusplus
}
#endif

#endif
