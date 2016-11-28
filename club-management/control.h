#ifndef __CONTROL_H_
#define __CONTROL_H_

#include "stdafx.h"

class control{
private:
	std::vector<club *> m_clubs;
	std::vector<player *> m_players;
	std::vector<employee *> m_employees;
	std::vector<player *> m_filterList;
	std::vector<employee *> m_employeeFilterList;
	bool m_filterValid, m_employeeFilterValid;
public:
	control();
	void insertClub(club &);
	void insertPlayer(player &);
	void insertEmployee(employee &);
	void fillFilterPlayer(const filter &);
	void fillFilterEmployee(const filter &);
	void filterPlayer(std::string); 
	void filterEmployee(std::string);
	void refresh();
	club * searchClubByName(std::string&);
	player * searchPlayerByName(std::string&);
	employee * searchEmployeeByName(std::string&);
	bool getFilterValid(){ return m_filterValid; }
	bool getEmployeeFilterValid() { return m_employeeFilterValid; }
	bool removeClub(std::vector<club *> &, club &);
	bool removePlayer(std::vector<player *> &, player &);
	bool removeEmployee(std::vector<employee *> &, employee &);
	filter drawFilterFromStr(std::string &);
	std::vector<player *> & getFilterList() { return m_filterList; }
	std::vector<employee *> & getEmployeeFilterList() { return m_employeeFilterList; }
	std::vector<player *> & getPlayers(){ return m_players; }
	std::vector<club *> & getClubs() { return m_clubs; }
	std::vector<employee *> & getEmployees(){ return m_employees; }
};

#endif