#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>
#include "Format.h"

void INIT_VIP(struct BANK *Bank){

	FILE *vip = fopen ( "VIP.dat" , "r" );
	char c;
	while (!feof(vip)){
		struct VIP *newp = ( struct VIP * ) malloc ( sizeof(struct VIP) );
		newp->next = NULL;
		fscanf(vip,"%s %s %d",newp->name,newp->ID,&(newp->deposit));
		do{
			c = fgetc(vip);
		}while( c == '\n' || c == ' ' || c == '\b');
		fseek(vip,-1,SEEK_CUR);
		if ( Bank->vip_data == NULL )
			Bank->vip_data = newp;
		else {
			newp->next = Bank->vip_data;
			Bank->vip_data = newp;
		}
		if ( c == -1 )
			break;
	}
	fclose(VIP);

}

void CASE_VIP(struct BANK *Bank){

	void VIP_WIN(void);
	void Add_VIP(struct BANK *Bank);
	void Del_VIP(struct BANK *Bank);
	void Rfe_VIP(struct BANK *Bank);
	VIP_WIN();
	char commands[3];
	scanf("%s",commands);
	while ( strcmp ( commands , "E" ) != 0 && strcmp (commands ,"e" ) != 0){
		if ( strcmp( commands , "V+") ==0 )
			Add_VIP(Bank);
		else if ( strcmp ( commands , "V-" ) == 0 )
			Del_VIP(Bank);
		else if ( strcmp ( commands , "V/" ) == 0 )
			Rfe_VIP(Bank);
		else {
			unvalid("Input is unvalid!",700);
			VIP_WIN();
			scanf("%s",commands);
			continue;
		}
		VIP_WIN();
		scanf("%s",commands);
	}
	work_flag = 0;
	return;
}

void VIP_WIN(){

	system("cls");
	system("color 1");
	printf("----------------------------------------------------------------------\n\n");
	printf("                         VIP Refresh Command\n");
	printf("      Add VIP : V+     Fresh VIP : V/    Remove VIP : V-   Exit : E \n\n");
	printf("                 Please input your command : ");
	system("color 7");

}

void Add_VIP(struct BANK *Bank){

	void PRINT_VIP(struct BANK *);
	struct VIP *add = (struct VIP *) malloc (sizeof (struct VIP));
	printf("-----------------------------------------------------------------------\n\n");
	printf("          Please input new VIP's name : ");
	scanf("%s",add->name);
	getchar();
	printf("\n          Please input new VIP's ID : ");
	scanf("%s",add->ID);
	printf("\n          Please input new VIP's deposit : ");
	scanf("%d",&(add->deposit));
	printf("\n                 Add VIP successfully!\n");
	fflush(stdin);
	if ( Bank->vip_data == NULL)
		Bank->vip_data = add;
	else {
		add->next = Bank->vip_data;
		Bank->vip_data = add;
	}
	PRINT_VIP(Bank);
	Sleep(500);
	fflush(stdin);
	return;

}

void Del_VIP(struct BANK *Bank){

	void PRINT_VIP(struct BANK *);
	printf("------------------------------------------------------------------------\n\n");
	char id[8];
	printf("        Please input VIP's id you want to delete : ");
	scanf("%s",id);
	struct VIP *findp = Bank->vip_data , *pre = NULL;
	while ( findp != NULL ){
		if ( strcmp(findp->ID,id) == 0 )
			break;
		pre = findp;
		findp = findp->next;
	}
	if ( findp != NULL && strcmp(findp->ID,id) == 0 ){
		printf("\n         VIP %s has been deleted successfully!\n",id);
		if ( findp == Bank->vip_data )
			Bank->vip_data = Bank->vip_data->next;
		else
			pre->next = findp->next;
		free(findp);
		PRINT_VIP(Bank);
	}
	else
		printf("\n              Can't find VIP %s !\n",id);
	Sleep(500);
	fflush(stdin);
	return;

}

void Rfe_VIP(struct BANK *Bank){

	void PRINT_VIP(struct BANK *);
	printf("------------------------------------------------------------------------\n\n");
	printf("        Please input VIP's id your want to fresh : ");
	char id[8];
	scanf("%s",id);
	struct VIP *findp = Bank->vip_data;
	while ( findp != NULL ){
		if ( strcmp(findp->ID , id) == 0 )
			break;
		findp = findp->next;
	}
	if ( findp != NULL && strcmp( findp->ID , id ) == 0 ){
		printf("\n       Please input his new name : ");
		scanf("%s",findp->name);
		getchar();
		printf("\n       Please input his new ID : ");
		scanf("%s",findp->ID);
		getchar();
		printf("\n       Please input his new deposit : ");
		scanf("%d",&(findp->deposit));
		printf("                   Refresh this VIP successfully !");
		fflush(stdin);
		PRINT_VIP(Bank);
	}
	else
		printf("\n           Can't find VIP %s !\n",id);
	Sleep(1000);
	fflush(stdin);
	return;

}

void PRINT_VIP(struct BANK *Bank){

	FILE * vipt = fopen ( "VIP.dat" , "w");
	struct VIP *vip = Bank->vip_data;
	while ( vip != NULL ){
		fprintf(vipt,"%s %s %d\n",vip->name,vip->ID,vip->deposit);
		vip = vip->next;
	}
	fclose(vipt);

}

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
	Bank->Time = 0;						// Bank time init
	thread_flag = 0;
	vip_flag = 0;
	FILE *reflec = fopen ( "Maintain_Per_Sec.dat", "w" );
	fclose(reflec);

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
