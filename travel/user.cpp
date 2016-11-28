#include "stdafx.h"
#include <iostream>
using namespace std;

userP * allUsers[201];

int userP::id = 0;

userP::userP(string name, string pass, bool is, city &c){
    m_name = name;
    m_pass =pass;
    admin = is;
    m_status = false;
    allUsers[id] = this;
    m_id = id++;
    curCity = c.getID();
    lineC = 0;
}

userP *getUser(string name){
    for (int i = 0; i < userP::getCount(); i++){
        if (allUsers[i]->getName() == name){
            return allUsers[i];
        }
    }
    return NULL;
}

