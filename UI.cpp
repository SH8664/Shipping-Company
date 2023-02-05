
#include "UI.h"
#include"Company.h"
#include"Truck.h"
#include"Cargo.h"
#include<iostream>
#include <chrono>
#include <thread>
using namespace std;
ostream& operator<<(ostream& out, Truck &t)
{
	out << t.getID();
	return out;
}
ostream& operator<<(ostream& out, Cargo& C) {
	out << C.getID();
	return out;
}
ostream& operator<<(ostream& out, Time T) {
	out << T.getday() << ":" << T.gethour();
	return out;
}
void UI::print_silent_mode()
{
	cout << "Silent Mode" << endl << "Simulation Starts..." << endl << "Simulation ends, Output file created" << endl;


}

void UI::printfirst() {
	cout << "1. Interactive Mode" << endl;
	cout << "2. Step-By-Step Mode" << endl;
	cout << "3.Silent Mode" << endl;
	cout << "choose Mode Number(1,2,3)" << endl;
	int n;
	cin >> n;
	while (n < 0 || n>3)
	{
		cout << "invaild Mode_Number choose from(1,2,3) " << endl;
		cin >> n;
	}
	mode_number = n;
	if (mode_number == 3) print_silent_mode();
}



void UI::print_interactive_mode(Company* c, Time& t)
{
	cin.get();
	print_moods(c, t);
}
void UI::print_stepbystep_mode(Company* c, Time& t)
{

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	print_moods(c, t);

}

