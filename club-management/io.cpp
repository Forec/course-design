#include "stdafx.h"
#include <fstream>
#include <WINSOCK2.H>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

control *CT;

void initServer(){
	CT = new control;
	std::ifstream fin("info_back.dat");
	std::string name, ability, clubd, pass;
	unsigned int salary, age, goals, years, transFee;
	std::string flag;
	do{
		salary = 0;
		age = 0;
		goals = 0;
		years = 0;
		transFee = 0;
		fin >> flag;
		if (flag == "#")
			break;
		else if (flag == "p"){
			fin >> name >> age >> goals >> salary >> transFee >> years >> ability >> clubd;
			if (clubd == "-")
				new player(name, age, ability, salary, transFee, goals, years, NULL);
			else
				new player(name, age, ability, salary, transFee, goals, years, CT->searchClubByName(clubd));
		}
		else if (flag == "e"){
			fin >> name >> age >> salary >> ability >> clubd;
			if (clubd == "-")
				new employee(name, age, ability, salary, NULL);
			else
				new employee(name, age, ability, salary, CT->searchClubByName(clubd));
		}
		else if (flag == "c"){
			fin >> name >> pass >> salary;
			new club(name, pass, salary);
		}
		else {
			break;
		}
	} while (true);
	fin.close();
}

std::string toUpper(std::string& s){
	for (unsigned int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]);
	return s;
}

int str2int(const std::string& s){
	int ans = 0;
	unsigned int i, j;
	for (i = 0; i < s.size(); i++){
		if (s[i] == '.')
			break;
		if (s[i] <'0' || s[i]>'9')
			return -1;
	}
	for (j = 0; j < i; j++){
		ans *= 10;
		ans += (s[j] - '0');
	}
	return ans;
}

bool isAlphaNum(std::string s){
	for (unsigned int i = 0; i < s.size(); i++){
		if (!(('0' <= s[i] && s[i] <= '9') ||
			  ('a' <= s[i] && s[i] <= 'z') ||
			  ('A' <= s[i] && s[i] <= 'Z')))
			return false;
	}
	return true;
}

void mainWinForClient(){
	std::cout << "+=============================================================================+\n";
	std::cout << "|                                                                             |\n";
	std::cout << "|                        PLAYER MANAGE SYSTEM                                 |\n";
	std::cout << "|                                       designed by forec, version 3.0        |\n";
	std::cout << "|   Guide:                                                                    |\n";
	std::cout << "|     AFFORD                                                                  |\n";
	std::cout << "|       [FUND]                                                                |\n";
	std::cout << "|             recharge $FUND into your club's account.                        |\n";
	std::cout << "|     REMOVE                                                                  |\n";
	std::cout << "|       -p [PLAYER]                                                           |\n";
	std::cout << "|             remove an existed player PLAYER from your club.                 |\n";
	std::cout << "|       -e [EMPLOYEE]                                                         |\n";
	std::cout << "|             remove an existed employee EMPLOYEE from your club.             |\n";
	std::cout << "|     TRANSFER                                                                |\n";
	std::cout << "|       [PLAYER]                                                              |\n";
	std::cout << "|             buy an existed player PLAYER from other club or server.         |\n";
	std::cout << "|     DESTORY                                                                 |\n";
	std::cout << "|             delete your club from server.                                   |\n";
	std::cout << "|     SEARCH                                                                  |\n";
	std::cout << "|       -p [REGULAR]                                                          |\n";
	std::cout << "|             search players by using regular expression REGULAR.             |\n";
	std::cout << "|       -e [REGULAR]                                                          |\n";
	std::cout << "|             search employees by using regular expression REGULAR.           |\n";
	std::cout << "|       -c [CLUB]                                                             |\n";
	std::cout << "|             search the club named CLUB.                                     |\n";
	std::cout << "|     ALTER                                                                   |\n";
	std::cout << "|       -n [CLUB]   change your club's named into CLUB.                       |\n";
	std::cout << "|       -p [PASS]   change your club's password into PASS.                    |\n";
	std::cout << "|     LISTALL                                                                 |\n";
	std::cout << "|       -p    list all the players existed.                                   |\n";
	std::cout << "|       -e    list all the employees existed.                                 |\n";
	std::cout << "|       -c    list all the clubs existed.                                     |\n";
	std::cout << "|       (-d)  with details.                                                   |\n";
	std::cout << "|     LOGOUT  logout and exit.                                                |\n";
	std::cout << "|     --VERSION  display current version number.                              |\n";
	std::cout << "|     --CLR      clear the screen.                                            |\n";
	std::cout << "|     --HELP     show the help information.                                   |\n";
	std::cout << "|                                                                             |\n";
	std::cout << "+=============================================================================+\n";
}

void mainWinForServer(){
	std::cout << "+======================================================================================+\n";
	std::cout << "|                                                                                      |\n";
	std::cout << "|                                 PLAYER MANAGE SERVER                                 |\n";
	std::cout << "|                                               designed by forec, version 3.0         |\n";
	std::cout << "|   Guide:                                                                             |\n";
	std::cout << "|     CREATE                                                                           |\n";
	std::cout << "|       -p [NAME] [SALARY=0] [TRANSFEE=0] [YEAR=0] [AGE=0] [GOAL=0] [ABILITY=Nothing]  |\n"; 
	std::cout << "|             create a player called NAME with salay SALARY, ability ABILITY, age AGE, |\n";
	std::cout << "|            GOAL goals, needs TRANSFEE fees and has been serverd for YEAR years. His  |\n";
	std::cout << "|            club will be set to NULL automaticly.                                     |\n";
	std::cout << "|       -e [NAME] [SALARY=0] [AGE=0] [ABILITY=Nothing]                                 |\n";
	std::cout << "|             create an employee called NAME with salay SALARY, age AGE and ability    |\n";
	std::cout << "|       -c [NAME] [FUND=0]                                                             |\n";
	std::cout << "|             create a club called NAME with fundation FUND.                           |\n";
	std::cout << "|     INSERT                                                                           |\n";
	std::cout << "|       -p [CLUB] [PLAYER] (-v)                                                        |\n";
	std::cout << "|             insert an existed player whose name is PLAYER with no club into an       |\n"; 
	std::cout << "|            existed club whose name is CLUB. -v means remove.                         |\n";
	std::cout << "|       -e [CLUB] [EMPLOYEE] (-v)                                                      |\n";
	std::cout << "|             insert an existed employee whose name is EMPLOYEE into an existed        |\n";
	std::cout << "|            club whose name is CLUB. -v means remove.                                 |\n";
	std::cout << "|     TRANSFER                                                                         |\n";
	std::cout << "|       [CLUB_A] [PLAYER]                                                              |\n";
	std::cout << "|             an existed club whose name is CLUB_A buys an existed player whose name   |\n";
	std::cout << "|            is PLAYER from an existed club or server.                                 |\n";
	std::cout << "|     DELETE                                                                           |\n";
	std::cout << "|       -p(r) [PLAYER]                                                                 |\n";
	std::cout << "|             delete an existed player whose name is PLAYER, and the club he belonged  |\n";
	std::cout << "|            to will delete him automaticly. Using -r to use regular expression.       |\n";
	std::cout << "|       -e(r) [EMPLOYEE]                                                               |\n";
	std::cout << "|             delete an existed employee whose name is EMPLOYEE, and the club he       |\n";
	std::cout << "|            belonged to will delete him automaticly. Using -r to use regular          |\n"; 
	std::cout << "|            expression.                                                               |\n";
	std::cout << "|       -c [CLUB]                                                                      |\n";
	std::cout << "|             delete an existed club whose name is CLUB, and all the players/employees |\n";
	std::cout << "|            belonged to this club will be set to null.                                |\n";
	std::cout << "|     SEARCH                                                                           |\n";
	std::cout << "|       -p [REGULAR]                                                                   |\n";
	std::cout << "|             search players by using regular expression REGULAR.                      |\n";
	std::cout << "|       -e [REGULAR]                                                                   |\n";
	std::cout << "|             search employees by using regular expression REGULAR.                    |\n";
	std::cout << "|       -c [CLUB]                                                                      |\n";
	std::cout << "|             search the club named CLUB.                                              |\n";
	std::cout << "|     ALTER                                                                            |\n";
	std::cout << "|       -p [PLAYER] [NAME=-u] [SALARY=-u] [TRANSFEE=-u] [YEAR=-u] [AGE=-u] [GOAL=-u]   |\n";
	std::cout << "|          [ABILITY = -u]                                                              |\n";
	std::cout << "|             alter an existed player named PLAYER into new profile. -u means that     |\n";
	std::cout << "|            character will not be changed.                                            |\n";
	std::cout << "|       -e [EMPLOYEE] [NAME=-u] [SALARY=-u] [AGE=-u] [ABILITY=-u]                      |\n";
	std::cout << "|             alter an existed employee named EMPLOYEE into new profile.               |\n";
	std::cout << "|       -c [CLUB] [NAME=-u] [FUND=-u]                                                  |\n";
	std::cout << "|             alter an existed club named CLUB into new profile.                       |\n";
	std::cout << "|     LISTALL                                                                          |\n";
	std::cout << "|       -p                                                                             |\n";
	std::cout << "|             list all the players existed.                                            |\n";
	std::cout << "|       -e                                                                             |\n";
	std::cout << "|             list all the employees existed.                                          |\n";
	std::cout << "|       -c                                                                             |\n";
	std::cout << "|             list all the clubs existed.                                              |\n";
	std::cout << "|       (-d)                                                                           |\n";
	std::cout << "|             with details.                                                            |\n";
	std::cout << "|     --VERSION                                                                        |\n";
	std::cout << "|             display current version number.                                          |\n";
	std::cout << "|     --CLR                                                                            |\n";
	std::cout << "|             clear the screen.                                                        |\n";
	std::cout << "|     --HELP                                                                           |\n";
	std::cout << "|             show the help information.                                               |\n";
	std::cout << "|                                                                                      |\n";
	std::cout << "+======================================================================================+\n";
}

