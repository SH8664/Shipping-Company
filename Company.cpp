#include "Company.h"
#include"Truck.h"
#include"Cargo.h"
#include <string>
#include"Event.h"
#include"CancelEvent.h"
#include"PrepareEvent.h"
#include"PromoteEvent.h"
#include<fstream>
#include"UI.h"
using namespace std;


Company::Company()
{}

void Company:: intialization(int nn, int ns, int nv, float sn, float ss, float sv, int cn, int cs, int cv, int t, int tm,int at)
{
	while (nn) {
		Truck* truck = new Truck(cn, t, sn, cn, 'N');
		waiting_trucks_normal.enqueue(truck);
		nn--;
	}
	while (ns) {
		Truck* truck = new Truck(cs, t, ss, cs, 'S');
		waiting_trucks_special.enqueue(truck);
		ns--;
	}
	while (nv) {
		Truck* truck = new Truck(cv, t, sv, cv, 'V');
		waiting_trucks_VIP.enqueue(truck);
		nv--;
	}
	Maxw = tm;
	Autop = at;

}
Cargo* Company::Get_Cargo_Pointer(int ID)
{
	
	
	
	Cargo** n = (waiting_cargos_Normal.search(ID));
	if (!n) return NULL;
		return *n;

}

bool Company::cancel_request(int id)
{
	
	return (waiting_cargos_Normal.deleting(id));
	
}






bool Company::promote_request(int id,int money)
{
	Cargo *cargo = Get_Cargo_Pointer(id);

	bool x = waiting_cargos_Normal.remove(id);
	if (x)
	{
		cargo->Set_Type('V');
		cargo->setcost(cargo->getcost() + money);
		waiting_cargos_VIP.Enqueue(cargo, cargo->Get_Priority());
		if(money==0)
		cargo->set_prometed(true);
	}
	return x;
}

Time Company::GetCargosAvgWait()
{
	Time t;

	int total_hours=0;
	
	Queue <Cargo*>tempn;
	Queue <Cargo*>temps;
	Queue <Cargo*>tempv;
	Cargo* c;
	int count=0;
	while (Delivered_normal_cargos.dequeue(c)) {
		total_hours += c->Get_wt().gethour() + c->Get_wt().getday() * 24;
		tempn.enqueue(c);
		count++;
	}
	while (Delivered_special_cargos.dequeue(c)) {
		total_hours += c->Get_wt().gethour() + c->Get_wt().getday() * 24;
		temps.enqueue(c);
		count++;
	}
	while (Delivered_VIP_cargos.dequeue(c)) {
		total_hours += c->Get_wt().gethour() + c->Get_wt().getday() * 24;
		tempv.enqueue(c);
		count++;
	}
	while (tempn.dequeue(c))
		Delivered_normal_cargos.enqueue(c);

	while (temps.dequeue(c))
		Delivered_special_cargos.enqueue(c);

	while (tempv.dequeue(c))
		Delivered_VIP_cargos.enqueue(c);



	float avg = total_hours / count;
	t.setday(avg / 24);
	t.sethour(int(avg )% 24);
	return t;





}

void Company::prepare_event(Cargo* cargo)
{
	char type = cargo->GetType();
	if (type == 'N' || type == 'n')
	{
		waiting_cargos_Normal.enqueue(cargo);
		Total_N_cargos++;
	}
	if (type == 's' || type == 'S')
	{
		waiting_cargos_Special.enqueue(cargo);
		Total_S_cargos++;

	}
	if (type == 'V' || type == 'v')
	{
		waiting_cargos_VIP.Enqueue(cargo, cargo->Get_Priority());
		Total_V_cargos++;
	}
}
bool Company::finish_simulation()
{
	return(waiting_cargos_Normal.is_empty() && waiting_cargos_Special.isEmpty() && waiting_cargos_VIP.IsEmpty() &&
		Moving_normal_trucks.IsEmpty() && Moving_special_trucks.IsEmpty() && Moving_VIP_trucks.IsEmpty() && events.isEmpty()&&Loading_normal_trucks==nullptr&& Loading_special_trucks == nullptr && Loading_VIP_trucks == nullptr &&
		Maintaining_trucks_normal.isEmpty()&&Maintaining_trucks_special.isEmpty()&&Maintaining_trucks_VIP.isEmpty());
}

