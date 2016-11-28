#pragma once

//#include "targetver.h"

#include <stdio.h>
//#include <tchar.h>


#define _PLANE 1
#define _BUS 2
#define _TRAIN 3
#define MAXNN 100
#define MAXLEN 10000 
#define INTERVAL 3000

#include "time.h"
#include "city.h"
#include "map.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <queue>
#include "vehicle.h"
#include "test.h"
#include "heap.h"
#include "user.h"


// For QT
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QListView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include "mainwindow.h"


class city;
class time;
class vehicle;
class userP;

const int inf = 0x03ffffff;
const int INF = 0x7fffffff;
const char _NAMES[4][7] = {"","Train", "Bus", "Flight"};

extern vehicle * allVehicles[100001];
extern city * allCities[31];
extern userP * allUsers[201];

struct queNode {
    int x;
    bool used[31];
    int cnt;
    int path[31];
    int f;
    int cost;
    bool operator<(const queNode &node) const {
    	if (f == node.f)
    		return cost < node.cost;
        return f > node.f;
    }
};

extern struct ANS{
	time cur;
	int path[31];
	int cost;
	int length;
	bool succ;
	time used;
}PERFECT;

extern heap_t<queNode,MAXLEN> heap;

extern wmap * MAP;
