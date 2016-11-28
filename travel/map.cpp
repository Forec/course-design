#include "stdafx.h"

vehicle *allVehicles[100001];
heap_t<queNode,MAXLEN> heap;
struct ANS PERFECT;

void wmap::time_fresh(){
    time add = time(0,1);
    now = now.modPlus(add);
    std::ofstream fout("time",std::ios::out);
    fout << now.getMins();
    fout.close();
}

wmap::wmap(){
	cities = city::getCount();
	lines = vehicle::getCount();
	now = time(0, 0);
	for (int i = 0; i <= cities; i++){
		for (int j = 0; j <= cities; j++){
			world[i][j][0] = 0;
		}
	}
	for (int i = 0; i < lines; i++){
		int s = allVehicles[i]->getStartCity().getID();
		int e = allVehicles[i]->getDestCity().getID();
		world[s][e][0]++;
		world[s][e][world[s][e][0]] = i;
	}
	succ = false;
    hasPerf = false;
	totalCost =0;
	perfectLength = 0;
}

void wmap::generate_Minimal_cost(){
	for (int i = 0; i < cities; i++){
		for (int j = 0; j < cities; j++){
			if ( i == j){
				tempMap[i][j][0] = -1;
				tempMap[i][j][1] = 0;
				continue;
			}
            if (world[i][j][0] == 0){
				tempMap[i][j][0] = -1;
				tempMap[i][j][1] = inf;
			}
			else{
				int minimal = world[i][j][1];
				for (int k = 2; k <= world[i][j][0]; k++){
					if (allVehicles[world[i][j][k]]->getCost() < allVehicles[minimal]->getCost()){
						minimal = world[i][j][k];
					}
				}
				tempMap[i][j][0] = minimal;
				tempMap[i][j][1] = allVehicles[minimal]->getCost();
			}
		}
	}
}

void wmap::adjacent_Edge(city &s, time & t, float a, float b){
	int start= s.getID();
	for (int i = 0; i < cities; i++){
		if (world[start][i][0] == 0){
			tempMap[start][i][0] = -1;
			tempMap[start][i][1] = inf;
			continue;
		}
		int minimal = world[start][i][1];
		for ( int k = 2; k <= world[start][i][0]; k++){
			int p1 = int(allVehicles[world[start][i][k]]->getCost()*a+allVehicles[world[start][i][k]]->getWait_and_LastTime(t).getMins()*b);
			int p2 = int(allVehicles[minimal]->getCost()*a+allVehicles[minimal]->getWait_and_LastTime(t).getMins()*b);
			if ( p1 < p2 )
					minimal = world[start][i][k];
		}	
		tempMap[start][i][0] = minimal;
		tempMap[start][i][1] = int(allVehicles[minimal]->getCost()*a+allVehicles[minimal]->getWait_and_LastTime(t).getMins()*b);
	}
}

void wmap::spfa_last(city &s, city &e, time &t){
    tempStart = t;
	std::priority_queue<int> pq;
	succ = false;
	totalCost = 0;
	totalTime = 0;
	int dist[31], pre[31];
	bool used[31];
	int start = s.getID(), end = e.getID();
	for ( int i = 0 ; i < 31;i++){
		used[i] = false;
		dist[i] = inf;
		pre[i] = -1;
	}
	pq.push(start); used[start] = true; dist[start] = 0; pre[start] = start;
    time startT = t;
	while (!pq.empty()){
		int cur = pq.top();
		pq.pop();
		time Last= time(dist[cur]);
		time curT = startT.modPlus(Last);
		adjacent_Edge(*allCities[cur], curT);
		for ( int k = 0; k < cities; k++){
			if (dist[cur] + tempMap[cur][k][1] < dist[k]){
				dist[k] = dist[cur] + tempMap[cur][k][1];
				pre[k] = cur;
				if (!used[k]){
					pq.push(k);
					used[k] = true;
				}
			}
		}
	}
	if (dist[end] == inf){
		succ = false;
	} else{ 
		int pred = pre[end], cur = end;
		int roads[31], top = 0;
		time st = startT;
		while (pred != -1 && cur != start){
			roads[top++] = tempMap[pred][cur][0];
			totalCost += allVehicles[tempMap[pred][cur][0]]->getCost();
			cur = pred;
			pred = pre[pred];
		}
		for ( int k = top-1; k>=0;k--){
			totalTime += allVehicles[roads[k]]->getWait_and_LastTime(st).getMins();
			time tempT = time(allVehicles[roads[k]]->getWait_and_LastTime(st));
			st = st.modPlus(tempT);
		}
		for (int k = top - 1; k >= 0; k--)
			perfect[top -1 - k] = roads[k];
		perfectLength = top;
		succ = true;
	}
    hasPerf = succ;
}

