#ifndef __Event
#define __Event
#include"Time.h"
class Cargo;

class Company;



class Event
{ 
protected:
	Time event_time;
	Cargo *cargo;
	Company *comp;
	
	int iD;
public:
	Event();
	Event(Time event_time1,Cargo *cargo1,Company* comp1);
	Time get_event_time();
	virtual void load(ifstream& InFile, Company* comp1,Cargo*c=NULL) = 0;
	virtual void excute() =0;
	
};

#endif