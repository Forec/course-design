#ifndef _MAP_H_
#define _MAP_H_

#include "stdafx.h"

class wmap{
private:
	int cities;
    int lines;
    bool hasPerf;
    time now;
	int world[31][31][201];
    int tempMap[31][31][2];
public:
    wmap();
    int totalCost;
    int totalTime;
    time tempStart;
    int perfect[30];
    int perfectLength;
    bool succ;
	void generate_Minimal_cost();
	void show_temp(); 
	void time_fresh();
    void setLine(bool t){hasPerf = t;}
    bool getPerValid(){return hasPerf;}
    void spfa_last(city &, city&, time&t);
	void adjacent_Edge(city &, time&, float a = 0.0, float b = 1.0);
    void limit_time_cost(city &, city & , time&,time &);
    void dijkstra_cost(city&, city&, time&);
	void needed_cost(city&, city &, city *, int);
    void setTime(int t){now.set(t/60, t%60);}
    void show_perfect(city &,city&);
	void output();
    time getTime();
};

#endif
