#include <iostream>
#include <synchapi.h>
#include <conio.h>
#include <string>
#include "windows.h"


const int weight = 30;
const int height = 40;
bool status;
int headX, headY;
int fruitX, fruitY;
using std::string;
using std::cout;
using std::endl;
enum Direction {
    STOP = 0, UP, DOWN, RIGHT, LEFT
};
Direction dir;
int score;
int tailsX[100];
int tailsY[100];
int tails;
bool eat = false;

void creatFruit();

void Setup() {
    status = true;
    dir = STOP;
    headX = weight / 2;
    headY = height / 2;
    creatFruit();
    score = 0;
    tails = 0;
}

void creatFruit() {
    fruitX = headX;
    fruitY = headY;
    while (fruitX == headX || fruitX == 0 || fruitX == weight - 1) fruitX = rand() % weight;
    while (fruitY == headY || fruitY == 0 || fruitY == height - 1) fruitY = rand() % height;
}

void Draw() {
    system("cls");
    string output;
    for (int i = 0; i < weight; ++i) {
        for (int j = 0; j < height; ++j) {
            if (i == 0 || j == 0 || i == weight - 1 || j == height - 1) {
                output += '#';
            } else if (i == fruitX && j == fruitY) {
                output += "\033[35mF\033[0m";
            } else if (i == headX && j == headY) {
                output += "\033[33m0\033[0m";
            } else {
                bool isTail = false;
                for (int k = 0; k < tails; ++k) {
                    if (i == tailsX[k] && j == tailsY[k]) {
                        output += "\033[32mo\033[0m";
                        isTail = !isTail;
                        break;
                    }
                }
                if (!isTail) output += ' ';
            }
        }
        output += '\n';
    }
    cout << output;
    cout << "\033[31m" << "Score:" << score << "\033[0m";

//    cout << "Fx" << fruitX << "  Fy" << fruitY<<std::endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                if (tails != 0 && dir == RIGHT)break;
                dir = LEFT;
                break;
            case 's':
                if (tails != 0 && dir == UP)break;
                dir = DOWN;
                break;
            case 'd':
                if (tails != 0 && dir == LEFT)break;
                dir = RIGHT;
                break;
            case 'w':
                if (tails != 0 && dir == DOWN)break;
                dir = UP;
                break;
            case 27:
            case 'p':
                status = false;
                break;
        }
    }
}

void Logic() {
    int preX = tailsX[0];
    int preY = tailsY[0];
    int pre2X, pre2Y;
    tailsX[0] = headX;
    tailsY[0] = headY;
    for (int i = 1; i < tails; ++i) {
        pre2X = tailsX[i];
        pre2Y = tailsY[i];
        tailsX[i] = preX;
        tailsY[i] = preY;
        preX = pre2X;
        preY = pre2Y;
    }
    switch (dir) {
        case LEFT:
            headY--;
            break;
        case RIGHT:
            headY++;
            break;
        case UP:
            headX--;
            break;
        case DOWN:
            headX++;
            break;
        default:
            break;
    }
    if (headX == weight - 1) headX = 1;
    else if (headX == 0) headX = weight - 2;
    if (headY == height - 1) headY = 1;
    else if (headY == 0) headY = height - 2;
    for (int i = 0; i < tails; ++i) {
        if (tailsX[i] == headX && tailsY[i] == headY) {
            status = !status;
            return;
        }
    }
    if (headX == fruitX && headY == fruitY) {
        score += 10;
        tails++;
        creatFruit();
    }
}

int main() {
    Setup();
    while (status) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
}