void Company::get_current_event(Time t, Queue<Event*>& temp)
{
	Event* v;
	while (events.peek(v) && (v->get_event_time() <= t))
	{
		events.dequeue(v);
		temp.enqueue(v);

	}
}
void Company::ReadFile()
{
	
	ifstream File;
	string file_name;
	cout << "Enter your file name " << endl;
	cin >> file_name;
	File.open(file_name + ".txt");
	
	while (!File.is_open()) {
		cout << "invalid !!! Try anther name" << endl;
		cin >> file_name;
	File.open(file_name + ".txt");
	}
	////////// reading number of trucks of each type /////////// 
	File >> count_Normal_Truck;
	File.ignore(1);                    //space
	File >> count_Special_Truck;
	File.ignore(1);                    //space
	File >> count_VIP_Truck;
       	////////// reading speed of trucks of each type /////////// 
	int speed_Normal_Truck;
	File >> speed_Normal_Truck;        //N speed  
	File.ignore(1);                   //space
	int speed_Special_Truck;
	File >> speed_Special_Truck;      //S speed
	File.ignore(1);                   //space
	int speed_VIP_Truck;              //V speed
	File >> speed_VIP_Truck;
	////////// Capacity of each truck    ///////////////
	int capacity_Normal_Truck;        //N Capacity
	File >> capacity_Normal_Truck;
	File.ignore(1);                  //space
	int capacity_Special_Truck;
	File >> capacity_Special_Truck;  //S Capacity
 	File.ignore(1);                  //space
	int capacity_VIP_Truck;        
	File >> capacity_VIP_Truck;      //V Capacity
	////////// reading number of journey //////////////
	int J;
	File >> J;                     //journey
	File.ignore(1);                //space
	////////// reading Check_Up of trucks of each type /////////// 
	int checkup_Normal_Truck;     //N check
	File >> checkup_Normal_Truck; 
	File.ignore(1);               //space
	int checkup_Special_Truck;    //S check
	File >> checkup_Special_Truck;
	File.ignore(1);               //space
	int checkup_VIP_Truck;        //V check
	File >> checkup_VIP_Truck;
	///////// auto promotion limit (days) ///////////
	
	File >> Autop;              //AutoP
	File.ignore(1);             //space
	////////  MaxW (hours)///////////
	File >> Maxw;               //Maxw
	/////////////// reading events and assigning the ///////////////
	int num_of_event;
	File >> num_of_event;      //num of events
	for (int i = 0; i < num_of_event;i++)
	{
		char type;
		File >> type;
		////New Preparation Event
		Event* new_Event=NULL;
		if (type == 'R')
		{
			new_Event = new PrepareEvent;
			Cargo* c = new Cargo;
			new_Event->load(File, this,c);
		}
		////New Promotion Event
		else if (type == 'P')
		{
			 new_Event = new PromoteEvent;
			 new_Event->load(File, this);
		}
		////New Cancelation Event
		else if (type == 'X')
		{  
			 new_Event = new CancelEvent;
			 new_Event->load(File, this);
		}
		if (new_Event->get_event_time().gethour() >= 5 && new_Event->get_event_time().gethour() <= 23)
			events.enqueue(new_Event);
		else
			delete new_Event;
	}
	events.get_count();
	File.close();
	///Assign Data Trucks 
	int count = count_Normal_Truck;
	while (count) {
		Truck* truck = new Truck(capacity_Normal_Truck, checkup_Normal_Truck, speed_Normal_Truck, J, 'N');
		waiting_trucks_normal.enqueue(truck);
		count--;
	}
	count = count_Special_Truck;
	while (count) {
		Truck* truck = new Truck(capacity_Special_Truck, checkup_Special_Truck, speed_Special_Truck, J, 'S');
		waiting_trucks_special.enqueue(truck);
		count--;
	}
	count = count_VIP_Truck;
	while (count)
	{
		Truck* truck = new Truck(capacity_VIP_Truck, checkup_VIP_Truck, speed_VIP_Truck, J, 'V');
		waiting_trucks_VIP.enqueue(truck);
		count--;
	}

}











void Company::MoveWaiting_deliverd()
{
	Cargo* c;
	/////////////VIP_movement
	{
		if (waiting_cargos_VIP.Dequeue(c))
		{
			Delivered_VIP_cargos.enqueue(c);
			
		}
	}
	//////////special_movement
	{
		if (waiting_cargos_Special.dequeue(c))
		{
			Delivered_special_cargos.enqueue(c);
			
		}

	}
	////////////////normal_movement
	{  
		if (waiting_cargos_Normal.dequeue(c))
		{
			Delivered_normal_cargos.enqueue(c);
			
		}
	}
}
Linked_List<Cargo*>& Company::get_waiting_normal()
{
	return waiting_cargos_Normal;
	// TODO: insert return statement here
}
Queue<Cargo*>& Company::get_waiting_special()
{
	return waiting_cargos_Special;
	// TODO: insert return statement here
}

PriorityQueue<Cargo*>& Company::get_waiting_VIP()
{
	return waiting_cargos_VIP;
	// TODO: insert return statement here
}


Queue<Cargo*>& Company::get_delivered_normal()
{
	return Delivered_normal_cargos;
	// TODO: insert return statement here
}

Queue<Cargo*>& Company::get_delivered_special()
{
	return Delivered_special_cargos;
	// TODO: insert return statement here
}

Queue<Cargo*>& Company::get_delivered_VIP()
{
	return Delivered_VIP_cargos;
	// TODO: insert return statement here
}

Queue<Truck*>& Company::get_waiting_normal_truck() { return waiting_trucks_normal; }
Queue<Truck*>& Company::get_waiting_special_truck() { return waiting_trucks_special; }
Queue<Truck*>& Company::get_waiting_VIP_truck() {
	return waiting_trucks_VIP;
}



