/*
author: Forec
last edit date: 2017/01/10
email: forec@bupt.edu.cn
LICENSE
Copyright (c) 2015-2017, Forec <forec@bupt.edu.cn>

Permission to use, copy, modify, and/or distribute this code for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include "base.hpp"

struct Param{
	int* num_waiting_north;
	int* num_waiting_south;
	HANDLE *mutex_south, *mutex_north;
	HANDLE *bridge, *north_entry, *south_entry;
	int param_number;
};

DWORD WINAPI single_thread1(LPVOID param){
	Param p = *(Param*) param;
    WaitForSingleObject(*(p.mutex_north), INFINITE);
    (*(p.num_waiting_north)) ++;
    ReleaseMutex(*(p.mutex_north));
	WaitForSingleObject(*(p.north_entry), INFINITE);
    WaitForSingleObject(*(p.bridge), INFINITE);
    Sleep(1000);	// 1 秒钟过桥  
    WaitForSingleObject(*(p.mutex_north), INFINITE);
    (*(p.num_waiting_north)) --;
    ReleaseMutex(*(p.mutex_north));
    printf("北方居民 %d 已经过桥，当前北方等待人数 %d，南方等待人数 %d\n", 
	    p.param_number, *(p.num_waiting_north), *(p.num_waiting_south));
    WaitForSingleObject(*(p.mutex_south), INFINITE);
    if (*(p.num_waiting_south) == 0)   
        ReleaseSemaphore(*(p.north_entry), 1, NULL);
    else
        ReleaseSemaphore(*(p.south_entry), 1, NULL);      
    ReleaseMutex(*(p.mutex_south));   
    ReleaseSemaphore(*(p.bridge), 1, NULL);
}

DWORD WINAPI single_thread2(LPVOID param){
	Param p = *(Param*) param;
    WaitForSingleObject(*(p.mutex_south), INFINITE);
    (*(p.num_waiting_south)) ++;
    ReleaseMutex(*(p.mutex_south));
	WaitForSingleObject(*(p.south_entry), INFINITE);
    WaitForSingleObject(*(p.bridge), INFINITE);
    Sleep(1000);	// 1 秒钟过桥 
    WaitForSingleObject(*(p.mutex_south), INFINITE);
    (*(p.num_waiting_south)) --;
    ReleaseMutex(*(p.mutex_south));
    printf("南方居民 %d 已经过桥，当前北方等待人数 %d，南方等待人数 %d\n", 
	    p.param_number, *(p.num_waiting_north), *(p.num_waiting_south));
    WaitForSingleObject(*(p.mutex_north), INFINITE);
    if (*(p.num_waiting_north) == 0)   
        ReleaseSemaphore(*(p.south_entry), 1, NULL);
    else
        ReleaseSemaphore(*(p.north_entry), 1, NULL);      
    ReleaseMutex(*(p.mutex_north));   
    ReleaseSemaphore(*(p.bridge), 1, NULL);
}

class Bridge1: public WorkStation{
private:
	int num_waiting_north;
	int num_waiting_south;
	HANDLE mutex_south, mutex_north;
	HANDLE bridge, north_entry, south_entry;
	void * getParam(int index){
		Param *p = new Param;
		p->num_waiting_north = &num_waiting_north;
		p->num_waiting_south = &num_waiting_south;
		p->mutex_north = &mutex_north;
		p->mutex_south = &mutex_south;
		p->bridge = &bridge;
		p->north_entry = &north_entry;
		p->south_entry = &south_entry;
		p->param_number = index;
		return (void*)p;
	}
public:	
	void init(){
    	thread_type = 2;
		_threads[0] = single_thread1;
		_threads[1] = single_thread2;
		num_waiting_north = 0;
		num_waiting_south = 0;
		mutex_south = CreateMutex(NULL, FALSE, NULL);
		mutex_north = CreateMutex(NULL, FALSE, NULL);
		bridge = CreateSemaphore(NULL, 1, 1, NULL);
		north_entry = CreateSemaphore(NULL, 1, 1, NULL);
		south_entry = CreateSemaphore(NULL, 1, 1, NULL);
	}
};

int main(){
	Bridge1 b = Bridge1();
	b.init();
	b.simulate(10, 60);
}
