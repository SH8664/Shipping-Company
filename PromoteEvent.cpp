#include "PromoteEvent.h"
#include"Company.h"
#include"Time.h"
#include"Cargo.h"

PromoteEvent::PromoteEvent()
{
}
PromoteEvent::PromoteEvent(Time event_time1, Cargo* cargo1, Company* comp1) :Event(event_time1, cargo1, comp1)
{
}

void PromoteEvent::excute()
{
	
	comp->promote_request(cargo_ID, Extra_Money);
	
}
void PromoteEvent::load(ifstream& InFile, Company* comp1, Cargo* c)
{
	comp = comp1;
	event_time.read_time(InFile);
	InFile >> iD;
	InFile >> Extra_Money;    //I donot know what it is refering to ?
	cargo_ID = iD;

 cargo = comp->Get_Cargo_Pointer(iD);


}
