#ifndef __prepare
#define __prepare
#include"Event.h"

class PrepareEvent :
    public Event
{
public:
	PrepareEvent();
	PrepareEvent(Time event_time1, Cargo* cargo1, Company* comp1);
	
	void excute();
	void load(ifstream& InFile, Company* comp1, Cargo* c);
	
};

#endif