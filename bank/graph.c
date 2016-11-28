#include <stdio.h>
#include <windows.h>
#include <memory.h>
#include "egg.h"
#include "Format.h"

#define Win_Width 1225
#define Win_Height 634

double bitmap[9][2]={{0,0},{140,460},{320,460},{500,460},{140,260},{320,260},{500,260},{710,460},{710,260}};
double stringmap[9][2]={{0,0},{181,410},{361,410},{541,410},{181,210},{361,210},{541,210},{751,410},{751,210}};
double buttonmap[9][2]={{200,268},{380,268},{560,268},{200,65},{380,65},{560,65},{770,268},{770,65}};
double nummap[13][2]={{1050,110},{970,245},{1050,245},{1130,245},{970,200},{1050,200},{1130,200},{970,155},{1050,155},{1130,155},{970,110},{1130,110}};
double funmap[4][2]={{970,65},{1050,65},{1130,65}};

extern char WINDOW_STATU_PRINT[4][11];
extern char GUEST_TYPE_PRINT[2][4];
extern char BANK_STATU_PRINT[3][5];
extern char WORK_TYPE_PRINT[6][11];

int endbuttontop = 25;
HEGG graphstatu[9];


BUTTON *CreateButton(double x,double y,double  width,double height,char *s){
    BUTTON *newb = (BUTTON *)malloc(sizeof(BUTTON));
    newb->Butt.width = width;
    newb->Butt.height = height;
    newb->Butt.posx = x - width / 2;
    newb->Butt.posy = y + height / 2;
    newb->Butt.color = 0;
    newb->Butt.active = 0;
    newb->lay = LayEgg();
    newb->Slay = LayEgg();
    strcpy(newb->name,s);
    newb->NeedF = 1;
    return newb;
}

BOOL IsButtonActive(BUTTON button){
    double x = GetMouseX() , y = GetMouseY();
    double x1 = button.Butt.posx - 12 , y1 = button.Butt.posy+button.Butt.height/2 ;
    double x2 = x1 + button.Butt.width + 24 , y2 = y1 - button.Butt.height;
    if (  x1 <= x && x <= x2 && y1 >= y && y >= y2)
        return 1;
    else return 0;
}

void SetButtonActive(BUTTON *button){
    if (button->Butt.active == 1)
        return;
    button->Butt.active = 1;
    button->Butt.width *= 1.1;
    button->Butt.height *= 1.1;
    button->Butt.color = 1;
}

void SetButtonNegative(BUTTON *button){
    if (button->Butt.active == 0)
        return;
    button->Butt.active = 0;
    button->Butt.width /= 1.1;
    button->Butt.height /= 1.1;
    button->Butt.color = 0;
}

void DrawSingleButton(BUTTON *button){
    SetActiveEgg(button->lay);
    EatEgg();
    button->lay = LayEgg();
    MovePen(button->Butt.posx,button->Butt.posy);
    if (button->Butt.color == 0)
        SetPenColor(BLACK);
    else if (button->Butt.color == 1)
        SetPenColor(GREEN);
    else if (button->Butt.color == 2)
        SetPenColor(DARK_GRAY);
    SetPenWidth(button->Butt.height);
    DrawLine(button->Butt.width,0);
    SetActiveEgg(button->Slay);
    EatEgg();
    button->Slay=LayEgg();
    MovePen(button->Butt.posx+button->Butt.width/2-GetStringWidth(button->name)/2,button->Butt.posy+8);
    if (button->Butt.color == 2)
        SetPenColor(DARK_GRAY);
    else
        SetPenColor(RED);
    DrawString(button->name);
}

void DrawMultipleButtons(BUTTON *button,int num){
    int i;
    for ( i = 0 ; i < num ; i++ ){
        if ( button[i].NeedF == 1 ){
            DrawSingleButton(button+i);
            button[i].NeedF = 0;
        }
    }
}

void PRINT_STATU(struct BANK *Bank,TEXTS *text){
    void rush(TEXTS *,struct BANK *);
    rush(text,Bank);
    int i;
    for ( i = 0 ; i < 6 ; i++ ){
        if (text[i].NeedF == 0){
           /* if ( i == 5 ){
                SetActiveEgg(text[5].lay);
                EatEgg();
                text[5].lay = LayEgg();
            } */
            continue;
        }
        SetActiveEgg(text[i].lay);
        EatEgg();
        text[i].lay = LayEgg();
        MovePen(text[i].x,text[i].y);
        DrawString(text[i].content);
        text[i].NeedF = 0;
    }
}