PriorityQueue<Truck*>& Company::get_moving_normal_truck()
{
	// TODO: insert return statement here
	return Moving_normal_trucks;
}

PriorityQueue<Truck*>& Company::get_moving_special_truck()
{
	// TODO: insert return statement here
	return Moving_special_trucks;
}

PriorityQueue<Truck*>& Company::get_moving_VIP_truck()
{
	// TODO: insert return statement here
	return Moving_VIP_trucks;
}

Truck*& Company::get_loading_normal_truck()
{
	// TODO: insert return statement here
	return Loading_normal_trucks;
}

Truck* & Company::get_loading_special_truck()
{
	// TODO: insert return statement here
	return Loading_special_trucks;
}

Truck*& Company::get_loading_VIP_truck()
{
	// TODO: insert return statement here
	return Loading_VIP_trucks;
}

Queue<Truck*>& Company::get_maintaining_normal_truck()
{
	// TODO: insert return statement here
	return Maintaining_trucks_normal;
}

Queue<Truck*>& Company::get_maintaining_special_truck()
{
	// TODO: insert return statement here
	return Maintaining_trucks_special;
}

Queue<Truck*>& Company::get_maintaining_VIP_truck()
{
	// TODO: insert return statement here
	return Maintaining_trucks_VIP;
}

void Company::Load_normal_cargos(Time current_time)
{
	if (Loading_normal_trucks) return;
	
	Truck* t = NULL;
	Truck* vt = NULL;
	Cargo* c = NULL;


	int count = waiting_cargos_Normal.get_count();
	waiting_trucks_normal.peek(t);
	waiting_trucks_VIP.peek(vt);

	waiting_cargos_Normal.peek(c);
	//just  to see if the first element exceed maxw


	
	if (!Loading_normal_trucks&&waiting_trucks_normal.peek(t) && waiting_cargos_Normal.peek(c) && t->get_capcity() <= count || !Loading_normal_trucks&& waiting_trucks_normal.peek(t) && waiting_cargos_Normal.peek(c) &&c->getWT(current_time) >= Maxw)
	{
		waiting_trucks_normal.dequeue(t);

		int total_loadtime = 0;
		for (int i = 0; i < t->get_capcity(); i++)
		{
			if (!waiting_cargos_Normal.dequeue(c)) break;
			c->set_truck(t);
			t->load_cargo(c);

			total_loadtime += c->get_loadtime();


		}
		
		Loading_normal_trucks = t;
		Time time;
		//time.sethour( (total_loadtime + current_time.gethour()) % 24);
		//time.setday(current_time.getday() + (total_loadtime + current_time.gethour()) / 24);
	
		////if(x=>23&&x<=5)
		if (23 - current_time.gethour() <= total_loadtime)
		{
			time.sethour((current_time.gethour() + total_loadtime +5)%24 );
			time.setday((current_time.getday() * 24 + (current_time.gethour() + total_loadtime + 5)) / 24);

		}
		else {
			time.sethour((total_loadtime + current_time.gethour()) % 24);
			time.setday(current_time.getday() + (total_loadtime + current_time.gethour()) / 24);

		}
		t->set_move_time(time);
		count -= t->get_capcity();
	}
	else  if(!Loading_VIP_trucks&&waiting_trucks_VIP.peek(vt) &&waiting_cargos_Normal.peek( c) && vt->get_capcity() <= count || !Loading_VIP_trucks&& waiting_trucks_VIP.peek(vt) && waiting_cargos_Normal.peek(c) && c->getWT(current_time) >= Maxw)
	{

		waiting_trucks_VIP.dequeue(vt);
		int total_loadtime = 0;
		for (int i = 0; i < vt->get_capcity(); i++)
		{
			if (!waiting_cargos_Normal.dequeue(c)) break;
			c->set_truck(vt);
			vt->load_cargo(c);
			
			total_loadtime += c->get_loadtime();


		}
		Loading_normal_trucks=vt;
		Time time;
		if (23 - current_time.gethour() <= total_loadtime)
		{
			time.sethour((current_time.gethour() + total_loadtime + 6) % 24);
			time.setday((current_time.getday() * 24 + (current_time.gethour() + total_loadtime + 6)) / 24);

		}
		else {
			time.sethour((total_loadtime + current_time.gethour()) % 24);
			time.setday(current_time.getday() + (total_loadtime + current_time.gethour()) / 24);

		}
		vt->set_move_time(time);
		count -= vt->get_capcity();
	}

}




