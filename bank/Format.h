#ifndef Format
#define Format
#include <stdio.h>
#include <windows.h>
#include "egg.h"

#define ERROR 0
#define REJECT 0
#define ACCEPT 1
#define TRUE 1
#define FALSE 0
#define BOOL int

enum WORK_TYPE{WITHDRAW,SAVE,ADDUSR,LOGOUT,STOCK,NONE};	// The present work of current window including save money .etc...
enum WINDOW_STATU{WAITING,DEALING,PAUSE,OUTW};			// The present statu of current window including waiting for customers .etc...
enum GUEST_TYPE{VIP,NOR};
enum BANK_STATU{OPEN,CLOSE,LAST};

struct VIP{
	char name[21];
	char ID[9];
	int deposit;
	struct VIP *next;
};

struct FORMAT{
	int MaxSeqLen;
    int MinSec;
    int MaxSec;
    int MinRestSec;
    int MaxRestSec;
    int VIPSERVLen;
    struct VIP *data;
};

struct INPUTING{
    char content[21];
    int top;
    int time;
};

struct BUTTON_S{
    double width;
    double height;
    double posx;
    double posy;
    int color;
    BOOL active;
};

typedef struct Text_S{
    double x,y;
    char content[51];
    HEGG lay;
    BOOL NeedF;
}TEXTS;

typedef struct BUTTON{
    struct BUTTON_S Butt;
    char name[11];
    HEGG Slay;
    HEGG lay;
    BOOL NeedF;
}BUTTON;

struct INPUTING INPUTING;
int inputflag;
BUTTON button[25];
TEXTS text[6];

struct Single_Window{									// Struct of a single window
	enum WINDOW_STATU statu;							// Window's current statu
	enum WORK_TYPE work;								// Window's current work type
	enum GUEST_TYPE type;
	int now;											// Current processed customer's number
	int nor_count;
	int vip_count;
	int time_used;
	int end_time;
	int pause_start_time;
	int pause_end_time;
//	int satisfy;
//	int unsatisfy;
};

struct HAND{											// Struct of a customer
	int time;											// Customer's time
	int number;											// Customer's number
	enum WORK_TYPE work;								// Customer's work type
	enum GUEST_TYPE type;								// Customer's level
	struct HAND *next;
};

struct WINDOWS{											// Gather of all of the windows
	struct Single_Window wins[9];
	int VIP_open;									// VIP windows be open
//	int VIP_pause[3];									// VIP windows be pause
	int NOR_open;
//	int NOR_pause[7];									// Same to NORMAL guest
	int VIP_SER_TIME;
};

struct GUEST{											// Gather of all of the guests
	int VIP_Len;										// How many VIPs have came
	int VIP_DEALED;
	int NOR_Len;										// Same to NORMAL guest
	int NOR_DEALED;
	struct HAND *VIP_Line,*VIP_Last;							// VIPs' head and rear
	struct HAND *NOR_Line,*NOR_Last;							// NORs' head and rear
};

struct BANK{											// Whole bank
	struct WINDOWS Desk;								// WINDOWS
	struct GUEST Customer;								// CUSTOMERS
	struct FORMAT Announce;
	struct VIP *vip_data;
	enum BANK_STATU Current_Statu;
	long long Time;
};

int thread_flag;
int vip_flag;
int maintain_flag;
int choose;
int work_flag;
int windows[9][3];
HEGG Fist;
HEGG TIME;
HEGG basic;

HANDLE vip_signal;
HANDLE signal;
HANDLE voice_signal;
unsigned int __stdcall REFRE(void *pPM);
void unvalid(char *,int);
void RELAX_WINDOW(struct BANK *,int);
void INIT_BANK(struct BANK *,FILE *);
void STATU_PRINT(struct BANK);
int CUSTOMER_COMING(struct BANK *,enum GUEST_TYPE);
void CLOSE_BANK(struct BANK *);
void CASE_VIP(struct BANK *Bank);
void CASE(char c,struct BANK *Bank);
void INIT_VIP(struct BANK *Bank);
void REFRESH(struct BANK *);
void MAIN_THREAD(struct BANK *);
void MakeNext(int,int,enum GUEST_TYPE);
void MakeString(char *);
int CHECK_VIP(struct BANK *);
void CHECK_WINDOW_TYPE(struct BANK*);
void CHECK_LEN(struct BANK *);
void graph(struct BANK *);
void BANK_MAINTAIN_PER_SEC(struct BANK);
void BANK_MAINTAIN_ALL(struct BANK);
void part_check(struct BANK*);
char *GET_TIME(struct BANK);
char *NUM_TO_STRING(int,enum GUEST_TYPE);
#endif
