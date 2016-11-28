#include "stdafx.h"

bool base::operator==(const base &b)const{
	return id == b.id;
}

bool player::operator==(const player &p)const{
	return base::operator==(base(p));
}

bool employee::operator==(const employee &e)const{
	return base::operator==(base(e));
}

player::~player() {
	if (m_club != NULL)
		m_club->removePlayer(*this);
	CT->removePlayer(CT->getPlayers(), *this);
}

employee::~employee(){
	if (m_club != NULL)
		m_club->removeEmployee(*this);
	CT->removeEmployee(CT->getEmployees(), *this);
}

base::base(std::string name,
	unsigned int age,
	std::string ability,
	unsigned int salary) :
	m_name(name),
	m_age(age),
	m_ability(ability),
	m_salary(salary){
	m_id = id++;
}

base::base(const base &b){
	m_name = b.m_name;
	m_age = b.m_age;
	m_ability = b.m_ability;
	m_id = b.m_id;
	m_salary = b.m_salary;
}

base& base::operator=(const base &b){
	if (this == &b)
		return *this;
	m_name = b.m_name;
	m_age = b.m_age;
	m_ability = b.m_ability;
	m_id = b.m_id;
	m_salary = b.m_salary;
	return *this;
}

void base::coutDetails(){
	std::cout << "NAME: " << m_name << "\tAGE: " << m_age << "\t\tABILITY: " 
		<< m_ability << "\tSALARY: " << m_salary;
}

std::ostream &operator<<(std::ostream &os, const base &b){
	os << b.m_name;
	return os;
}

player::player(std::string name,
	unsigned int age,
	std::string ability,
	unsigned int salary,
	unsigned int transFee,
	unsigned int goals,
	unsigned int years,
	club * clubp) :base(name, age, ability, salary){
	m_transFee = transFee;
	m_goals = goals;
	m_years = years;
	m_club = clubp;
	if (clubp != NULL){
		clubp->insertPlayer(*this);
	}
	CT->insertPlayer(*this);
}

player::player(const player &p) :base(p){
	m_transFee = p.m_transFee;
	m_goals = p.m_goals;
	m_years = p.m_years;
	m_club = p.m_club;
}

player & player::operator=(const player &p){
	if (this == &p)
		return *this;
	m_ability = p.m_ability; m_name = p.m_name;
	m_id = p.m_id; m_salary = p.m_salary;
	m_age = p.m_age; m_years = p.m_years;
	m_club = p.m_club; m_transFee = p.m_transFee;
	m_goals = p.m_goals; 
	return *this;
}

void player::setClub(club *c){
	m_club = c;
}

void player::coutDetails(){
	std::cout << "CATEGORY: PLAYER\n";
	base::coutDetails();
	std::cout << std::endl << "GOALS: " << m_goals << "\tCLUB: ";
	if (m_club == NULL){
		std::cout << "None";
	}
	else{
		std::cout << m_club->getName();
	}
	std::cout << "\tYEARS: " << m_years << "\tTRANSFEE: " << m_transFee << std::endl;
}

std::string player::toStr(){
	std::string toReturn;
	toReturn.clear();
	char tempage[21], tempsala[21];
	_itoa_s(m_age, tempage, 10); _itoa_s(m_salary, tempsala, 10);
	toReturn += "CATEGORY: PLAYER\n";
	toReturn += ("NAME: " + m_name + "\tAGE: " + tempage + "\t\tABILITY: " +
		m_ability + "\tSALARY: " + tempsala);
	_itoa_s(m_goals, tempage, 10);
	toReturn += ("\nGOALS: " + std::string(tempage) + "\tCLUB: ");
	if (m_club == NULL){
		toReturn+= "None";
	}
	else{
		toReturn += m_club->getName();
	}
	_itoa_s(m_years, tempsala, 10); _itoa_s(m_transFee, tempage, 10);
	toReturn+= ("\tYEARS: " + std::string(tempsala) + "\t\tTRANSFEE: " + tempage + "\n");
	return toReturn;
}

std::ostream & operator<<(std::ostream & os, const player &p){
	os << "player " << p.m_name;
	return os;
}

employee::employee(std::string name,
	unsigned int age,
	std::string ability,
	unsigned int salary,
	club * clubp) :
	base(name, age, ability, salary){
	m_club = clubp;
	if (clubp != NULL){
		clubp->insertEmployee(*this);
	}
	CT->insertEmployee(*this);
}

employee & employee::operator=(const employee & e){
	if (this == &e)
		return *this;
	m_name = e.m_name; m_age = e.m_age;
	m_ability = e.m_ability; m_club = e.m_club;
	m_id = e.m_id; m_salary = e.m_salary;
	return *this;
}

std::string employee::toStr(){
	std::string toReturn;
	toReturn.clear();
	toReturn += "CATEGORY: EMPLOYEE\t\t BELONG TO: ";
	if (m_club == NULL){
		toReturn+= "NONE\n";
	}
	else{
		toReturn+=( m_club->getName() +"\n");
	}
	char tempage[21], tempsala[21];
	_itoa_s(m_age, tempage, 10); _itoa_s(m_salary, tempsala, 10);
	toReturn += "CATEGORY: PLAYER\n";
	toReturn += ("NAME: " + m_name + "\tAGE: " + tempage + "\t\tABILITY: " +
		m_ability + "\tSALARY: " + tempsala + "\n");
	return toReturn;
}

void employee::coutDetails(){
	std::cout << "CATEGORY: EMPLOYEE\t\t BELONG TO: ";
	if (m_club == NULL){
		std::cout << "NONE\n";
	}
	else{
		std::cout << m_club->getName() << std::endl;
	}
	base::coutDetails();
	std::cout << std::endl;
}

std::ostream & operator<<(std::ostream & os, employee &e){
	os << "employee " << e.m_name;
	return os;
}