void wmap::limit_time_cost(city & s, city & e, time &lim, time &t){
	bool flag = true;
    tempStart = t;
	float a = 0.0, b = 1.0;
	int start = s.getID(), end = e.getID();
	int limit_time = lim.getMins();
	totalTime = inf;
	totalCost = inf;
	succ = false;
	while (flag){
		std::priority_queue<int> pq;
		int dist[31], pre[31];
		bool used[31];
		for ( int i = 0 ; i < 31;i++){
			used[i] = false;
			dist[i] = inf;
			pre[i] = -1;
		}
		pq.push(start); used[start] = true; dist[start] = 0; pre[start] = start;
        time startT = t;
		while (!pq.empty()){
			int cur = pq.top();
			pq.pop();
			time Last= time(dist[cur]);
			time curT = startT.modPlus(Last);
			adjacent_Edge(*allCities[cur], curT, a, b);
			for ( int k = 0; k < cities; k++){
				if (dist[cur] + tempMap[cur][k][1] < dist[k]){
					dist[k] = dist[cur] + tempMap[cur][k][1];
					pre[k] = cur;
					if (!used[k]){
						pq.push(k);
						used[k] = true;
					}
				}
			}
		}
		if (dist[end] == inf){
			if (succ == true){
				break;
			}
			succ = false;
		} else{ 
			int pred = pre[end], cur = end;
			int roads[31], top = 0;
			long long total_time = 0;
			int total_cost = 0; 
			time st = startT;
			while (pred != -1 && cur != start){
				roads[top++] = tempMap[pred][cur][0];
				total_cost += allVehicles[tempMap[pred][cur][0]]->getCost();
				cur = pred;
				pred = pre[pred];
			}
			for ( int k = top-1; k>=0;k--){
				total_time += allVehicles[roads[k]]->getWait_and_LastTime(st).getMins();
				time tempT = time(allVehicles[roads[k]]->getWait_and_LastTime(st));
				st = st.modPlus(tempT);
			}
//			std::cout << "total_time is " << total_time << "  total_cost is " << total_cost <<std::endl;
			if (total_time > limit_time){
				if (succ== true)
					break;
				else
					flag = false;
			} else if (total_cost >= totalCost ){
                a += 0.01f;
                b -= 0.01f;
				if (a < -0.002 || b < -0.002)
					break;
				continue;
			}
			totalCost = total_cost;
			totalTime = total_time;
//			std::cout << "here refresh " << std::endl;
			for (int k = top - 1; k >= 0; k--)
				perfect[top -1 - k] = roads[k];
			perfectLength = top;
			succ = true;
		}
        a += 0.01f;
        b -= 0.01f;
		if (a < -0.002 || b < -0.002)
			break;
    }/*
	if (flag == false){
		std::cout << "Sorry not have filtered path, but we got some path take more time" << std::endl;
	}else{
		std::cout << "Found the best answer" << std::endl;
    }*/
    hasPerf = flag;
}

void wmap::dijkstra_cost(city &s, city &e, time &nowt){
	generate_Minimal_cost();
	//show_temp();
    tempStart = nowt;
	succ =false;
	totalCost= 0;
	totalTime = 0;
    time startT = nowt;
	int dist[31], pre[31];
	bool vis[31];
	int start = s.getID(), end = e.getID();
	for (int i = 0; i < cities; i++){
		dist[i] = inf;
		vis[i] = false;
		pre[i] = -1;
	}
	dist[start] = 0; pre[start] = start;
	for (int i = 1; i < cities; i++){
		int minimal = inf, minj = start;
		for (int j = 0; j < cities; j++)
			if (dist[j] < minimal && !vis[j]){
				minimal = dist[j];
				minj = j;
			}
		vis[minj] = true;
		for (int k = 0; k < cities; k++)
			if (dist[minj] + tempMap[minj][k][1] < dist[k]){
				dist[k] = tempMap[minj][k][1] + dist[minj];
				pre[k] = minj;
			}
	}
	if (dist[end] != inf){
		totalCost = dist[end];
		int pred = pre[end], cur = end;
		int roads[31], top = 0;
		time st = startT;
		while (pred != -1 && cur != start){
			roads[top++] = tempMap[pred][cur][0];
			cur = pred;
			pred = pre[pred];
		}
		for ( int k = top-1; k>=0;k--){
			totalTime += allVehicles[roads[k]]->getWait_and_LastTime(st).getMins();
			time tempT = time(allVehicles[roads[k]]->getWait_and_LastTime(st));
			st = st.modPlus(tempT);
		}
		for (int k = top - 1; k >= 0; k--)
			perfect[top -1 - k] = roads[k];
		perfectLength = top;
		succ = true;
	} else{
		succ = false;
	}
    hasPerf = succ;
}

