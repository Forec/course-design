#ifndef __HUMAN_H_
#define __HUMAN_H_

#include <iostream>

class club;

class base{
private:
	static unsigned int id;
protected:
	std::string m_name;
	unsigned int m_id;
	unsigned short m_age;
	std::string m_ability;
	unsigned int m_salary;
public:
	static unsigned int getCount(){ return id; }
	base(std::string name = "unknown",
		unsigned int age = 0,
		std::string ability = "Nothing",
		unsigned int salary = 0);
	base(const base &b);
	base & operator=(const base &);
	std::string getName(){ return m_name; }
	unsigned short getAge(){ return m_age; }
	unsigned int getSalary() { return m_salary; }
	unsigned int getID() { return m_id; }
	std::string getAbility(){ return m_ability; }
	void setName(std::string & name){ m_name = name; }
	void setSalary(unsigned int salary) { m_salary = salary; }
	void setAbility(std::string ability){ m_ability = ability; }
	void setAge(unsigned short age){ m_age = age; }
	bool operator == (const base &b)const;
	void coutDetails();
	friend std::ostream& operator<<(std::ostream &os, const base &b);
};

class player : public base{
private:
	unsigned int m_transFee;
	unsigned int m_goals;
	unsigned short m_years;
	club * m_club;
public:
	player(std::string name = "unknown",
		unsigned int age = 0,
		std::string ability = "Nothing",
		unsigned int salary = 0,
		unsigned int transFee = 0,
		unsigned int goals = 0,
		unsigned int years = 0,
		club * clubp = NULL);
	player(const player &p);
	~player();
	player & operator=(const player &);
	unsigned int getTransFee(){ return m_transFee; }
	unsigned int getGoals(){ return m_goals; }
	unsigned short getYears(){ return m_years; }
	club* getClub(){ return m_club; }
	void setClub(club * c);
	void setTransFee(unsigned int transFee){ m_transFee = transFee; }
	void setYears(unsigned int years){ m_years = years; }
	void setGoals(unsigned int goals){ m_goals = goals; }
	void coutDetails();
	bool operator==(const player &p) const;
	std::string toStr();
	friend std::ostream & operator<<(std::ostream & os, const player &p);
};

class employee :public base{
private:
	club * m_club;
public:
	employee(std::string name = "unknown",
		unsigned int age = 0,
		std::string ability = "Nothing",
		unsigned int salary = 0,
		club * clubp = NULL);
	employee & operator=(const employee &);
	~employee();
	void setClub(club * clubp){
		m_club = clubp;
	}
	void coutDetails();
	bool operator==(const employee &e) const;
	club* getClub(){ return m_club; }
	std::string toStr();
	friend std::ostream & operator<<(std::ostream & os, employee &e);
};

#endif