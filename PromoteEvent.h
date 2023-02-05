#ifndef __promote
#define __promote
#include"Event.h"

class PromoteEvent:public Event
{
	int cargo_ID;
	int Extra_Money;
public:
	PromoteEvent();
	PromoteEvent(Time event_time1, Cargo* cargo1, Company* comp1);

	void excute();
	void load(ifstream& InFile, Company* comp1,Cargo*c);
};

#endif