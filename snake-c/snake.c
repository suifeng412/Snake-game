#include "snake.h"

//利用结构体指针初始化蛇身信息
void initSnake(Snake *s){
	s->x = 1;
	s->y = 1;
	s->pre = NULL;
	s->next = NULL;
}

//判断游戏结束：当蛇头碰到蛇身，游戏结束
int isSnakeEatItself(Snake *head){
	int gameOver = 0;
	Snake *pt = head->next;
	while (pt){
		if (head->x == pt->x && head->y == pt->y){
			gameOver = 1;
			break;
		}
		pt = pt->next;
	}
	return gameOver;
}


//蛇是否吃到食物
int isSnakeEatMeetFood(Snake *snake, Food *food){
	if (snake->x == food->x && snake->y == food->y)
		return 1;
	else
		return 0;
}

//蛇身增长一节
Snake *snakeGrow(Snake *head){
	Snake *p = (Snake *)malloc(sizeof(Snake));
	Snake *pt = head;	//蛇头
	while (pt->next)	//获取蛇尾的指针地址
		pt = pt->next;
	p->pre = pt;		//新增的一节蛇身【结构体pre】指向原来蛇尾最后一节蛇身【指针地址】
	pt->next = p;		//原来的蛇尾最后一节蛇身【结构体next】指向新蛇身【指针地址】
	p->next = NULL;
	return p;
}


//随机生成食物
void createFood(Food *food){
	food->x = rand() % LENGTH;
	food->y = rand() % WIDTH;
	food->c = 65 + rand() % 26;
}


//避免食物坐标和蛇身重叠，如果重叠则重新生成食物
int avoidOverlap(Snake *head, Food *food){
	int t = 0, flag = 1;
	while (flag){
		if (t > OVERLAP)
			break;
		flag = 0;
		t++;
		Snake *pt = head;
		while (pt){
			if (isSnakeEatMeetFood(pt, food)){
				flag = 1;
				createFood(food);
				break;
			}
			pt = pt->next;
		}
	}
	return t;
}


//食物和蛇身重叠检测次数超过重叠检测阀值，则根据蛇运动的方向设置食物坐标
void setFoodLocation(Food *food, Snake *head, int numOverlap, char c){
	if (numOverlap > OVERLAP){
		if (c == 'd'){
			food->x = head->x + 1;
			food->y = head->y + 1;
			if (food->x >= LENGTH)
				food->x -= LENGTH;
		}
		else if (c == 'a'){
			food->x = head->x - 1;
			food->y = head->y - 1;
			if (food->x >= LENGTH)
				food->x -= LENGTH;
		}
		else if (c == 'w'){
			food->x = head->x + 1;
			food->y = head->y + 1;
			if (food->x >= LENGTH)
				food->x -= LENGTH;
		}
		else if (c == 's'){
			food->x = head->x - 1;
			food->y = head->y - 1;
			if (food->x >= LENGTH)
				food->x -= LENGTH;
		}
	}
}


//设置当前按键
char setCurKeyButton(char c){
	char c1 = _getch();
	if (c1 == 27)
		return 'x';
	if (c != 'd'&&c1 == 'a')
		c = c1;
	else if (c != 'a' && c1 == 'd')
		c = c1;
	else if (c != 'w' && c1 == 's')
		c = c1;
	else if (c != 's'&& c1 == 'w')
		c = c1;
	return c;
}


//处理蛇的移动
void snakeMove(Snake *head, Snake *rear, char c){
	Snake *pt = rear;
	while (pt != head){
		pt->x = pt->pre->x;
		pt->y = pt->pre->y;
		pt = pt->pre;
	}
	if (c == 's'){
		head->y += 1;
		if (head->y >= WIDTH)
			head->y -= WIDTH;
	}
	else if (c == 'a'){
		head->x -= 1;
		if (head->x >= WIDTH)
			head->x -= WIDTH;
	}
	else if (c == 'w'){
		head->y -= 1;
		if (head->y >= WIDTH)
			head->y -= WIDTH;
	}
	else if (c == 'd'){
		head->x += 1;
		if (head->x >= WIDTH)
			head->x -= WIDTH;
	}
}


//绘制蛇、食物、围墙
void drawPicture(Snake *head, Food *food){
	int flag;
	Snake *pt;
	system("cls");
	printf("--------------------------------------------\n");  //绘制上围墙
	for (int j = 0; j < WIDTH; j++){
		printf("|");										  //绘制左围墙
		for (int i = 0; i < LENGTH; i++){
			flag = 0;
			pt = head;
			while (pt){								//绘制蛇
				if (i == pt->x&&j == pt->y){
					if (pt == head)
						printf("■");				//绘制蛇头
					else
						printf("□");				//绘制蛇身
					flag = 1;
					break;
				}
				pt = pt->next;
			}
			if (flag == 0){							//绘制食物
				if (i == food->x&&j == food->y){
					putchar(food->c);
					putchar(food->c);
					continue;
				}
				printf("  ");
			}
		}
		printf("|");								//绘制右围墙
		putchar('\n');
	}
	printf("--------------------------------------------\n");	//绘制下围墙
}