void drawATMOpen(double x,double y){
    MovePen(x,y);
    DrawBitmap("atmopen.bmp");
    SetPenWidth(6);
    MovePen(x,y);
    DrawLine(125,0);
    DrawLine(0,-164);
    DrawLine(-125,0);
    DrawLine(0,164);
}

void drawATMClose(double x,double y){
    MovePen(x,y);
    DrawBitmap("atmclose.bmp");
    SetPenWidth(6);
    MovePen(x,y);
    DrawLine(125,0);
    DrawLine(0,-164);
    DrawLine(-125,0);
    DrawLine(0,164);
}

int isinput = 0;

void drawStatu(HEGG *thislay,double x,double y,int num,enum WINDOW_STATU now,enum WORK_TYPE work,enum GUEST_TYPE type){
    SetPenWidth(1);
    if ( now == OUTW )
        return;
    char temp[11];
    double t;
    SetActiveEgg(*thislay);
    EatEgg();
    *thislay = LayEgg();
    if ( now == DEALING ){
        SetPenColor(GREEN);
        t = GetStringWidth(WINDOW_STATU_PRINT[DEALING]);
        MovePen(x-t/2,y+10);
        DrawString(WINDOW_STATU_PRINT[DEALING]);
        t = GetStringWidth(NUM_TO_STRING(num,type));
        MovePen(x-t/2,y-6);
        DrawString(NUM_TO_STRING(num,type));
        sprintf(temp,"%s",WORK_TYPE_PRINT[work]);
        t = GetStringWidth(temp);
        MovePen(x-t/2,y-22);
        DrawString(temp);
    }
    else if ( now == PAUSE ){
        SetPenColor(RED);
        sprintf(temp,"%7s",WINDOW_STATU_PRINT[PAUSE]);
        t = GetStringWidth(temp);
        MovePen(x-t/2,y-8);
        DrawString(temp);
    }
    else if ( now == WAITING ){
        SetPenColor(BLUE);
        t = GetStringWidth("WAITING");
        MovePen(x-t/2,y);
        DrawString("WAITING");
       // sprintf(temp,"%d",num);
       // t = GetStringWidth(temp);
       // MovePen(x-t/2,y-16);
       // DrawString(temp);
    }
}

void DRAWWINWDOW(struct BANK *Bank){
    int i;
    SetActiveEgg(Fist);
    for ( i = 1 ; i <= 8 ; i++ ){
        if ( windows[i][1]){
            drawStatu(graphstatu+i,stringmap[i][0],stringmap[i][1],Bank->Desk.wins[i].now,Bank->Desk.wins[i].statu,Bank->Desk.wins[i].work,Bank->Desk.wins[i].type);
            windows[i][1] = 0;
        }
    }
}

void drawInitGraph(){
    void drawATM();
    MovePen(0,Win_Height);
    DrawBitmap("ground.bmp");
    MovePen(663,496);
    SetPenWidth(6);
    DrawLine(0,-466);
	drawATM();
}

HEGG ATMMAP[9];

void drawATM(){
    int i;
    for ( i = 1 ; i <= 8 ; i++ ){
        if (!windows[i][2])
            continue;
        SetActiveEgg(ATMMAP[i]);
        EatEgg();
        ATMMAP[i] = LayEgg();
        if ( windows[i][0] == 1 )
            drawATMOpen(bitmap[i][0],bitmap[i][1]);
        else
            drawATMClose(bitmap[i][0],bitmap[i][1]);
        windows[i][2] = 0;
    }
}

void rush(TEXTS *text,struct BANK *Bank){
    sprintf(text[0].content,"当前银行状态：%s",BANK_STATU_PRINT[Bank->Current_Statu]);
   // if (Bank->Customer.NOR_Line == NULL)
  //      sprintf(text[1].content,"当前普通客户已到：000");
  //  else
        sprintf(text[1].content,"当前普通客户已到：%s",NUM_TO_STRING(Bank->Customer.NOR_DEALED,NOR));//Bank->Customer.NOR_Line->number);
    if (Bank->Customer.NOR_Line == NULL)
        sprintf(text[2].content,"当前无普通客户排队");
    else
        sprintf(text[2].content,"当前普通客户排队人数：%d",Bank->Customer.NOR_Last->number - Bank->Customer.NOR_Line->number +1);
 //   if (Bank->Customer.VIP_Line == NULL)
 //       sprintf(text[3].content,"当前VIP客户已到：V00");
 //   else
        sprintf(text[3].content,"当前VIP客户已到：%s",NUM_TO_STRING(Bank->Customer.VIP_DEALED,VIP));//Bank->Customer.VIP_Line->number);
    if (Bank->Customer.VIP_Line == NULL )
        sprintf(text[4].content,"当前无VIP客户排队");
    else
        sprintf(text[4].content,"当前VIP客户排队人数：%d",Bank->Customer.VIP_Last->number - Bank->Customer.VIP_Line->number +1);
    if ( inputflag == 1 && isinput ==  1){
        sprintf(text[5].content,"正在输入：%s",INPUTING.content);
        text[5].NeedF = 1;
        isinput = 0;
    }
}


