#include "PrepareEvent.h"
#include"Company.h"
#include"Cargo.h"
#include"Time.h"


PrepareEvent::PrepareEvent()
{
}
PrepareEvent::PrepareEvent(Time event_time1, Cargo* cargo1, Company* comp1) :Event(event_time1, cargo1, comp1)
{
}

void PrepareEvent::excute()

{

	comp->prepare_event(cargo);
	
}
void PrepareEvent::load(ifstream& InFile, Company* comp1, Cargo* c)
{
	float Load_Time, Cost, Dist;
	int ID;
	char Type;
	InFile >> Type;
	event_time.read_time(InFile);
	InFile >> ID;
	InFile >> Dist;
	InFile >> Load_Time;
	InFile >> Cost;
	
	cargo = c;
	cargo->set_cargo(ID, Type, Dist, Load_Time, Cost,event_time.getday(),event_time.gethour());
	comp = comp1;
}