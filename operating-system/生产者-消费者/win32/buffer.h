// @author: Forec(王耀)
// @last-edit: 2016-11-4 
// @email: forec@bupt.edu.cn
// @codec: UTF-8
// @platform: Windows 10
// @g++ version: MinGW x86_64 5.3.0
// @filename: buffer.h
// this file is part of the homework for Operating System
// PRODUCER AND CONSUMER PROBLEM
// Compile: g++ main.cpp -pthread -o t
// Usage: t.exe <producer count> <consumer count> <sleep time>

#include <windows.h>

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
HANDLE Mutex, Empty, Full;

// insert a BUFFER_ITEM object into buffer
int insert_item(BUFFER_ITEM item){
	WaitForSingleObject(Empty, INFINITE);
	WaitForSingleObject(Mutex, INFINITE);
	if ( buffers.count >= BUFFER_SIZE ){
		ReleaseMutex(Mutex);
		return -1;
	}
	buffers.buffer[ buffers.top ] = item;
	buffers.top = (buffers.top + 1) % BUFFER_SIZE;
	buffers.count++;
	ReleaseMutex(Mutex);
	ReleaseSemaphore(Full, 1, NULL);
	return 0;
}

// remove a BUFFER_ITEM object from buffer
int remove_item(BUFFER_ITEM *item){
	WaitForSingleObject(Full, INFINITE);
	WaitForSingleObject(Mutex, INFINITE);
	if ( buffers.count <= 0 ){
		ReleaseMutex(Mutex);
		return -1;
	}
	buffers.count--;
	buffers.top = (buffers.top - 1) % BUFFER_SIZE;
	*item = buffers.buffer[buffers.top];
	ReleaseMutex(Mutex);
	ReleaseSemaphore(Empty, 1, NULL);
	return 0;
}

// initialize the buffer, mutex and semaphores
void initialize(){
	Mutex = CreateMutex(NULL, false, NULL);
	Empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
	Full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
	for (int i = 0; i < BUFFER_SIZE; i++){
		buffers.buffer[i] = BUFFER_NIL;
	}
	buffers.count = 0;
	buffers.top = 0;
}