void clear(std::string &or, std::vector<std::string> &ors){
	or = "";
	ors.clear();
	std::cout << ">>> ";
}

void IO(){
	mainWinForServer();
	std::string order;
	std::vector<std::string> orders;
	while (true){
		clear(order, orders);
		getline(std::cin, order);
		int count = 0;
		int pre = 0;
		for (unsigned int i = 0; i < order.length(); i++){
			if (order[i] == ' ' || order[i] == '\t' || i == order.length() - 1){
				if (i == pre && i != order.length() - 1){
					pre = i;
					continue;
				}
				if (i == order.length() - 1 && order[i] != ' ' && order[i] != '\t')
					i++;
				orders.push_back(order.substr(pre, i - pre));
				pre = i + 1;
			}
		}
		if (orders.size() == 0){
			std::cout << "Meanless Input...\n";
		}
		else if (toUpper(orders[0]) == "CREATE"){
			if (orders.size() <= 2){
				std::cout << "Lack parameter...\n";
				continue;
			}
			std::string name, pass;
			int money = 0;
			bool _flag = true;
			if (orders.size() > 2 && orders[1] == "-c"){
				if (orders.size() > 5){
					std::cout << "Too many arguments...\n";
					continue;
				}
				if (isAlphaNum(orders[2]) && isAlphaNum(orders[3])){
					name = orders[2];
					pass = orders[3];
				}
				else _flag = false;
				if (orders.size() == 5){
					if (str2int(orders[3]) >= 0)
						money = str2int(orders[3]);
					else _flag = false;
				}
				if (orders.size() > 5){
					 _flag = false;
				}
				if (_flag){
					if (CT->searchClubByName(name) == NULL){
						new club(name, pass, money);
						CT->refresh();
					}
					else{
						std::cout << "club named " << name << " already exists...\n";
					}
				}
				else{
					std::cout << "Invalid Input...\n";
				}
			}
			else if (orders.size() > 2 && orders[1] == "-p"){
				if (orders.size() > 9){
					std::cout << "Too many arguments...\n";
					continue;
				}
				int transFee = 0, year = 0, goal = 0, age = 0;
				std::string ability = "Nothing";
				bool __flag = true;
				if (isAlphaNum(orders[2]))
					name = orders[2];
				else __flag = false;
				if (orders.size() > 3 ){
					if (str2int(orders[3]) >= 0)
						money = str2int(orders[3]);
					else __flag = false;
				}
				if (orders.size() > 4 ){
					if (str2int(orders[4]) >= 0)
						transFee = str2int(orders[4]);
					else __flag = false;
				}
				if (orders.size() > 5){
					if (str2int(orders[5]) >= 0)
						year = str2int(orders[5]);
					else __flag = false;
				}
				if (orders.size() > 6){
					if (str2int(orders[6]) >= 0)
						age = str2int(orders[6]);
					else __flag = false;
				}
				if (orders.size() > 7){
					if (str2int(orders[7]) >= 0)
						goal = str2int(orders[7]);
					else __flag = false;
				}
				if (orders.size() > 8) {
					if(isAlphaNum(orders[8]))
						ability = orders[8];
					else __flag = false;
				}
				if (__flag){
					if (CT->searchPlayerByName(name) == NULL){
						new player(name, age, ability, money, transFee, goal, year, NULL);
						CT->refresh();
					}
					else{
						std::cout << "player named " << name << " already exists...\n";
					}
				}
				else{
					std::cout << "Invalid Input...\n";
				}
			}
			else if (orders.size() > 2 && orders[1] == "-e"){
				if (orders.size() > 6){
					std::cout << "Too many arguments...\n";
					continue;
				}
				int age = 0;
				std::string ability = "Nothing";
				bool __flag = true;
				if (isAlphaNum(orders[2]))
					name = orders[2];
				else __flag = false;
				if (orders.size() > 3){
					if (str2int(orders[3]) >= 0)
						money = str2int(orders[3]);
					else __flag = false;
				}
				if (orders.size() > 4){
					if (str2int(orders[4]) >= 0)
						age = str2int(orders[4]);
					else __flag = false;
				}
				if (orders.size() > 5) {
					if (isAlphaNum(orders[5]))
						ability = orders[5];
					else __flag = false;
				}
				if (__flag){
					if (CT->searchEmployeeByName(name) == NULL){
						new employee(name, age, ability, money, NULL);
						CT->refresh();
					}
					else{
						std::cout << "employee named " << name << " already exists...\n";
					}
				}

				else{
					std::cout << "Invalid Input...\n";
				}
			}
			else{
				std::cout << "Invalid Input...\n";
			}
		}
		else if (toUpper(orders[0]) == "LISTALL"){
			if (orders.size() < 2){
				std::cout << "Lack Parameters...\n";
			}
			else {
				int state = 0;
				unsigned int i = 7;
				bool p = false, d = false, c = false, e = false, invalid = false;
				while (i < order.length()){
					switch (state){
					case 0:			// space
						if (order[i] == '-'){
							state = 1;
						}
						if (order[i] != ' ' && order[i] != '\t' && order[i] != '-')
							invalid = true;
						break;
					case 1:			// -
						if (order[i] != 'p' && order[i] != 'c' && order[i] != 'e' &&
							order[i] != 'd' && order[i] != ' ' && order[i] != '\t')
							invalid = true;
						if (order[i] == 'p')
							p = true;
						if (order[i] == 'c')
							c = true;
						if (order[i] == 'e')
							e = true;
						if (order[i] == 'd')
							d = true;
						state = 2;
						if (order[i] == ' ' || order[i] == '\t'){
							invalid = true;
							state = 0;
						}
						break;
					case 2:
						if (order[i] != 'p' && order[i] != 'c' && order[i] != 'e' &&
							order[i] != 'd' && order[i] != ' ' && order[i] != '\t')
							invalid = true;
						if (order[i] == 'p')
							p = true;
						if (order[i] == 'c')
							c = true;
						if (order[i] == 'e')
							e = true;
						if (order[i] == 'd')
							d = true; 
						if (order[i] == ' ' || order[i] == '\t'){
							state = 0;
						}
						break;
					}
					i++;
				}
				if (invalid){
					std::cout << "Invalid Input...\n";
					continue;
				}
				if (p){
					std::cout << "All Players:\n";
					shows(CT->getPlayers(), d);
				}
				if (e){
					std::cout << "All Employees:\n";
					shows(CT->getEmployees(), d);
				}
				if (c){
					std::cout << "All Clubs:\n";
					shows(CT->getClubs(), d);
				}
			}
		}
		else if (toUpper(orders[0]) == "INSERT"){
			if (orders.size() < 4){
				std::cout << "Lack parameters...\n";
				continue;
			}
			if (orders.size() > 5){
				std::cout << "Too many arguments...\n";
				continue;
			}
			if (isAlphaNum(orders[2]) && isAlphaNum(orders[3]) &&
				(orders[1] == "-p" || orders[1] == "-e")){
				bool reverse = false;
				if (orders.size() == 5){
					if (orders[4] != "-v"){
						std::cout << "Invalid parameter format...\n";
						continue;
					}
					reverse = true;
				}
				club * c = CT->searchClubByName(orders[2]);
				if (c == NULL){
					std::cout << "club named " << orders[2] << " does not exist...\n";
				}
				else if (orders[1] == "-p"){
					player *p = CT->searchPlayerByName(orders[3]);
					if (p != NULL ){
						if (reverse == false && p->getClub() == NULL){
							c->insertPlayer(*p);
							CT->refresh();
						}
						else if (reverse == true && p->getClub()->getName() == orders[2]){
							c->removePlayer(*p);
							CT->refresh();
						}
					}
					else {
						if (p == NULL){
							std::cout << "player named " << orders[3] << " does not exist...\n";
						}
						else {
							if (reverse == false && p->getClub() != NULL){
								std::cout << "unsuccessful, player " << orders[3] << " was belonging to club " <<
									p->getClub()->getName() << "...\n";
							}
							else if (reverse == true && p->getClub()->getName()!= orders[2]){
								std::cout << "unsuccessful, player " << orders[3] << " didn't belong to club " <<
									p->getClub()->getName() << "...\n";
							}
						}
					}
				}
				else if (orders[1] == "-e"){
					employee *e = CT->searchEmployeeByName(orders[3]);
					if (e != NULL){
						if (reverse == false && e->getClub() == NULL){
							c->insertEmployee(*e);
							CT->refresh();
						}
						else if (reverse == true && e->getClub()->getName() == orders[2]){
							c->removeEmployee(*e);
							CT->refresh();
						}
					}
					else {
						if (e == NULL){
							std::cout << "employee named " << orders[3] << " does not exist...\n";
						}
						else{
							if (reverse == false && e->getClub() != NULL){
								std::cout << "unsuccessful, employee " << orders[3] << " was belonging to club " <<
								e->getClub()->getName() << "...\n";
							}
							else if (reverse == true && e->getClub()->getName() != orders[2]){
								std::cout << "unsuccessful, employee " << orders[3] << " didn't belong to club " <<
								e->getClub()->getName() << "...\n";
							}
						}
					}
				}
			}
			else{
				std::cout << "Invalid Input...\n";
			}
		}
		else if (toUpper(orders[0]) == "SEARCH"){
			if (orders.size() >= 3){
				unsigned int index;
				for (index = orders[0].size(); order[index] == ' ' || order[index] == '\t'; index++);
				index = index + orders[1].length();
				std::string parameter = order.substr(index, order.length() - index);
		//		std::cout << "reger::" << parameter << std::endl;
				if (orders[1] == "-p"){
					CT->filterPlayer(parameter);
					if (CT->getFilterValid()){
						if (CT->getFilterList().size() > 0)
							showDetails(CT->getFilterList());
						else
							std::cout << "There's no player matches this condition...\n";
					}
					else{
						std::cout << "Invalid Regular Expression...\n";
					}
				}
				else if (orders[1] == "-c"){
					club * c = CT->searchClubByName(orders[2]);
					if (c == NULL){
						std::cout << "There's No club named " << orders[2] << "...\n";
					}
					else{
						c->coutDetails();
					}
				}
				else if (orders[1] == "-e"){
					CT->filterEmployee(parameter);
					if (CT->getEmployeeFilterValid()){
						if (CT->getEmployeeFilterList().size() > 0)
							showDetails(CT->getEmployeeFilterList());
						else
							std::cout << "There's no employee matches this condition...\n";
					}
					else{
						std::cout << "Invalid Regular Expression...\n";
					}
				}
				else {
					std::cout << "Invalid Input...\n";
				}
			}
			else{
				std::cout << "Lack Parameters...\n";
			}
		}
		else if (toUpper(orders[0]) == "DELETE"){
			if (orders.size() < 3){
				std::cout << "Lack parameters...\n";
			}
			else{
				unsigned int index;
				for (index = orders[0].size(); order[index] == ' ' || order[index] == '\t'; index++);
				index = index + orders[1].length();
				std::string parameter = order.substr(index, order.length() - index);
				if (orders[1] == "-p" || orders[1] == "-pr"){
					if (orders[1] == "-p"){
						if (orders.size() > 3){
							std::cout << "Too many arguments...\n";
							continue;
						}
						if (!isAlphaNum(orders[2])){
							std::cout << "Name can only contains letters and numbers...\n";
							continue;
						}
						player * p = CT->searchPlayerByName(orders[2]);
						if (p == NULL){
							std::cout << "player named " << orders[2] << " does not exist...\n";
						}
						else{
							std::cout << "player named " << orders[2] << " has been deleted successfully...\n";
							delete p;
							CT->refresh();
						}
					}
					else if (orders[1] == "-pr"){
						CT->filterPlayer(parameter);
						if (!CT->getFilterValid()){
							std::cout << "Invalid Regular Expression...\n";
						}
						else{
							if (CT->getFilterList().size() == 0){
								std::cout << "No player matches this condition...\n";
							}
							else{
								for (unsigned int i = 0; i < CT->getFilterList().size(); i++){
									std::cout << "player named " << CT->getFilterList()[i]->getName() << 
										" has been deleted successfully...\n";
									delete (CT->getFilterList()[i]);
								}
								CT->refresh();
							}
						}
					}
				}
				else if (orders[1] == "-e" || orders[1] == "-er"){
					if (orders[1] == "-e"){
						if (orders.size() > 3){
							std::cout << "Too many arguments...\n";
							continue;
						}
						if (!isAlphaNum(orders[2])){
							std::cout << "Name can only contains letters and numbers...\n";
							continue;
						}
						employee * e = CT->searchEmployeeByName(orders[2]);
						if (e == NULL){
							std::cout << "employee named " << orders[2] << " does not exist...\n";
						}
						else{
							std::cout << "employee named " << orders[2] << " has been deleted successfully...\n";
							delete e;
							CT->refresh();
						}
					}
					else if (orders[1] == "-er"){
						CT->filterEmployee(parameter);
						if (!CT->getEmployeeFilterValid()){
							std::cout << "Invalid Regular Expression...\n";
						}
						else{
							if (CT->getEmployeeFilterList().size() == 0){
								std::cout << "No employee matches this condition...\n";
							}
							else{
								for (unsigned int i = 0; i < CT->getEmployeeFilterList().size(); i++){
									std::cout << "employee named " << CT->getEmployeeFilterList()[i]->getName() <<
										" has been deleted successfully...\n";
									delete (CT->getEmployeeFilterList()[i]);
								}
								CT->refresh();
							}
						}
					}
				}
				else if (orders[1] == "-c"){
					if (orders.size() > 3){
						std::cout << "Too many arguments...\n";
						continue;
					}
					if (!isAlphaNum(orders[2])){
						std::cout << "Name can only contains letters and numbers...\n";
						continue;
					}
					club * c = CT->searchClubByName(orders[2]);
					if (c == NULL){
						std::cout << "club called " << orders[2] << " does not exist...\n";
					}
					else{
						std::cout << "club named " << orders[2] << " has been deleted successfully...\n";
						delete c;
						CT->refresh();
					}
				}
				else {
					std::cout << "Invalid Input...\n";
				}
			}
		}
		else if (toUpper(orders[0]) == "ALTER"){
			if (orders[1] == "-p"){
				if (orders.size() < 10){
					std::cout << "Lack parameters...\n";
					continue;
				}
				else if (orders.size() > 10){
					std::cout << "Too many arguments...\n";
					continue;
				}
				if (!isAlphaNum(orders[2]) || (!isAlphaNum(orders[3]) && orders[3] != "-u")){
					std::cout << "Players' name can only contains letters and numbers or be -u...\n";
					continue;
				}
				if ((str2int(orders[4]) < 0 && orders[4] != "-u" )|| 
					(str2int(orders[5]) < 0 && orders[5] != "-u" )|| 
					(str2int(orders[6]) < 0 && orders[6] != "-u" )||
					(str2int(orders[7]) < 0 && orders[7] != "-u" )|| 
					(str2int(orders[8]) < 0 && orders[8] != "-u")){
					std::cout << "Characters in SALARY/TRANSFEE/YEAR/AGE/GOAL can only be numbers or -u...\n";
					continue;
				}
				player * p = CT->searchPlayerByName(orders[2]);
				if (p == NULL){
					std::cout << "player named " << orders[2] << " does not exist...\n";
					continue;
				}
				else{
					bool __changed = false;
					if (orders[3] != "-u" && p->getName()!= orders[3]){
						p->setName(orders[3]); __changed = true;
					}
					if (orders[4] != "-u" && p->getSalary() != str2int(orders[4])){
						p->setSalary(str2int(orders[4])); __changed = true;
					}
					if (orders[5] != "-u" && p->getTransFee() != str2int(orders[5])){
						p->setTransFee(str2int(orders[5])); __changed = true;
					}
					if (orders[6] != "-u" && p->getYears() != str2int(orders[6])){
						p->setYears(str2int(orders[6])); __changed = true;
					}
					if (orders[7] != "-u" && p->getAge() != str2int(orders[6])){
						p->setAge(str2int(orders[7])); __changed = true;
					}
					if (orders[8] != "-u" && p->getGoals() != str2int(orders[7])){
						p->setGoals(str2int(orders[8])); __changed = true;
					}
					if (orders[9] != "-u" && p->getAbility() != orders[9]){
						p->setAbility(orders[9]); __changed = true;
					}
					if (__changed){
						CT->refresh();
						std::cout << "player " << orders[2] << " has been changed successfully...\n";
					}
					else{
						std::cout << "no changes has been used to player " << orders[2] << "\n";
					}
				}
			}
			else if (orders[1] == "-e"){
				if (orders.size() < 7){
					std::cout << "Lack parameters...\n";
					continue;
				}
				else if (orders.size() > 7){
					std::cout << "Too many arguments...\n";
					continue;
				}
				if (!isAlphaNum(orders[2]) || (!isAlphaNum(orders[3]) && orders[3] != "-u")){
					std::cout << "Employees' name can only contains letters and numbers or be -u...\n";
					continue;
				}
				if ((str2int(orders[4]) < 0 && orders[4] != "-u") ||
					(str2int(orders[5]) < 0 && orders[5] != "-u")){
					std::cout << "Characters in SALARY/AGE can only be numbers or -u...\n";
					continue;
				}
				employee * e = CT->searchEmployeeByName(orders[2]);
				if (e == NULL){
					std::cout << "employee named " << orders[2] << " does not exist...\n";
					continue;
				}
				else{
					bool __changed = false;
					if (orders[3] != "-u" && e->getName() != orders[3]){
						e->setName(orders[3]); __changed = true;
					}
					if (orders[4] != "-u" && e->getSalary() != str2int(orders[4])){
						e->setSalary(str2int(orders[4])); __changed = true;
					}
					if (orders[5] != "-u" && e->getAge() != str2int(orders[5])){
						e->setAge(str2int(orders[5])); __changed = true;
					}
					if (orders[6] != "-u" && e->getAbility() != orders[6]){
						e->setAbility(orders[6]); __changed = true;
					}
					if (__changed){
						CT->refresh();
						std::cout << "employee " << orders[2] << " has been changed successfully...\n";
					}
					else{
						std::cout << "no changes has been used to employee " << orders[2] << "\n";
					}
				}
			}
			else if (orders[1] == "-c"){
				if (orders.size() < 5){
					std::cout << "Lack parameters...\n";
					continue;
				}
				else if (orders.size() > 5){
					std::cout << "Too many arguments...\n";
					continue;
				}
				if (!isAlphaNum(orders[2]) || (!isAlphaNum(orders[3]) && orders[3] != "-u")){
					std::cout << "Clubs' name can only contains letters and numbers or be -u...\n";
					continue;
				}
				if ((str2int(orders[4]) < 0 && orders[4] != "-u")){
					std::cout << "Characters in FUNDS can only be numbers or -u...\n";
					continue;
				}
				club * c = CT->searchClubByName(orders[2]);
				if (c == NULL){
					std::cout << "club called " << orders[2] << " does not exist...\n";
					continue;
				}
				else{
					bool __changed = false;
					if (orders[3] != "-u" && c->getName() != orders[3]){
						c->setName(orders[3]); __changed = true;
					}
					if (orders[4] != "-u" && c->getFunds() != str2int(orders[4])){
						c->setFunds(str2int(orders[4])); __changed = true;
					}
					if (__changed){
						CT->refresh();
						std::cout << "club " << orders[2] << " has been changed successfully...\n";
					}
					else{
						std::cout << "no changes has been used to club " << orders[2] << "\n";
					}
				}
			}
			else{
				std::cout << "Invalid parameter format...\n";
			}
		}
		else if (toUpper(orders[0]) == "TRANSFER"){
			if (orders.size() < 3){
				std::cout << "Lack parameter...\n";
				continue;
			}
			if (orders.size() > 3){
				std::cout << "Too many arguments...\n";
				continue;
			}
			if (!isAlphaNum(orders[1]) || !isAlphaNum(orders[2])){
				std::cout << "Invalid Input...\n";
				continue;
			}
			club * clubA = CT->searchClubByName(orders[1]);
			if (clubA == NULL){
				std::cout << "club called " << orders[1] << " doesn't exist...\n";
				continue;
			}
			player *p = CT->searchPlayerByName(orders[2]);
			if (p == NULL){
				std::cout << "player called " << orders[2] << " doesn't exist...\n";
				continue;
			}
			if (p->getClub() == clubA){
				std::cout << "player " << p->getName() << " is already in club " << clubA->getName() << std::endl;
				continue;
			}
			if (p->getClub() == NULL){
				if (clubA->getFunds() >= p->getTransFee()){
					std::string yn; yn.clear();
					while (true){
						std::cout << "need to pay $" << p->getTransFee()<< " to the server, confirm (Y/N)?...";
						std::getline(std::cin, yn);
						if (yn.length() != 1 || (toupper(yn[0]) != 'Y' && toupper(yn[0]) != 'N')){
							if (toUpper(yn) == "YES" || toUpper(yn) == "NO")
								break;
							std::cout << "Invalid Input, input Again...\n";
							yn.clear();
						}
						else{
							break;
						}
					}
					if (toupper(yn[0]) == 'Y'){
						clubA->insertPlayer(*p);
						CT->refresh();
						std::cout << "successful...\n";
					}
					else{
						std::cout << "operation canceled...\n";
					}
				}
				else{
					std::cout << "failed, insufficient funds...\n";
				}
			}
			else{
				if (clubA->getFunds() >= p->getTransFee()){
					std::string yn; yn.clear();
					while (true){
						std::cout << "need to pay $" << p->getTransFee() << " to club " << p->getClub()->getName() <<
							", confirm (Y/N)?...";
						std::getline(std::cin, yn);
						if (yn.length() != 1 || (toupper(yn[0]) != 'Y' && toupper(yn[0]) != 'N')){
							if (toUpper(yn) == "YES" || toUpper(yn) == "NO")
								break;
							std::cout << "Invalid Input, input Again...\n";
							yn.clear();
						}
						else{
							break;
						}
					}
					if (toupper(yn[0]) == 'Y'){
						std::string ryn; ryn.clear();
						while (true){
							std::cout << "club " << clubA->getName() << " wants to buy player " << p->getName() <<
								", accept (Y/N)?...";
							std::getline(std::cin, ryn);
							if (ryn.length() != 1 || (toupper(ryn[0]) != 'Y' && toupper(ryn[0]) != 'N')){
								if (toUpper(ryn) == "YES" || toUpper(ryn) == "NO")
									break;
								std::cout << "Invalid Input, Input Again...\n";
								ryn.clear();
							}
							else{
								break;
							}
						}
						if (toupper(ryn[0]) == 'Y'){
							clubA->transPlayer(*(p->getClub()), *p);
							CT->refresh();
							std::cout << "successful...\n";
						}
						else{
							std::cout << "operation canceled...\n";
						}
					}
					else{
						std::cout << "operation canceled...\n";
					}
				}
				else{
					std::cout << "failed, insufficient funds...\n";
				}
			}
		}
		else if (toUpper(orders[0]) == "--VERSION"){
			std::cout << "Player Manage System, @2016, designed by forec, version v3.0\n";
		}
		else if (toUpper(orders[0]) == "--CLR"){
			system("cls");
		}
		else if (toUpper(orders[0]) == "--HELP"){
			mainWinForServer();
		}
		else if (toUpper(orders[0]) == "EXIT"){
			std::cout << "Good Bye...\n";
			return;
		}
		else {
			std::cout << "Invalid Input...\n";
			mainWinForClient();
		}
	}
}

