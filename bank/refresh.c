#include <malloc.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "Format.h"
#include <egg.h>

char WINDOW_STATU_PRINT[4][11]={"WAITING","DEALING","PAUSE","OUT"};
char GUEST_TYPE_PRINT[2][4]={"VIP","NOR"};
char BANK_STATU_PRINT[3][5]={"OPEN","CLOSE","LAST"};
char WORK_TYPE_PRINT[6][11]={"WDRAW","SAVE","ADDUSR","LOGOUT","STOCK","NONE"};

/*
void STATU_PRINT(struct BANK Bank){
    SetActiveEgg(TIME);
    EatEgg();
    TIME = LayEgg();
	void BANK_MAINTAIN_ALL(struct BANK);
	void BANK_MAINTAIN_PER_SEC(struct BANK,int,int,int);
	char *NUM_TO_STRING( int , enum GUEST_TYPE );
	char *GET_TIME( int , int , int );
	int sec = Bank.Time % 60;
	int hour = Bank.Time / 3600;
	int min = ( Bank.Time - hour * 3600 - sec ) / 60;
	char temp[101];
	sprintf(temp,"Time : %s\n" , GET_TIME(sec,min,hour) );
	MovePen(1000,500);
	DrawString(temp);
	if ( Bank.Current_Statu == CLOSE){
		BANK_MAINTAIN_ALL(Bank);
		exit(0);
	}
	BANK_MAINTAIN_PER_SEC(Bank,hour,min,sec);

}
*/
char *GET_TIME(struct BANK Bank){
    int secd = Bank.Time % 60;
	int hourd = Bank.Time / 3600;
	int mind= ( Bank.Time - hourd * 3600 - secd ) / 60;
	char sec[3],hour[3],min[3];
	sec[0] = secd / 10 + '0' ; sec[1] = secd % 10 + '0' ;sec[2] = '\0';
	hour[0] = hourd / 10 + '0' ; hour[1] = hourd % 10 + '0' ;hour[2] = '\0';
	min[0] = mind / 10 + '0' ; min[1] = mind % 10 + '0';min[2] = '\0';
	char *time = (char *) malloc ( 31 * sizeof ( char ) );
	sprintf( time , "TIME : %s : %s : %s", hour , min , sec );
	return time;
}

char *NUM_TO_STRING(int num,enum GUEST_TYPE guest){		// int.toString

	char *s = (char *) malloc ( 4 * sizeof(char) );
	s[2] = num % 10 + '0';
	s[1] = ( num % 100 ) / 10 + '0';
	if (guest == NOR)
		s[0] = num / 100 + '0';
	else
		s[0] = 'V';
	s[3]='\0';
	return s;

}

void BANK_MAINTAIN_PER_SEC(struct BANK Bank){
	FILE *out = fopen ( "Maintain_Per_Sec.dat", "a" );
	fprintf(out,"Time:%s  MAX_NOR:%s MAX_VIP:%s ",GET_TIME(Bank),NUM_TO_STRING(Bank.Customer.NOR_Len,NOR),NUM_TO_STRING(Bank.Customer.VIP_Len,VIP));
	int i;
	for ( i = 1 ; i <= 8 ; i++){
		fprintf(out,"Win%d-%s",i,WINDOW_STATU_PRINT[Bank.Desk.wins[i].statu]);
		if (Bank.Desk.wins[i].statu == DEALING)
			fprintf(out,"-%s",Bank.Desk.wins[i].type == VIP ?NUM_TO_STRING(Bank.Desk.wins[i].now,VIP):NUM_TO_STRING(Bank.Desk.wins[i].now,NOR));
		fprintf(out," ");
	}
	fprintf(out,"%s",Bank.Current_Statu != OPEN ? "Y":"N");
	fprintf(out,"\n");
	fclose(out);
	return;
}

