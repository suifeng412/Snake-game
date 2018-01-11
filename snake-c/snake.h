#ifndef _SNAKE_H
#define _SNAKE_H

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define LENGTH 20	  //围墙的长度
#define WIDTH 10	  //围墙的宽度
#define OVERLAP 3     //食物与蛇身重叠次数，放置食物时需要用到

//蛇结构体
typedef struct Snake{
	int x;				//蛇身横坐标
	int y;				//蛇身纵坐标
	struct Snake *pre;	//结构体指针，指向当前蛇身的前一节蛇身
	struct Snake *next;	//结构体指针，指向当前蛇身的后一节蛇身
}Snake;

//食物结构体
typedef struct Food{
	int x;				//食物横坐标
	int y;				//食物纵坐标
	char c;				//食物的字符表示
}Food;


void initSnake(Snake *s);							//蛇身初始化
int isSnakeEatItself(Snake *head);					//判断游戏结束，当蛇头碰到蛇身
int isSnakeEatMeetFood(Snake *snake, Food *food);	//蛇是否吃到食物
Snake *snakeGrow(Snake *head);		//蛇身增长一节
void createFood(Food *food);		//随机生成食物
//避免食物坐标和蛇身重叠，重新生成食物
int avoidOverlap(Snake *head, Food *food);
//如果生成食物和蛇身重叠超过阀值，则直接按蛇移动的方向设置食物位置
void setFoodLocation(Food *food, Snake *head, int numOverlap, char c);
char setCurKeyButton(char c1 );				//设置当前按键
void snakeMove(Snake *head, Snake *rear, char c);	//处理蛇的移动
void drawPicture(Snake *head, Food *food);			//绘制蛇、食物和围墙

#endif




