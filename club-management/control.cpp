#include "stdafx.h"
#include <stack>
#include <fstream>

control::control(){
	m_clubs.clear();
	m_players.clear();
	m_employees.clear();
	m_filterList.clear();
	m_employeeFilterList.clear();
	m_filterValid = false;
	m_employeeFilterValid = false;
}

void control::refresh(){
	std::ofstream fout("info_back.dat");
	for (unsigned int i = 0; i < m_clubs.size(); i++){
		fout << "c " << m_clubs[i]->getName() << " " << m_clubs[i]->getPass() << " " << m_clubs[i]->getFunds() << std::endl;
	}
	for (unsigned int i = 0; i < m_players.size(); i++)
		fout << "p " << m_players[i]->getName() << " " << m_players[i]->getAge() << " " <<
		m_players[i]->getGoals() << " " << m_players[i]->getSalary() << " " << 
		m_players[i]->getTransFee() << " " << m_players[i]->getYears() << " " << 
		m_players[i]->getAbility() << " " << 
		(m_players[i]->getClub() == NULL ? "-" : m_players[i]->getClub()->getName()) << std::endl;
	for (unsigned int i = 0; i < m_employees.size(); i++){
		fout << "e " << m_employees[i]->getName() << " " << m_employees[i]->getAge() << " " <<
			m_employees[i]->getSalary() << " " << m_employees[i]->getAbility() << " " <<
			(m_employees[i]->getClub() == NULL ? "-" : m_employees[i]->getClub()->getName()) << std::endl;
	}
	fout << "#";
	fout.close();
}

bool control::removePlayer(std::vector<player *> &tlist, player & t){
	for (unsigned int i = 0; i < tlist.size(); i++){
		if (tlist[i]->getName() == t.getName()){
			tlist.erase(tlist.begin() + i);
			return true;
		}
	}
	return false;
}

bool control::removeEmployee(std::vector<employee *> &tlist, employee & t){
	for (unsigned int i = 0; i < tlist.size(); i++){
		if (tlist[i]->getName() == t.getName()){
			tlist.erase(tlist.begin() + i);
			return true;
		}
	}
	return false;
}

bool control::removeClub(std::vector<club *> &tlist, club & t){
	for (unsigned int i = 0; i < tlist.size(); i++){
		if (tlist[i]->getName() == t.getName()){
			tlist.erase(tlist.begin() + i);
			return true;
		}
	}
	return false;
}

void control::insertClub(club & c){
	m_clubs.push_back(&c);
}
void control::insertPlayer(player &p){
	m_players.push_back(&p);
}
void control::insertEmployee(employee &e){
	m_employees.push_back(&e);
}