std::string backIO(std::string order){
	std::vector<std::string> orders;
	orders.clear();
	int count = 0;
	int pre = 0;
	for (unsigned int i = 0; i < order.length(); i++){
		if (order[i] == ' ' || order[i] == '\t' || i == order.length() - 1){
			if (i == pre && i != order.length() - 1){
				pre = i;
				continue;
			}
			if (i == order.length() - 1 && order[i] != ' ' && order[i] != '\t')
				i++;
			orders.push_back(order.substr(pre, i - pre));
			pre = i + 1;
		}
	}
	if (orders.size() == 0){
		return "Meanless Input...\n";
	}
	else if (orders[0] == "AREYOULIVE"){
		return "true";
	}
	else if (toUpper(orders[0]) == "LOGIN"){
		if (orders.size() < 3){
			return "Lack Parameters...\n";
		}
		else if (orders.size() > 3){
			return "Too many arguments...\n";
		}
		else if (!isAlphaNum(orders[1]) || !isAlphaNum(orders[2])){
			return "Invalid name/password format...\n";
		}
		else{
			club * cp = CT->searchClubByName(orders[1]);
			if (cp != NULL && cp->checkPass(orders[2])){
				return "true";
			}
			else{
				return "false";
			}
		}
	}
	else if (toUpper(orders[0]) == "REGISTER"){
		if (orders.size() < 3){
			return "Lack Parameters...\n";
		}
		else if (orders.size() > 3){
			return "Too many arguments...\n";
		}
		else if (!isAlphaNum(orders[1]) || !isAlphaNum(orders[2])){
			return "Invalid name/password format...\n";
		}
		else{
			club * cp = CT->searchClubByName(orders[1]);
			if (cp == NULL){
				new club(orders[1], orders[2], 0);
				CT->refresh();
				return "true";
			}
			else{
				return "false";
			}
		}
	}
	else if (toUpper(orders[0]) == "LISTALL"){
		if (orders.size() < 2){
			return "Lack Parameters...\n";
		}
		else {
			int state = 0;
			unsigned int i = 7;
			bool p = false, d = false, c = false, e = false, invalid = false;
			while (i < order.length()){
				switch (state){
				case 0:			// space
					if (order[i] == '-'){
						state = 1;
					}
					if (order[i] != ' ' && order[i] != '\t' && order[i] != '-')
						invalid = true;
					break;
				case 1:			// -
					if (order[i] != 'p' && order[i] != 'c' && order[i] != 'e' &&
						order[i] != 'd' && order[i] != ' ' && order[i] != '\t')
						invalid = true;
					if (order[i] == 'p')
						p = true;
					if (order[i] == 'c')
						c = true;
					if (order[i] == 'e')
						e = true;
					if (order[i] == 'd')
						d = true;
					state = 2;
					if (order[i] == ' ' || order[i] == '\t'){
						invalid = true;
						state = 0;
					}
					break;
				case 2:
					if (order[i] != 'p' && order[i] != 'c' && order[i] != 'e' &&
						order[i] != 'd' && order[i] != ' ' && order[i] != '\t')
						invalid = true;
					if (order[i] == 'p')
						p = true;
					if (order[i] == 'c')
						c = true;
					if (order[i] == 'e')
						e = true;
					if (order[i] == 'd')
						d = true;
					if (order[i] == ' ' || order[i] == '\t'){
						state = 0;
					}
					break;
				}
				i++;
			}
			if (invalid){
				return "Invalid Input...\n";
			}
			std::string toReturn = "";
			if (p){
				toReturn += "All Players:\n";
				showsToString(CT->getPlayers(), d, toReturn);
			}
			if (e){
				toReturn += "All Employees:\n";
				showsToString(CT->getEmployees(), d, toReturn);
			}
			if (c){
				toReturn+= "All Clubs:\n";
				showsToString(CT->getClubs(), d, toReturn);
			}
		//	std::cout << toReturn <<std::endl;
			return toReturn;
		}
	}
	else if (toUpper(orders[0]) == "INSERT"){
		if (orders.size() < 5){
			return "Lack parameters...\n";
		}
		if (orders.size() > 5){
			return "Too many arguments...\n";
		}
		if (isAlphaNum(orders[2]) && isAlphaNum(orders[3]) &&
			(orders[1] == "-p" || orders[1] == "-e")){
			bool reverse = false;
			if (orders.size() == 5){
				if (orders[4] != "-v"){
					return "Invalid parameter format...\n";
				}
				reverse = true;
			}
			else{
				return "Invalid parameter format...\n";
			}
			club * c = CT->searchClubByName(orders[2]);
			if (c == NULL){
				return "club named " + orders[2] + " does not exist...\n";
			}
			else if (orders[1] == "-p"){
				player *p = CT->searchPlayerByName(orders[3]);
				if (p != NULL){
					if (p->getClub() == NULL){
						return "player " + orders[3] + " was not your member...\n";
					}
					else if (reverse == true && p->getClub()->getName() == orders[2]){
						c->removePlayer(*p);
						CT->refresh();
						return "successful...\n";
					}
				}
				else {
					if (p == NULL){
						return "player named " + orders[3] + " does not exist...\n";
					}
					else {
						if (reverse == false && p->getClub() != NULL){
							return "unsuccessful, player " + orders[3] + " was belonging to club " +
								p->getClub()->getName() + "...\n";
						}
						else if (reverse == true && p->getClub()->getName() != orders[2]){
							return "unsuccessful, player " + orders[3] + " didn't belong to club " +
								p->getClub()->getName() + "...\n";
						}
					}
				}
			}
			else if (orders[1] == "-e"){
				employee *e = CT->searchEmployeeByName(orders[3]);
				if (e != NULL){
					if (e->getClub() == NULL){
						return "employee " + orders[3] + " was not your member...\n";
					}
					else if (reverse == true && e->getClub()->getName() == orders[2]){
						c->removeEmployee(*e);
						CT->refresh();
						return "successful...\n";
					}
				}
				else {
					if (e == NULL){
						return "employee named " + orders[3] + " does not exist...\n";
					}
					else{
						if (reverse == false && e->getClub() != NULL){
							return "unsuccessful, employee " + orders[3] + " was belonging to club " +
								e->getClub()->getName() + "...\n";
						}
						else if (reverse == true && e->getClub()->getName() != orders[2]){
							return "unsuccessful, employee " + orders[3] + " didn't belong to club " +
								e->getClub()->getName() + "...\n";
						}
					}
				}
			}
		}
		else{
			return "Invalid Input...\n";
		}
	}
	else if (toUpper(orders[0]) == "SEARCH"){
		if (orders.size() >= 3){
			unsigned int index;
			for (index = orders[0].size(); order[index] == ' ' || order[index] == '\t'; index++);
			index = index + orders[1].length();
			std::string parameter = order.substr(index, order.length() - index);
		//	std::cout << "reger::" << parameter << std::endl;
			if (orders[1] == "-p"){
				CT->filterPlayer(parameter);
				if (CT->getFilterValid()){
					if (CT->getFilterList().size() > 0){
						std::string toReturn;
						toReturn.clear();
						showDetailsToString(CT->getFilterList(), toReturn);
						return toReturn;
					}
					else
						return "There's no player matches this condition...\n";
				}
				else{
					return "Invalid Regular Expression...\n";
				}
			}
			else if (orders[1] == "-c"){
				club * c = CT->searchClubByName(orders[2]);
				if (c == NULL){
					return "There's No club named " + orders[2] + "...\n";
				}
				else{
					return c->toStr();
				}
			}
			else if (orders[1] == "-e"){
				CT->filterEmployee(parameter);
				if (CT->getEmployeeFilterValid()){
					if (CT->getEmployeeFilterList().size() > 0){
						std::string toReturn;
						toReturn.clear();
						showDetailsToString(CT->getEmployeeFilterList(), toReturn);
						return toReturn;
					}
					else
						return "There's no employee matches this condition...\n";
				}
				else{
					return "Invalid Regular Expression...\n";
				}
			}
			else {
				return "Invalid Input...\n";
			}
		}
		else{
			return "Lack Parameters...\n";
		}
	}
	else if (toUpper(orders[0]) == "DELETE"){
		if (orders.size() < 3){
			std::cout << "Lack parameters...\n";
		}
		else{
			unsigned int index;
			for (index = orders[0].size(); order[index] == ' ' || order[index] == '\t'; index++);
			index = index + orders[1].length();
			std::string parameter = order.substr(index, order.length() - index);
			if (orders[1] == "-c"){
				if (orders.size() > 3){
					return "Too many arguments...\n";
				}
				if (!isAlphaNum(orders[2])){
					return "Name can only contains letters and numbers...\n";
				}
				club * c = CT->searchClubByName(orders[2]);
				if (c == NULL){
					return "error, club called " + orders[2] + " does not exist...\n";
				}
				else{
					delete c;
					CT->refresh();
					return "your club " + orders[2] + " has been deleted successfully...\n";
				}
			}
			else {
				return "Unknown error...\n";
			}
		}
	}
	else if (toUpper(orders[0]) == "ALTER"){
		if (orders[1] == "-c"){
			if (orders.size() < 5){
				return "Lack parameters...\n";
			}
			else if (orders.size() > 5){
				return "Too many arguments...\n";
			}
			if (!isAlphaNum(orders[2]) || (!isAlphaNum(orders[3]) && orders[3] != "-u")){
				return "Clubs' name can only contains letters and numbers or be -u...\n";
			}
			if ((str2int(orders[4]) < 0 && orders[4] != "-u")){
				return "Characters in FUNDS can only be numbers or -u...\n";
			}
			club * c = CT->searchClubByName(orders[2]);
			if (c == NULL){
				return "club called " + orders[2] + " does not exist...\n";
			}
			else{
				bool __changed = false;
				if (orders[3] != "-u" && c->getName() != orders[3]){
					c->setName(orders[3]); __changed = true;
				}
				if (orders[4] != "-u" && c->getFunds() != str2int(orders[4])){
					c->setFunds(str2int(orders[4])); __changed = true;
				}
				if (__changed){
					CT->refresh();
					return "club " + orders[2] + " has been changed successfully...\n";
				}
				else{
					return "no changes has been used to club " + orders[2] + "\n";
				}
			}
		}
		else{
			return "Invalid parameter format...\n";
		}
	}
	else if (toUpper(orders[0]) == "TRANSFER"){
		if (orders.size() < 3){
			return "Lack parameter...\n";
		}
		if (orders.size() > 3){
			return "Too many arguments...\n";
		}
		if (!isAlphaNum(orders[1]) || !isAlphaNum(orders[2])){
			return "Invalid Input...\n";
		}
		club * clubA = CT->searchClubByName(orders[1]);
		if (clubA == NULL){
			return "club called " + orders[1] + " doesn't exist...\n";
		}
		player *p = CT->searchPlayerByName(orders[2]);
		if (p == NULL){
			return "player called " + orders[2] + " doesn't exist...\n";
		}
		if (p->getClub() == clubA){
			return "player " + p->getName() + " is already in club " + clubA->getName() + "\n";
		}
		if (p->getClub() == NULL){
			if (clubA->getFunds() >= p->getTransFee()){
				clubA->insertPlayer(*p);
				clubA->addFunds(0 - p->getTransFee());
				CT->refresh();
				return "successful...\n";
			}
			else{
				return "failed, insufficient funds...\n";
			}
		}
		else{
			if (clubA->getFunds() >= p->getTransFee()){
				clubA->transPlayer(*(p->getClub()), *p);
				CT->refresh();
				return "successful...\n";
			}
			else{
				return "failed, insufficient funds...\n";
			}
		}
	}
	else {
		return "Invalid Input...\n";
	}
	return "²Êµ°\n";
}

