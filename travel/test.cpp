#include "stdafx.h"

using namespace std;

wmap * MAP;

void loadUsers(){
    userP *u1 = new userP("forec", "12345", false , *allCities[1]);
    userP *root = new userP("root","",true, *allCities[0]);
}

void _log(const std::string &s){
    ofstream fout("oper.log",ios::app);
    fout << s << std::endl;
    fout.close();
}

void readTime(){
    ifstream fin("time");
    int tims;
    fin >> tims;
    fin.close();
    MAP->setTime(tims);
}

void init(){
	readData();
    loadUsers();
    //readPos();
    cout << "Read " << city::getCount() << " cities and " << vehicle::getCount() << " vehicles..." << endl;
    MAP = new wmap;
    cout << "Load map ready..."<<endl;
    readTime();
}

void simple_test(){
	string city_names[11] = { "Beijing", "shanghai", "hongkong", "nanJING", "tianjin", "dalian", "shenzhen", "guangzhou" };
	string vehicle_names[6] = {"K1503","GB1923", "GOQ923", "T12","Z094","K1234"};
	for (int i = 0; i < 8; i++)
		new city(city_names[i]);
	int a1 = _TRAIN, a2 = _BUS, a3 = _PLANE;
	new vehicle(vehicle_names[0],a1, 10, time(10, 30), time(2, 30), *allCities[0], *allCities[2]);
	new vehicle(vehicle_names[1],a2, 20, time(11, 0), time(3, 20), *allCities[0], *allCities[2]);
	new vehicle(vehicle_names[2],a1, 20, time(12, 30), time(5, 00), *allCities[2], *allCities[4]);
	new vehicle(vehicle_names[3],a3, 50, time(2, 0), time(1, 30), *allCities[4], *allCities[5]);
	new vehicle(vehicle_names[4],a1, 10, time(3, 10), time(0, 10), *allCities[4], *allCities[3]);
	new vehicle(vehicle_names[5],a1, 10, time(7, 30), time(7, 50), *allCities[3], *allCities[5]);
//	run_test_last();
}

void output_cities(){
	ofstream out("testouttemp.txt");
	for(int i = 0 ; i < city::getCount();i++)
		out << allCities[i]->getID() << " "<<*allCities[i] << endl;
	out.close();
}

void run_test_cost(){
	time t(0,0);
	MAP->dijkstra_cost(*allCities[1], *allCities[8],t);
	MAP->show_perfect(*allCities[1],*allCities[8]);
}

void run_test_last(){
	time t = time(0,0);
	MAP->spfa_last(*allCities[1], *allCities[8], t);
	MAP->show_perfect(*allCities[1],*allCities[8]);
}

void readData(){
    ifstream cinnt("randomData.txt");
	city *t1, *t2;
	vehicle * check;
	string name, startCity, endCity;
    int classify, cost, startTime, lastTime;
    for ( int i = 0; i < 100000;i++){
		t1 = NULL;
        t2 = NULL;
        cinnt >> classify >> name >> startCity >> endCity >> startTime >> lastTime>>cost;
     //   cout << classify << name << startCity << endCity << startTime << lastTime << cost<<endl;
		for ( int j = 0 ; j < city::getCount();j++){
			if (allCities[j]->name() == startCity)
				t1 = allCities[j];
			if (allCities[j]->name() == endCity)
				t2 = allCities[j];
		}
		if (t1==NULL){
		 	t1 = new city(startCity);
   //         cout << *t1<<std::endl;
		 }
		if (t2 ==NULL){
			t2 = new city(endCity);
  //          cout << *t2 << std::endl;
		}
		check = new vehicle(name,classify,cost,startTime,lastTime,*t1,*t2);	
	}
    cinnt.close();
}

void run_test_need(){
	city needed[9] = {*allCities[10], *allCities[2],*allCities[11],*allCities[21], *allCities[24],
        *allCities[14], *allCities[25], *allCities[6], *allCities[29]};
	MAP->needed_cost(*allCities[3], *allCities[7], needed, 9);
    MAP->show_perfect(*allCities[3],*allCities[7]);
}

void run_test_limit(){
	time t = time(0,0);
    time lim = time(2000);
	MAP->limit_time_cost(*allCities[1], *allCities[8], t, lim);
    MAP->show_perfect(*allCities[1],*allCities[8]);
}

city* searchCity(std::string name){
    for (int i = 0 ; i < city::getCount(); i++)
        if (allCities[i]->name() == name)
            return allCities[i];
    return NULL;
}

void readPos(){
    fstream cint("pos.txt");
    string name;
    int x,y;
    for(int i = 0;i < 30;i++){
        cint>>name >> x >>y;
    //    cout << name << x << y;
        for (int j = 0; j < city::getCount();j++){
            if (allCities[j]->name() == name){
                allCities[j]->setXY(x,y);
                break;
            }
        }
    }
    cint.close();
}
