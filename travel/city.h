#ifndef _CITY_H_
#define _CITY_H_

#include <iostream>
#include <string>

class city{
private:
	static int id;
	std::string m_name;
    int m_x,m_y;
    bool flag;
	int m_id;
public:
	city(){ m_name = "unknown"; m_id = -1; }
	city(std::string);
	city(const city &);
	std::string name(){ return m_name; }
    int getID() { return m_id; }
	static int getCount() { return id; }
    int getX(){return m_x;}
    bool getFlag(){return flag;}
    void setFlag(bool fl){flag = fl;}
    int getY(){return m_y;}
    void setXY(int x,int y){
        m_x =x;
        m_y = y;
    }
	friend class vehicle;
	friend std::ostream & operator<< (std::ostream & os, const city &c);
};

#endif
