#ifndef USER_H_
#define USER_H_

#include "stdafx.h"
#include<iostream>
#include <string>

class userP{
private:
    static int id;
    std::string m_name;
    bool admin;
    bool m_status;
    std::string m_pass;
	int curCity;
    int m_id;
    int lineC;
public:
    int line[31];
    userP(std::string,std::string, bool, city&);
    static int getCount(){return id;}
    int getID(){return m_id;}
    int getLineC(){return lineC;}
    void setLineC(int t){lineC = t;}
    int getCurCitt(){return curCity;}
    void setCurCitt(int t) { curCity= t;}
    void setName(std::string name){m_name = name;}
    std::string getName(){return m_name;}
    std::string getPass(){return m_pass;}
    bool isAdmin(){return admin;}
    bool isOnbord(){return m_status;}
    void setOnbord(bool t){m_status = t;}
    void onTrip();

};

userP * getUser(std::string);

#endif 