void console(int argc, char **argv){
	if (argc > 2){
		std::cout << "Too many arguments...\n";
		return;
	}
	else if (argc < 2){
		std::cout << "Lack parameter...\n";
		return;
	}
	else{
		if (toUpper(std::string(argv[1])) == "--SERVER_OFFLINE"){
			std::cout << "username: ";
			std::string root, password;
			root.clear(); password.clear();
			std::getline(std::cin, root);
			std::cout << "password: ";
			std::getline(std::cin, password);
			if (root == "root" && password == "admin"){
				initServer();
				IO();
			}
			else{
				std::cout << "wrong username/password...\n";
				return;
			}
		}
		else if (toUpper(std::string(argv[1])) == "--SERVER_ONLINE"){
			std::cout << "username: ";
			std::string root, password;
			root.clear(); password.clear();
			std::getline(std::cin, root);
			std::cout << "password: ";
			std::getline(std::cin, password);
			if (root == "root" && password == "admin"){
				std::cout << "server is starting...\nrunning...\n";
				initServer();
				startServerSocket();
			}
			else{
				std::cout << "wrong username/password...\n";
				return;
			}
		}
		else if (toUpper(std::string(argv[1])) == "--CLIENT"){
			startClient();
		}
		else{
			std::cout << "Invalid option...\n";
			std::cout << "use --server_online/offline to start a server, --client to start a client...\n";
			return;
		}
	}
}

