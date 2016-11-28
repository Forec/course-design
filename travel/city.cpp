#include "stdafx.h"

int city::id = 0;
city * allCities[31];

city::city(std::string name){
	m_name = name; 
    m_id = id++;
    m_x = m_y = 0;
    flag = false;
	allCities[m_id] = this;
}

std::ostream & operator << (std::ostream &os,const city & c){
	os << c.m_name;
	return os;
}

city::city(const city& c){
	m_id = c.m_id;
	m_name = c.m_name;
}

