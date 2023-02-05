#ifndef __company
#define __company

#include"Queue.h"
#include"PriorityQueue.h"
#include"Linked_List.h"
#include"Time.h"
class Cargo ;
class PrepareEvent;
class Truck;
class PromoteEvent;
class CancelEvent;
class Event;
class UI;
using namespace std;

class Company
{
	Queue<Event*>events;


	Linked_List<Cargo*>waiting_cargos_Normal;
	Queue<Cargo*>waiting_cargos_Special;
	PriorityQueue<Cargo*>waiting_cargos_VIP;

	Queue<Truck*>waiting_trucks_normal;
	Queue<Truck*>waiting_trucks_special;
	Queue<Truck*>waiting_trucks_VIP;


	Queue<Cargo*>Delivered_normal_cargos;   //for print
	Queue<Cargo*>Delivered_special_cargos;  //for print
	Queue<Cargo*>Delivered_VIP_cargos;      //for print

	Queue<Cargo*>Delivered_cargos; ///for output file

	Queue<Truck*>Maintaining_trucks_normal;
	Queue<Truck*>Maintaining_trucks_special;
	Queue<Truck*>Maintaining_trucks_VIP;

	////////////Queue<Cargo*>Loading_cargos;

	
	PriorityQueue<Truck*>Moving_normal_trucks;//trucks carrying normal cargos 
	PriorityQueue<Truck*>Moving_special_trucks;//trucks carrying special cargos 
	PriorityQueue<Truck*>Moving_VIP_trucks;//trucks carrying VIP cargos 

	Truck*Loading_normal_trucks; //trucks carrying normal cargos
	Truck* Loading_special_trucks;//trucks carrying special cargos 
	Truck* Loading_VIP_trucks;//trucks carrying VIP cargos 

	
	int Maxw;
	int Autop;


	int Total_N_cargos;
	int Total_V_cargos;
	int Total_S_cargos;

	int count_Normal_Truck;
	int count_Special_Truck;
	int count_VIP_Truck;
	Time finish_time;
public:
	Company();
	void intialization(int nn, int ns, int nv, float sn, float ss, float sv, int cn, int cs, int cv, int t, int tm,int at);
	void ReadFile();
	void prepare_event(Cargo*cargo);

	bool  cancel_request(int id);
	////Get pointer of cargo by id 
	Cargo* Get_Cargo_Pointer(int ID);

	bool  promote_request(int id,int money);
	
	void MoveWaiting_deliverd();
	Time GetCargosAvgWait();
	
	 
	bool finish_simulation();
	void get_current_event(Time t, Queue<Event*>& temp);
	Linked_List<Cargo*>& get_waiting_normal();
	Queue<Cargo*>& get_waiting_special();
	PriorityQueue<Cargo*>& get_waiting_VIP();

	Queue<Cargo*>& get_delivered_normal();
	Queue<Cargo*>& get_delivered_special();
	Queue<Cargo*>& get_delivered_VIP();

	Queue<Truck*>& get_waiting_normal_truck();
	Queue<Truck*>& get_waiting_special_truck();
	Queue<Truck*>& get_waiting_VIP_truck();

	PriorityQueue<Truck*>& get_moving_normal_truck();

	PriorityQueue<Truck*>& get_moving_special_truck();

	PriorityQueue<Truck*>& get_moving_VIP_truck();

	Truck*& get_loading_normal_truck();

	Truck*& get_loading_special_truck();

	Truck*& get_loading_VIP_truck();

	Queue<Truck*>& get_maintaining_normal_truck();

	Queue<Truck*>& get_maintaining_special_truck();

	Queue<Truck*>& get_maintaining_VIP_truck();
	void Load_normal_cargos(Time current_time);
	void Load_special_cargos(Time current_time);
	void Load_VIP_cargos(Time current_time);
	int num_promoted_cargos();//Normal only

	double AutoPromotedCargos();///////outputFile

	int Total_Active_Time();

	double Avg_Active_Time();  ///////outputFile

	int Get_Sim_Time();

	//Getter for all Cargos And Trucks count

	int Total_Normal_Cargos();

	int Total_VIP_Cargos();

	int Total_Special_Cargos();

	int Total_Cargos();

	int Total_Normal_Trucks();

	int Total_VIP_Trucks();

	int Total_Special_Trucks();

	int Total_Trucks();

	//Utilization Parameters
	//Total cargo delivered by this truck
	int Get_tDC(Truck* T);
	double Utilization_Truck(Truck* T);
	double Avg_Utilization();
	void writeFile();


	void truck_moving_to_waiting(Time current_time);
	void truck_maintaining_to_waiting(Time current_time);
	void cargos_moving_to_deliverd(Time current_time);
	void auto_promotion(Time current_time);
	void truck_loading_moving(Time current_time );
	void simulation();
	int count_moving_cargos();
};
#endif