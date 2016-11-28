#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "Format.h"

void INIT_BANK(struct BANK *Bank,FILE *fp){						// Statu before open

	int DEFINE_INIT(char s[],int num,struct BANK *Bank);					// Get initial constant
	int top=0,count=0;
	char ele,temp[21];
	while (fscanf(fp,"%c",&ele)!=EOF){					// Get Configure file
		if (ele == '['){
			while (ele != ']'){
				if(fscanf(fp,"%c",&ele) == EOF )
					return;
				temp[top++] = ele;
			}
			fscanf(fp,"%d",&count);
			temp[top-1] = '\0';
			if (!DEFINE_INIT(temp,count,Bank)){				// Configure File is in wrong format
				printf("Invalid Configure File!\n");
				system("pause");
				exit(0);
			}
			top=0;
		}
	}

	int i;
	for ( i = 1 ; i <= 8 ; i++ ){
		Bank->Desk.wins[i].statu = OUTW;
		Bank->Desk.wins[i].work = NONE;
		Bank->Desk.wins[i].now = 0;
		Bank->Desk.wins[i].nor_count = 0;
		Bank->Desk.wins[i].vip_count = 0;
		Bank->Desk.wins[i].time_used = 0;
		Bank->Desk.wins[i].end_time = 0;
		Bank->Desk.wins[i].pause_start_time = -1;
		Bank->Desk.wins[i].pause_end_time = -1;
	//	Bank->Desk.wins[i].satisfy = 0;
	//	Bank->Desk.wins[i].unsatisfy = 0;
		Bank->Desk.wins[i].type = ( i > 6 ? VIP : NOR );
	}
	Bank->Desk.VIP_open = 1;
	Bank->Desk.NOR_open = 3;
	Bank->Desk.VIP_SER_TIME = 0;
	for ( i = 1 ; i <= 3 ; i++ )	// Open windows init
		Bank->Desk.wins[i].statu = WAITING ;
	Bank->Desk.wins[7].statu = WAITING ;
	Bank->Customer.VIP_Len = 0;
	Bank->Customer.NOR_Len = 0;
	Bank->Customer.VIP_DEALED = 0;
	Bank->Customer.NOR_DEALED = 0;
	Bank->Customer.VIP_Line = NULL;
	Bank->Customer.VIP_Last = NULL;
	Bank->Customer.NOR_Line = NULL;
	Bank->Customer.NOR_Last = NULL;
	Bank->Current_Statu = OPEN;			// Bank statu init
	Bank->vip_data = NULL;
	Bank->Time = 8 * 3600;						// Bank time init
	thread_flag = 0;
	vip_flag = 0;
//	FILE *out = fopen ( "Maintain_Per_Sec.dat", "w" );
//	fclose(out);

}

int DEFINE_INIT(char s[],int num,struct BANK *Bank){

	if ( !strcmp( s , "MaxSeqLen" ) )
		Bank->Announce.MaxSeqLen = num;
	else if ( !strcmp( s , "MinSec" ) )
		Bank->Announce.MinSec = num;
	else if ( !strcmp( s , "MaxSec" ) )
		Bank->Announce.MaxSec = num;
	else if ( !strcmp( s , "MinRestSec" ) )
		Bank->Announce.MinRestSec = num;
	else if ( !strcmp( s , "MaxRestSec" ) )
		Bank->Announce.MaxRestSec = num;
	else if ( !strcmp( s , "VIPSERVLen" ) )
		Bank->Announce.VIPSERVLen = num;
	else return 0;
	return 1;
}