bool startServerSocket(){
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest = MAKEWORD(1, 1);
	int err;
	err = WSAStartup(myVersionRequest, &wsaData);
	SOCKET serSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = PF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8760);

	bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	listen(serSocket, 10);

	int len;
	while (true){
		SOCKADDR_IN clientsocket;
		int len = sizeof(SOCKADDR);
		SOCKET serConn = accept(serSocket, (SOCKADDR*)&clientsocket, &len);
		char receiveBuf[100];
		len = 0;
		recv(serConn, receiveBuf, strlen(receiveBuf), 0);
		sscanf_s(receiveBuf, "%d", &len);
		std::string truerecv = std::string(receiveBuf).substr(6, len);
	//	std::cout << "flag:"<<truerecv << std::endl;
		std::string back = backIO(truerecv);
		char backlen[6];
		sprintf_s(backlen, "%5d", back.length());
		back = std::string(backlen) + " " + back;
		send(serConn, back.c_str(), strlen(back.c_str()), NULL);
	//	std::cout << "We send:" << back << std::endl;
		closesocket(serConn);
	}
	closesocket(serSocket);
	WSACleanup();
}

std::string reck(SOCKET & socket_s, SOCKADDR_IN &socket_in, std::string &s, bool &flag){
	socket_s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(socket_s, (SOCKADDR*)&socket_in, sizeof(SOCKADDR));
	memset(&socket_in, 0, sizeof(socket_in));
	socket_in.sin_addr.s_addr = inet_addr("127.0.0.1");
	socket_in.sin_family = PF_INET;
	socket_in.sin_port = htons(8760);
	int t = connect(socket_s, (SOCKADDR*)&socket_in, sizeof(SOCKADDR));
	if (t < 0){
		flag = false;
		return "Server shutdown...\n";
	}
	char temp[30001];
	char len[6];
	sprintf_s(len, "%5d", s.length());
	s = std::string(len) + " " + s;
	//std::cout << "we send::" << s.c_str() << std::endl;
	send(socket_s, s.c_str(), strlen(s.c_str()), NULL);
	recv(socket_s, temp, strlen(temp), NULL);
	int le;
	sscanf_s(temp, "%d", &le);
	closesocket(socket_s);
	return std::string(temp).substr(6, le);
}

