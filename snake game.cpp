#include <iostream>
#include <Windows.h>

using namespace std;

bool gameOver;
bool snakeMode;
bool borderMode = true;

int width = 20;
int height = 10;
int x, y, obj_x, obj_y, score;
int tail_x[100], tail_y[100];
int tailVolume = 0;

enum direction { STOP, LEFT, RIGHT, UP, DOWN };
enum speed { SLOW = 180, MIDLE = 125, FAST = 10 };

direction dir;
speed snakeSpeed;

void setting();
void setup();
void drawGame();
void gameControl();
void operatingLogic();

void start() {
	int choose;
	cout << "1. Start game" << endl;
	cout << "2. Setting" << endl;
	cin >> choose;
	system("cls");
	if (choose == 1) {
		while (!gameOver) {
			drawGame();
			gameControl();
			operatingLogic();
		}
	} else if (choose == 2) {
		setting();
	}
}

void setting() {
	int temp;
	int choose;
	bool state = true;

	while (state) {
		cout << "1. Set the snake's speed" << endl;
		cout << "2. Set map size" << endl;
		cout << "3. Set the border mode" << endl;
		cout << "4. Exit" << endl << "Your choose: ";
		cin >> choose;
		
		if (choose == 1)
		{
			system("cls");
			cout << "1. Slow" << endl;
			cout << "2. Midle" << endl;
			cout << "3. Fast" << endl << endl << "Your choose: ";
			cin >> choose;
			system("cls");
			switch (choose)
			{
			case 1:
				snakeSpeed = speed::SLOW;
				break;
			case 2:
				snakeSpeed = speed::MIDLE;
				break;
			case 3:
				snakeSpeed = speed::FAST;
				break;
			}
		}
		else if (choose == 2) {
			system("cls");
			cout << "1. Small" << endl;
			cout << "2. Medium" << endl;
			cout << "3. Big" << endl << "Your choose: ";
			cin >> choose;
			system("cls");
			if (choose == 1) {
				width = 20;
				height = 10;
			} else if (choose == 2) {
				width = 30;
				height = 15;
			} else if (choose == 3) {
				width = 35;
				height = 20;
			}
		}
		else if (choose == 3) {
			system("cls");
			cout << "1. Walking through a wall" << endl;
			cout << "2. Death against the wall" << endl;
			cin >> temp;
			system("cls");
			if (temp == 1) {
				borderMode = true;
				
			}
			else if (temp == 2) {
				borderMode = false;
			}
		}
		else if (choose == 4) {
			system("cls");
			start();
		}
	}
}

void setup() {
	srand(time(NULL));
	gameOver = false;

	dir = STOP;

	x = width / 2 - 1;
	y = height / 2 - 1;
	obj_x = rand() % width;
	obj_y = rand() % height;

	score = 0;
}

void drawGame() {
	system("cls");

	for (int i = 0; i < width + 1; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				cout << "#";
			}
			if (i == y && j == x) {
				cout << "0";
			} else if (i == obj_y && j == obj_x) {
				cout << "*";
			}
			else {
				bool printN = false;

				for (int k = 0; k < tailVolume; k++) {
					if (tail_x[k] == j && tail_y[k] == i) {
						printN = true;
						cout << "o";
					}
				}

				if (!printN) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++) {
		cout << "#";
	}

	cout << endl;
	cout << "Your score: " << score;

	cout << endl;
	cout << "Coord X: " << x << "	" << "Coord Y: " << y;

	Sleep(snakeSpeed);
}

void gameControl() {
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		dir = LEFT;
		
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		dir = RIGHT;
		
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000) {
		dir = UP;
		
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		dir = DOWN;
		
	}
	else if (GetAsyncKeyState('X') & 0x8000) {
		gameOver = true;
		cout << endl;
		exit(0);
	}
	else if (GetAsyncKeyState('A') & 0x8000) {
		dir = LEFT;
		
	}
	else if (GetAsyncKeyState('D') & 0x8000) {
		dir = RIGHT;
		
	}
	else if (GetAsyncKeyState('W') & 0x8000) {
		dir = UP;
		
	}
	else if (GetAsyncKeyState('S') & 0x8000) {
		dir = DOWN;
		
	}
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
		gameOver = true;
		cout << endl;
		exit(0);
	}
}

void operatingLogic() {
	int prev_x = tail_x[0];
	int prev_y = tail_y[0];
	int prev2x, prev2y;

	tail_x[0] = x;
	tail_y[0] = y;

	for (int i = 1; i < tailVolume; i++) {
		prev2x = tail_x[i];
		prev2y = tail_y[i];

		tail_x[i] = prev_x;
		tail_y[i] = prev_y;

		prev_x = prev2x;
		prev_y = prev2y;
	}

	switch (dir)
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

	if (borderMode == true) {
		if (x >= width - 1) {
			x = 0;
		}
		else if (x < 0) {
			x = width - 2;
		}

		if (y >= height) {
			y = 0;
		}
		else if (y < 0) {
			y = height - 1;
		}
	}
	else if (borderMode == false) {
		if (x > width - 2 || x < 0) {
			gameOver = true;
			exit(0);
		}
		if (y > height - 1 || y < 0) {
			gameOver = true;
			exit(0);
		}
	}

	for (int i = 0; i < tailVolume; i++) {
		if (tail_x[i] == x && tail_y[i] == y) {
			gameOver = true;
			exit(0);
		}
	}

	if (x == obj_x && y == obj_y) {
		score++;
		obj_x = rand() % width;
		obj_y = rand() % height;
		tailVolume++;

	}
}

int main() {
	setup();
	start();

	return 0;
}