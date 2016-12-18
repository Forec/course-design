// @author: Forec(王耀)
// @last-edit: 2016-11-4 
// @email: forec@bupt.edu.cn
// @codec: UTF-8
// @platform: GNU/Linux(Kernel 4.4.0)
// @g++ version: 5.4
// @filename: main.cpp
// this file is part of the homework for Operating System
// PRODUCER AND CONSUMER PROBLEM
// Compile: g++ main.cpp -pthread -o t
// Usage: ./t <producer count> <consumer count> <sleep time>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "buffer.h"

void *producer(void *Param){
	BUFFER_ITEM rand_item;
	while (true){
		usleep( int(1000000 * float(rand()) / RAND_MAX));
		rand_item = rand();
		printf("producer produced %d\n", rand_item);
		if (insert_item(rand_item)){
			fprintf(stderr, "producer report error condition");
		}
	}
	pthread_exit(0);
}

void *consumer(void *Param){
	BUFFER_ITEM rand_item;
	while (true){
		usleep( int(1000000 * float(rand()) / RAND_MAX));
		if (remove_item(&rand_item)){
			fprintf(stderr, "consumer report error condition");
		} else {
			printf("consumer consumed %d\n", rand_item);
		}
	}
	pthread_exit(0);
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
	
	pthread_attr_t attrs[PRODUCER_SIZE + CONSUMER_SIZE];
	pthread_t tids[PRODUCER_SIZE + CONSUMER_SIZE];
	
	// initialize the mutex, semaphores and buffer
	initialize();
	
	// create producer threads
	for (int i = 0; i < PRODUCER_SIZE; i++){
		pthread_attr_init(&attrs[i]);
		pthread_create(&tids[i], &attrs[i], producer, NULL);
	}
	
	// create consumer threads
	for (int i = PRODUCER_SIZE; i < PRODUCER_SIZE + CONSUMER_SIZE; i++){
		pthread_attr_init(&attrs[i]);
		pthread_create(&tids[i], &attrs[i], consumer, NULL);
	}
	// sleep SLEEP_PERIOD seconds and then terminate
	usleep( 1000000 * SLEEP_PERIOD );
	return 0;
}
