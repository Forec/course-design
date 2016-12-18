// @author: Forec(王耀)
// @last-edit: 2016-11-4 
// @email: forec@bupt.edu.cn
// @codec: UTF-8
// @platform: GNU/Linux(kernel 4.4.0)
// @g++ version: 5.4
// @filename: buffer.h
// this file is part of the homework for Operating System
// PRODUCER AND CONSUMER PROBLEM
// Compile: g++ main.cpp -pthread -o t
// Usage: ./t <producer count> <consumer count> <sleep time>

#include <pthread.h>
#include <semaphore.h>

#define BUFFER_NIL 0
#define BUFFER_SIZE 10
typedef int BUFFER_ITEM;

static struct {
	BUFFER_ITEM buffer[BUFFER_SIZE];
	int top;
	int count;
} buffers;

// @Mutex: mutex for locking operations on top, count
// @Empty: semaphore for producers, intialized to 0, maximum BUFFER_SIZE
// @Full: semaphore for consumers, intialized to BUFFER_SIZE, maximum BUFFER_SIZE
pthread_mutex_t Mutex;
sem_t Empty, Full;

// insert a BUFFER_ITEM object into buffer
int insert_item(BUFFER_ITEM item){
	sem_wait(&Empty);
	pthread_mutex_lock(&Mutex);
	if ( buffers.count >= BUFFER_SIZE ){
		pthread_mutex_unlock(&Mutex);
		return -1;
	}
	buffers.buffer[ buffers.top ] = item;
	buffers.top = (buffers.top + 1) % BUFFER_SIZE;
	buffers.count++;
	pthread_mutex_unlock(&Mutex);
	sem_post(&Full);
	return 0;
}

// remove a BUFFER_ITEM object from buffer
int remove_item(BUFFER_ITEM *item){
	sem_wait(&Full);
	pthread_mutex_lock(&Mutex);
	if ( buffers.count <= 0 ){
		pthread_mutex_unlock(&Mutex);
		return -1;
	}
	buffers.count--;
	buffers.top = (buffers.top - 1) % BUFFER_SIZE;
	*item = buffers.buffer[buffers.top];
	pthread_mutex_unlock(&Mutex);
	sem_post(&Empty);
	return 0;
}

// initialize the buffer, mutex and semaphores
void initialize(){
	pthread_mutex_init(&Mutex, NULL);
	sem_init(&Full, BUFFER_SIZE, 0);
	sem_init(&Empty, BUFFER_SIZE, BUFFER_SIZE);
	for (int i = 0; i < BUFFER_SIZE; i++){
		buffers.buffer[i] = BUFFER_NIL;
	}
	buffers.count = 0;
	buffers.top = 0;
}
