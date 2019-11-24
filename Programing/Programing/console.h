#pragma once
#pragma warning(disable:4996)
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

#define OUTPUT_HANDLE GetStdHandle(STD_OUTPUT_HANDLE)

enum CUBE_TYPE {
	FAKE_CUBE = 600, REAL_CUBE, SELECTED_CUBE
};

enum GAME_SCENE {
	SCENE_MAIN = 500, SCENE_SETING, SCENE_HOWTOPLAY, SCENE_EXIT, SCENE_GAMEOVER, SCENE_INGAME, SCENE_WIN
};
enum CUBE_FACE {
	FACE_DOWN = 400, FACE_FORWARD, FACE_UP, FACE_BACK, FACE_RIGHT, FACE_LEFT
};

enum INPUT_KEYCODE {
	ARROW_UP = 300, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT, SPACE
};

typedef struct _BOX_SIZE {
	short width, height;
} BOX_SIZE;

BOX_SIZE consoleSize = { 120, 30 };

void setCursorPos(short x, short y);
void setCursorVisibility(unsigned long size, bool visibility);
void setConsoleSize(short width, short height);
int getKeyDown();
int random(int min, int max);

void setCursorPos(short x, short y) {
	COORD position = { x, y };
	SetConsoleCursorPosition(OUTPUT_HANDLE, position);
}

void setCursorVisibility(unsigned long size, bool visibility) {
	CONSOLE_CURSOR_INFO cursorInfo = { size, visibility };
	SetConsoleCursorInfo(OUTPUT_HANDLE, &cursorInfo);
}

void setConsoleSize(short width, short height) {
	SMALL_RECT rect = { 0, 0, width, height };
	SetConsoleWindowInfo(OUTPUT_HANDLE, TRUE, &rect);

	COORD bufferSize = { width + 1, height + 1 };
	SetConsoleScreenBufferSize(OUTPUT_HANDLE, bufferSize);

	consoleSize.height = height, consoleSize.width = width;
}

int getKeyDown() {
	if (_kbhit()) {
		unsigned char ch = _getch();
		if (ch == 224) {
			switch (_getch()) {
			case 72:
				return ARROW_UP;
				break;
			case 75:
				return ARROW_LEFT;
				break;
			case 77:
				return ARROW_RIGHT;
				break;
			case 80:
				return ARROW_DOWN;
				break;
			}
		}
		else if (ch == ' ')
			return SPACE;
		else
			return ch;
	}
	return -1;
}

int rand_int = 0;

int random(int min, int max) {
	srand(rand_int++ + time(NULL));
	return rand() % (max - min + 1) + min;
}