/*
* �¼�����ѯ���ַ�
*/

#include "XApplication.h"
#include "XWidget.h"
#include "XUseful.h"

XApplication::XApplication()
{
	putenv ("SDL_VIDEO_WINDOW_POS");
	putenv ("SDL_VIDEO_CENTERED=1");
	
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);	
	if(TTF_Init() == -1)
	{
		LOG("TTF_init:");
	}
}
/*
*�ر�ע�⣺XApplication�����Ϊ�ֲ������ͻ����,��Ϊ�������ͷ��ڴ�
*/
XApplication::~XApplication()
{
	SDL_FreeSurface(XWidget::screen);
	
	if(XWidget::share_font){
		delete XWidget::share_font;
	}
	
	if(XFont::dafult_font){
		TTF_CloseFont(XFont::dafult_font);
		XFont::dafult_font=NULL;
	}
	TTF_Quit();
	SDL_Quit();
	
}


/*
* ����ַ���Ϣ
* ����ƽ����齨ֻ��һ��
* ���Բ�������Ӧ�������
*/

int XApplication::run()
{
	if(XAbstractWidget::root_widget)
	{
		((XWidget *)XAbstractWidget::root_widget)->onInit();	
		((XWidget *)XAbstractWidget::root_widget)->reLayout();	
	}
	
	PollMessage();

	return 0;
}

int XApplication::PollMessage()
{
	SDL_Event event;
	X_Event   x_event;
	
	while(1){
		
		SDL_WaitEvent(&event);
		x_event.type=event.type;
		//x_event.user=&event.user;
#ifdef USE_MOUSE		
		x_event.mouse_type = event.motion.state;
		x_event.motion=&event.motion;
       	x_event.button=&event.button;
#endif       	
#ifdef USE_KEYBOARD
		x_event.key=&event.key;
#endif      
		if(XAbstractWidget::globalPoll(&x_event) )
			continue;
		switch(x_event.type)
		{
			case SDL_VIDEORESIZE:
			if(XAbstractWidget::root_widget){
				((XWidget *)XAbstractWidget::root_widget)->reLayout();
			}
			break;
			
			case X_RELAYOUT:
			{
				((XWidget *)XAbstractWidget::root_widget)->reLayout();
			}
			break;
				
#ifdef  USE_MOUSE
			
			case SDL_MOUSEMOTION:
       		case SDL_MOUSEBUTTONDOWN:
       		case SDL_MOUSEBUTTONUP:
       			  
 			  XAbstractWidget::root_widget->responseEvent(&x_event);     			  	  
 			  break;   
#endif 		
/*
#ifdef USE_KEYBOARD
       		case SDL_KEYUP:
       		case SDL_KEYDOWN:
				 x_event.button=&event.button;
				 XWidgetProcess::root_widget->responseEvent(&x_event);
				 break;	
#endif			 
*/			
			case X_UPDATE:
			{
				XAbstractWidget::root_widget->responseEvent(&x_event); 
			}
			break;
			case X_WIDGETCLOSE:
			{
				goto end;
			}
			break;
			
			//����Ŀǰ��messageBox���������ڻָ�����Ӧ�ûָ������
			case X_RESUME:	
			{
				
			}
			goto end;	
			
			case SDL_QUIT:
			{
				if(((XWidget *)XAbstractWidget::root_widget)->onCloseWindowEvent() == true)
					goto end;
			}
		}
	}
end:	
	return 0;
}

