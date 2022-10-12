#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

#define high 20   //定义尺寸
#define width 35
//游戏原则：0输出空格，1输出蛇头，>1输出蛇身 ,movedirection=1,2,3,4分别上下左右移动 ,-2输出食物
int canves[high][width];   //记录元素
int i,j;
int movedirection;    //移动方向
int foodx,foody;    //食物位置
int newheadx,newheady;                          //记录 新蛇头

void hide()        //隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &cursor_info);
}

void gotoxy(int x,int y){                 //高级清屏
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle,pos);
}


void startup(){             //初始化
	canves[high/2][width/2]=1;                  //初始化蛇头与蛇身位置
	for(i=1;i<=4;i++){
		canves[high/2][width/2-i]=1+i;
	}

	movedirection=4;               //初始化向右移动

	foodx=rand()%(high-4)+2;          //初始化食物位置
	foody=rand()%(width-4)+2;
	if(canves[foodx][foody]>0){
		foodx=foodx+1;
		foody=foody+1;
	}
	canves[foodx][foody]=-2;
}

void show(){
	gotoxy(0,0);
	hide();
	for(i=0;i<high;i++){
		for(j=0;j<=width-1;j++){
			if(canves[i][j]==1){                 //输出蛇头
				printf("O");
			}
			else if(canves[i][j]>1){             //输出蛇身
				printf("*");
			}
			else if(canves[i][j]==-2){            //输出食物
				printf("F");
			}
		    else {
		    	printf(" ");
			}
		    if(j==width-1){                       //输出边框
				printf("|");
			}
	}
	printf("\n");
	if(i==high-1){
		for(j=0;j<=width-1;j++){                  //输出下框
				printf("_");
			if(j==width-1){
				printf("/");
			}
		}
	}
}
    printf("\n");
}

void updatewithout(){
	int max=0;
	int oldtailx,oldtaily;
	int oldheadx,oldheady;
	for(i=0;i<high;i++){
		for(j=0;j<width;j++){
			if(canves[i][j]>0){                    //使全身前进
				canves[i][j]++;
				if(canves[i][j]>max){              //寻找尾巴所在位置
					max=canves[i][j];
					oldtailx=i;
					oldtaily=j;
				}
				if(canves[i][j]==2){               //记录蛇头位置
					oldheadx=i;
					oldheady=j;
				}
			}
		}
	}

	if(movedirection==4){                          //使蛇自行移动
		newheadx=oldheadx;
		newheady=oldheady+1;
		if(newheady==width){                       //判断是否撞上边界
		printf("游戏失败\n");
		exit(0);
	}
	}
	if(movedirection==3){
		newheadx=oldheadx;
		newheady=oldheady-1;
		if(newheady==-1){                            //判断是否撞上边界
		printf("游戏失败\n");
		exit(0);
	}
	}
	if(movedirection==2){
		newheadx=oldheadx+1;
		newheady=oldheady;
		if(newheadx==high){                     //判断是否撞上边界
		printf("游戏失败\n");
		exit(0);
	}
	}
	if(movedirection==1){
		newheadx=oldheadx-1;
		newheady=oldheady;
		if(newheadx==-1){                     //判断是否撞上边界
		printf("游戏失败\n");
		exit(0);
	}
	}
	if(canves[newheadx][newheady]==-2){                     //判断是否吃到食物 且重新生成
		foodx=rand()%(high-4)+2;
		foody=rand()%(width-4)+2;
		if(canves[foodx][foody]>0){
			foodx=foodx+1;
			foody=foody+1;
		}
		canves[foodx][foody]=-2;
	}
	else{
		canves[oldtailx][oldtaily]=0;                      //若没吃到食物保证其长度不变
	}
	if(canves[newheadx][newheady]>0){                      //判断是否撞到自己
		printf("游戏失败\n");
		exit(0);
	}
	else{
		canves[newheadx][newheady]=1;
	}
	Sleep(50);
}

void updateinput(){
 	char input;
	if(kbhit()){
		input=getch();
		if(input=='a'){                       //控制移动方向
			if(canves[newheadx][newheady-1]>0){             //防止误触反方向导致死亡
				movedirection=movedirection;
			}
			else{
				movedirection=3;
			}
		}
		if(input=='d'){
			if(canves[newheadx][newheady+1]>0){           //防止误触反方向导致死亡
				movedirection=movedirection;
			}
			else{
				movedirection=4;
			}
		}
		if(input=='w'){
			if(canves[newheadx-1][newheady]>0){           //防止误触反方向导致死亡
				movedirection=movedirection;
			}
			else{
				movedirection=1;
			}
		}
		if(input=='s'){
			if(canves[newheadx+1][newheady]>0){             //防止误触反方向导致死亡
				movedirection=movedirection;
			}
			else{
				movedirection=2;
			}
		}
	}
}

int main(){                    //主函数
	startup();
	while(1){
		show();
		updatewithout();
		updateinput();
	}
	return 0;
}