#ifndef __cancel
#define __cancel
#include"Event.h"
class CancelEvent :public Event
{
	int cargo_id;
public:
	CancelEvent();
	CancelEvent(Time event_time1, Cargo* cargo1, Company* comp1);
	void excute();
	void load(ifstream &InFile, Company* comp1, Cargo* c);
	
};

#endif