void Company::Load_special_cargos(Time current_time)
{
	if (Loading_special_trucks!=nullptr) return;
	Truck* t = NULL;
	Cargo* c = NULL;
	

	int count = waiting_cargos_Special.get_count();
	waiting_trucks_special.peek(t);


	waiting_cargos_Special.peek(c);    //just  to see if the first element exceed maxw



	if (waiting_trucks_special.peek(t) && waiting_cargos_Special.peek(c) && t->get_capcity() <= count || waiting_trucks_special.peek(t) && waiting_cargos_Special.peek(c) && c->getWT(current_time) >= Maxw)
	{

		waiting_trucks_special.dequeue(t);

		int total_loadtime = 0;
		for (int i = 0;i < t->get_capcity();i++) {
			if (!waiting_cargos_Special.dequeue(c)) break;
			c->set_truck(t);
			t->load_cargo(c);
			
			total_loadtime += c->get_loadtime();

		}
		Loading_special_trucks=t;
		Time time;
		if (23 - current_time.gethour() <= total_loadtime)
		{
			time.sethour((current_time.gethour() + total_loadtime + 6) % 24);
			time.setday((current_time.getday() * 24 + (current_time.gethour() + total_loadtime + 6)) / 24);

		}
		else {
			time.sethour((total_loadtime + current_time.gethour()) % 24);
			time.setday(current_time.getday() + (total_loadtime + current_time.gethour()) / 24);

		}
		t->set_move_time(time);
		count -= t->get_capcity();
	}

}
void Company::Load_VIP_cargos(Time current_time)
{
	if (Loading_VIP_trucks) return;
	
	Truck* t = NULL;
	Cargo* c = NULL;
	Truck* st = NULL;
	Truck* vt = NULL;

	int count = waiting_cargos_VIP.get_count();
	waiting_trucks_normal.peek(t);
	waiting_trucks_special.peek(st);
	waiting_trucks_VIP.peek(vt);

	waiting_cargos_VIP.peek(c);    //just  to see if the first element exceed maxw



	if (!Loading_VIP_trucks&&waiting_trucks_VIP.peek(vt) && waiting_cargos_VIP.peek(c) && vt->get_capcity() <= count|| !Loading_VIP_trucks&& waiting_trucks_VIP.peek(vt) && waiting_cargos_VIP.peek(c) && c->getWT(current_time) >= Maxw)
	{
		waiting_trucks_VIP.dequeue(t);

		int total_loadtime = 0;
		for (int i = 0; i < t->get_capcity(); i++) {
			if (!waiting_cargos_VIP.Dequeue(c)) break;
			c->set_truck(t);
			vt->load_cargo(c);

			total_loadtime += c->get_loadtime();

		}
		Loading_VIP_trucks=(vt);
		Time time;
		if (23 - current_time.gethour() <= total_loadtime)
		{
			time.sethour((current_time.gethour() + total_loadtime + 6) % 24);
			time.setday((current_time.getday() * 24 + (current_time.gethour() + total_loadtime + 6)) / 24);

		}
		else {
			time.sethour((total_loadtime + current_time.gethour()) % 24);
			time.setday(current_time.getday() + (total_loadtime + current_time.gethour()) / 24);

		}
		vt->set_move_time(time);
		count -= vt->get_capcity();
	}
	else if (!Loading_normal_trucks&&waiting_trucks_normal.peek(t) &&waiting_cargos_VIP.peek(c) && t->get_capcity() <= count|| !Loading_normal_trucks && waiting_trucks_normal.peek(t) && waiting_cargos_VIP.peek(c) && c->getWT(current_time) >= Maxw)
	{
		waiting_trucks_normal.dequeue(t);

		int total_loadtime = 0;
		for (int i = 0; i < t->get_capcity(); i++) {
			if (!waiting_cargos_VIP.Dequeue(c)) break;
			c->set_truck(t);
			t->load_cargo(c);

			total_loadtime += c->get_loadtime();

		}
		Loading_VIP_trucks=(t);
		Time time;
		if (23 - current_time.gethour() <= total_loadtime)
		{
			time.sethour((current_time.gethour() + total_loadtime + 6) % 24);
			time.setday((current_time.getday() * 24 + (current_time.gethour() + total_loadtime + 6)) / 24);

		}
		else {
			time.sethour((total_loadtime + current_time.gethour()) % 24);
			time.setday(current_time.getday() + (total_loadtime + current_time.gethour()) / 24);

		}
		t->set_move_time(time);
		count -= t->get_capcity();
	}
	else if (!Loading_special_trucks&&waiting_trucks_special.peek(st) && waiting_cargos_VIP.peek(c)&& st->get_capcity() <= count|| !Loading_special_trucks&&waiting_trucks_special.peek(st) && waiting_cargos_VIP.peek(c) && c->getWT(current_time) >= Maxw)
	{
		waiting_trucks_special.dequeue(st);

		int total_loadtime = 0;
		for (int i = 0; i < st->get_capcity(); i++) {
			if (!waiting_cargos_VIP.Dequeue(c)) break;
			c->set_truck(st);
			st->load_cargo(c);

			total_loadtime += c->get_loadtime();

		}
		Loading_VIP_trucks=(st);
		Time time;
		if (23 - current_time.gethour() <= total_loadtime)
		{
			time.sethour((current_time.gethour() + total_loadtime + 6) % 24);
			time.setday((current_time.getday() * 24 + (current_time.gethour() + total_loadtime + 6)) / 24);

		}
		else {
			time.sethour((total_loadtime + current_time.gethour()) % 24);
			time.setday(current_time.getday() + (total_loadtime + current_time.gethour()) / 24);

		}
		st->set_move_time(time);
		count -=st->get_capcity();
	}
}
void Company::writeFile()
{

	ofstream File;
	string out_File;
	cout << "Enter name of Output File" << endl;
	cin >> out_File;
	File.open(out_File+".txt");
	File << "CDT" << " " << "ID" << " " << "PT" << " " << "WT" << " " << "TID" << endl;
	Cargo* delv_cargo;
	Queue<Cargo*> temp;
	Time avg_wait(0, 0);
	int hour = 0;

	while (Delivered_cargos.dequeue(delv_cargo))
	{
		delv_cargo->get_cdt().write_time(File);
		File << " " << delv_cargo->getID() << " ";
		delv_cargo->Get_pt().write_time(File);
		File << " ";
		delv_cargo->Get_wt().write_time(File);
		File << " " << delv_cargo->Get_Truck()->getID() << endl;

		//calculate sum of waitting time for statistics 
		hour += delv_cargo->Get_wt().gethour() + (delv_cargo->Get_wt().getday() * 24);
		temp.enqueue(delv_cargo);
	}
	//calculate avg_wait

	hour /= temp.get_count();
	avg_wait.sethour(hour % 24);
	avg_wait.setday(hour / 24);
	while (temp.dequeue(delv_cargo))
	{
		Delivered_cargos.enqueue(delv_cargo);
	}
	File << "-------------------------------------" << endl;
	File << "-------------------------------------" << endl;
	File << "Cargos: " << Total_Cargos() << "[ N : " << Total_Normal_Cargos() << " , S : " << Total_Special_Cargos() << " , V : " << Total_VIP_Cargos() << " ]" << endl;
	File << "Cargo Avg Wait = ";
	avg_wait.write_time(File);
	File << endl;

	File << "Auto - promoted Cargos : " << AutoPromotedCargos() << " %" << endl;
	File << "Trucks: " << Total_Trucks() << "[ N : " << Total_Normal_Trucks() << " , S : " << Total_Special_Trucks() << " , V : " << Total_VIP_Trucks() << " ]" << endl;
	File << "Avg Active time = " << Avg_Active_Time() << "%" << endl;
	File << "Avg utilization = " << Avg_Utilization() << "%" << endl;

}
	int Company::num_promoted_cargos()
	{
		//VIP only
		Cargo* c;
		Queue<Cargo*>temp;
		int countP = 0;
		while (Delivered_VIP_cargos.dequeue(c))
		{
			temp.enqueue(c);
			if (c->IsPromoted())countP++;
		}
		while (temp.dequeue(c))
			Delivered_VIP_cargos.enqueue(c);
		return countP;
	}
	double Company::AutoPromotedCargos()
	{
		if (Total_Normal_Cargos())
			return (100 * num_promoted_cargos()) / float(Total_Normal_Cargos());
		else
			return 0;
	}
	int Company::Total_Active_Time()
	{
		//Assuming that All Trucks are now in waiting
		Queue<Truck*>temp;
		Truck* T;
		double Total_Time = 0;

		//First Normal 

		while (waiting_trucks_normal.dequeue(T))
		{
			temp.enqueue(T);
			Total_Time += T->Get_Active_Time();
		}
		while (temp.dequeue(T))
		{
			waiting_trucks_normal.enqueue(T);
		}

		//Second Special

		while (waiting_trucks_special.dequeue(T))
		{
			temp.enqueue(T);
			Total_Time += T->Get_Active_Time();
		}
		while (temp.dequeue(T))
		{
			waiting_trucks_special.enqueue(T);
		}

		//third VIP

		while (waiting_trucks_VIP.dequeue(T))
		{
			temp.enqueue(T);
			Total_Time += T->Get_Active_Time();
		}
		while (temp.dequeue(T))
		{
			waiting_trucks_VIP.enqueue(T);
		}
		return Total_Time;
	}
	double Company::Avg_Active_Time()//is not complete
	{
		return ((100 * Total_Active_Time()) / (float(Get_Sim_Time())*Total_Trucks()));
	}
	//check it with sara and nesma
	int Company::Get_Sim_Time()
	{
		return (finish_time.gethour() + (24 * finish_time.getday()));
	}

	int Company::Total_Normal_Cargos()
	{
		return Total_N_cargos;
	}
	int Company::Total_VIP_Cargos()
	{
		return Total_V_cargos;
	}

	int Company::Total_Special_Cargos()
	{
		return Total_S_cargos;
	}

	int Company::Total_Cargos()
	{
		return Total_N_cargos + Total_V_cargos + Total_S_cargos;
	}

	int Company::Total_Normal_Trucks()
	{
		return count_Normal_Truck;
	}

	int Company::Total_VIP_Trucks()
	{
		return count_VIP_Truck;
	}

	int Company::Total_Special_Trucks()
	{
		return count_Special_Truck;
	}

	int Company::Total_Trucks()
	{
		return (Total_Special_Trucks() + Total_Normal_Trucks() + Total_VIP_Trucks());
	}
	int Company::Get_tDC(Truck * T)
	{
		Cargo* c;
		Queue<Cargo*>temp;
		int count = 0;
		while (Delivered_cargos.dequeue(c))
		{
			temp.enqueue(c);
			if (c->Get_Truck()->getID() == T->getID())count++;
		}
		while (temp.dequeue(c))
			Delivered_cargos.enqueue(c);
		return count;
	}
	double Company::Utilization_Truck(Truck * T)
	{
		if (!(T->Get_j()))return 0;
		double x = 0;
		x += (T->get_capcity() * T->Get_j());
		x = Get_tDC(T) / x;
		x = x * (T->Get_Active_Time() / float(Get_Sim_Time()));
		return x;
		//	return (100*(float(Get_tDC(T)) / float(T->get_capcity() * T->Get_j()) * float(T->Get_Active_Time() / Get_Sim_Time())));
	}
	double Company::Avg_Utilization()
	{
		//Assuming that All Trucks are now in waiting
		Queue<Truck*>temp;
		Truck* T;
		double U = 0;

		//First Normal 

		while (waiting_trucks_normal.dequeue(T))
		{
			temp.enqueue(T);
			U += Utilization_Truck(T);
		}
		while (temp.dequeue(T))
		{
			waiting_trucks_normal.enqueue(T);
		}

		//Second Special

		while (waiting_trucks_special.dequeue(T))
		{
			temp.enqueue(T);
			U += Utilization_Truck(T);
		}
		while (temp.dequeue(T))
		{
			waiting_trucks_special.enqueue(T);
		}

		//third VIP

		while (waiting_trucks_VIP.dequeue(T))
		{
			temp.enqueue(T);
			U += Utilization_Truck(T);
		}
		while (temp.dequeue(T))
		{
			waiting_trucks_VIP.enqueue(T);
		}
		return ((100 * U)/Total_Trucks());
	}





