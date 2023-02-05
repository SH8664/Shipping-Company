#ifndef __cargo
#define __cargo

#include"Time.h"
#include<iostream>
class Truck;
using namespace std;
class Cargo
{
	Time Preparation_Time;
	float Load_time;
	float Unload_time;
	float Delivery_distance;
	float Cost;
	int ID;
	char cargo_type;
	Truck* cargo_truck;
	bool Promoted;  //added to know how many of cargo is promoted
	Time CDT;
	Time my_truck_MT;
	
public:
	void set_cdt(Time x);
	Time get_cdt();
	Cargo(int id=0);
	Cargo(int id, char t,  float ld, float cst, float dis, Time PT);
	char GetType();
	int getID();
	float get_delivery_distance();
	float get_loadtime();
	float get_unloadtime();
	void Set_Type(char c);
	int Get_Priority();
	Time Get_pt();
	Time Get_wt();
	void set_truck(Truck* t);
	Time GET_CDT();
	int get_CDT_prority();
	void set_cargo(int id, char t, int dis, int load, int cost,int day,int hour);
	void setcost(int c);
	int getcost();
	bool operator ==(int i);
	Truck* Get_Truck();
	bool IsPromoted();
	float getWT(Time current_time);
	void set_prometed(bool x);
	void set_unload_time(int n);
	int get_unload_time();
	int get_delivery_priority();
	void set_my_truck_MT(Time t);
	
};

#endif

