#ifndef __CLUB_H_
#define __CLUB_H_

#include "stdafx.h"

class club{
private:
	static unsigned int id;
	unsigned int m_id;
	unsigned int m_funds;
	std::string m_name;
	std::string m_pass;
	std::vector<player *> m_players;
	std::vector<employee *> m_employees;
public:
	static unsigned int getCount(){ return id; }
	club(std::string name, std::string pass, unsigned int funds = 0);
	club(const club &);
	~club();
	club & operator=(const club &);
	unsigned int getID() { return m_id; }
	int getPlayerCount() { return m_players.size(); }
	std::string getName() { return m_name; }
	std::string getPass() { return m_pass; }
	std::string toStr();
	bool checkPass(std::string p) { return m_pass == p; }
	unsigned int getFunds() { return m_funds; }
	int searchPlayer(const player &p)const;
	int searchEmployee(const employee &e)const;
	void insertPlayer(player &p){
		p.setClub(this);
		m_players.push_back(&p);
	}
	void insertEmployee(employee &e){
		e.setClub(this);
		m_employees.push_back(&e);
	}
	void setName(std::string name){ m_name = name; }
	void setFunds(int fund){ m_funds = fund; }
	void addFunds(int fund){ m_funds += fund; }
	void coutDetails();
	std::vector<player *> & getPlayers(){ return m_players; }
	std::vector<employee *> & getEmployees(){ return m_employees; }
	friend std::ostream &operator <<(std::ostream &, const club &c);
	bool removePlayer(player &p);
	bool removeEmployee(employee &e);
	bool transPlayer(club &c, player &p);
};

#endif