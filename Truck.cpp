#include "Truck.h"
#include"Cargo.h"
 int Truck:: truck_id = 0;
 
 

 
 Truck::Truck(int TC, float MC, float s, int j, char t)
{
	
	truck_id++;
	
	type = t;
	max_no_of_jounreys= j;
	J = 0;
	count = 0;
	Truck_Capacity = TC;
	Maintenance_period = MC;
	Speed = s;
	ID= truck_id;
}

bool Truck::load_cargo( Cargo* c)
{
	
		cargos.Enqueue(c,c->get_delivery_priority());
		
		return true;



}

bool Truck::unload_cargo()
{
	if (count == 0) return false;
	else {
		Cargo* c;
		cargos.Dequeue(c);
		count--;
		return true;
	}
}

float Truck::get_Delivery_interval()
{
	Cargo *c;
	Stack<Cargo*> temp;
	float max = 0;   //maxium distance
	float sum = 0;
	while (cargos.Dequeue(c)) {
		temp.push(c);
		if (c->get_delivery_distance() > max)  max = c->get_delivery_distance();
		sum += c->get_loadtime() + c->get_unloadtime();
	}
	while (temp.pop(c))
		cargos.Enqueue(c, c->get_delivery_priority());
	return (2 * (max / Speed) + sum);

}

bool Truck::need_mantiance()
{
	if (J % max_no_of_jounreys == 0)return true;
	return false;
}

void Truck::set_move_time(Time t)
{
	move_time = t;
}

Time Truck::get_MT()
{
	return move_time;
}

float Truck::get_speed()
{
	return Speed;
}

int Truck::getID()
{
	return ID;
}

//int Truck::get_max_cdt_priority()
//{
//	Cargo *c;
//	int max = -1;
//	Queue <Cargo*> temp;
//	while (cargos.Dequeue(c))
//	{
//		if (c->get_CDT_prority() > max) max = c->get_CDT_prority();
//		temp.enqueue(c);
//	}
//	while (temp.dequeue(c))cargos.Enqueue(c, c->get_delivery_priority());
//	return float(INT_MAX) / max;
//}



Truck::~Truck()
{
}

int Truck::get_capcity()
{
	return Truck_Capacity;
}

PriorityQueue<Cargo*> &Truck::get_my_cargos()
{
	return cargos;
}
int Truck::Get_Active_Time()/////////
{
	return Active_Time;
}

int Truck::Get_j()
{
	return J;
}

Time Truck::get_maintaining_finish_time()
{
	Time t;
	int m = (Maintaning_time.gethour() + Maintenance_period);
	if (m > 24) { t.sethour(m % 24);      t.setday(Maintaning_time.getday() + (m / 24)); }
	else { t.sethour(m);    t.setday(Maintaning_time.getday()); }
	return t;
}

void Truck::set_maintaining_time(Time t)
{
	Maintaning_time = t;
}

Time Truck::get_moving_finish_time()
{
	Time t;
	Queue <Cargo*>temp;
	Cargo* c;
	
	//t.setday (( max_cdt.getday()*24+max_cdt.gethour() + int(max_distance / Speed))/24);
	//t.sethour((max_cdt.getday() * 24 + max_cdt.gethour() + int(max_distance / Speed)) % 24);
	t.setday((get_MT().gethour() + get_MT().getday() * 24 +( 2* int(max_distance/Speed) )+ unload_total_of_my_cargos) / 24);
		t.sethour((get_MT().gethour() + get_MT().getday() * 24 + (2 *int (max_distance / Speed)) + unload_total_of_my_cargos) %24);
		finish_time = t;
	return t;
}



char Truck::get_type()
{
	return type;
}

void Truck::increse_j()
{
	J++;
}

Time Truck::get_max_cdt()
{
	Cargo* c;
	Time max(0, 0);
	Queue < Cargo*>temp;
	while (cargos.Dequeue(c)) 
	{
		if (c->GET_CDT() >= max)max = c->GET_CDT();
		temp.enqueue(c);
	}

	while (temp.dequeue(c))cargos.Enqueue(c, c->get_delivery_priority());
	max_cdt = max;
	return max;
}

void Truck::set_unload_total_of_my_cargos(int t)
{
	unload_total_of_my_cargos = t;
}

int Truck::get_max_distance()
{
	Cargo* c;
	int dis_max = 0;
	Queue<Cargo*>temp;
	while (get_my_cargos().Dequeue(c))
	{
		if (c->get_delivery_distance() > dis_max) dis_max = c->get_delivery_distance();
		temp.enqueue(c);

	}
	while (temp.dequeue(c))get_my_cargos().Enqueue(c, c->get_delivery_priority());
	return dis_max;
}

void Truck::set_max_distance(int n)
{
	max_distance = n;
}
int Truck::get_unload_time()
{
	return unload_total_of_my_cargos;
}
void Truck::Set_Active_Time(int x)
{
	Active_Time = x;
}

int Truck::get_finish_priority()
{
	int x = finish_time.getday() * 24 + finish_time.gethour();
	return INT_MAX/x;
}

