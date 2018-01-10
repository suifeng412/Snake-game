#include<time.h>


#include <windows.h>
#include "snake.h"

void main(){
	int testNum = 0;
	char c = 'd';
	srand((unsigned)time(NULL));

	Food food = { 5, 8, 'A' };
	Snake snake, *head, *rear;
	initSnake(&snake);
	head = rear = &snake;

	while (1){
		drawPicture(head, &food);
		if (isSnakeEatMeetFood(head, &food)){
			rear = snakeGrow(head);
			createFood(&food);
			testNum = avoidOverlap(head, &food);
			setFoodLocation(&food, head, testNum, c);
		}
		if (_kbhit())
			c = setCurKeyButton(c);
		if (c == 'x')
			break;
		snakeMove(head, rear, c);
		if (isSnakeEatItself(head)){
			puts("game over!\n");
			break;
		}
		//_sleep(150);
		Sleep(300);
	}
	_getch();
}