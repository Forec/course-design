#include "stdafx.h"

club::club(std::string name, std::string pass,unsigned int funds) :
	m_name(name),
	m_pass(pass),
	m_funds(funds) {
	m_players.clear();
	m_employees.clear();
	m_id = id++;
	CT->insertClub(*this);
}

club::club(const club &c){
	m_name = c.m_name;
	m_pass = c.m_pass;
	m_funds = c.m_funds;
	m_id = c.m_id;
	m_players.clear();
	m_employees.clear();
	m_players = c.m_players;
	m_employees = c.m_employees;
}

club::~club(){
	for (unsigned int i = 0; i < m_players.size(); i++)
		m_players[i]->setClub(NULL);
	for (unsigned int i = 0; i < m_employees.size(); i++)
		m_employees[i]->setClub(NULL);
	CT->removeClub(CT->getClubs(), *this);
}

club & club::operator=(const club& c){
	if (this == &c)
		return *this;
	m_name = c.m_name;
	m_funds = c.m_funds;
	m_id = c.m_id;
	m_players.clear();
	m_employees.clear();
	m_players = c.m_players;
	m_employees = c.m_employees;
	return *this;
}

bool club::removePlayer(player &p){
	int index = searchPlayer(p);
	if (index != -1){
		m_players.erase(m_players.begin() + index);
		p.setClub(NULL);
		return true;
	}
	return false;
}

bool club::removeEmployee(employee &e){
	int index = searchEmployee(e);
	if (index != -1){
		m_employees.erase(m_employees.begin() + index);
		e.setClub(NULL);
		return true;
	}
	return false;
}

int club::searchPlayer(const player &p)const{
	for (unsigned int i = 0 ; i < m_players.size(); i++){
		if (*(m_players[i]) == p){
			return i;
		}
	}
	return -1;
}

int club::searchEmployee(const employee &e)const{
	for (unsigned int i = 0; i < m_employees.size(); i++){
		if ((*m_employees[i]) == e){
			return i;
		}
	}
	return -1;
}

bool club::transPlayer(club &c, player &p){
	int index = c.searchPlayer(p);
	if (index == -1 || m_funds < p.getTransFee())
		return false;
	m_funds -= p.getTransFee();
	c.addFunds(p.getTransFee());
	c.removePlayer(p);
	insertPlayer(p);
	return true;
}

std::ostream & operator << (std::ostream & os, const club &c){
	os << "club " << c.m_name;
	return os;
}

std::string club::toStr(){
	std::string toReturn;
	toReturn.clear();
	char temp[21]; _itoa_s(m_funds, temp, 10);
	toReturn += ("CLUB: " + m_name + "   FUND: " + temp +"\nPLAYERS LIST\n");
	if (m_players.size() == 0)
		toReturn+= "EMPTY\n";
	else{
		for (unsigned int i = 0; i < m_players.size(); i++){
			toReturn+= (m_players[i]->toStr() +" ");
			if ((i + 1) % 5 == 0)
				toReturn += "\n";
		}
	}
	if (m_players.size() != 0 && (m_players.size() + 1) % 5 != 0)
		toReturn += "\n";
	toReturn += "EMPLOYEES LIST\n";
	if (m_employees.size() == 0)
		toReturn += "EMPTY\n";
	else{
		for (unsigned int i = 0; i < m_employees.size(); i++){
			toReturn+= (m_employees[i]->toStr() + " ");
			if ((i + 1) % 5 == 0)
				toReturn += "\n";
		}
		toReturn += "\n";
	}
	return toReturn;
}

void club::coutDetails(){
	std::cout << "CLUB: " << m_name << "   FUND: " << m_funds << std::endl;
	std::cout << "PLAYERS LIST\n";
	if (m_players.size() == 0)
		std::cout << "EMPTY\n";
	else{
		for (unsigned int i = 0; i < m_players.size(); i++){
			std::cout << *(m_players[i]) << " ";
			if ((i + 1) % 5 == 0)
				std::cout << std::endl;
		}
	}
	if (m_players.size() != 0 && (m_players.size() + 1) % 5 != 0)
		std::cout << std::endl;
	std::cout << "EMPLOYEES LIST\n";
	if (m_employees.size() == 0)
		std::cout << "EMPTY\n";
	else{
		for (unsigned int i = 0; i < m_employees.size(); i++){
			std::cout << *(m_employees[i]) << " ";
			if ((i + 1) % 5 == 0)
				std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}