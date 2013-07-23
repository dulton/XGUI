#ifndef _XLIST_H
#define _XLIST_H

#include<iostream>
using namespace std;


class XPOSITION;

template <class T> 
class Xdata
{
public:
	T  data;
	
	Xdata<T> *previous;
	Xdata<T> *next;
};

template <class T>
class XList
{
public:

	XList();
	~XList();
	/*
	*1 �����ܳ���
	*2 ������������ָ������λ��
	*/
	int  getCount();
	int  getCurrentIndex();
	
	XPOSITION getHeadPosition();
	XPOSITION getTailPosition();
	XPOSITION find(const T& value);
	T&        getNext(XPOSITION& rPosition);
	T&        getPrev(XPOSITION& rPosition);
	
	
	/*
	*��һ���Ǽ���Ԫ�ص�����ֵ
	*�ڶ����Ǽ������������ֵ
	*return �Ǹ����������������û��
	*/
	int indexOf(const T& e);
	
	void setPosition(const T& value);
	//operation
	void append(const T& value);
	void remove(int index);
	void removeAll();
	
	/*
	*������ֵΪbefore�ڵ�ǰ�棻
	*���before==count��ô�������
	*/
	void insert(int before,const T& value);
	
	T& getAt(int index);
	
	void begin();
	void final();
	/*
	*���¼��������Ƕ��ڼ����Ĳ���
	*/
	bool isEmpty();
	
	T& takeFirst();
	
	T& takeLast();
	
	T& current();
	
	bool isNext();
	T& next();
	
	bool isPrevious();
	T& previous();
	
private:
	Xdata<T> *head;
	Xdata<T> *last;
	
	Xdata<T> *current_data;

	int count;
	
};

class XPOSITION
{
public:
	bool isEmpty()
	{
		if(!pValue) return true;
		
		return false;
	}

	void *pValue;

};


#include "XList.h"

template <class T>
XList<T>::XList()
{
	head=NULL;
	last=NULL;
	
	count=0;
	current_data=NULL;
}

template <class T>
XList<T>::~XList()
{
	Xdata<T> *p;
	
	if(!head)
		return ;
	
	while(head)
	{
		p=head;
		head=head->next;
		delete p;
	}
}
template <class T>
void XList<T>::append(const T& value)
{
	Xdata<T> *p;
	
	p=new Xdata<T>;
	p->data=value;

	if(head==NULL){
		head=p;
		last=p;
		
		p->previous=NULL;
		p->next=NULL;
		current_data=head;
	}
	else{
		last->next=p;
		p->previous=last;
		last=last->next;
		last->next=NULL;
	}
		
	++count;
}

template <class T>
XPOSITION XList<T>::getHeadPosition()
{
	XPOSITION pos;
	pos.pValue = head;
	
	return pos;
}

template <class T>
XPOSITION XList<T>::getTailPosition()
{
	XPOSITION pos;
	pos.pValue = last;
	
	return pos;
}

template <class T>
XPOSITION XList<T>::find(const T& value)
{
	XPOSITION pos;
	Xdata<T> *swap;
	
	pos.pValue=NULL;
	swap=head;
	
	while(swap)
	{
		if(swap->data == value)
		{
			pos.pValue = swap;
			break;
		}
		swap = swap->next;
	}
	
	return pos;
}

template <class T>
T&  XList<T>::getNext(XPOSITION& rPosition)
{
	Xdata<T> *swap;
	
	swap = ((Xdata<T> *)rPosition.pValue);
	rPosition.pValue = ((Xdata<T> *)(rPosition.pValue))->next;
	return swap->data;
}

template <class T>
T&  XList<T>::getPrev(XPOSITION& rPosition)
{
	Xdata<T> *swap;
	
	swap = ((Xdata<T> *)rPosition.pValue);
	rPosition.pValue = ((Xdata<T> *)(rPosition.pValue))->previous;
	return swap->data;
}

template <class T>
int XList<T>::indexOf(const T& e)
{
	Xdata<T> *swap;
	int i=0;

	swap=head;

	while(swap)
	{
		if(e == (swap->data))
			return i;
		swap=swap->next;
		i++;
	}

	return -1;
}