void control::fillFilterPlayer(const filter &f){
	m_filterList.clear();
	if (f.invalid){
		m_filterValid = false;
		return;
	}
	if (f.none){
		m_filterValid = true;
		return;
	}
	if (f.all){
		m_filterValid = true;
		m_filterList = m_players;
	}
	for (unsigned int i = 0; i < m_players.size(); i++){
	//	std::cout << m_players[i]->getName() << std::endl;
		bool _flag = true;
		if (_flag && !f.nameFilter.empty()){
			bool __flag = false;
			for (unsigned int j = 0; j < f.nameFilter.size(); j++){
				if (f.nameFilter[j] == m_players[i]->getName()){
					__flag = true;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.clubFilter.empty()){
			bool __flag = false;
			for (unsigned int j = 0; j < f.clubFilter.size(); j++){
				if (f.clubFilter[j] == m_players[i]->getClub()->getName()){
					__flag = true;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.abilityFilter.empty()){
			bool __flag = false;
			for (unsigned int j = 0; j < f.abilityFilter.size(); j++){
				if (f.abilityFilter[j] == m_players[i]->getAbility()){
					__flag = true;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.nameInclude.empty()){
			bool __flag = false;
			for (unsigned int j = 0; j < f.nameInclude.size(); j++){
				if (m_players[i]->getName().find(f.nameInclude[j]) <
					m_players[i]->getName().length()){
					__flag = true;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.clubInclude.empty()){
			bool __flag = false;
			for (unsigned int j = 0; j < f.clubInclude.size(); j++){
			//	std::cout << m_players[i]->getClub()->getName(); // .find(f.clubInclude[j]) << std::endl;
				if (m_players[i]->getClub()->getName().find(f.clubInclude[j]) <
					m_players[i]->getClub()->getName().length()){
					__flag = true;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.abilityInclude.empty()){
			bool __flag = false;
			for (unsigned int j = 0; j < f.abilityInclude.size(); j++){
				if (m_players[i]->getAbility().find(f.abilityInclude[j]) <
					m_players[i]->getAbility().length()){
					__flag = true;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.noNameFilter.empty()){
			bool __flag = true;
			for (unsigned int j = 0; j < f.noNameFilter.size(); j++){
				if (f.noNameFilter[j] == m_players[i]->getName()){
					__flag = false;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.noClubFilter.empty()){
			bool __flag = true;
			for (unsigned int j = 0; j < f.noClubFilter.size(); j++){
				if (f.noClubFilter[j] == m_players[i]->getClub()->getName()){
					__flag = false;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.noAbilityFilter.empty()){
			bool __flag = true;
			for (unsigned int j = 0; j < f.noAbilityFilter.size(); j++){
				if (f.noAbilityFilter[j] == m_players[i]->getAbility()){
					__flag = false;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.noNameInclude.empty()){
			bool __flag = true;
			for (unsigned int j = 0; j < f.noNameInclude.size(); j++){
				if (m_players[i]->getName().find(f.noNameInclude[j]) <
					m_players[i]->getName().length()){
					__flag = false;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.noClubInclude.empty()){
			bool __flag = true;
			for (unsigned int j = 0; j < f.noClubInclude.size(); j++){
				if (m_players[i]->getClub()->getName().find(f.noClubInclude[j]) <
					m_players[i]->getClub()->getName().length()){
					__flag = false;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.noAbilityInclude.empty()){
			bool __flag = true;
			for (unsigned int j = 0; j < f.noAbilityInclude.size(); j++){
				if (m_players[i]->getAbility().find(f.noAbilityInclude[j]) <
					m_players[i]->getAbility().length()){
					__flag = false;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.ageFilter.empty()){
			for (unsigned int j = 0; j < f.ageFilter.size(); j++){
				if ((f.ageFilter[j].lSideCheck && f.ageFilter[j].lSide >= (int)m_players[i]->getAge()) ||
					(f.ageFilter[j].rSideCheck && f.ageFilter[j].rSide <= (int)m_players[i]->getAge())){
					_flag = false;
					break;
				}
			}
		}
		if (_flag && !f.goalFilter.empty()){
			for (unsigned int j = 0; j < f.goalFilter.size(); j++){
				if ((f.goalFilter[j].lSideCheck && f.goalFilter[j].lSide >= (int)m_players[i]->getGoals()) ||
					(f.goalFilter[j].rSideCheck && f.goalFilter[j].rSide <= (int)m_players[i]->getGoals())){
					_flag = false;
					break;
				}
			}
		}
		if (_flag && !f.yearsFilter.empty()){
			for (unsigned int j = 0; j < f.yearsFilter.size(); j++){
				if ((f.yearsFilter[j].lSideCheck && f.yearsFilter[j].lSide >= (int)m_players[i]->getYears()) ||
					(f.yearsFilter[j].rSideCheck && f.yearsFilter[j].rSide <= (int)m_players[i]->getYears())){
					_flag = false;
					break;
				}
			}
		}
		if (_flag && !f.salaryFilter.empty()){
			for (unsigned int j = 0; j < f.salaryFilter.size(); j++){
				if ((f.salaryFilter[j].lSideCheck && f.salaryFilter[j].lSide >= (int)m_players[i]->getSalary()) ||
					(f.salaryFilter[j].rSideCheck && f.salaryFilter[j].rSide <= (int)m_players[i]->getSalary())){
					_flag = false;
					break;
				}
			}
		}
		if (_flag && !f.transFeeFilter.empty()){
			for (unsigned int j = 0; j < f.transFeeFilter.size(); j++){
				if ((f.transFeeFilter[j].lSideCheck && f.transFeeFilter[j].lSide >= (int)m_players[i]->getTransFee()) ||
					(f.transFeeFilter[j].rSideCheck && f.transFeeFilter[j].rSide <= (int)m_players[i]->getTransFee())){
					_flag = false;
					break;
				}
			}
		}
		if (_flag){
			m_filterList.push_back(m_players[i]);
		}
	}
	m_filterValid = true;
}

void control::fillFilterEmployee(const filter &f){
	m_employeeFilterList.clear();
	if (f.invalid){
		m_employeeFilterValid = false;
		return;
	}
	if (f.none){
		m_employeeFilterValid = true;
		return;
	}
	if (f.all){
		m_employeeFilterValid = true;
		m_employeeFilterList = m_employees;
	}
	for (unsigned int i = 0; i < m_employees.size(); i++){
		//	std::cout << m_employees[i]->getName() << std::endl;
		bool _flag = true;
		if (_flag && !f.nameFilter.empty()){
			bool __flag = false;
			for (unsigned int j = 0; j < f.nameFilter.size(); j++){
				if (f.nameFilter[j] == m_employees[i]->getName()){
					__flag = true;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.clubFilter.empty()){
			bool __flag = false;
			for (unsigned int j = 0; j < f.clubFilter.size(); j++){
				if (f.clubFilter[j] == m_employees[i]->getClub()->getName()){
					__flag = true;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.abilityFilter.empty()){
			bool __flag = false;
			for (unsigned int j = 0; j < f.abilityFilter.size(); j++){
				if (f.abilityFilter[j] == m_employees[i]->getAbility()){
					__flag = true;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.nameInclude.empty()){
			bool __flag = false;
			for (unsigned int j = 0; j < f.nameInclude.size(); j++){
				if (m_employees[i]->getName().find(f.nameInclude[j]) <
					m_employees[i]->getName().length()){
					__flag = true;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.clubInclude.empty()){
			bool __flag = false;
			for (unsigned int j = 0; j < f.clubInclude.size(); j++){
				//	std::cout << m_employees[i]->getClub()->getName(); // .find(f.clubInclude[j]) << std::endl;
				if (m_employees[i]->getClub()->getName().find(f.clubInclude[j]) <
					m_employees[i]->getClub()->getName().length()){
					__flag = true;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.abilityInclude.empty()){
			bool __flag = false;
			for (unsigned int j = 0; j < f.abilityInclude.size(); j++){
				if (m_employees[i]->getAbility().find(f.abilityInclude[j]) <
					m_employees[i]->getAbility().length()){
					__flag = true;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.noNameFilter.empty()){
			bool __flag = true;
			for (unsigned int j = 0; j < f.noNameFilter.size(); j++){
				if (f.noNameFilter[j] == m_employees[i]->getName()){
					__flag = false;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.noClubFilter.empty()){
			bool __flag = true;
			for (unsigned int j = 0; j < f.noClubFilter.size(); j++){
				if (f.noClubFilter[j] == m_employees[i]->getClub()->getName()){
					__flag = false;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.noAbilityFilter.empty()){
			bool __flag = true;
			for (unsigned int j = 0; j < f.noAbilityFilter.size(); j++){
				if (f.noAbilityFilter[j] == m_employees[i]->getAbility()){
					__flag = false;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.noNameInclude.empty()){
			bool __flag = true;
			for (unsigned int j = 0; j < f.noNameInclude.size(); j++){
				if (m_employees[i]->getName().find(f.noNameInclude[j]) <
					m_employees[i]->getName().length()){
					__flag = false;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.noClubInclude.empty()){
			bool __flag = true;
			for (unsigned int j = 0; j < f.noClubInclude.size(); j++){
				if (m_employees[i]->getClub()->getName().find(f.noClubInclude[j]) <
					m_employees[i]->getClub()->getName().length()){
					__flag = false;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.noAbilityInclude.empty()){
			bool __flag = true;
			for (unsigned int j = 0; j < f.noAbilityInclude.size(); j++){
				if (m_employees[i]->getAbility().find(f.noAbilityInclude[j]) <
					m_employees[i]->getAbility().length()){
					__flag = false;
					break;
				}
			}
			if (!__flag){
				_flag = false;
				continue;
			}
		}
		if (_flag && !f.ageFilter.empty()){
			for (unsigned int j = 0; j < f.ageFilter.size(); j++){
				if ((f.ageFilter[j].lSideCheck && f.ageFilter[j].lSide >= (int)m_employees[i]->getAge()) ||
					(f.ageFilter[j].rSideCheck && f.ageFilter[j].rSide <= (int)m_employees[i]->getAge())){
					_flag = false;
					break;
				}
			}
		}
		if (_flag && !f.salaryFilter.empty()){
			for (unsigned int j = 0; j < f.salaryFilter.size(); j++){
				if ((f.salaryFilter[j].lSideCheck && f.salaryFilter[j].lSide >= (int)m_employees[i]->getSalary()) ||
					(f.salaryFilter[j].rSideCheck && f.salaryFilter[j].rSide <= (int)m_employees[i]->getSalary())){
					_flag = false;
					break;
				}
			}
		}
		if (_flag){
			m_employeeFilterList.push_back(m_employees[i]);
		}
	}
	m_employeeFilterValid = true;
}

filter control::drawFilterFromStr(std::string& filterStr){
	struct catoge{
		std::string cur;
		unsigned short cate;
		catoge(std::string s, unsigned short c){
			cur = s;
			cate = c;
		}
	};
	std::stack<filter> runs;
	std::vector<catoge> _back_stack;
	std::stack<catoge> _temp;
	filter ans, a, b, p;
	p.invalid = true;
	bool _valid_flag = true;
	unsigned int i;

	m_filterValid = false;
	m_filterList.clear();
	while (!_temp.empty())
		_temp.pop();
	while (!runs.empty())
		runs.pop();
	_back_stack.clear();

	// TRANSFER REVERSE POLAN
	i = 0;
	while (i < filterStr.size()){
		unsigned int index;
		switch (filterStr[i])
		{
		case '@':
			index = i + 1;
			_valid_flag = true;
			while (index < filterStr.size() && filterStr[index] != ')' &&
				filterStr[index] != '&' && filterStr[index] != '|'){
				if (!('a' <= filterStr[index] && filterStr[index] <= 'z' ||
					'A' <= filterStr[index] && filterStr[index] <= 'Z' ||
					'0' <= filterStr[index] && filterStr[index] <= '9' ||
					filterStr[index] == '_' || filterStr[index] == '>' ||
					filterStr[index] == '<' || filterStr[index] == '=' ||
					filterStr[index] == '.' || filterStr[index] == ' ' ||
					filterStr[index] == '\t' || filterStr[index] == '~'))
					_valid_flag = false;
				index++;
			}
			if (!_valid_flag){
				return p;
			}
			_back_stack.push_back(catoge(filterStr.substr(i, index - i), 0));
			i = index;
			break;
		case '(':
			_temp.push(catoge("(", 1));
			i++;
			break;
		case ')':
			if (_temp.empty())
				return p;
			while (!_temp.empty() && _temp.top().cate != 1){
				_back_stack.push_back(_temp.top());
				_temp.pop();
			}
			if (_temp.empty())
				return p;
			_temp.pop();
			i++;
			break;
		case '!':
			_temp.push(catoge("!", 2));;
			i++;
			break;
		case '&':
			if (i + 2 < filterStr.size() && filterStr[i + 1] == '&' &&
				filterStr[i + 2] != '&' && filterStr[i + 2] != '|'){
				i = i + 2;
				while (!_temp.empty() && _temp.top().cate != 1 && _temp.top().cate != 4){
					_back_stack.push_back(_temp.top());
					_temp.pop();
				}
				_temp.push(catoge("&&", 3));
			}
			else{
				return p;
			}
			break;
		case '|':
			if (i + 2 < filterStr.size() && filterStr[i + 1] == '|' &&
				filterStr[i + 2] != '|' && filterStr[i + 2] != '&'){
				i = i + 2;
				while (!_temp.empty() && _temp.top().cate != 1){
					_back_stack.push_back(_temp.top());
					_temp.pop();
				}
				_temp.push(catoge("||", 4));
			}
			else{
				return p;
			}
			break;
		default:
			i++;
			break;
		};
	}
	while (!_temp.empty()){
		_back_stack.push_back(_temp.top());
		_temp.pop();
	}
	/*for (i = 0; i < _back_stack.size(); i++){
	std::cout << _back_stack[i].cur << " " << _back_stack[i].cate << std::endl;
	}
	std::cout << std::endl;*/

	for (i = 0; i < _back_stack.size(); i++){
		switch (_back_stack[i].cate){
		case 0:
			runs.push(filter(_back_stack[i].cur));
			break;
		case 2:
			if (runs.size() < 1){
				return p;
			}
			else{
				a = runs.top();
				runs.pop();
				a.cancelReverse();
				runs.push(a);
			}
			break;
		case 3:
			if (runs.size() < 2){
				return p;
			}
			else{
				a = runs.top();
				runs.pop();
				b = runs.top();
				runs.pop();
				a.andMerge(b);
				runs.push(a);
			}
			break;
		case 4:
			if (runs.size() < 2){
				return p;
			}
			else{
				a = runs.top();
				runs.pop();
				b = runs.top();
				runs.pop();
				a.orMerge(b);
				runs.push(a);
			}
			break;
		default:
			break;
		}
	}
	if (runs.size() == 1)
		return runs.top();
	else{
		return p;
	}
}

void control::filterPlayer(std::string filterStr){
	filter p = drawFilterFromStr(filterStr);
	fillFilterPlayer(p);
}

void control::filterEmployee(std::string filterStr){
	filter p = drawFilterFromStr(filterStr);
	fillFilterEmployee(p);
}

club * control::searchClubByName(std::string &name){
	for (unsigned int i = 0; i < m_clubs.size(); i++){
		if (m_clubs[i]->getName() == name)
			return m_clubs[i];
	}
	return NULL;
}

player * control::searchPlayerByName(std::string &name){
	for (unsigned int i = 0; i < m_players.size(); i++){
		if (m_players[i]->getName() == name)
			return m_players[i];
	}
	return NULL;
}

employee * control::searchEmployeeByName(std::string &name){
	for (unsigned int i = 0; i < m_employees.size(); i++){
		if (m_employees[i]->getName() == name)
			return m_employees[i];
	}
	return NULL;
}
