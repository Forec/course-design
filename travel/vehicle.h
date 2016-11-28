#ifndef _VEHICLE_H_
#define _VEHICLE_H_

#include "stdafx.h"
class vehicle{
private:
	static int id;
	int m_classify;
	int m_id;
	std::string m_name;
	unsigned int m_cost;
	time m_time;
	time m_last;
	city m_start, m_dest;
public:
	vehicle();
	vehicle(std::string &,int classify, int cost, time s, time last, city& start, city& dest);
	int getID(){ return m_id; }
	time getStartTime() { return m_time; }
	time getLastTime() { return m_last; }
	time getEndTime() {return m_time.modPlus(m_last);}
	time getWait_and_LastTime(time &t) { return (m_time-t)+m_last;}
	city getStartCity() { return m_start; }
	city getDestCity() { return m_dest; }
    std::string getName() { return m_name;}
	int getCost(){ return m_cost; }
	static int getCount() { return id; }
	friend std::ostream & operator << (std::ostream & os, const vehicle & v);
};

#endif
