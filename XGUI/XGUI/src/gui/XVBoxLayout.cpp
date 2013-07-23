/*
*��ֱ���ֹ�����
*/

#include "XVBoxLayout.h"

XVBoxLayout::XVBoxLayout()
{
	
}

/*
*�����������BOX����ѭ�����λ��
*�㷨
	 _______
	|	  |
	|_______|
	|	  |
	|_______|
	
*���BOX�ɱ䣬��������Ӧ�Ŀ�Ⱥ͸߶�	
*/
void XVBoxLayout::computeLayout()
{
	int 	h=0;
	XRect   swap_rect;
	XLayout *swap_layout;
	XWidget *swap_widget;
	int 	un=0;
	bool    mark=true;

	Uint8  child_type;
	int    h_margin=0;
	int    v_margin=0;
	int    h_variable=0;
	int    v_variable=0;
	
	if(list_int.isEmpty())
		return ;
	compute(&h_margin,&v_margin,&h_variable,&v_variable);	
	

	XPOSITION intPos = list_int.getHeadPosition();
	XPOSITION widPos = list_widget.getHeadPosition();
	XPOSITION layPos = list_layout.getHeadPosition();
	
	child_type=list_int.getNext(intPos)->type;
	if( child_type == WIDGET)
	{	
		swap_widget = list_widget.getNext(widPos);
		swap_rect=swap_widget->getMinRect();
		
		if(swap_widget->isHVariable())//ˮƽ�ɱ�
		{
			swap_rect.w =rect.w-2*h_margin;
		}
		
		//�Ƿ񿿱�
		if(h_dock == false)
			swap_rect.x=rect.x + (rect.w-swap_rect.w)/2;
		else
			swap_rect.x=rect.x;
				
		if(swap_widget->isVVariable())//��ֱ�ɱ�
		{	
			swap_rect.h +=v_variable;	
		}
		
		if(v_dock == false)
			swap_rect.y=rect.y+v_margin;
		else swap_rect.y=rect.y;
				
		swap_widget->setLayoutRect(&swap_rect);
		swap_widget->computeLayout();
		
		mark=true;
		
		/*����������Դ���Ϊ��ʼ��
		  h��������BOX�ײ�Y����
		*/	
		h=swap_rect.y+swap_rect.h;
		
	}else if(child_type == LAYOUT)
	{
		swap_layout=list_layout.getNext(layPos);
		swap_rect=swap_layout->getMinRect();
		/*�鿴���ֹ��������Ƿ��пɱ�BOX*/
		if(swap_layout->getHVariableCount(&un) !=0 || swap_layout->getVVariableCount(&un)!=0)
		{
			swap_rect.h+=v_variable * swap_layout->getVVariableCount(&un) ; 		
		}
		mark=false;
		
		/*������BOX���ϱ߾�*/
		swap_rect.h +=(swap_layout->getVCount()+1) *v_margin;
		swap_rect.w=rect.w;
		swap_rect.x=rect.x;
		swap_rect.y=rect.y;
			
		swap_layout->setRect(&swap_rect);
		
		//�����Խڵ�
		swap_layout->computeLayout();
		
		/*����������Դ���Ϊ��ʼ��
	 	 h��������BOX�ײ�Y����
		*/	
		h=swap_rect.y+swap_rect.h;
	}else
	{
		h = rect.y + v_variable;
	}
	
	while(!intPos.isEmpty())
	{	
		child_type = list_int.getNext(intPos)->type;
		if(child_type == WIDGET)
		{	
			swap_widget=list_widget.getNext(widPos);
			swap_rect=swap_widget->getMinRect();
			
			if(swap_widget->isHVariable())
			{
				swap_rect.w =rect.w-2*h_margin;
			}
			
			if(swap_widget->isVVariable())
				swap_rect.h+=v_variable;
			
			if(h_dock == false)
				swap_rect.x=rect.x + (rect.w-swap_rect.w)/2;
			else
				swap_rect.x=rect.x;
				
			swap_rect.y=h;
			
			if(mark == true) swap_rect.y+=v_margin;
			
			swap_widget->setLayoutRect(&swap_rect);
			swap_widget->computeLayout();
			mark=true;
			
			h=swap_rect.y+swap_rect.h;
			
		}else if(child_type == LAYOUT)
		{
			swap_layout=list_layout.getNext(layPos); 
			swap_rect=swap_layout->getMinRect();
			
			/*�鿴���ֹ��������Ƿ��пɱ�BOX*/
			if(swap_layout->getHVariableCount(&un) !=0 || swap_layout->getVVariableCount(&un)!=0) //��
			{	
				swap_rect.h+=v_variable * swap_layout->getVVariableCount(&un);
			}
			
			swap_rect.x=rect.x;
			swap_rect.y= h;
			swap_rect.w =rect.w;
			
			/*�����һ��BOX�ǲ���������ô����һ���߾࣬�����һ��BOX������߾���Ŀ�ǣ������Ŀ��1��
			  ��������������������ڣ���ô���õڶ�������������һ���������BOX����
			*/
			if(mark == false){
				swap_rect.h+=v_margin*(swap_layout->getVCount());
				swap_layout->setVDock(true);
			}else 
				swap_rect.h+=v_margin*(swap_layout->getVCount()+1);
			
			swap_layout->setRect(&swap_rect);
			
			//�����Խڵ�
			swap_layout->computeLayout();
			
			mark=false;
			
			h=swap_rect.y+swap_rect.h;
	    }else
	    {
	    	 h+=v_variable;
		}
	}
}