void BANK_MAINTAIN_ALL(struct BANK Bank){
	FILE *out = fopen ( "Maintain_All.dat","w");
	fprintf(out,"Total_normal_guests: %d\n",Bank.Customer.NOR_Len);
	fprintf(out,"Total_vip_guests: %d\n\n",Bank.Customer.VIP_Len);
	int i;
	for ( i = 1 ; i <= 8 ; i++){
		fprintf(out,"Win%d : Total_guests:%d  ",i,Bank.Desk.wins[i].nor_count+Bank.Desk.wins[i].vip_count);
		fprintf(out,"Total_time:%d  ",Bank.Desk.wins[i].time_used);
		if (Bank.Desk.wins[i].nor_count+Bank.Desk.wins[i].vip_count == 0)
			fprintf(out,"Average_time:%d\n",0);
		else
			fprintf(out,"Average_time:%d\n",Bank.Desk.wins[i].time_used/(Bank.Desk.wins[i].nor_count+Bank.Desk.wins[i].vip_count));
	}
	fclose(out);
}

int CUSTOMER_COMING(struct BANK *Bank,enum GUEST_TYPE guest){	// return the task statu

	if (Bank->Current_Statu == LAST || Bank->Current_Statu == CLOSE)
		return FALSE;
	struct HAND *newg;
	newg = (struct HAND *)malloc(sizeof(struct HAND));
	if ( guest == NOR )
		newg->number = ++Bank->Customer.NOR_Len;
	else
		newg->number = ++Bank->Customer.VIP_Len;
//	MakeWelcome(newg->number,guest);
//	Voice();
	srand((unsigned)newg->number);
	rand();
	newg->work = (1+(int)(5.0*rand()/(RAND_MAX+1.0))) % 5;
	newg->time = ((1+(int)(100.0*rand()/(RAND_MAX+1.0))) % ( Bank->Announce.MaxSec - Bank->Announce.MinSec )) + Bank->Announce.MinSec;
	newg->type = guest;
	newg->next = NULL;
	if (guest == NOR){
		if (Bank->Customer.NOR_Last == NULL || Bank->Customer.NOR_Line == NULL ){
			Bank->Customer.NOR_Last = newg;
			Bank->Customer.NOR_Line = newg;
		}
		else {
			Bank->Customer.NOR_Last->next = newg;
			Bank->Customer.NOR_Last = newg;
		}
		text[3].NeedF = 1;
	}
	else {
		if (Bank->Customer.VIP_Last == NULL || Bank->Customer.VIP_Line == NULL ){
			Bank->Customer.VIP_Last = newg;
			Bank->Customer.VIP_Line = newg;
		}
		else {
			Bank->Customer.VIP_Last->next = newg;
			Bank->Customer.VIP_Last = newg;
		}
		text[4].NeedF = 1;
	}
	return TRUE;
}

