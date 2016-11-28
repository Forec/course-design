#ifndef __FILTER_H_
#define __FILTER_H_

#include "stdafx.h"

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

namespace cp1{
	template <typename T>
	void swap(T & a, T &b){
		T temp;
		temp = a;
		a = b;
		b = temp;
	}
};

struct filter{
	struct block{
		int lSide, rSide;
		bool lSideCheck, rSideCheck;
	};
	void reverseBlock(std::vector<block> &blist){
		for (unsigned int i = 0; i < blist.size(); i++){
			blist[i].lSide += 1;
			blist[i].rSide -= 1;
			cp1::swap(blist[i].lSide, blist[i].rSide);
			cp1::swap(blist[i].lSideCheck, blist[i].rSideCheck);
		}
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
	void andMergeBlockFilter(std::vector<block> &t, const std::vector<block> &f){
		if (!f.empty()){
			if (t.empty()){
				t = f;
				return;
			}
			for (unsigned int i = 0; i < t.size(); i++){
				int l, r;
				bool lCheck = t[i].lSideCheck, rCheck = t[i].rSideCheck,
					lChanged = false, rChanged = false;
				if (t[i].lSideCheck){
					l = t[i].lSide;
				}
				if (t[i].rSideCheck){
					r = t[i].rSide;
				}
				for (unsigned int j = 0; j < f.size(); j++){
					if (f[j].lSideCheck){
						if (!lChanged){
							lCheck = true;
							lChanged = true;
							l = f[j].lSide;
						}
						else if (f[j].lSide < l &&
							(!t[i].lSideCheck ||
							f[i].lSide >= t[i].lSide)){
							l = f[j].lSide;
							lCheck = true;
							lChanged = false;
						}
					}
					if (f[j].rSideCheck){
						if (!rChanged){
							rCheck = true;
							rChanged = true;
							r = f[j].rSide;
						}
						else if (f[j].rSide > r &&
							(!t[i].rSideCheck ||
							f[i].rSide <= t[i].rSide)){
							r = f[j].rSide;
							rCheck = true;
							rChanged = false;
						}
					}
				}
				t[i].lSideCheck = lCheck;
				t[i].rSideCheck = rCheck;
				t[i].lSide = l;
				t[i].rSide = r;
			}
		}
	}
	std::vector<std::string> nameFilter; 
	std::vector<std::string> noNameFilter; 
	std::vector<std::string> nameInclude;
	std::vector<std::string> clubInclude;
	std::vector<std::string> noAbilityFilter;
	std::vector<std::string> abilityFilter;
	std::vector<std::string> noNameInclude;
	std::vector<std::string> noClubInclude;
	std::vector<std::string> noAbilityInclude;
	std::vector<std::string> abilityInclude;
	std::vector<std::string> clubFilter;
	std::vector<std::string> noClubFilter;
	std::vector<block> yearsFilter;
	std::vector<block> ageFilter; 
	std::vector<block> goalFilter;
	std::vector<block> transFeeFilter;
	std::vector<block> salaryFilter;
	bool none, all, invalid;
	filter(){
		nameFilter.clear(); 
		noNameFilter.clear();
		nameInclude.clear();
		clubInclude.clear();
		abilityInclude.clear();
		noNameInclude.clear();
		noClubInclude.clear();
		noAbilityInclude.clear();
		abilityFilter.clear();
		noAbilityFilter.clear();
		clubFilter.clear(); 
		noClubFilter.clear();
		yearsFilter.clear();
		ageFilter.clear();
		goalFilter.clear();
		transFeeFilter.clear();
		salaryFilter.clear();
		none = false, all = false; invalid = false;
	}
	filter(std::string filterStr){
		nameFilter.clear();
		noNameFilter.clear();
		nameInclude.clear();
		clubInclude.clear();
		abilityInclude.clear();
		noAbilityFilter.clear();
		clubFilter.clear();
		noClubFilter.clear();
		abilityFilter.clear();
		noNameInclude.clear();
		noClubInclude.clear();
		noAbilityInclude.clear();
		yearsFilter.clear();
		ageFilter.clear();
		goalFilter.clear();
		transFeeFilter.clear();
		salaryFilter.clear();
		none = false, all = false; invalid = false;
		unsigned int i = 1, index = 0;
		while (i < filterStr.size() && (('a' <= filterStr[i] && filterStr[i] <= 'z') ||
			('A' <= filterStr[i] && filterStr[i] <= 'Z') ||
			('0' <= filterStr[i] && filterStr[i] <= '9')))
			i++;
		std::string a = filterStr.substr(1, i - 1);
		while (i < filterStr.size() && (filterStr[i] == ' ' || filterStr[i] == '\t'))
			i++;
		if (i == filterStr.size() || i + 1 == filterStr.size() ||
			(filterStr[i] != '>' && filterStr[i] != '<' && 
			 filterStr[i] != '=' && filterStr[i] != '~')){
			invalid = true;
			return;
		}
		else{
			std::string symbol = filterStr.substr(i,1);
			switch (filterStr[i + 1]){
			case '=':
				symbol = filterStr.substr(i, 2);
				i++;
				break;
			case '>':
			case '<':
			case '~':
				invalid = true;
				return;
				break;
			default:
				break;
			}
			i++;
			while (i < filterStr.size() && (filterStr[i] == ' ' || filterStr[i] == '\t'))
				i++;
			index = i;
			std::string b;
			while (index < filterStr.size()){
				if (filterStr[index] == ' ' || filterStr[index] == '\t'){
					b = filterStr.substr(i, index - i);
					break;
				}
				if (filterStr[index] == '>' || filterStr[index] == '<' || 
					filterStr[index] == '=' || filterStr[index] == '~'){
					invalid = true;
					return;
				}
				index++;
			}
			if (index < filterStr.size()){
				while (index < filterStr.size()){
					if (filterStr[index] != ' ' && filterStr[index] != '\t'){
						invalid = true;
						return;
					}
					index++;
				}
			}
			else{
				b = filterStr.substr(i, index - i);
			}
//			std::cout << a << " " << symbol << " " << b << std::endl;
			int tempN = str2int(b);
			if (tempN == -1 || a == "name" || a == "club" || a == "ability"){
				if ((a != "name" && a != "club" && a != "ability") || 
					(symbol != "=" && symbol != "==" && symbol != "~")){
					invalid = true;
					return;
				}
				else{
					if (symbol == "==" || symbol == "="){
						if (a == "name"){
							nameFilter.push_back(b);
						}
						else if (a == "club"){
							clubFilter.push_back(b);
						}
						else{
							abilityFilter.push_back(b);
						}
					}
					else{
						if (a == "name"){
							nameInclude.push_back(b);
						}
						else if (a == "club"){
							clubInclude.push_back(b);
						}
						else{
							abilityInclude.push_back(b);
						}
					}
					return;
				}
			}
			else {
				if (symbol == ">="){
					tempN--;
				}
				if (symbol == "<="){
					tempN++;
				}
				block B;
				if (symbol == ">" || symbol == ">="){
					B.lSide = tempN; B.rSideCheck = false;
					B.lSideCheck = true;
				}
				if (symbol == "=" || symbol == "=="){
					B.lSide = tempN - 1; B.rSide = tempN + 1;
					B.lSideCheck = true; B.rSideCheck = true;
				}
				if (symbol == "<" || symbol == "<="){
					B.rSide = tempN; B.lSideCheck = false;
					B.rSideCheck = true;
				}
				if (a == "age"){
					ageFilter.push_back(B);
					return;
				}
				else if (a == "kick"){
					goalFilter.push_back(B);
					return;
				}
				else if (a == "experience"){
					yearsFilter.push_back(B);
					return;
				}
				else if (a == "transfer"){
					transFeeFilter.push_back(B);
					return;
				}
				else if (a == "salary"){
					salaryFilter.push_back(B);
					return;
				}
				else{
					invalid = true;
					return;
				}
			}
		}
	}
	friend std::ostream & operator<<(std::ostream &os, const filter & f){
		os << "NameFilter: ";
		for (unsigned int i = 0; i < f.nameFilter.size(); i++){
			os << f.nameFilter[i] << "|";
		}
		os << "\nClub Filter: ";
		for (unsigned int i = 0; i < f.clubFilter.size(); i++){
			os << f.clubFilter[i] << "|";
		}
		os << "\nClub Include: ";
		for (unsigned int i = 0; i < f.clubInclude.size(); i++){
			os << f.clubInclude[i] << "|";
		}
		os << "\nName Include: ";
		for (unsigned int i = 0; i < f.nameInclude.size(); i++){
			os << f.nameInclude[i] << "|";
		}
		os << "\nAge Filter: ";
		for (unsigned int i = 0; i < f.ageFilter.size(); i++){
			os << std::endl << f.ageFilter[i].lSideCheck << " " << f.ageFilter[i].rSideCheck <<
				" " << f.ageFilter[i].lSide << " " << f.ageFilter[i].rSide;
		}
		os << "\nYears Filter: ";
		for (unsigned int i = 0; i < f.yearsFilter.size(); i++){
			os << std::endl << f.yearsFilter[i].lSideCheck << " " << f.yearsFilter[i].rSideCheck <<
				" " << f.yearsFilter[i].lSide << " " << f.yearsFilter[i].rSide;
		}
		os << "\nsalary Filter: ";
		for (unsigned int i = 0; i < f.salaryFilter.size(); i++){
			os << std::endl << f.salaryFilter[i].lSideCheck << " " << f.salaryFilter[i].rSideCheck <<
				" " << f.salaryFilter[i].lSide << " " << f.salaryFilter[i].rSide;
		}
		os << std::endl;
		return os;
	}
	filter & operator=(const filter &f){
		if (this == &f)
			return *this;
		nameFilter = f.nameFilter;
		noNameFilter = f.noNameFilter;
		clubFilter = f.clubFilter;
		nameInclude = f.nameInclude;
		clubInclude = f.clubInclude;
		abilityFilter = f.abilityFilter;
		noAbilityFilter = f.noAbilityFilter;
		abilityInclude = f.abilityInclude;
		noClubFilter = f.noClubFilter;
		yearsFilter = f.yearsFilter;
		noNameInclude = f.noNameInclude;
		noClubInclude = f.noClubInclude;
		noAbilityInclude = f.noAbilityInclude;
		ageFilter = f.ageFilter;
		goalFilter = f.goalFilter;
		transFeeFilter = f.transFeeFilter;
		salaryFilter = f.salaryFilter;
		none = f.none;
		invalid = f.invalid;
		return *this;
	}

	// REVERSE_METHOD
	void cancelReverse(){
		if (none || all){
			cp1::swap(none, all);
			return;
		}
		cp1::swap(nameFilter, noNameFilter);
		cp1::swap(clubFilter, noClubFilter);
		cp1::swap(abilityFilter, noAbilityFilter);
		cp1::swap(nameInclude, noNameInclude);
		cp1::swap(clubInclude, noClubInclude);
		cp1::swap(abilityInclude, noAbilityInclude);
		reverseBlock(yearsFilter);
		reverseBlock(ageFilter);
		reverseBlock(goalFilter);
		reverseBlock(transFeeFilter);
		reverseBlock(salaryFilter);
	}

	// sub Function of AND/OR MERGE
	void orMergeVectorFilter(std::vector<std::string> & vectorFilter,
		 const std::vector<std::string> & fvectorFilter){
		if (vectorFilter.empty()){
			vectorFilter = fvectorFilter;
		}
		else{
			for (unsigned int i = 0; i < vectorFilter.size(); i++){
				bool _find = false;
				for (unsigned int j = 0; j < fvectorFilter.size(); j++){
					if (fvectorFilter[j] == vectorFilter[i]){
						_find = true;
						break;
					}
				}
				if (_find){
					vectorFilter.erase(vectorFilter.begin() + i);
					i--;
				}
			}
			vectorFilter.insert(vectorFilter.end(), fvectorFilter.begin(), fvectorFilter.end());
		}
	}

	// AND_MERGE_METHOD
	void andMerge(const filter &f){
		if (invalid || f.invalid){
			invalid = true;
			return;
		}
		if (f.none || none){
			none = true;
			return;
		}
		if (f.all){
			return;
		}
		if (!f.nameFilter.empty()){
			orMergeVectorFilter(nameFilter, f.nameFilter);
		}
		if (!f.noNameFilter.empty()){
			orMergeVectorFilter(noNameFilter, f.noNameFilter);
		}
		if (!f.clubFilter.empty()){
			orMergeVectorFilter(clubFilter, f.clubFilter);
		}
		if (!f.noClubFilter.empty()){
			orMergeVectorFilter(noClubFilter, f.noClubFilter);
		}
		if (!f.nameInclude.empty()){
			orMergeVectorFilter(nameInclude, f.nameInclude);
		}
		if (!f.clubInclude.empty()){
			orMergeVectorFilter(clubInclude, f.clubInclude);
		}
		if (!f.abilityFilter.empty()){
			orMergeVectorFilter(abilityFilter, f.abilityFilter);
		}
		if (!f.noAbilityFilter.empty()){
			orMergeVectorFilter(noAbilityFilter, f.noAbilityFilter);
		}
		if (!f.noAbilityInclude.empty()){
			orMergeVectorFilter(noAbilityInclude, f.noAbilityInclude);
		}
		if (!f.abilityInclude.empty()){
			orMergeVectorFilter(abilityInclude, f.abilityInclude);
		}
		if (!f.noNameInclude.empty()){
			orMergeVectorFilter(noNameInclude, f.noNameInclude);
		}
		if (!f.noClubInclude.empty()){
			orMergeVectorFilter(noClubInclude, f.noClubInclude);
		}
		andMergeBlockFilter(ageFilter, f.ageFilter);
		andMergeBlockFilter(goalFilter, f.goalFilter);
		andMergeBlockFilter(salaryFilter, f.salaryFilter);
		andMergeBlockFilter(transFeeFilter, f.transFeeFilter);
		andMergeBlockFilter(yearsFilter, f.yearsFilter);
	}
	
	// OR_MERGE_METHOD
	void orMerge(const filter &f){
		if (f.invalid || invalid){
			invalid = true;
			return;
		}
		if (f.none){
			return;
		}
		if (f.all){
			all = true;
			return;
		}
		if (!f.nameFilter.empty()){
			orMergeVectorFilter(nameFilter, f.nameFilter);
		}
		if (!f.noNameFilter.empty()){
			orMergeVectorFilter(noNameFilter, f.noNameFilter);
		}
		if (!f.clubFilter.empty()){
			orMergeVectorFilter(clubFilter, f.clubFilter);
		}
		if (!f.noClubFilter.empty()){
			orMergeVectorFilter(noClubFilter, f.noClubFilter);
		}		
		if (!f.nameInclude.empty()){
			orMergeVectorFilter(nameInclude, f.nameInclude);
		}
		if (!f.clubInclude.empty()){
			orMergeVectorFilter(clubInclude, f.clubInclude);
		}
		if (!f.abilityFilter.empty()){
			orMergeVectorFilter(abilityFilter, f.abilityFilter);
		}
		if (!f.noAbilityFilter.empty()){
			orMergeVectorFilter(noAbilityFilter, f.noAbilityFilter);
		}
		if (!f.noAbilityInclude.empty()){
			orMergeVectorFilter(noAbilityInclude, f.noAbilityInclude);
		}		
		if (!f.abilityInclude.empty()){
			orMergeVectorFilter(abilityInclude, f.abilityInclude);
		}
		if (!f.noNameInclude.empty()){
			orMergeVectorFilter(noNameInclude, f.noNameInclude);
		}
		if (!f.noClubInclude.empty()){
			orMergeVectorFilter(noClubInclude, f.noClubInclude);
		}
		ageFilter.insert(ageFilter.end(), f.ageFilter.begin(), f.ageFilter.end());
		goalFilter.insert(goalFilter.end(), f.goalFilter.begin(), f.goalFilter.end());
		salaryFilter.insert(salaryFilter.end(), f.salaryFilter.begin(), f.salaryFilter.end());
		transFeeFilter.insert(transFeeFilter.end(), f.salaryFilter.begin(), f.salaryFilter.end());
		yearsFilter.insert(yearsFilter.end(), f.yearsFilter.begin(), f.yearsFilter.end());
	}
};

#endif