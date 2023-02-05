
#include "Cargo.h"
#include"Truck.h"

#include<cmath>
void Cargo::set_cdt(Time x)
{
    CDT = x;
}
Time Cargo::get_cdt()
{
    return CDT;
}
Cargo::Cargo (int id) :ID(id)
{}

Cargo::Cargo(int id, char t, float ld, float cst, float dis, Time PT) : ID(id)

{
    cargo_type = t;
    Unload_time = ld;
    Load_time = ld;
    Cost = cst;
    Delivery_distance = dis;
    Preparation_Time = PT;
    cargo_truck = NULL;
    Promoted = false;
}

char Cargo::GetType()
{
    return cargo_type;
}

int Cargo::getID()
{
    return ID;
}

float Cargo::get_delivery_distance()
{
    return Delivery_distance;
}

float Cargo::get_loadtime()
{
    return Load_time;
}

float Cargo::get_unloadtime()
{
    return Unload_time;
}

void Cargo::Set_Type(char c)
{
    cargo_type = c;
}

int Cargo::Get_Priority()
{
    int x = ceil(Preparation_Time.getday() + Preparation_Time.gethour() / 24.00);
    int pr = ((Cost / (Delivery_distance * float(x))));
    if (cargo_type == 'V') return pr;
    else return -1;
}

Time Cargo::Get_pt()
{
    return Preparation_Time;
}
Time Cargo::Get_wt()
{

    Time t;
    Time mt = my_truck_MT;
    int hour = (mt.gethour() + (mt.getday() * 24)) - (Preparation_Time.gethour() + (Preparation_Time.getday() * 24));
    t.setday(hour / 24);
    t.sethour(hour % 24);
    return t;
}

void Cargo::set_truck(Truck* t)
{
   cargo_truck = t;
}

Time Cargo::GET_CDT()
{
    Time t;

    Time mt = cargo_truck->get_MT();
  if( (mt.gethour() + (Delivery_distance / cargo_truck->get_speed()) + Unload_time)>=24)
  { t.sethour((mt.gethour() + (Delivery_distance / cargo_truck->get_speed()) + Unload_time) - 24);
  t.setday(mt.getday() +1);
  }
  else {
     t. sethour((mt.gethour() + (Delivery_distance /float( cargo_truck->get_speed())) + Unload_time));
          t.setday(mt.getday());
  }
    return t;
}

int Cargo::get_CDT_prority()
{
   return(float(INT_MAX)/( GET_CDT().getday() * 24 + GET_CDT().gethour()));
}

void Cargo::set_cargo(int id, char t, int dis, int load, int cost,int day,int hour)
{

    ID = id;
    cargo_type = t;
    Delivery_distance = dis;
  Load_time=load;
    Unload_time=load;
    Cost = cost;
    Preparation_Time.setday(day);
    Preparation_Time.sethour(hour);
}

void Cargo::setcost(int c)
{
    Cost = c;
}

int Cargo::getcost()
{
    return Cost;
}

bool Cargo::operator==(int data)
{
    return (data == ID);
}
Truck* Cargo::Get_Truck()
{
    return cargo_truck;
}
bool Cargo::IsPromoted()
{
    return Promoted;
}
float Cargo::getWT(Time current_time)
{
    return(abs((Preparation_Time.getday() * 24 + Preparation_Time.gethour()) - (current_time.getday() * 24 + current_time.gethour())));
}

void Cargo::set_prometed(bool x)
{
    Promoted = x;
}

void Cargo::set_unload_time(int n)
{
    Unload_time = n;

}

int Cargo::get_unload_time()
{
    return Unload_time;
}

int Cargo::get_delivery_priority()
{
    return INT_MAX/Delivery_distance;
}

void Cargo::set_my_truck_MT(Time t)
{
    my_truck_MT = t;
}