std::string login(SOCKET &socket, SOCKADDR_IN &socket_in, bool &flag){
	std::cout << "+=============================================================================+\n";
	std::cout << "|                     PLAYER MANAGE CLIENT                                    |\n";
	std::cout << "|                                      designed by forec, version 3.0         |\n";
	std::cout << "|   Guide:                                                                    |\n";
	std::cout << "|     LOGIN                                                                   |\n";
	std::cout << "|       [NAME] [PASSWORD]                                                     |\n";
	std::cout << "|             login your club.                                                |\n";
	std::cout << "|     REGISTER                                                                |\n";
	std::cout << "|       [NAME] [PASSWORD]                                                     |\n";
	std::cout << "|             create your new club named NAME with password PASSWORD.         |\n";
	std::cout << "|     EXIT    exit.                                                           |\n";
	std::cout << "+=============================================================================+\n";
	std::string order;
	std::vector<std::string> orders;
	while (flag){
		clear(order, orders);
		getline(std::cin, order);
		int count = 0;
		int pre = 0;
		for (unsigned int i = 0; i < order.length(); i++){
			if (order[i] == ' ' || order[i] == '\t' || i == order.length() - 1){
				if (i == pre && i != order.length() - 1){
					pre = i;
					continue;
				}
				if (i == order.length() - 1 && order[i] != ' ' && order[i] != '\t')
					i++;
				orders.push_back(order.substr(pre, i - pre));
				pre = i + 1;
			}
		}
		if (orders.size() == 0){
			std::cout << "Meanless Input...\n";
		}
		else if (orders.size() == 1 && toUpper(orders[0]) == "EXIT"){
			std::cout << "GoodBye...\n";
			return "---";
		}
		else if (orders.size() < 3){
			std::cout << "Invalid Input...\n";
		}
		else if (orders.size() > 3){
			std::cout << "Too many arguments...\n";
		}
		else if (toUpper(orders[0]) == "LOGIN"){
			if (!isAlphaNum(orders[1]) || !isAlphaNum(orders[2])){
				std::cout << "Invalid name/password format, can only contains letters and numbers...\n";
				continue;
			}
			else{
				std::string toSend;
				std::string ans;
				toSend = "LOGIN " + orders[1] + " " + orders[2];
				ans = reck(socket, socket_in, toSend, flag);
			//	std::cout << "In login we got :" << ans << std::endl;
				if (ans == "true"){
					std::cout << "success, you have been online...\n";
					return orders[1];
				}
				else if (ans == "Server shutdown...\n"){
					std::cout << "Server shutdown...\n";
					return "---";
				}
				else{
					std::cout << "wrong name/password...\n";
				}
			}
		}
		else if (toUpper(orders[0]) == "REGISTER"){
			if (!isAlphaNum(orders[1]) || !isAlphaNum(orders[2])){
				std::cout << "Invalid name/password format, can only contains letters and numbers...\n";
			}
			else{
				std::string toSend;
				std::string ans;
				toSend = "REGISTER " + orders[1] + " " + orders[2];
				ans = reck(socket, socket_in, toSend, flag);
				if (ans == "true"){
					std::cout << "success, you have been online...\n";
					return orders[1];
				}
				else if (ans == "Server shutdown...\n"){
					std::cout << "Server shutdown...\n";
					return "---";
				}
				else{
					std::cout << "There's already some club named " << orders[1] << "...\n";
				}
			}
		}
		else {
			std::cout << "Invalid Input...\n";
		}
	}
}

