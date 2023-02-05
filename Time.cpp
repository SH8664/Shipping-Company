#include "Time.h"

Time::Time(int d, int h)
{
	day = d;
	hour = h;
}

// Amember Function for reading Time form File 
void Time::read_time(ifstream& cin)
{
	int h, d;

	cin >> d;
	cin.ignore(1);
	cin >> h;
	day = d;
	hour = h;


}

//int Time::operator-(Time time)
//{
//	int h =abs( hour - time.hour);
//	int d = abs(day - time . day);
//	return h + d * 24;
//}

bool Time::operator<=(Time t2)
{
	if (day < t2.getday()) return true;
	else if (hour <= t2.gethour()&&day==t2.getday()) return true;
	return false;
}

bool Time::operator>=(Time t2)
{
	if (day > t2.getday()) return true;
	else if (hour >= t2.gethour() && day == t2.getday()) return true;
	return false;
}

void Time::sethour(int h)
{
	hour = h;
}

void Time::setday(int d)
{
	day = d;
}



int Time::gethour()
{
	return hour;
}

int Time::getday()
{
	return day;
}


Time::Time() {}

void Time::increase()
{
	hour += 1;
	if (hour >= 24)
	{
		hour -= 24;
		day++;
	}

}

bool Time::operator==(Time t2)
{
	if (getday() == t2.getday() && gethour() == t2.gethour()) return true;
	else return false;
}


void Time::write_time(ofstream& cout)
{
	cout << this->day << ':' << this->hour;
}

Time Time:: operator +(Time t2)
{
	Time sum_t;
	if ((this->hour + t2.hour) > 24)
	{
		sum_t.sethour((this->hour + t2.hour) - 24);
		sum_t.setday(this->day + t2.day + 1);
	}
	else
	{
		sum_t.sethour(this->hour + t2.hour);
		sum_t.setday(this->day + t2.day);
	}
	return sum_t;
}