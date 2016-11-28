#ifndef _TIME_H_
#define _TIME_H_

#include <iostream>

class time{
private:
	int m_hour;
	int m_min;
public:
	time(){ m_hour = 0; m_min = 0; }
	time(int hour, int min){ m_hour = hour; m_min = min; }
	time(int min){ m_hour = min/60; m_min =min%60;}
	void show(char *);
	void set(int hour , int min){ m_hour = hour, m_min = min; }
	int getMins()const{ return 60 * m_hour + m_min; }
    int getHour() const{return m_hour;}
    int getMin()const{return m_min;}
	time modPlus(time &);
	time(const time &);
	friend bool operator <(const time &t1,const time &t2);
	bool operator >(time &t);
	time operator +(time &t);
	time operator -(time &t);
    std::string toString(){
        char temp[11];
        sprintf(temp, "%02d:%02d", m_hour, m_min);
        return std::string(temp);
    }
	friend std::ostream & operator << (std::ostream & os, const time & t);
};


#endif
