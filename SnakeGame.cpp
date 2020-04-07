#include <iostream>
#include <conio.h>                  //For giving input without pressing enter.
#include <windows.h>                //For system("cls");
bool gameOver, stop;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
  
void Setup() {
    nTail = 0;
    gameOver = false;
    dir = STOP;                     //Initializes the to be in stopping position
    x = width / 2;                  //Sets the starting point at middle of the map
    y = height / 2;                 //Same as above
    fruitX = (rand() % width) + 1;  //+1 so that the fruit doesn't spawn in the border 
    fruitY = (rand() % height) + 1;
    score = 0;
}

void Draw() {
    system("cls");                                          //Clears the screen
    for(int i = 0; i <= height + 2; i++) {                 
        for(int j = 0; j <= width + 2; j++) {
            if(i == 0 || i == height + 2) {                 //Prints out the horizontal border
                std::cout << "#";
            } else {
                if(j == 0 || j == width + 2) {              //Prints out the verticle border
                    std::cout << "|";
                } else if(i == y && j == x) {               //Prints out the head of snake
                    std::cout << "O";
                } else if(i == fruitY && j == fruitX) {     //Prints out the fruit
                    std::cout << "F";
                } else {
                    bool print = false;                     
                    for(int k = 0; k < nTail; k++) {
                        if(tailX[k] == j && tailY[k] == i) {    //Prints out the body
                            std::cout << "*";
                            print = true;                   //Checks if segment of the body is there
                        }
                    }
                    if(!print) std::cout << " ";            //Reduces a space to maintain border deformity 
                }                                           //if a body is taking up some space
            }
        }
        std::cout << "\n";
    }
    std::cout << "Score: " << score << "\n" << "Made by Pallab XD" << "\n";
}

void Input() {                         //Control system
    if (_kbhit()) {
        switch(_getch()) {
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
            stop = true;
            break;
        case 'r':
            gameOver = false;           //Retry button
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir) {
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
        default:
            break;
    }
    if(x >= width + 2 || x <= 0 || y >= height + 2 || y <= 0) {     //Gameover if snake touches the boundary
        gameOver = true;
    }
    for(int i = 0; i < nTail; i++) {
        if(x == tailX[i] && y == tailY[i]) {                        //Gameover if snake head touches the tail
            gameOver = true;
        }
    }
    
    if(x == fruitX && y == fruitY) {                                //Eats fruit
        score += 10;
        fruitX = (rand() % width) + 1;                              //Randomly generates another fruit after eating the first one
        fruitY = (rand() % height) + 1;
        nTail++;
    }
}

void Pause() {
    std::cout << "\nPress R to retry and X to exit" << "\n\n" << "Your score: " << score;
}

int main() {
    while(!stop) {
        Setup();
        while(!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(100);
        }
        Pause();
        while(gameOver && !stop) {
            Input();
        }
    }
    return 0;
}