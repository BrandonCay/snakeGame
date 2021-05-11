#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
using namespace std;
bool gameOver;

const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;//x,y = position of snake head
int tailX[100], tailY[100];
int nTail;

enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void setUp() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;

}
void draw() {
	system("cls");
	for (int i = 0; i < width+2; ++i) {
		cout << "#";	
	}
	cout << endl;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width+2; ++j) {
			if (j == 0 || j==width+1) {
				cout << "#";
			}
			else if (i == y && j == x) {
				cout << "O";
			}
			else if (i==fruitY && j==fruitX) {
				cout << "F";
			}
			else {
				bool print = true;
				for (int k = 0; k < nTail && print; ++k) {
					if (j == tailX[k] && i == tailY[k]) {
						cout << "o";//asd
						print = false;
					}
				}
				if(print)
					cout << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width+2; ++i) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}
void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver=true;
			break;
		}
	}

}
void logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2x, prev2y;
	tailX[0] = x;
	tailY[0] = y;//asd
	for (int i = 1; i < nTail; ++i) {
		prev2x = tailX[i];//save
		prev2y = tailY[i];
		tailX[i] = prevX;//give
		tailY[i] = prevY;
		prevX = prev2x;//save
		prevY = prev2y;
	}
	switch (dir) {
	case UP:
		--y;
		break;
	case LEFT:
		--x;
		break;
	case RIGHT:
		++x;
		break;
	case DOWN:
		++y;
		break;
	default:
		break;
	}
	if (x<0 || x>width || y<0 || y>height) {
		gameOver = true;
	}
	for (int i = 0; i < nTail; ++i) {
		if (x == tailX[i] && y == tailY[i]) {
			gameOver = true;
		}
	}
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		while ((fruitX <= 2 || fruitX >=20) || (fruitY >= 20 || fruitY <= 2)) {
			srand(time(NULL));
			fruitX = rand() % width;
			fruitY = rand() % height;
		}
		++nTail;
	}
}
int main() {
	setUp();
	while (!gameOver) {
		draw();
		input();
		logic();
		Sleep(30);
	}
	return 0;
}