void wmap::show_perfect(city &s,city&e){
	std::ofstream out("testout.txt");
	out << "At " << tempStart <<std::endl;
	out << "The perfect path is length " << perfectLength << std::endl; 
	out << "FROM " << s.name() <<" TO "  <<e.name()<<std::endl;
	if (succ == true){
		for (int i = 0; i < perfectLength; i++){
			out << (*allVehicles[perfect[i]]);
		}
		out << "Total cost : " << totalCost << std::endl;
		out << "Total time : " << totalTime << std::endl;
	}else{
		out << "fuck no path" << std::endl;
	}
	out.close();
}

void wmap::show_temp(){
	std::cout << "temp[0]:\n";
	for (int i = 0; i < cities;i++){
		for( int j = 0 ; j < cities;j++)
			std::cout<< tempMap[i][j][0] <<" ";
		std::cout<<std::endl;
	}
	
	std::cout << "temp[1]:\n";
	for (int i = 0; i < cities;i++){
		for( int j = 0 ; j < cities;j++)
			std::cout<< tempMap[i][j][1] <<" ";
		std::cout<<std::endl;
	}
}

void wmap::needed_cost(city &s, city &e, city * needs, int need_count){
	succ = false;
	generate_Minimal_cost();
	bool needed[MAXNN];
	totalCost = inf;
	memset(needed, false, sizeof(needed));
	for (int i = 0 ; i < need_count ;i++)
		needed[needs[i].getID()] = true;
	int i,j;
    queNode now;
    queNode head;
    head.x = s.getID();
    memset(head.used, false,sizeof(head.used));
    memset(head.path, 0, sizeof(head.path));
    head.used[head.x]=true;
    head.f = 0; head.cnt = 0; head.cost = 0;
    heap.push(head);
	while (!heap.empty()) {
        now = heap.pop();
//        std::cout << "pop " << now.x << std::endl;
        for (i=0;i<cities;i++) {
        	if (tempMap[now.x][i][0]==-1 || now.used[i] ||now.cost + tempMap[now.x][i][1] >= totalCost)
        		continue;
            queNode newn;
            bool found = true;
            newn.x = i;
            for (j=0;j<now.cnt;j++) {
                newn.path[j] = now.path[j];
            }
            newn.path[now.cnt] = tempMap[now.x][i][0];
            newn.cnt = now.cnt+1;
            for (j=0;j<=cities;j++) {
                newn.used[j] = now.used[j];
            }
            newn.used[newn.x] = true;
            newn.cost = now.cost + tempMap[now.x][i][1];
            if (needed[newn.x]) {
                newn.f = now.f - 2;
            }
            else {
                newn.f = now.f + 1;
            }           
			if (newn.x==e.getID()) {
                for (j = 0; j < cities; j++) {
                    if ((!newn.used[j]) && needed[j]) {
        				found = false;
        				break;
         			}
            	}
            	if (found && totalCost>newn.cost) {
            		succ = true;
                    perfectLength = newn.cnt;
                    totalCost = newn.cost;
                    for (j = 0; j < newn.cnt; j++) 
                        perfect[j] = newn.path[j];
                    hasPerf = true;
                    return;
        		}
        	}
        	else
                heap.push(newn);
        }
    }
    hasPerf = false;
}

void wmap::output(){
	PERFECT.cost = totalCost;
	PERFECT.used = time(totalTime);
	PERFECT.cur = tempStart;
	PERFECT.length = perfectLength;
	PERFECT.succ = succ;
	if (!succ)
		return;
	for ( int i =0 ; i < perfectLength; i++)
		PERFECT.path[i] = perfect[i];
}

time wmap::getTime(){
    return now;
}
