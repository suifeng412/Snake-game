#include<time.h>


#include <windows.h>
#include "snake.h"

void main(){
	int testNum = 0;	//食物和蛇身重叠检测次数
	char c = 'd';		//方向按键初始化为d,即蛇初始向右移动
	srand((unsigned)time(NULL));	//随机种子

	Food food = { 5, 8, 'A' };		//初始化食物
	Snake snake, *head, *rear;		//蛇头、蛇尾
	initSnake(&snake);				//初始化蛇
	head = rear = &snake;

	while (1){
		drawPicture(head, &food);				//绘制墙、蛇、食物
		if (isSnakeEatMeetFood(head, &food)){	//蛇吃到食物后
			rear = snakeGrow(head);				//增加一节蛇身
			createFood(&food);					//生成蛇身
			testNum = avoidOverlap(head, &food);		//判断新生成的食物坐标与蛇是否有重叠，有则重新生成
			setFoodLocation(&food, head, testNum, c);	//当重叠超过预订次数，则根据蛇前进的方向设置食物
		}
		/*按键处理*/
		if (_kbhit())
			c = setCurKeyButton(c);		//设置当前的按键
		if (c == 'x')				
			break;						//结束退出处理
		snakeMove(head, rear, c);		//蛇移动
		if (isSnakeEatItself(head)){	//蛇碰到蛇身就结束游戏
			puts("game over!\n");
			break;
		}
		Sleep(300);			//屏幕刷新时间间隔
	}
	_getch();
}