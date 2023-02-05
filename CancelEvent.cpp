#include "CancelEvent.h"
#include"Company.h"
#include"Time.h"
#include"Cargo.h"

CancelEvent::CancelEvent()
{
}

CancelEvent::CancelEvent(Time event_time1, Cargo* cargo1, Company* comp1):Event(event_time1, cargo1, comp1)
{
}

void CancelEvent::excute()
{
	comp->cancel_request(cargo_id);
	
}

void CancelEvent::load(ifstream& InFile, Company* comp1, Cargo* c)
{
	
	int ID;
	event_time.read_time(InFile);
	InFile >> ID;
	comp = comp1;
	cargo_id = ID;
	cargo = comp1->Get_Cargo_Pointer(ID);
	
}