void Company::truck_moving_to_waiting(Time current_time)
{

	Truck* v=NULL;
	///////////////////////normal
	
	
	while (Moving_normal_trucks.peek(v) &&current_time >= v->get_moving_finish_time())
	{
		Moving_normal_trucks.Dequeue(v);
			v->increse_j();
			if (v->need_mantiance())
			{
				v->set_maintaining_time(current_time);
				if (v->get_type() == 'N')Maintaining_trucks_normal.enqueue(v);
				if (v->get_type() == 'S')Maintaining_trucks_special.enqueue(v);
				if (v->get_type() == 'V')Maintaining_trucks_VIP.enqueue(v);
			}
			if (!(v->need_mantiance()))
			{
				if (v->get_type() == 'N')waiting_trucks_normal.enqueue(v);
				if (v->get_type() == 'S')waiting_trucks_special.enqueue(v);
				if (v->get_type() == 'V')waiting_trucks_VIP.enqueue(v);
			}

			
		
	}
	
	///////////////////////special
	
	while (Moving_special_trucks.peek(v) && current_time >= v->get_moving_finish_time())
	{
		Moving_special_trucks.Dequeue(v);
		v->increse_j();
		if (v->need_mantiance())
		{
			v->set_maintaining_time(current_time);
			if (v->get_type() == 'N')Maintaining_trucks_normal.enqueue(v);
			if (v->get_type() == 'S')Maintaining_trucks_special.enqueue(v);
			if (v->get_type() == 'V')Maintaining_trucks_VIP.enqueue(v);
		}
		if (!(v->need_mantiance()))
		{
			if (v->get_type() == 'N')waiting_trucks_normal.enqueue(v);
			if (v->get_type() == 'S')waiting_trucks_special.enqueue(v);
			if (v->get_type() == 'V')waiting_trucks_VIP.enqueue(v);
		}

		

	}
	//////////////////////VIP

	
	while (Moving_VIP_trucks.peek(v) && current_time >= v->get_moving_finish_time())
	{
		Moving_VIP_trucks.Dequeue(v);
		v->increse_j();
		if (v->need_mantiance())
		{
			v->set_maintaining_time(current_time);
			if (v->get_type() == 'N')Maintaining_trucks_normal.enqueue(v);
			if (v->get_type() == 'S')Maintaining_trucks_special.enqueue(v);
			if (v->get_type() == 'V')Maintaining_trucks_VIP.enqueue(v);
		}
		if (!(v->need_mantiance()))
		{
			if (v->get_type() == 'N')waiting_trucks_normal.enqueue(v);
			if (v->get_type() == 'S')waiting_trucks_special.enqueue(v);
			if (v->get_type() == 'V')waiting_trucks_VIP.enqueue(v);
		}

		

	}

}
void Company::truck_maintaining_to_waiting(Time current_time)
{

	Truck* v=NULL;
	
	/////////////////////normal
	
	while (Maintaining_trucks_normal.peek(v) && v->get_maintaining_finish_time() <= current_time) {
		
		    Maintaining_trucks_normal.dequeue(v);
			waiting_trucks_normal.enqueue(v);
			
		
	}

	/////////////////////special
	
	while (Maintaining_trucks_special.peek(v) && v->get_maintaining_finish_time() <= current_time) {

		Maintaining_trucks_special.dequeue(v);
		waiting_trucks_special.enqueue(v);
		

	}
	/////////////////////VIP
	
	while (Maintaining_trucks_VIP.peek(v)
		
		
		
		
		
		&& v->get_maintaining_finish_time() <= current_time) {

		Maintaining_trucks_VIP.dequeue(v);
		waiting_trucks_VIP.enqueue(v);
		;

	}


}
void Company::cargos_moving_to_deliverd(Time current_time)
{
	Cargo* c = NULL;
	
	Truck* v = NULL;
	Queue< Truck*>tempv;
	//////////////////////////////////
	/////////////////////////////normal
	while (Moving_normal_trucks.Dequeue(v))
	{
		
		while (v->get_my_cargos().peek(c) && c->GET_CDT() <= current_time)
		{

			
			    v->get_my_cargos().Dequeue(c);
				v->unload_cargo();
				Delivered_cargos.enqueue(c);
				Delivered_normal_cargos.enqueue(c);
				
			
		}

		
		tempv.enqueue(v);
	}
	while (tempv.dequeue(v))Moving_normal_trucks.Enqueue(v, v->get_finish_priority());

	////////////////////////////////////
	/////////////////////////////special
	while (Moving_special_trucks.Dequeue(v))
	{
		
		while (v->get_my_cargos().peek(c) && c->GET_CDT() <= current_time)
		{

			
			v->get_my_cargos().Dequeue(c);
			Delivered_cargos.enqueue(c);
			Delivered_special_cargos.enqueue(c);
			

		}
			tempv.enqueue(v);
		
	}
	while (tempv.dequeue(v))Moving_special_trucks.Enqueue(v, v->get_finish_priority());


	////////////////////////////////
	/////////////////////////////VIP
	while (Moving_VIP_trucks.Dequeue(v))
	{
		
		while (v->get_my_cargos().peek(c) && c->GET_CDT() <= current_time)
		{

			
			v->get_my_cargos().Dequeue(c);
			Delivered_cargos.enqueue(c);
			Delivered_VIP_cargos.enqueue(c);
			

		}
			tempv.enqueue(v);
		
	}
	while (tempv.dequeue(v))Moving_VIP_trucks.Enqueue(v, v->get_finish_priority());
}
void Company::auto_promotion(Time current_time)
{
	Cargo* c = NULL;
	Queue< Cargo*>temp;
	while (waiting_cargos_Normal.peek(c))
	{
		if (c->getWT(current_time) >=(Autop * 24)) 
		{ 
			c->set_prometed(true);
			promote_request(c->getID(), 0);
		
		}
		else {
			waiting_cargos_Normal.dequeue(c);
			temp.enqueue(c);
		}
	}

	while (temp.dequeue(c))  waiting_cargos_Normal.enqueue(c);

}

