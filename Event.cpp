#include "Event.h"
#include"Company.h"

Event::Event()
{
	
}

Event::Event(Time event_time1, Cargo *cargo1, Company* comp1)
{
	event_time = event_time1;
	cargo = cargo1;
	comp = comp1;
}
Time Event::get_event_time()
{
	return event_time;
}
