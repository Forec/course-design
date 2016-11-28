#include "stdafx.h"

int vehicle::id = 0;

vehicle::vehicle(std::string & name,int classify, int cost, time s, time last, city &start, city &dest){
	m_classify = classify;
	m_name = name;
	m_cost = cost;
	m_time = s;
	m_last = last;
	m_start = start;
	m_dest = dest;
	m_id = id++;
	allVehicles[m_id] = this;
}

std::ostream & operator<<(std::ostream &os, const vehicle & v){
	os << _NAMES[v.m_classify] << " ";
	os << v.m_name << ": " << v.m_start << "->" << v.m_dest << "   with Cost :" << v.m_cost << " and Time: " << v.m_last.getMins() << std::endl;
	return os;
}