void Company::truck_loading_moving(Time current_time)
{
	Truck* tn=NULL ;
	Truck* ts= NULL;
	Truck* tv= NULL;
	tn=Loading_normal_trucks;
	ts=Loading_special_trucks;
	tv=Loading_VIP_trucks;
	/////////////////////normal
	
	if (tn&&(tn->get_MT()<=current_time))
	{
		tn->get_max_cdt();
		//tn->set_move_time(current_time);
		Loading_normal_trucks=nullptr;
		Cargo* c1;
		Queue<Cargo*>temp1;
		int n1=0;
		int increase_unload=0;
		while (tn->get_my_cargos().Dequeue(c1)) 
		{
			tn->get_moving_finish_time();
			n1 += c1->get_loadtime();
			c1->set_unload_time(c1->get_unloadtime() + increase_unload);
			increase_unload = c1->get_unloadtime();
			c1->set_cdt(c1->GET_CDT());
			c1->set_my_truck_MT(tn->get_MT());
			temp1.enqueue(c1);
		}
		while (temp1.dequeue(c1))tn->get_my_cargos().Enqueue(c1, c1->get_delivery_priority());
		tn->set_unload_total_of_my_cargos(n1);
		tn->set_max_distance( tn->get_max_distance());
		Moving_normal_trucks.Enqueue(tn,tn->get_finish_priority());
		
		tn->Set_Active_Time((tn->get_max_distance() / tn->get_speed()) +2*tn->get_unload_time());
	//	if(!Loading_normal_trucks.peek(tn)) break;
	}
	/////////////////special
	if (ts && ts->get_MT() <= current_time)
	{
		ts->get_moving_finish_time();
		ts->get_max_cdt();
		//ts->set_move_time(current_time);
		Loading_special_trucks=nullptr;
		Cargo* c2;
		Queue<Cargo*>temp2;
		int n2 = 0;
		int increase_unload2 = 0;
		while (ts->get_my_cargos().Dequeue(c2))
		{
			n2 += c2->get_loadtime();
			c2->set_unload_time(c2->get_unloadtime() + increase_unload2);
			increase_unload2 = c2->get_unloadtime();
			c2->set_cdt(c2->GET_CDT());
			c2->set_my_truck_MT(ts->get_MT());
			temp2.enqueue(c2);
		}
		while (temp2.dequeue(c2))ts->get_my_cargos().Enqueue(c2, c2->get_delivery_priority());
		ts->set_unload_total_of_my_cargos(n2);
		ts->set_max_distance(ts->get_max_distance());
		ts->Set_Active_Time((ts->get_max_distance() / ts->get_speed()) + 2 *ts->get_unload_time());
		Moving_special_trucks.Enqueue(ts, ts->get_finish_priority());
		//if (!Loading_special_trucks.peek(ts)) break;
	}

	/////////////////VIP
	if (tv && tv->get_MT() <= current_time)
	{
		tv->get_moving_finish_time();
		tv->get_max_cdt();
		//tv->set_move_time(current_time);
		Loading_VIP_trucks=nullptr;
		Cargo* c3;
		Queue<Cargo*>temp3;
		int n3 = 0;
		int increase_unload3 = 0;
		while (tv->get_my_cargos().Dequeue(c3))
		{
			n3 += c3->get_loadtime();
			c3->set_unload_time(c3->get_unloadtime() + increase_unload3);
			increase_unload3 = c3->get_unloadtime();
			c3->set_cdt(c3->GET_CDT());
			c3->set_my_truck_MT(tv->get_MT());
			temp3.enqueue(c3);
		}
		while (temp3.dequeue(c3))tv->get_my_cargos().Enqueue(c3, c3->get_delivery_priority());
		tv->set_unload_total_of_my_cargos(n3);
		tv->set_max_distance(tv->get_max_distance());
		tv->Set_Active_Time((tv->get_max_distance() / tv->get_speed()) + 2  *tv->get_unload_time());
		Moving_VIP_trucks.Enqueue(tv, tv->get_finish_priority());
		//if (!Loading_VIP_trucks.peek(tv)) break;
	}

}



