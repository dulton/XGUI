/*
* �¼�����ѯ���ַ�
*/

#ifndef _XAPPLICATION_H
#define _XAPPLICATION_H

#include "XObject.h"


class XApplication
{
public:
	
	XApplication();
	~XApplication();
	int run();
	
	static int PollMessage();

};

#endif
