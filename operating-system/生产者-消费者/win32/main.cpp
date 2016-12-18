// @author: Forec(王耀)
// @last-edit: 2016-11-4 
// @email: forec@bupt.edu.cn
// @codec: UTF-8
// @platform: Windows 10
// @g++ version: MinGW x86_64 5.3.0
// @filename: main.cpp
// this file is part of the homework for Operating System
// PRODUCER AND CONSUMER PROBLEM
// Compile: g++ main.cpp -pthread -o t
// Usage: t.exe <producer count> <consumer count> <sleep time>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "buffer.h"

DWORD WINAPI producer(LPVOID Param){
	BUFFER_ITEM rand_item;
	while (true){
		Sleep(int(1000 * (float(rand()) / RAND_MAX)));
		rand_item = rand();
		printf("producer produced %d\n", rand_item);
		if (insert_item(rand_item)){
			fprintf(stderr, "producer report error condition");
		}
	}
}

DWORD WINAPI consumer(LPVOID Param){
	BUFFER_ITEM rand_item;
	while (true){
		Sleep(int(1000 * (float(rand()) / RAND_MAX)));
		if (remove_item(&rand_item)){
			fprintf(stderr, "consumer report error condition");
		} else {
			printf("consumer consumed %d\n", rand_item);
		}
	}
}

int main(int argc, char *argv[]){
	// args: argv[1] = PRODUCER_SIZE; 
	// argv[2] = CONSUMER_SIZE;
	// argv[3] = SLEEP_PERIOD
	// argv[3] unit: second
	
	unsigned int PRODUCER_SIZE, CONSUMER_SIZE, SLEEP_PERIOD;
	
	// check parameters
	if (argc != 4){
		fprintf(stderr, "Three integer parameters are required(producers, consumers and sleep time)\n");
		return -1;
	}
	PRODUCER_SIZE = atoi(argv[1]);
	CONSUMER_SIZE = atoi(argv[2]);
	SLEEP_PERIOD = atoi(argv[3]);
	if (PRODUCER_SIZE < 0 || CONSUMER_SIZE < 0 || SLEEP_PERIOD < 0){
		fprintf(stderr, "Three integers >= 0 are required\n");
		return -1;
	}
	
	HANDLE ThreadHandle[PRODUCER_SIZE + CONSUMER_SIZE];
	DWORD ThreadId[PRODUCER_SIZE + CONSUMER_SIZE];
	
	// initialize the mutex, semaphores and buffer
	initialize();
	
	srand(time(NULL));
	
	// create producer threads
	for (int i = 0; i < PRODUCER_SIZE; i++){
		ThreadHandle[i] = CreateThread(
			NULL,
			0,
			producer,
			NULL,
			0,
			&ThreadId[i]
		);
	}
	
	// create consumer threads
	for (int i = PRODUCER_SIZE; i < PRODUCER_SIZE + CONSUMER_SIZE; i++){
		ThreadHandle[i] = CreateThread(
			NULL,
			0,
			consumer,
			NULL,
			0,
			&ThreadId[i]
		);
	}
	// sleep SLEEP_PERIOD seconds and then terminate
	Sleep( SLEEP_PERIOD * 1000 );
	return 0;
}
