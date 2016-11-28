#include "stdafx.h"

void time::show(char *t){
	sprintf(t, "%2d:%2d", m_hour, m_min);
}

bool operator<(const time &t1,const time & t2){
	return t1.getMins() < t2.getMins();
}

bool time::operator>(time & t){
	return this->getMins() > t.getMins();
}

time time::operator+(time &t){
	return time(m_hour+t.m_hour+(m_min+t.m_min)/60, (m_min + t.m_min)%60);
}

time time::modPlus(time &t){
	return time((m_hour+t.m_hour+(m_min+t.m_min)/60)%24, (m_min + t.m_min)%60);
}

std::ostream & operator<<(std::ostream &os, const time & t){
	os << t.m_hour << ":" <<t.m_min;
	return os;
}

time time::operator -(time &t){
	if( *this > t){
		return time(this->getMins() - t.getMins());
	} else{
		return time(1440 - t.getMins() + this->getMins());
	}
}

time::time(const time & t1){
	m_hour = t1.m_hour;
	m_min = t1.m_min;
}