void UI::print(Company* c, Time& t)
{
	if (mode_number == 1) print_interactive_mode(c, t);
	if (mode_number == 2)  print_stepbystep_mode(c, t);
}
void UI::print_moods(Company *c,Time&t){
	cout << "Current Time (Day:Hour): ";
	cout << t << endl;
	cout << " --------------------------------" << endl;
	Cargo* ca;
	Truck* tr;
	Linked_List <Cargo*>temp1;
	Queue<Cargo*>temp2;
	PriorityQueue<Cargo*>temp3;
	////////////////////////////
	/////////printing Waiting Cargos
	int n = c->get_waiting_normal().get_count() + c->get_waiting_special().get_count() + c->get_waiting_VIP().get_count();
	cout << n << "  Waiting Cargos: [ ";
	while (c->get_waiting_normal().dequeue(ca)) { cout << *ca;if (!c->get_waiting_normal().is_empty()) cout << ",";temp1.enqueue(ca); }
	while (temp1.dequeue(ca))  c->get_waiting_normal().enqueue(ca);
	cout << " ] ( ";
	while (c->get_waiting_special().dequeue(ca)) { cout << *ca;if (!c->get_waiting_special().isEmpty()) cout << ","; temp2.enqueue(ca); }
	while (temp2.dequeue(ca)) c->get_waiting_special().enqueue(ca);
	cout << ") {";


	while (c->get_waiting_VIP().Dequeue(ca)) { cout << *ca;if (!c->get_waiting_VIP().IsEmpty()) cout << ","; temp3.Enqueue(ca, ca->Get_Priority()); }
	while (temp3.Dequeue(ca)) c->get_waiting_VIP().Enqueue(ca, ca->Get_Priority());
	cout << "}" << endl;

	cout << " --------------------------------" << endl;
	/////////////////////////
	///////////////Printing loading trucks

	Queue <Truck*>temp__1;
	Queue<Truck*>temp__2;
	Queue<Truck*>temp__3;
	Queue<Cargo*>temp__4;

	n = 0;
	if (c->get_loading_normal_truck())n++;
	if (c->get_loading_special_truck())n++;
	if (c->get_loading_VIP_truck())n++;

	cout << n << "  Loading Trucks: ";

	if (c->get_loading_normal_truck() != nullptr)
	{
		cout << *c->get_loading_normal_truck() << "[";
		while (c->get_loading_normal_truck()->get_my_cargos().Dequeue(ca))
		{
			cout << *ca;
			if (!(c->get_loading_normal_truck()->get_my_cargos().IsEmpty()))cout << ",";
			temp__4.enqueue(ca);
		}
		cout << "] ";
		//temp__1.enqueue(tr);
		while (temp__4.dequeue(ca))   c->get_loading_normal_truck()->get_my_cargos().Enqueue(ca, ca->get_delivery_priority());
	}
	//while (temp__1.dequeue(tr))  c->get_loading_normal_truck().enqueue(tr);

	if (c->get_loading_special_truck() != nullptr)
	{
		cout << *c->get_loading_special_truck() << "(";
		while (c->get_loading_special_truck()->get_my_cargos().Dequeue(ca))
		{
			cout << *ca;
			if (!(c->get_loading_special_truck()->get_my_cargos().IsEmpty()))cout << ",";
			temp__4.enqueue(ca);
		}
		cout << ")";
		//temp__2.enqueue(tr);
		while (temp__4.dequeue(ca))   c->get_loading_special_truck()->get_my_cargos().Enqueue(ca, ca->get_delivery_priority());
	}
	//while (temp__2.dequeue(tr))  c->get_loading_special_truck().enqueue(tr);


	if (c->get_loading_VIP_truck() != nullptr)
	{
		cout << *c->get_loading_VIP_truck() << "{";
		while (c->get_loading_VIP_truck()->get_my_cargos().Dequeue(ca))
		{
			cout << *ca;
			if (!(c->get_loading_VIP_truck()->get_my_cargos().IsEmpty()))cout << ",";
			temp__4.enqueue(ca);
		}
		cout << "} ";
		//temp__3.enqueue(tr);
		while (temp__4.dequeue(ca))   c->get_loading_VIP_truck()->get_my_cargos().Enqueue(ca, ca->get_delivery_priority());
	}
	//while (temp__3.dequeue(tr))  c->get_loading_VIP_truck().enqueue(tr);
	cout << endl;

	cout << " --------------------------------" << endl;
	/////////// printing Empty Trucks
	Queue <Truck*>temp_1;
	Queue<Truck*>temp_2;
	Queue<Truck*>temp_3;
	n = c->get_waiting_normal_truck().get_count() + c->get_waiting_special_truck().get_count() + c->get_waiting_VIP_truck().get_count();
	cout << n << "  Empty Trucks: [ ";
	while (c->get_waiting_normal_truck().dequeue(tr)) { cout << *tr;if (!c->get_waiting_normal_truck().isEmpty()) cout << ",";temp_1.enqueue(tr); }
	while (temp_1.dequeue(tr))  c->get_waiting_normal_truck().enqueue(tr);
	cout << " ] ( ";

	while (c->get_waiting_special_truck().dequeue(tr)) { cout << *tr;if (!c->get_waiting_special_truck().isEmpty()) cout << ","; temp_2.enqueue(tr); }
	while (temp_2.dequeue(tr)) c->get_waiting_special_truck().enqueue(tr);
	cout << ") {";


	while (c->get_waiting_VIP_truck().dequeue(tr)) { cout << *tr;if (!c->get_waiting_VIP_truck().isEmpty()) cout << ","; temp_3.enqueue(tr); }
	while (temp_3.dequeue(tr)) c->get_waiting_VIP_truck().enqueue(tr);
	cout << "}" << endl;

	cout << " --------------------------------" << endl;
	//////////////printing moving cargos


	n = c->count_moving_cargos();
	cout << n << "  Moving Cargos: ";

	while (c->get_moving_normal_truck().Dequeue(tr))
	{
		cout << *tr << "[";
		while (tr->get_my_cargos().Dequeue(ca))
		{
			cout << *ca;
			if (!(tr->get_my_cargos().IsEmpty()))cout << ",";
			temp__4.enqueue(ca);
		}
		cout << "] ";
		temp__1.enqueue(tr);
		while (temp__4.dequeue(ca))   tr->get_my_cargos().Enqueue(ca, ca->get_delivery_priority());
	}
	while (temp__1.dequeue(tr))  c->get_moving_normal_truck().Enqueue(tr, tr->get_finish_priority());

	while (c->get_moving_special_truck().Dequeue(tr))
	{
		cout << *tr << "(";
		while (tr->get_my_cargos().Dequeue(ca))
		{
			cout << *ca;
			if (!(tr->get_my_cargos().IsEmpty()))cout << ",";
			temp__4.enqueue(ca);
		}
		cout << ") ";
		temp__2.enqueue(tr);
		while (temp__4.dequeue(ca))   tr->get_my_cargos().Enqueue(ca, ca->get_delivery_priority());
	}
	while (temp__2.dequeue(tr))  c->get_moving_special_truck().Enqueue(tr, tr->get_finish_priority());


	while (c->get_moving_VIP_truck().Dequeue(tr))
	{
		cout << *tr << "{";
		while (tr->get_my_cargos().Dequeue(ca))
		{
			cout << *ca;
			if (!(tr->get_my_cargos().IsEmpty()))cout << ",";
			temp__4.enqueue(ca);
		}
		cout << "}";
		temp__3.enqueue(tr);
		while (temp__4.dequeue(ca))   tr->get_my_cargos().Enqueue(ca, ca->get_delivery_priority());
	}
	while (temp__3.dequeue(tr))  c->get_moving_VIP_truck().Enqueue(tr, tr->get_finish_priority());
	cout << endl;
	cout << " --------------------------------" << endl;
	///////// printing In-Checkup Trucks
	n = c->get_maintaining_normal_truck().get_count() + c->get_maintaining_special_truck().get_count() + c->get_maintaining_VIP_truck().get_count();
	cout << n << "  In-Checkup Trucks: [ ";
	while (c->get_maintaining_normal_truck().dequeue(tr)) { cout << *tr; if (!c->get_maintaining_normal_truck().isEmpty()) cout << ","; temp_1.enqueue(tr); }
	while (temp_1.dequeue(tr))  c->get_maintaining_normal_truck().enqueue(tr);
	cout << " ] ( ";

	while (c->get_maintaining_special_truck().dequeue(tr)) { cout << *tr; if (!c->get_maintaining_special_truck().isEmpty()) cout << ","; temp_2.enqueue(tr); }
	while (temp_2.dequeue(tr)) c->get_maintaining_special_truck().enqueue(tr);
	cout << ") {";


	while (c->get_maintaining_VIP_truck().dequeue(tr)) { cout << *tr; if (!c->get_maintaining_VIP_truck().isEmpty()) cout << ","; temp_3.enqueue(tr); }
	while (temp_3.dequeue(tr)) c->get_maintaining_VIP_truck().enqueue(tr);
	cout << "}" << endl;



	cout << " --------------------------------" << endl;
	////////// printing delivered cargos
	Queue <Cargo*>temp1_;
	Queue<Cargo*>temp2_;
	Queue<Cargo*>temp3_;
	n = c->get_delivered_normal().get_count() + c->get_delivered_VIP().get_count() + c->get_delivered_special().get_count();
	cout << n << "  delivered Cargos : [";
	while (c->get_delivered_normal().dequeue(ca)) { cout << *ca;if (!c->get_delivered_normal().isEmpty()) cout << ",";temp1_.enqueue(ca); }
	while (temp1_.dequeue(ca))  c->get_delivered_normal().enqueue(ca);
	cout << " ] ( ";
	while (c->get_delivered_special().dequeue(ca)) { cout << *ca;if (!c->get_delivered_special().isEmpty()) cout << ","; temp2_.enqueue(ca); }
	while (temp2_.dequeue(ca)) c->get_delivered_special().enqueue(ca);
	cout << ") {";


	while (c->get_delivered_VIP().dequeue(ca)) { cout << *ca;if (!c->get_delivered_VIP().isEmpty()) cout << ","; temp3_.enqueue(ca); }
	while (temp3_.dequeue(ca)) c->get_delivered_VIP().enqueue(ca);
	cout << "}" << endl;

	cout << "############################" << endl;
}