void REFRESH(struct BANK *Bank){

//	void CHECK_LEN(struct BANK *);
//	void CHECK_WINDOW_TYPE(struct BANK *);
	void RELEX_WINDOW(struct BANK *);
//	void CASE(char,struct BANK*);

	if ( Bank->Current_Statu == CLOSE )
		return;

	CHECK_LEN(Bank);
    if (choose == 1)
        CHECK_WINDOW_TYPE(Bank);
 //   else
 //       part_check(Bank);
	int Close_flag = 0;

	int i;
	for ( i = 1 ; i <= 8 ; i ++ ){
		if ( Bank->Desk.wins[i].type == NOR){
			if ( Bank->Desk.wins[i].statu == DEALING && Bank->Desk.wins[i].pause_start_time == Bank->Time ){
				Bank->Desk.wins[i].statu = PAUSE;
				Bank->Desk.wins[i].pause_start_time = -1;
				windows[i][1] = 1;
			}
			if ( Bank->Desk.wins[i].statu == PAUSE && Bank->Desk.wins[i].pause_end_time == Bank->Time ){
				Bank->Desk.wins[i].statu = WAITING;
				Bank->Desk.wins[i].pause_end_time = -1;
				windows[i][1] = 1;
			}
			if ( Bank->Desk.wins[i].statu == DEALING ){
                Close_flag = 1;
				Bank->Desk.wins[i].time_used++;
                if ( Bank->Desk.wins[i].end_time == Bank->Time ){
					Bank->Desk.wins[i].statu = WAITING;
					windows[i][1] = 1;
                }
			}
			if ( Bank->Desk.wins[i].statu == WAITING ){
				if ( Bank->Customer.NOR_Line != NULL ){
					Bank->Desk.wins[i].statu = DEALING;
					Bank->Customer.NOR_DEALED++;
					windows[i][1] = 1;
					Bank->Desk.wins[i].now = Bank->Customer.NOR_Line->number;
					MakeNext(Bank->Desk.wins[i].now,i,NOR);
		//			voice_signal = CreateEvent(NULL,FALSE,FALSE,NULL);
					PulseEvent(voice_signal);
		//			CloseHandle(voice_signal);
					Bank->Desk.wins[i].nor_count++;
					Bank->Desk.wins[i].end_time = Bank->Time + Bank->Customer.NOR_Line->time;
					Bank->Desk.wins[i].work = Bank->Customer.NOR_Line->work;
					struct HAND *temp = Bank->Customer.NOR_Line;
					Bank->Customer.NOR_Line = Bank->Customer.NOR_Line->next;
					text[1].NeedF = 1;
					text[2].NeedF = 1;
					free(temp);
				}
			}
		}

		else {
			if ( Bank->Desk.wins[i].statu == DEALING && Bank->Desk.wins[i].pause_start_time == Bank->Time ){
				Bank->Desk.wins[i].statu = PAUSE;
				Bank->Desk.wins[i].pause_start_time = -1;
				windows[i][1] = 1;
			}
			if ( Bank->Desk.wins[i].statu == PAUSE && Bank->Desk.wins[i].pause_end_time == Bank->Time ){
				Bank->Desk.wins[i].statu = WAITING;
				Bank->Desk.wins[i].pause_end_time = -1;
				windows[i][1] = 1;
			}
			if ( Bank->Desk.wins[i].statu == DEALING ){
                Close_flag = 1;
				Bank->Desk.wins[i].time_used++;
				if ( Bank->Desk.wins[i].end_time == Bank->Time ){
					Bank->Desk.wins[i].statu = WAITING;
					windows[i][1] = 1;
				}
			}
			if ( Bank->Desk.wins[i].statu == WAITING ){
				if ( Bank->Customer.VIP_Line != NULL ){
					Bank->Desk.wins[i].statu = DEALING;
					Bank->Customer.VIP_DEALED++;
					windows[i][1] = 1;
					Bank->Desk.wins[i].now = Bank->Customer.VIP_Line->number;
					MakeNext(Bank->Desk.wins[i].now,i,VIP);
		//			voice_signal = CreateEvent(NULL,FALSE,FALSE,NULL);
					PulseEvent(voice_signal);
			//		CloseHandle(voice_signal);
					Bank->Desk.wins[i].work = Bank->Customer.VIP_Line->work;
					Bank->Desk.wins[i].vip_count++;
					Bank->Desk.wins[i].end_time = Bank->Time + Bank->Customer.VIP_Line->time;
					struct HAND *temp = Bank->Customer.VIP_Line;
					Bank->Customer.VIP_Line = Bank->Customer.VIP_Line->next;
					text[3].NeedF = 1;
					text[4].NeedF = 1;
					free(temp);
				}
			}
		}
	}

	if ( Bank->Customer.VIP_Line ==NULL && Bank->Customer.NOR_Line  == NULL && Close_flag == 0 && Bank->Current_Statu == LAST ){
        text[0].NeedF = 1;
		Bank->Current_Statu = CLOSE;
	}
	return ;
}

void part_check(struct BANK *Bank){
    int i;
    for ( i = 7 ; i < 7 + Bank->Desk.VIP_open ; i++ )
        if (Bank->Desk.wins[i].statu != DEALING)
            Bank->Desk.wins[i].type = NOR;
}

