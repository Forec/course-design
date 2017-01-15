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

#ifndef __BRIDGE_ALGO_H
#define __BRIDGE_ALGO_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define random(x) (rand()%x)

class WorkStation{
protected:
	DWORD WINAPI (*_threads[10])(LPVOID);
	int thread_type;
public:
	WorkStation(){ 
		thread_type = 0;
    }
	virtual void init() = 0;
	virtual void* getParam(int) = 0;
	void simulate(int count, int interval){
		srand( (int)time(NULL) );
		int length = count * thread_type;
		int *sort = new int[length];
		for (int i = 0; i < length; i++)
			sort[i] = i;
		int tmpLength = length;
		for (int i = 0; i < length; i++){
			int k = random(tmpLength)+1;
			int temp = sort[k-1];
			sort[k-1] = sort[tmpLength-1];
			sort[tmpLength-1] = temp;
			tmpLength --;
		}	// 生成随机序列 
		DWORD *thread_ids = new DWORD[length];
		HANDLE *threads = new HANDLE[length];
		for (int i = 0; i < length; i++){
			int index = sort[i];
			int j = index/count;
			threads[i] = CreateThread(
			    NULL,
			    0,
			    (*WorkStation::_threads[j]),
			    getParam(index),
			    0,
			    &thread_ids[i]);
			if (threads[i] == NULL){
				printf("Error happens when creating thread %d of type %d", index+1, j+1);
				return;
		    }
	    }
	    Sleep(interval * 1000);
	    for (int i = 0; i < length; i++){
	    	CloseHandle(threads[i]);
	    	printf("Thread %d of type %d has exited", sort[i]+1, sort[i]/count + 1);
	    }
	}
};

#endif