void FreshMap(struct BANK *Bank,BUTTON *button,TEXTS *text){
    DrawMultipleButtons(button,endbuttontop);
    PRINT_STATU(Bank,text);
    drawATM();
    DRAWWINWDOW(Bank);
}

void graph(struct BANK *Bank)
{
//    int curnum = 10 , curvipnum = 20 , statu = 0;
    choose = 0;
    work_flag = 0;
	EggStart(Win_Width,Win_Height);
	HWND now = GetForegroundWindow();
	if (now != NULL)
	SetWindowText(now,"Bank System V2.0     Developed By Group 201421131202");
    ShowConsoleWindow(0);
	int i;
	for ( i = 1 ; i <= 8 ; i++ )
        ATMMAP[i] = LayEgg();
	for (i=1;i<=3;i++)
        windows[i][0] = 1;
    for ( i = 4; i <= 6; i++)
        windows[i][0] = 0;
	windows[7][0] = 1;
	windows[8][0] = 0;
	for ( i = 1 ; i <= 8 ; i++ ){
        graphstatu[i] = LayEgg();
        windows[i][1] = 1;
        windows[i][2] = 1;
	}
    basic = LayEgg();
	drawInitGraph();
	TIME = LayEgg();
	Fist = LayEgg();
	text[0].x = 930 ; text[0].y = 480 ; text[0].lay = LayEgg(); text[0].NeedF = 1;
	text[1].x = 930 ; text[1].y = 457 ; text[1].lay = LayEgg(); text[1].NeedF = 1;
    text[2].x = 930 ; text[2].y = 434 ; text[2].lay = LayEgg(); text[2].NeedF = 1;
    text[3].x = 930 ; text[3].y = 411 ; text[3].lay = LayEgg(); text[3].NeedF = 1;
    text[4].x = 930 ; text[4].y = 388 ; text[4].lay = LayEgg(); text[4].NeedF = 1;
    text[5].x = 930 ; text[5].y = 365 ; text[5].lay = LayEgg(); text[5].NeedF = 0;
    SetActiveEgg(basic);
	for ( i = 0 ; i < 8 ; i++ )
        button[i] = *CreateButton(buttonmap[i][0],buttonmap[i][1],26,17,"Relex");
    char temp[3];
    for ( i = 8 ; i < 18 ; i++ ){
        sprintf(temp,"%d",i-8);
        button[i] = *CreateButton(nummap[i-8][0],nummap[i-8][1],26,25,temp);
        //button[i].Butt.color = 2;
    }


    button[18] = *CreateButton(nummap[10][0],nummap[10][1],26,25,"Back");
    button[19] = *CreateButton(nummap[11][0],nummap[11][1],26,25,"OK");
 //   button[18].Butt.color = 2;
 //   button[19].Butt.color = 2;
    button[20] = *CreateButton(funmap[0][0],funmap[0][1],26,25,"Normal");
    button[21] = *CreateButton(funmap[1][0],funmap[1][1],26,25,"VIP");
    button[22] = *CreateButton(funmap[2][0],funmap[2][1],26,25,"Exit");
    button[23] = *CreateButton(140,540,26,25,"Choice");
    button[24] = *CreateButton(200,540,26,25,"Admin");
    FreshMap(Bank,button,text);
    INPUTING.content[0] = 'I';
    INPUTING.content[1] = 'D';
    INPUTING.top = 2;
    Update();
	EVENT_TYPE ev;
//	FILE *fp = fopen("target.txt","w");
    StartTimer(1000);
	while ((ev=WaitForEvent())!= EXIT){
        if ( work_flag == 1)
            continue;
        if (ev == TIMER ){
            if (work_flag == 1)
                continue;
            Bank->Time ++;
            REFRESH(Bank);
            BANK_MAINTAIN_PER_SEC(*Bank);
            SetActiveEgg(TIME);
            EatEgg();
            TIME = LayEgg();
            MovePen(116,600);
            DrawString(GET_TIME(*Bank));
            FreshMap(Bank,button,text);
            Update();
           // Sleep(5000);

        }
        if (ev==MOUSEMOVE){
            BOOL flag = 0;
            for ( i = 0 ; i < endbuttontop ; i++ ){
                 if ( button[i].Butt.color == 2){
                    button[i].NeedF = 0;
                    continue;
                 }
                 if (IsButtonActive(button[i]) && button[i].Butt.active == 0 ){
                    SetButtonActive(button+i);
                    flag = 1;
                    button[i].NeedF = 1;
                }
                else if (!IsButtonActive(button[i]) && button[i].Butt.active == 1){
                    SetButtonNegative(button+i);
                    flag = 1;
                    button[i].NeedF = 1;
                }
            }
            if(flag == 1){
                FreshMap(Bank,button,text);
                Update();
            }
        }
   /*     if (ev==KEYDOWN)
            if (GetStruckKey() == VK_LBUTTON){
                printf("%d %d\n",(int)GetMouseX(),(int)GetMouseY());
                fprintf(fp,"{%d,%d},",(int)GetMouseX(),(int)GetMouseY());
            }*/
        if ( ev == KEYDOWN ){
            for ( i = 0 ; i < endbuttontop ; i++ )
            if (IsButtonActive(button[i])&&button[i].Butt.active == 1&&button[i].Butt.color != 2){
                if (0<=i && i<8 && windows[i+1][0] == 1)
                    RELAX_WINDOW(Bank,i+1);
                else if ( 8<= i && i <=17 && inputflag == 1){
                    INPUTING.content[INPUTING.top++] = i - 8 + '0';
                    INPUTING.content[INPUTING.top] = '\0';
                    isinput = 1;
                }
                else if ( i == 20 ){
                    CUSTOMER_COMING(Bank,NOR);
           //         printf("successful\n");
                }
                else if ( i == 21 && Bank->Current_Statu == OPEN ){
                    if (inputflag == 1)
                        continue;
                    else {
                        isinput = 1;
                        inputflag = 1;
                    }
                }
                else if ( i == 18 && inputflag == 1 && INPUTING.top > 2 && Bank->Current_Statu == OPEN){
                    INPUTING.content[--INPUTING.top]='\0';
                    isinput = 1;
                }
                else if ( i == 19 && inputflag == 1&& Bank->Current_Statu == OPEN){
                    if (CHECK_VIP(Bank)==1){
                        inputflag = 0;
                        CUSTOMER_COMING(Bank,VIP);
                        INPUTING.content[2] = '\0';
                        INPUTING.top = 2;
                        isinput = 0;
                        text[5].NeedF = 0;
                        SetActiveEgg(text[5].lay);
                        EatEgg();
                        text[5].lay = LayEgg();
                    }
                    else {
                        INPUTING.content[2] = '\0';
                        INPUTING.top = 0;
                        isinput = 1;
                        if ( ++INPUTING.time < 3){
                            INPUTING.content[2]='\0';
                            INPUTING.top = 2;
                        }
                        else {
                            INPUTING.time = 0;
                            INPUTING.content[2] = '\0';
                            INPUTING.top = 2;
                            CUSTOMER_COMING(Bank,NOR);
                            SetActiveEgg(text[5].lay);
                            EatEgg();
                            text[5].lay = LayEgg();
                            text[5].NeedF = 0;
                            inputflag = 0;
                            isinput = 0;
                        }
                    }
                }
                else if ( i == 22 ){
                    CLOSE_BANK(Bank);
                    INPUTING.content[2] = '\0';
                    INPUTING.top = 0;
                    SetButtonNegative(button+22);
                    int j;
                    endbuttontop = 8;
                    for ( j = 8 ; j <= 22 ; j++ ){
                        SetActiveEgg(button[j].Slay);
                        EatEgg();
                        SetActiveEgg(button[j].lay);
                        EatEgg();
                    }
                }
                else if ( i == 23 ){
                        if (choose == 1){
                            choose = 0;
                            part_check(Bank);
                        }
                        else choose = 1;
                }
                else if ( i == 24 ){
                    ShowConsoleWindow(1);
                    work_flag = 1;
                    CASE_VIP(Bank);
                    ShowConsoleWindow(0);
                }
            }
            REFRESH(Bank);
            FreshMap(Bank,button,text);
            Update();
        }
        if (ev==EXIT)
            exit(0);
        if (Bank->Current_Statu == CLOSE){
            BANK_MAINTAIN_ALL(*Bank);
            exit(0);
        }
	}
//	return 0;
}

int main()
{
    struct BANK *B = (struct BANK *)malloc(sizeof(struct BANK));
    FILE *format = fopen("Format.dat","r");
    INIT_BANK(B,format);
    INIT_VIP(B);
    MAIN_THREAD(B);
    return 0;
}