void CHECK_WINDOW_TYPE(struct BANK *Bank){
    if ( Bank->Customer.VIP_Len - Bank->Customer.VIP_DEALED <= 0 )
        part_check(Bank);
	if ( Bank->Customer.VIP_Len - Bank->Customer.VIP_DEALED > 0 ){
		int i;
		for ( i = 7 ; i < 7 + Bank->Desk.VIP_open ; i++ )
			if (Bank->Desk.wins[i].statu != DEALING)
				Bank->Desk.wins[i].type = VIP;
			else if ( Bank->Time == Bank->Desk.wins[i].end_time )
				Bank->Desk.wins[i].type = VIP;
	}

}

void CHECK_LEN(struct BANK *Bank){

	int i,temp_open=0;

	for ( i = 1 ; i <= 6 ; i++)
		if ( Bank->Desk.wins[i].statu == DEALING || Bank->Desk.wins[i].statu == WAITING )
			temp_open++;

	if ( Bank->Customer.NOR_Len - Bank->Customer.NOR_DEALED > 3 * temp_open){
		if (Bank->Desk.NOR_open <6){
			++Bank->Desk.NOR_open;
			Bank->Desk.wins[Bank->Desk.NOR_open].statu = WAITING ;
			windows[Bank->Desk.NOR_open][1] = 1;
            windows[Bank->Desk.NOR_open][2] = 1;
			windows[Bank->Desk.NOR_open][0] = 1;
        }
	}

	if ( Bank->Customer.NOR_Len - Bank->Customer.NOR_DEALED < 2 * temp_open && Bank->Desk.NOR_open > 3 ){
		Bank->Desk.wins[Bank->Desk.NOR_open--].statu = OUTW;
		windows[Bank->Desk.NOR_open+1][1] = 1;
		windows[Bank->Desk.NOR_open+1][2] = 1;
		windows[Bank->Desk.NOR_open+1][0] = 0;
	}

	if ( Bank->Desk.VIP_open == 1 && Bank->Customer.VIP_Len - Bank->Customer.VIP_DEALED >= 3 ){
		Bank->Desk.VIP_open = 2;
		Bank->Desk.wins[8].statu = WAITING;
		windows[8][1] = 1;
		windows[8][2] = 1;
		windows[8][0] = 1;
	}

	if ( Bank->Desk.VIP_open == 2 && Bank->Customer.VIP_Len - Bank->Customer.VIP_DEALED < 3 ){
		if ( Bank->Time - Bank->Desk.VIP_SER_TIME >= Bank->Announce.VIPSERVLen ){
			Bank->Desk.VIP_open = 1;
			Bank->Desk.wins[8].statu = OUTW;
			windows[8][1] = 1;
			windows[8][2] = 1;
			windows[8][0] = 0;
			Bank->Desk.VIP_SER_TIME = Bank->Time;
		}
	}
	else
		Bank->Desk.VIP_SER_TIME = Bank->Time ;

}
/*
void CASE(char c,struct BANK *Bank){

	int CHECK_VIP(struct BANK*);
	if ( Bank->Current_Statu == CLOSE )
		return;
	if ( c == 'g' || c == 'G' ){
		if ( Bank->Current_Statu == OPEN ){
			CUSTOMER_COMING(Bank,NOR);
		}
		else{
			if ( Bank->Current_Statu == LAST){
				unvalid("Bank is ready for close!",0);
				Sleep(1000);
			}
			else
				unvalid("Bank is already close!",1000);
		}
	}
	else if ( c == 'X' || c == 'x' ){
		thread_flag = 1;
		vip_flag = 1;
		Sleep(10);
		HANDLE handle = (HANDLE)_beginthreadex(NULL,0,REFRE,Bank,0,NULL);
		Sleep(10);
		WaitForSingleObject(signal,INFINITE);
		CloseHandle(handle);
		thread_flag = 0;
		vip_flag = 0;
		fflush(stdin);
	}
	else if ( c == 'Q' || c == 'q' ){
		CLOSE_BANK(Bank);
		system("cls");
		STATU_PRINT(*Bank);
	}
	else if ( c == 'R' || c == 'r' ){
//		RELAX_WINDOW(Bank);
		fflush(stdin);
	}
	else if ( c == 'V' || c == 'v' ){
		if ( Bank->Current_Statu == OPEN ){
			if ( CHECK_VIP(Bank) == 1 )
				CUSTOMER_COMING(Bank,VIP);
			else CUSTOMER_COMING(Bank,NOR);
		}
		else{
			if ( Bank->Current_Statu == LAST){
				unvalid("Bank is ready for close!",0);
				Sleep(1000);
			}
			else
				unvalid("Bank is already close!",1000);
		}
	}

}
*/
int CHECK_VIP(struct BANK *Bank){
		struct VIP *findp = Bank->vip_data;
		while ( findp != NULL ){
			if ( strcmp (findp->ID,INPUTING.content) == 0)
				break;
			findp = findp -> next;
		}
		if( findp == NULL || strcmp(findp->ID,INPUTING.content) != 0 )
            return 0;
		else if ( strcmp(findp->ID , INPUTING.content) == 0 )
            return 1;
        return 0;
}