int Company::count_moving_cargos()
{
	int count = 0;
	Queue<Truck*>nt;
	Queue<Truck*>st;
	Queue<Truck*>vt;
	Queue<Cargo*>temp;
	Cargo* c = NULL;
	Truck* t = NULL;

	while (Moving_normal_trucks.Dequeue(t)) 
	{
		while (t->get_my_cargos().Dequeue(c))
		{
			count++;
			temp.enqueue(c);
		}
		while (temp.dequeue(c)) (t->get_my_cargos().Enqueue(c, c->get_delivery_priority()));
		nt.enqueue(t);
	}
	/// <summary>
	/// </summary>
	/// <returns></returns>
	while (Moving_special_trucks.Dequeue(t))
	{
		while (t->get_my_cargos().Dequeue(c))
		{
			count++;
			temp.enqueue(c);
		}
		while (temp.dequeue(c)) (t->get_my_cargos().Enqueue(c, c->get_delivery_priority()));
		st.enqueue(t);

		}


		while(Moving_VIP_trucks.Dequeue(t))
		{
			while (t->get_my_cargos().Dequeue(c))
			{
				count++;
				temp.enqueue(c);
			}
			while (temp.dequeue(c)) (t->get_my_cargos().Enqueue(c, c->get_delivery_priority()));
			vt.enqueue(t);

		}
		while (nt.dequeue(t)) Moving_normal_trucks.Enqueue(t, t->get_finish_priority());
		while (st.dequeue(t)) Moving_special_trucks.Enqueue(t, t->get_finish_priority());
		while (vt.dequeue(t)) Moving_VIP_trucks.Enqueue(t, t->get_finish_priority());
		return count;
}


//////////////////////////////////////////simulation

void Company::simulation()
{
	UI my_ui;
	ReadFile();
my_ui.printfirst();
	
	Time current_time(0, -1);
	Event* current_event;
	Queue<Event*>my_events;


	while (!finish_simulation())
	{
		current_time.increase();
		this->cargos_moving_to_deliverd(current_time);
		if (current_time.gethour() >=5 && current_time.gethour() <23)
		{ this->truck_loading_moving(current_time); }
		this->truck_moving_to_waiting(current_time);
		this->truck_maintaining_to_waiting(current_time);

		if (current_time.gethour() >= 5 && current_time.gethour() < 23)
		{
			this->auto_promotion(current_time);

			get_current_event(current_time, my_events);
			while (my_events.dequeue(current_event))
				current_event->excute();

            this->Load_VIP_cargos(current_time);
		
			this->Load_special_cargos(current_time);
				this->Load_normal_cargos(current_time);
        }
		my_ui.print(this, current_time);




	}
	finish_time = current_time;
	writeFile();
	cout << "output file is written";
}

