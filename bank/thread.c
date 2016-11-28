#include <stdio.h>

#include <conio.h>

#include <windows.h>

#include <process.h>

#include <time.h>

#include "Format.h"

#include <direct.h>

#include"process.h"

//CRITICAL_SECTION Lock;


unsigned int __stdcall Voice(void *pPM)
{
	struct BANK *temp = (struct BANK *)pPM;
	char buf[101];
	getcwd(buf,sizeof(buf));
	char order1[101];
	sprintf(order1,"cd %s",buf);
	while (temp->Current_Statu != CLOSE){
		WaitForSingleObject(voice_signal,INFINITE);
		system(order1);
		system("voice.vbs");
	//	spawnl(P_WAIT,"/s voice.vbs",NULL);
	}
	return 0;
}

extern unsigned int __stdcall REFRE(void *pPM){

	thread_flag = 1;
	vip_flag = 1;
//	EnterCriticalSection(&Lock);
	signal = CreateEvent(NULL,FALSE,FALSE,NULL);
	vip_signal = CreateEvent(NULL,FALSE,FALSE,NULL);
	struct BANK * temp = (struct BANK *)pPM;
	CASE_VIP(temp);
	thread_flag = 0;
	PulseEvent(signal);
	PulseEvent(vip_signal);
	PulseEvent(signal);
	PulseEvent(vip_signal);
//	LeaveCriticalSection(&Lock);
	return 0;
}
/*
unsigned int __stdcall sINPUT(void *pPM){

	void CASE(char , struct BANK *);
	struct BANK *temp = ( struct BANK * ) pPM;
	while (1){
		if ( thread_flag == 1 ){
			WaitForSingleObject(signal,INFINITE);
			thread_flag = 0;
			fflush(stdin);
		}
		char c = getch();
		CASE( c , temp );
	}
	return 0;
}*/
/*
unsigned int __stdcall TIMEP(void *pPM){
	struct BANK *temp = ( struct BANK * )pPM;
	while (1){
		InterlockedIncrement((LPLONG)&(temp->Time));
		clock_t start = clock();
	 	while ((double)(clock() - start)/CLOCKS_PER_SEC < 1);
	 	if ( vip_flag == 1 ){
	 		WaitForSingleObject(vip_signal,INFINITE);
	 		vip_flag = 0;
	 	}
	 	REFRESH(temp);
	}
}
*//*
unsigned int __stdcall OUTPUT(void *pPM){
//	struct BANK *temp = ( struct BANK * )pPM;
//	Graph(temp);
	return 0;
}*/


void MAIN_THREAD(struct BANK *Bank)
{
//	InitializeCriticalSection(&Lock);
//	SetCriticalSectionSpinCount(&Lock,1000);
//	HANDLE handle1 = (HANDLE)_beginthreadex(NULL,0,OUTPUT,Bank,0,NULL);
//	HANDLE handle2 = (HANDLE)_beginthreadex(NULL,0,sINPUT,Bank,0,NULL);
//	HANDLE handle3 = (HANDLE)_beginthreadex(NULL,0,TIMEP,Bank,0,NULL);
	HANDLE handle4 = (HANDLE)_beginthreadex(NULL,0,Voice,Bank,0,NULL);
	voice_signal = CreateEvent(NULL,FALSE,FALSE,NULL);
	graph(Bank);
//	WaitForSingleObject(handle2,INFINITE);
//	WaitForSingleObject(handle3,INFINITE);
	WaitForSingleObject(handle4,INFINITE);
	CloseHandle(signal);
	CloseHandle(voice_signal);
//	CloseHandle(handle1);
//	CloseHandle(handle2);
//	CloseHandle(handle3);
	CloseHandle(handle4);
//	DeleteCriticalSection(&Lock);
}