void RELAX_WINDOW(struct BANK *Bank,int number){

	srand((unsigned)Bank->Time);
	if ( Bank->Desk.wins[number].statu == DEALING ){
        Bank->Desk.wins[number].pause_start_time = Bank->Desk.wins[number].end_time;
        Bank->Desk.wins[number].pause_end_time = Bank->Desk.wins[number].end_time + (1+(int)(100.0*rand()/(RAND_MAX+1.0)))  % ( Bank->Announce.MaxRestSec - Bank->Announce.MinRestSec ) + Bank->Announce.MinRestSec;
    }
    else {
        Bank->Desk.wins[number].statu = PAUSE;
        windows[number][1] = 1;
        Bank->Desk.wins[number].pause_end_time = Bank->Time + rand() % ( Bank->Announce.MaxRestSec - Bank->Announce.MinRestSec ) + Bank->Announce.MinRestSec;
    }
}

void CLOSE_BANK(struct BANK *Bank){						// Give the close order
	if (Bank->Customer.VIP_Len !=0 || Bank->Customer.NOR_Len !=0)
		Bank->Current_Statu = LAST;
	else
		Bank->Current_Statu = CLOSE;
    text[0].NeedF = 1;
}

void unvalid(char *s,int timestop){

	thread_flag = 1;
	vip_flag = 1;
	signal = CreateEvent(NULL,FALSE,FALSE,NULL);
	system("cls");
//	system("color 4");
	printf("\n\n----------------------------------------------------------------\n");
	printf("\n         Unvalid operation : %s\n\n",s);
	printf("----------------------------------------------------------------");
	MakeString(s);
	PulseEvent(voice_signal);
//	system("color 7");
	Sleep(timestop);
	PulseEvent(signal);
	CloseHandle(signal);
	vip_flag = 0;
	thread_flag = 0;
}

void MakeNext(int num,int window,enum GUEST_TYPE type){
	FILE *fp = fopen("voice.vbs","w");
	char make[101];
	if (type == NOR )
		sprintf(make,"msg=\"顾客%d，请到窗口%d\"\nset sapi=createobject(\"sapi.spvoice\")\nsapi.speak msg",num,window);
	else
		sprintf(make,"msg=\"会员%d，请到窗口%d\"\nset sapi=createobject(\"sapi.spvoice\")\nsapi.speak msg",num,window);
	fprintf(fp,"%s",make);
	fclose(fp);
	return;
}

void MakeString(char *s){
	FILE *fp = fopen("voice.vbs","w");
	char make[101];
	sprintf(make,"msg=\"%s\"\nset sapi=createobject(\"sapi.spvoice\")\nsapi.speak msg",s);
	fprintf(fp,"%s",make);
	fclose(fp);
	return;
}