template <class T>
void XList<T>::setPosition(const T& value)
{
	Xdata<T> *swap;
	
	swap=head;
	do{
		current_data=swap;
		swap=swap->next;
	}while(swap->data != value);
	
}

/*
template <class T>
int XList<T>::indexOf(XObject *obj)
{
	Xdata<T> *swap;
	int i=0;

	swap=head;
	while(swap)
	{
		if(swap->data.equals(obj))
			return i;
			
		swap=swap->next;
		i++;
		
	}
	
	return -1;
}
*/

template <class T>
int XList<T>::getCount()
{
	return count;
}

template <class T>
void XList<T>::removeAll()
{
	Xdata<T> *p;
	
	
	while(head)
	{
		p=head;
		head=head->next;
		delete p;
	}
	head=NULL;
	last=NULL;
	
	count=0;
	current_data=NULL;
}

template <class T>
void XList<T>::remove(int index)
{
	Xdata<T> *swap;
	Xdata<T> *c;
	Xdata<T> *p;
	
	int i=0;
	
	if(index <0) return ;
	
	swap=head;
	while(swap)
	{
		/*
		*һ��ɾ��������current_data�ͻ����
		*ɾ��֮���ܳ��ȼ���
		*/
		
		if(index ==i){
			
			count--;
			
			/*
			*���濼��current_data��currrent_index���ƶ����
			*1.���ɾ����λ�ô���current_index��û��ϵ
			*2.���ɾ����λ��С��current_index��ֻ��--current_index
			*3.���ɾ����λ�õ���current_index,���������һ���ڱ�ͷ��ֻ��current_data�����ƶ�
			  ������������ڱ�ͷcurrent_data�����ƶ�
			*/
			if(current_data == swap)
			{
				current_data=current_data->next;
				
			}
			/*
			*���ɾ����ͷֻ��head���ƶ�
			*���ɾ����βֻ��lastǰ��
			*���ɾ���м�ٵ�һ��
			*/
			if(index == 0)
			{	
				head=head->next;
				if(head)
					head->previous=NULL;
				
			}else if(index == count){
				
				last=last->previous;
				if(last)
					last->next=NULL;
				
			}else{
			
				c=swap->previous;
				p=swap->next;
				
				c->next=p;
				p->previous=c;			
			}
			
			delete swap;
			break;
		}
		swap=swap->next;
		++i;	
	}
}

template <class T>
void XList<T>::insert(int before,const T& value)
{
	Xdata<T> *p;
	Xdata<T> *c;
	Xdata<T> *swap;
	int i=0;
	
	swap=head;
				
	while(swap)
	{
		if(i == before ){
			
			p=new Xdata<T>;
			p->data=value;
			
			if(before == 0)
			{
				p->next=head;
				head=p;
				head->previous=NULL;
			}else
			{
				c=swap->previous;
				c->next=p;
				p->next=swap;
				swap->previous=p;
			}

			count++;
			break;
		}
		swap=swap->next;
		i++;	
	}
	
	if(before == count)
	{
		p=new Xdata<T>;
		p->data=value;
		
		last->next=p;
		p->previous=last;
		p->next=NULL;
	}
}
template <class T>
void XList<T>::begin()
{
	current_data=head;
}

template <class T>
void XList<T>::final()
{
	current_data =last;
}


/*
*���¼��������Ƕ��ڼ����Ĳ���
*/
template <class T>
T& XList<T>::takeFirst()
{
	return head->data;
}

template <class T>
T& XList<T>::takeLast()
{
	return last->data;
}

template <class T>
bool XList<T>::isEmpty()
{
	if(count==0)
		return true;
	
	return false;
}

template <class T>
bool XList<T>::isNext()
{
	if(current_data && current_data->next) 
		return true;
	
	return false;
}

template <class T>
T& XList<T>::next()
{
	current_data=current_data->next;
	
	return current_data->data;
}

static int i=0;

template <class T>
bool XList<T>::isPrevious()
{
	if(current_data && current_data->previous) 
		return true;
	
	return false;
}

template <class T>
T& XList<T>::previous()
{
	current_data=current_data->previous;
	
	return current_data->data;
}

template <class T>
T& XList<T>::current()
{
	return current_data->data; 
}

template <class T>
int  XList<T>::getCurrentIndex()
{
	return 0;
}


#endif
