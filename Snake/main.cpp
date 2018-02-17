#include "Map.h"
#include <unistd.h>
#include <thread>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define DUP 72
#define DDOWN 80
#define DLEFT 75
#define DRIGHT 77
#define EXIT 27

Point MapSize(10, 20);

void getKey()
{
	Way way;
	Snake *snake = Snake::getSnake();
	while(true)
	{
		system("stty raw -echo");
		char key = getchar();
		system("stty cooked");
		switch(key)
		{
			case DUP:
				if(snake->getWay() != DOWN)
				  snake->setWay(UP);
				break;
			case DDOWN:
				if(snake->getWay() != UP)
				  snake->setWay(DOWN);
				break;
			case DLEFT:
				if(snake->getWay() != RIGHT)
				  snake->setWay(LEFT);
				break;
			case DRIGHT:
				if(snake->getWay() != LEFT)
				  snake->setWay(RIGHT);
				break;
			case EXIT:
				std::exit(0);
		}
		std::this_thread::sleep_for(std::chrono::microseconds(50));
	}	
}

int main()
{
	Snake *snake = Snake::getSnake();
	snake->resize(MapSize, 3);
	Map map(MapSize);
	//std::thread getKeyThread(getKey);
	//getKeyThread.join();
	while(true)
	{
		map.flush();
		snake->move();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return 0;
}
