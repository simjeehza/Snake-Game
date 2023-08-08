#include <iostream>
#include <conio.h> 
#include <windows.h> 

using namespace std;

bool gameOver;
const int width = 30;
const int height = 30;
int x, y, xFruit, yFruit;
int score = 0;
int hScore = score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

int tailX[100], tailY[100]; 
int nTail = 0; 

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    xFruit = rand() % width;
    yFruit = rand() % height;
    score = 0;
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 1; i++) {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                cout << "#";
            }
            else if (i == y && j == x) {
                cout << "O"; 
            }
            else if (i == yFruit && j == xFruit) {
                cout << "F"; // Draw the fruit
            }
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Draw the snake tail
                        printTail = true;
                    }
                }
                if (!printTail) {
                    cout << " ";
                }
            }
            if (j == width - 1) {
                cout << "#";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 1; i++) {
        cout << "#";
    }
    cout << endl;
}

void Input() {
    if (_kbhit()) { 
        switch (_getch()) { 
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
            gameOver = true; // Exit the game
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

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
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


    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;


    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true; 
        }
    }

    if (x == xFruit && y == yFruit) {
        score += 10;
        if (score > hScore) {
            hScore = score;
        }
        xFruit = rand() % width;
        yFruit = rand() % height;
        nTail++;
    }
}

void DrawGameOver() {
    system("cls");
    cout << "GAME OVER" << endl;
    cout << "Score: " << score << endl;
    cout << "High Score: " << hScore << endl;
    cout << "Play again? (Y/N): ";
}

bool PlayAgain() {
    char choice = _getch();
    return (choice == 'y' || choice == 'Y');
}

int main() {
    bool playagain = true;
    Setup();
    while(playagain){
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(100); 
        }

        DrawGameOver();
        Sleep(1000);

        playagain = PlayAgain();

        if(playagain) {
            Setup();
        }
    }
    cout << "Thanks for playing!" << endl;
    return 0;
}