void startClient(){
	int err;
	WORD versionRequired;
	WSADATA wsaData;
	versionRequired = MAKEWORD(1, 1);
	err = WSAStartup(versionRequired, &wsaData);
	SOCKET clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN clientsock_in;
	bool flag = true;
	reck(clientSocket, clientsock_in, std::string("AREYOULIVE"), flag);
	if (flag==false){
		std::cout << "Server not online...\n";
		return;
	}
	std::string clubn = login(clientSocket, clientsock_in, flag);
	if (clubn == "---"){
		return;
	}
	mainWinForClient();
	std::string order;
	std::vector<std::string> orders;
	std::string toSend;
	while (flag){
		toSend = "===";
		clear(order, orders);
		getline(std::cin, order);
		int count = 0;
		int pre = 0;
		for (unsigned int i = 0; i < order.length(); i++){
			if (order[i] == ' ' || order[i] == '\t' || i == order.length() - 1){
				if (i == pre && i != order.length() - 1){
					pre = i;
					continue;
				}
				if (i == order.length() - 1 && order[i] != ' ' && order[i] != '\t')
					i++;
				orders.push_back(order.substr(pre, i - pre));
				pre = i + 1;
			}
		}
		if (orders.size() == 0){
			std::cout << "Meanless Input...\n";
		}
		else if (toUpper(orders[0]) == "AFFORD"){
			if (orders.size() < 2){
				std::cout << "Lack parameter...\n";
			}
			else if (orders.size() > 2){
				std::cout << "Too many arguments...\n";
			}
			else {
				toSend = "ALTER -c " + clubn + " -u " + orders[1];
				std::cout << reck(clientSocket, clientsock_in, toSend, flag);
			}
		}
		else if (toUpper(orders[0]) == "REMOVE"){
			if (orders.size() < 3){
				std::cout << "Lack parameters...\n";
			}
			else if (orders.size() > 3){
				std::cout << "Too many arguments...\n";
			}
			else {
				toSend = "INSERT " +orders[1] + " " +  clubn + " " + orders[2] + " -v";
				std::cout << reck(clientSocket, clientsock_in, toSend, flag);
			}
		}
		else if (toUpper(orders[0]) == "TRANSFER"){
			if (orders.size() < 2){
				std::cout << "Lack parameter...\n";
			}
			else if (orders.size() > 2){
				std::cout << "Too many arguments...\n";
			}
			else{
				toSend = "TRANSFER " + clubn + " " + orders[1];
				std::cout << reck(clientSocket, clientsock_in, toSend, flag);
			}
		}
		else if (orders[0] == "DESTORY"){
			if (orders.size() > 1){
				std::cout << "Too many arguments...\n";
			}
			else{
				toSend = "DELETE -c " + clubn;
				std::cout << reck(clientSocket, clientsock_in, toSend, flag);
				return;
			}
		}
		else if (orders[0] == "SEARCH"){
			if (orders.size() < 3){
				std::cout << "Lack Parameters...\n";
			}
			else if (orders.size() > 3){
				std::cout << "Too many arguments...\n";
			}
			else{
				toSend = "SEARCH " + orders[1] + " " + orders[2];
				std::cout << reck(clientSocket, clientsock_in, toSend, flag);
			}
		}
		else if (orders[0] == "ALTER"){
			if (orders.size() < 3){
				std::cout << "Lack Parameters...\n";
			}
			else if (orders.size() > 3){
				std::cout << "Too many arguments...\n";
			}
			else{
				if (orders[1] == "-n"){
					toSend = "ALTER -c " + clubn + " "+ orders[2] + " -u";
					std::cout << reck(clientSocket, clientsock_in, toSend, flag);
				}
				else if (orders[1] == "-p"){
					toSend = "ALTER -p" + clubn + " -u " + orders[2];
					std::cout << reck(clientSocket, clientsock_in, toSend, flag);
				}
				else {
					std::cout << "Invalid Input...\n";
				}
			}
		}
		else if (toUpper(orders[0]) == "LISTALL"){
			toSend = order;
			std::cout << reck(clientSocket, clientsock_in, toSend, flag);
		}
		else if (toUpper(orders[0]) == "LOGOUT"){
			if (orders.size() == 1){
				std::cout << "GoodBye...\n";
				std::cout << "disconnect...\n";
				break;
			}
		}
		else if (toUpper(orders[0]) == "--VERSION"){
			std::cout << "Player Manage Client, @2016, designed by forec, version v3.0\n";
		}
		else if (toUpper(orders[0]) == "--CLR"){
			system("cls");
		}
		else if (toUpper(orders[0]) == "--HELP"){
			mainWinForClient();
		}
		else {
			std::cout << "Invalid Input...\n";
		}
	}
	closesocket(clientSocket);
	WSACleanup();
}

