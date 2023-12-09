#include <iostream>
#include <synchapi.h>
#include <conio.h>
#include <string>
#include <stack>
#include <deque>
#include <ctime>
#include "windows.h"


const int weight = 30;
const int height = 40;
bool status;
int headX, headY;
int fruitX, fruitY;
int minusX, minusY;
using namespace std;
enum Direction {
    STOP = 0, UP, DOWN, RIGHT, LEFT
};
Direction dir;
int score;
int tailsX[100];
int tailsY[100];
deque<int> tailsNumber;
int tails;
bool eat = false;

void creatFruit();

void creatMinus();

void SetWindowSize1(int cols, int lines);

void Setup() {
    std::srand(std::time(nullptr));
    status = true;
    dir = STOP;
    headX = weight / 2;
    headY = height / 2;
    creatFruit();
    creatMinus();
    SetWindowSize1(height * 2, weight * 2);
    score = 0;
    tails = 0;
}

void SetWindowSize1(int cols, int lines)//设置窗口大小
{
    system("title Snako");//设置窗口标题
    char cmd[30];
    sprintf(cmd, "mode con cols=%d lines=%d", cols, lines);//一个图形■占两个字符，故宽度乘以2
    system(cmd);//system(mode con cols=88 lines=88)设置窗口宽度和高度
}

void creatFruit() {
    fruitX = headX;
    fruitY = headY;
    while (fruitX == headX || fruitX == 0 || fruitX == weight - 1 || fruitX == minusX) fruitX = rand() % weight;
    while (fruitY == headY || fruitY == 0 || fruitY == height - 1 || fruitY == minusY) fruitY = rand() % height;
}

void creatMinus() {
    minusX = headX;
    minusY = headY;
    while (minusX == headX || minusX == 0 || minusX == weight - 1 || minusX == fruitX) minusX = rand() % weight;
    while (minusX == headY || minusX == 0 || minusX == height - 1 || minusY == fruitY) minusY = rand() % height;
}

void Draw() {
    system("cls");
//    system("chcp 65001");
    string output;
    for (int i = 0; i < weight; ++i) {
        for (int j = 0; j < height; ++j) {
            if (i == 0 || j == 0 || i == weight - 1 || j == height - 1) {
                output += '#';
            } else if (i == minusX && j == minusY) {
                output += "\033[36m-\033[0m";
            } else if (i == fruitX && j == fruitY) {
                output += "\033[38mF\033[0m";
            } else if (i == headX && j == headY) {
                output += "\033[37m0\033[0m";
            } else {
                bool isTail = false;
                for (int k = 0; k < tails; ++k) {
                    if (i == tailsX[k] && j == tailsY[k]) {
                        int num = tailsNumber[k];
                        switch (num) {
                            case 1:
                                output += "\033[31mo\033[0m";
                                break;
                            case 2:
                                output += "\033[32mo\033[0m";
                                break;
                            case 4:
                                output += "\033[33mo\033[0m";
                                break;
                            case 8:
                                output += "\033[34mo\033[0m";
                                break;
                            case 16:
                                output += "\033[35mo\033[0m";
                                break;
                            case 32:
                                output += "\033[36mo\033[0m";
                                break;
                        }
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
    cout << endl;
    cout << "\033[31m" << "o:" << "\033[0m" << "1\t";
    cout << "\033[32m" << "o:" << "\033[0m" << "2\t";
    cout << "\033[33m" << "o:" << "\033[0m" << "4\n";
    cout << "\033[34m" << "o:" << "\033[0m" << "8\t";
    cout << "\033[35m" << "o:" << "\033[0m" << "16\t";
    cout << "\033[36m" << "o:" << "\033[0m" << "32\t";

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
        if (tails == 0 || tailsNumber.front() != 1) {
            tails++;
            score += 1;
            tailsNumber.push_front(1);
        } else {
            int temp = 1;
            tails++;
            while (!tailsNumber.empty() && temp == tailsNumber.front()) {
                temp += tailsNumber.front();
                score += temp;
                tailsNumber.pop_front();
                tails--;
            }
            tailsNumber.push_front(temp);
        }
        creatFruit();
    } else if (headX == minusX && headY == minusY) {
        if (tails > 0) {
            tails--;
            tailsNumber.pop_front();
            creatMinus();
        }
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
    system("cls");
    cout << "Game over!";
    system("pause");
}
