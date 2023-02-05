#ifndef __time
#define __time
#include<iostream>
#include<fstream>
using namespace std;
class Time
{
	int hour;
	int day;
public:
	Time(int d, int h);
	Time();
	void sethour(int h);
	void setday(int d);
	int gethour();
	int getday();
	void increase();
	bool operator ==( Time t2);
	bool operator <=(Time t2);
	bool operator >=(Time t2);
	void read_time(ifstream& cin);
//	int operator-(Time time);
	void write_time(ofstream& cout);
	Time operator +(Time t2);
	
};



#endif