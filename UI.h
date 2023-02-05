#ifndef __ui
#define __ui
#include<iostream>
using namespace std;

class Company;
class Time;
class UI

{
	int mode_number;
	void print_silent_mode();
	
public:
	void printfirst();


	void print_interactive_mode(Company *c,Time&t);
	void print_stepbystep_mode(Company* c, Time& t);

	void print(Company* c, Time& t);
	void print_moods(Company* c, Time& t);

};
#endif