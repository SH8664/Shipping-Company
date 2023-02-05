#ifndef __truck
#define __truck
#include"Stack.h"
#include"Time.h"
#include"Queue.h"
#include"PriorityQueue.h"
class Cargo;
#include<iostream>
using namespace std;
class Truck
{
	int Truck_Capacity;
	float  Maintenance_period;
	int unload_total_of_my_cargos;
	Time   Maintaning_time;
	int count;
	int max_distance;
	static int truck_id;
	int J;
	int max_no_of_jounreys;
	float Speed;
	PriorityQueue<Cargo*> cargos;
	char type;
	Time move_time;
	int ID;
	int Active_Time;//Hours that Truck is Loading or Moving (it doesn't include when the Truck return to Company)
	Time finish_time;
public:
	
	Truck(int TC, float MC, float s, int j, char t);
	bool load_cargo( Cargo* c);
	bool unload_cargo();
	float get_Delivery_interval();
	bool need_mantiance();
	void set_move_time(Time t);
	Time get_MT();
	float get_speed();
	int getID();
//	int get_max_cdt_priority();
	~Truck();
	int get_capcity();
	PriorityQueue <Cargo*>& get_my_cargos();
	int Get_Active_Time();///////////
	int Get_j();
	Time get_maintaining_finish_time();
	void set_maintaining_time(Time t);
	Time get_moving_finish_time();
	//Get total num of journey
	char get_type();
	void increse_j();
	Time get_max_cdt();
	 void set_unload_total_of_my_cargos(int t);
	int get_max_distance();
	void set_max_distance(int n);
	int get_unload_time();
	void Set_Active_Time(int x);
	Time max_cdt;
	int get_finish_priority();
};

#endif