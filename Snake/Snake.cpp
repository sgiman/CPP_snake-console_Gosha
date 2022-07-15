// -------------------------------------------------------------------------------------
// SNAKE | FINAL (for only Console)
// Создание игры на C++ / Змейка
// https://www.youtube.com/watch?v=6qaAZTwemXY&list=PL0lO_mIqDDFXqS9ww1Xu8dZ-0zFQYFaGr
//--------------------------------------------------------------------------------------
// Visual Studio 2019
// GOSHA & SGIMAN @ 2022
//--------------------------------------------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };	// направление движени¤
eDirection dir;
int tailX[100], tailY[100];								// длина хвоста змейки
int nTail;												// кол-во элементов хвоста 

int sleep_time = 100;									// переменная частоты кадров 

//-------- Настройка параметров --------
void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

//-------- ќтрисовка игровой карты --------
void Draw() {

	system("cls");										// очистить терминал
	bool print = false;

	for (int i = 0; i < width + 1; i++)
		cout << "#";									// верхняя "граница" (строка)
	cout << endl;										// конец строки 

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				cout << "#";							// боковая граница
			if (i == y && j == x)						// ecли координаты совпадают,	
				cout << "0";							// тогда змейка "0"
			else if (i == fruitY && j == fruitX)		// иначе координаты 
				cout << "F";							// дл¤ фрукта "F"
			else
			{
				print = false;							// не рисовать хвост
				for (int k = 0; k < nTail; k++)			// наращивание хвоста змейки 
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;					// рисовать хвост
						cout << "o";
					}
			}

			if (!print)
				cout << " ";							// остальное заполнить пробелами 
		}
		cout << endl;									// конец строки	
	}

	for (int i = 0; i < width + 1; i++)
		cout << "#";									// нижняя "граница" (строка)

	cout << endl;										// конец строки 
	cout << "Score: " << score << endl;					// общий счет
}

//-------- Ввод с клавы комманд --------
void Input() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

//-------- Логика игры (?) --------
void Logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)	// наращивание хвоста змейки
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)					// пeремещенине змейки  
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	// if (x > width || x < 0 || y > height || y < 0)	// если змейка за границами игрового поля - выйти из игры 
	//	gameOver = true;
	
	if (x >= width)									// если имеется касание границ - продолжать
		x = 0;
	else if (x < 0)
		x = width - 2;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < nTail; i++)					// выйти из игры, если змейка съела свой хвост
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)					// если найден фрукт 
	{
		score += 10;								//	добавтиь очки
		fruitX = rand() % width;					//	новые координаты дл¤ фрукта
		fruitY = rand() % height;
		nTail++;									// после поедани¤ фрукта - хвост змейки на единицу больше 
	}

}

/*=============== MAIN  ===============*/
int main()
{
	Setup();
	while (!gameOver)
	{
		Sleep(sleep_time);	// задержка потока программы на заданный ранее интервал
		Draw();				// отрисовка игровой карты 	
		Input();			// ввод комманд
		Logic();			// логика игры
	}
	return 0;
}
/*=============== END ===============*/