void simpleTest(){
	using namespace std;
	player b1("u1", 18, "AA", 100, 2000, 20, 1, NULL);
	player b2("u2", 19, "BB", 200, 3000, 30, 2, NULL);
	player b3("u3", 20, "AA", 300, 4000, 40, 3, NULL);
	player b4("u4", 21, "AA", 400, 5000, 50, 4, NULL);
	employee e1("e1", 30, "AA", 400, NULL);
	club c1("club1", ""), c2("club2","root", 3000);
	c1.insertPlayer(b1);
	c1.insertPlayer(b2);
	c1.insertPlayer(b3);
	c2.insertPlayer(b4);
	c1.insertEmployee(e1);
//	c2.transPlayer(c1, b2);

	/*cout << "total employees and players: "<<base::getCount() << endl;
	showPlayerDetails(CT->getPlayers());
	showEmployeeDetails(CT->getEmployees());*/

	CT->filterPlayer("@age>10");
	std::cout << "valid ? " << CT->getFilterValid() << endl;
	showDetails(CT->getFilterList());
}

template <typename T>
void simpleShow(T & t){
	using namespace std;
	if (t.size() == 0)
		std::cout << "EMPTY\n";
	for (unsigned int i = 0; i < t.size(); i++){
		cout << *(t[i]) << "\t";
		if ((i + 1) % 5 == 0)
			cout << endl;
	}
	if (t.size() % 5 != 0)
		cout << endl;
}

template <typename T>
void showDetails(T & t){
	if (t.size() == 0)
		std::cout << "EMPTY\n";
	for (unsigned int i = 0; i < t.size(); i++){
		t[i]->coutDetails();
	}
}

template <typename T>
void shows(T & t, bool d){
	if (d){
		showDetails(t);
	}
	else{
		simpleShow(t);
	}
	std::cout << std::endl;
}

template <typename T>
void simpleShowToString(T & t, std::string &s){
	using namespace std;
	if (t.size() == 0){
		s += "EMPTY\n";
		return;
	}
	for (unsigned int i = 0; i < t.size(); i++){
		s += (t[i]->getName() + " ");
		if ((i + 1) % 5 == 0)
			s+="\n";
	}
	if (t.size() % 5 != 0)
		s += "\n";
}

template <typename T>
void showDetailsToString(T & t, std::string &s){
	if (t.size() == 0)
		s+= "EMPTY\n";
	for (unsigned int i = 0; i < t.size(); i++){
		s+=t[i]->toStr();
	}
}

template <typename T>
void showsToString(T & t, bool d, std::string &s){
	if (d){
		showDetailsToString(t, s);
	}
	else{
		simpleShowToString(t, s);
	}
}