/*ˮƽ*/
int XVBoxLayout::getHVariableCount(int *w,bool cal)
{
	XWidget  *swap_widget;
	
	int      max_weight=0;
	int      swap_w=0;
	int      s;

	/*������úܴ�ȥ�����������*/
	if(cal == false ){
	   *w= min_w;
	   return h_v_num;
	}
	h_v_num=0;
	
	XPOSITION widPos = list_widget.getHeadPosition();
	XPOSITION layPos = list_layout.getHeadPosition();

	while(!widPos.isEmpty())
	{
		swap_widget = list_widget.getNext(widPos);

		if (swap_widget->isHVariable())
		{
			h_v_num=1;
		}
		
		if(max_weight < swap_widget->getMinRect().w)
			max_weight= swap_widget->getMinRect().w;
	}
	
	while(!layPos.isEmpty())
	{
		swap_w=0;
		s=list_layout.getNext(layPos)->getHVariableCount(&swap_w,cal);
		if(h_v_num < s)
			h_v_num=s;
		if(max_weight < swap_w)
			max_weight=swap_w;	
	}
	rect.w=max_weight;
	min_w=max_weight;
	
	*w+=max_weight;
	
	return h_v_num; 	
}

/*��ֱ*/
/*�㷨�������һ��������Ļ���ô����϶��������
	����BOX����в��������в�����϶
*/
int XVBoxLayout::getVVariableCount(int *h,bool cal)
{
	/*��BOX��С�߶�*/
	int t_h=0;
	XWidget  *swap_widget;
	
	/*������úܴ�ȥ�����������*/
	if(cal == false ) {
		*h=min_h;
		return v_v_num;
	}
	v_v_num=0;
	
	XPOSITION widPos = list_widget.getHeadPosition();
	XPOSITION layPos = list_layout.getHeadPosition();
	XPOSITION intPos = list_int.getHeadPosition();

	if(list_int.getCount() ==0) return 0;
	
	while(!widPos.isEmpty())
	{
		swap_widget=list_widget.getNext(widPos);
		if(swap_widget->isVVariable())
			++v_v_num;
		t_h+= swap_widget->getMinRect().h;
	}

	while(!layPos.isEmpty())
	{
		v_v_num+=list_layout.getNext(layPos)->getVVariableCount(&t_h,cal);
	}
	
	while(!intPos.isEmpty())
	{
		if(list_int.getNext(intPos)->type == SPACE)
			++v_v_num;
	}

	rect.h=t_h;
	min_h=t_h;
	
	*h+=t_h;
	
	return v_v_num;	
}

int XVBoxLayout::getHCount()
{
	int num=0;
	int max_num=0;
	
	XPOSITION widPos = list_widget.getHeadPosition();
	XPOSITION layPos = list_layout.getHeadPosition();

	if(!list_widget.isEmpty()) max_num=1;
	
	while(!layPos.isEmpty())
	{
		num=list_layout.getNext(layPos)->getHCount();
		if(max_num < num) max_num=num;
	}
	
	return max_num;
}

int XVBoxLayout::getVCount()
{
	int num=0;
	list_layout.begin();
	list_widget.begin();
	
	XPOSITION widPos = list_widget.getHeadPosition();
	XPOSITION layPos = list_layout.getHeadPosition();


	if(!list_widget.isEmpty())
		num=list_widget.getCount(); 

	while (!layPos.isEmpty())
	{
		num+=list_layout.getNext(layPos)->getVCount();
	}
	
	return num;
}

