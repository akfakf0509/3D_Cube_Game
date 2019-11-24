#pragma warning(disable:4996)
#pragma warning(disable:6011)
#pragma warning(disable:6031)
#pragma warning(disable:6386)
#include <stdio.h>
#include "console.h"

int face = FACE_FORWARD;
int selectScene = SCENE_MAIN;
int cubeSize;
int ***cubes;
int countTry = 0;
int real_cubeX, real_cubeY, real_cubeZ, real_cubeF;
int page = 0;

void loadScene(int input_scene);
void printFace(int input_face);

int main() {
	setCursorVisibility(1, false);
	loadScene(SCENE_MAIN);
}

void loadScene(int input_scene) {
	int selectScene = input_scene;
	int answer[3];
	switch (input_scene) {
	case SCENE_MAIN:
		selectScene = SCENE_SETING;
		setConsoleSize(35, 8);
		printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
		printf("             Cube Game             \n");
		printf("                                   \n");
		printf("                                   \n");
		printf("                                   \n");
		printf("                                   \n");
		printf(" ▶Game Start◀How to Play  exit   \n");
		printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

		bool breakWhile = false;
		while (!breakWhile) {
			switch (getKeyDown()) {
			case ARROW_RIGHT:
				if (selectScene == SCENE_EXIT)
					continue;
				selectScene++;
				switch (selectScene) {
				case SCENE_SETING:
					setCursorPos(0, 6);
					printf(" ▶Game Start◀How to Play  exit   \n");
					break;
				case SCENE_HOWTOPLAY:
					setCursorPos(0, 6);
					printf("   Game Start▶How to Play◀exit   \n");
					break;
				case SCENE_EXIT:
					setCursorPos(0, 6);
					printf("   Game Start  How to Play▶exit◀ \n");
					break;
				}
				break;
			case ARROW_LEFT:
				if (selectScene == SCENE_SETING)
					continue;
				selectScene--;
				switch (selectScene) {
				case SCENE_SETING:
					setCursorPos(0, 6);
					printf(" ▶Game Start◀How to Play  exit   \n");
					break;
				case SCENE_HOWTOPLAY:
					setCursorPos(0, 6);
					printf("   Game Start▶How to Play◀exit   \n");
					break;
				case SCENE_EXIT:
					setCursorPos(0, 6);
					printf("   Game Start  How to Play▶exit◀ \n");
					break;
				}
				break;
			case SPACE:
				loadScene(selectScene);
				breakWhile = true;
				break;
			}
		}
		break;
	case SCENE_SETING:
		selectScene = SCENE_INGAME;
		setConsoleSize(35, 8);
		printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
		printf("             Cube Size             \n");
		printf("                                   \n");
		printf(" Input Cube Size :                 \n");
		printf("                                   \n");
		printf("      Max = 10       Min = 3       \n");
		printf("                                   \n");
		printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
		setCursorPos(19, 3); 
		scanf("%d", &cubeSize);
		if (cubeSize > 10)
			cubeSize = 10;
		if (cubeSize < 3)
			cubeSize = 3;

		cubes = (int ***)malloc(sizeof(int **) * cubeSize);
		for (int a = 0; a < cubeSize; a++) {
			cubes[a] = (int **)malloc(sizeof(int *)*cubeSize);
			for (int b = 0; b < cubeSize; b++) {
				cubes[a][b] = (int *)malloc(sizeof(int)*cubeSize);
			}
		}

		for (int a = 0; a < cubeSize; a++) {
			for (int b = 0; b < cubeSize; b++) {
				for (int c = 0; c < cubeSize; c++) {
					cubes[a][b][c] = FAKE_CUBE;
				}
			}
		}

		real_cubeX = random(0, cubeSize - 1);
		real_cubeY = random(0, cubeSize - 1);
		real_cubeZ = random(0, cubeSize - 1);
		real_cubeF = random(400, 405);
		switch (real_cubeF) {
			case FACE_FORWARD:
				cubes[real_cubeX][real_cubeY][0] = REAL_CUBE;
				real_cubeZ = 0;
				break;
			case FACE_BACK:
				cubes[real_cubeX][real_cubeY][cubeSize - 1] = REAL_CUBE;
				real_cubeZ = cubeSize - 1;
				break;
			case FACE_UP:
				cubes[real_cubeX][0][real_cubeZ] = REAL_CUBE;
				real_cubeY = 0;
				break;
			case FACE_DOWN:
				cubes[real_cubeX][cubeSize - 1][real_cubeZ] = REAL_CUBE;
				real_cubeY = cubeSize - 1;
				break;
			case FACE_LEFT:
				cubes[0][real_cubeY][real_cubeZ] = REAL_CUBE;
				real_cubeX = 0;
				break;
			case FACE_RIGHT:
				cubes[cubeSize - 1][real_cubeY][real_cubeZ] = REAL_CUBE;
				real_cubeX = cubeSize - 1;
				break;
		}

		loadScene(selectScene);
		break;
	case SCENE_HOWTOPLAY:
		setCursorPos(0, 0);
		selectScene = SCENE_MAIN;
		breakWhile = false;
		while (!breakWhile) {
			setCursorPos(0, 0);
			switch (page) {
			case 0:
				setConsoleSize(35, 8);
				printf("-=-=-=-=-=-=-=-=-=-=-=-Page< %d/3 >-\n",page);
				printf("             Cube Game             \n");
				printf("                                   \n");
				printf(" 게임시작후 정답인 큐브의 좌표를   \n");
				printf(" 예상 합니다. 틀렸으면 피드백 출력 \n");
				printf("  R : 오른쪽 U : 위쪽   F : 앞쪽   \n");
				printf("  L : 왼쪽   D : 아래쪽 B : 뒷쪽   \n");
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				break;
			case 1:
				setConsoleSize(35, 8);
				printf("-=-=-=-=-=-=-=-=-=-=-=-Page< %d/3 >-\n", page);
				printf("             Cube Game             \n");
				printf("                                   \n");
				printf(" 정답인 큐브는 항상 큐브 바깥면에  \n");
				printf(" 있습니다. 틀렸을시 화살표로 오른쪽\n");
				printf(" 하단에 있는 전개도로 확인이 가능합\n");
				printf(" 니다.확인이 끝나면 스페이스바로   \n");
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				break;
			case 2:
				setConsoleSize(35, 8);
				printf("-=-=-=-=-=-=-=-=-=-=-=-Page< %d/3 >-\n", page);
				printf("             Cube Game             \n");
				printf("                                   \n");
				printf(" 다시 시작합니다. 5번 안에 맞추면  \n");
				printf(" 승리, 초과할시 게임오버입니다.    \n");
				printf(" (단 y좌표는 내려갈수록 커집니다.) \n");
				printf("                                   \n");
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				break;
			case 3:
				setConsoleSize(35, 8);
				printf("-=-=-=-=-=-=-=-=-=-=-=-Page< %d/3 >-\n", page);
				printf("             Cube Game             \n");
				printf("       %%press space to exit%%       \n");
				printf("            □         뒷면        \n");
				printf("            □         윗면        \n");
				printf("          □■□  왼면 정면 오른면 \n");
				printf("            □        아랫면       \n");
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				break;
			}
			switch (getKeyDown()) {
			case ARROW_RIGHT:
				if (page == 3)
					continue;
				page++;
				break;
			case ARROW_LEFT:
				if (page == 0)
					continue;
				page--;
				break;
			case SPACE:
				breakWhile = true;
				loadScene(selectScene);
				break;
			}
		}
		break;
	case SCENE_EXIT:
		exit(0);
		break;
	case SCENE_GAMEOVER:
		printf("You Lose!");
		setCursorPos(0, 1);
		for (int a = 0; a < cubeSize; a++) {
			for (int b = 0; b < cubeSize; b++) {
				printf("  ");
			}
			printf("\n");
		}
		setCursorPos(0, 2);
		printf("You tryied %d\n", countTry);
		printf("Press anykey to exit\n");
		_getch();
		break;
	case SCENE_INGAME:
		selectScene = SCENE_GAMEOVER;
		setConsoleSize(35, 12);
		setCursorPos(0, 0);
		printf("-=-=-=-=-=-=-=-=-=-=-||=-=-=-=-=-=-\n");
		printf("                     ||            \n");
		printf("                     ||▶          \n");
		printf("                     ||            \n");
		printf("                     ||            \n");
		printf("                     || ♥♥♥♥♥ \n");
		printf("                     ||            \n");
		printf("                     ||     □     \n");
		printf("                     ||     □     \n");
		printf("                     ||   □■□   \n");
		printf("                     ||     □     \n");
		printf("-=-=-=-=-=-=-=-=-=-=-||=-=-=-=-=-=-\n");
		setConsoleSize(35, 12);

		breakWhile = false;
		while (!breakWhile) {
			setCursorVisibility(1, true);
			printFace(face);
			setCursorPos(25, 2);
			scanf("%d %d %d", &answer[0], &answer[1], &answer[2]);
			setCursorPos(25, 2);
			printf("          ");
			setCursorPos(25, 3);
			printf("%s%s%s",answer[0] == real_cubeX + 1 ? " - " : answer[0] > real_cubeX + 1 ? " L " : " R ", answer[1] == real_cubeY + 1 ? " - " : answer[1] < real_cubeY + 1 ? " D " : " U ", answer[2] == real_cubeZ + 1 ? " - " : answer[2] < real_cubeZ + 1 ? " B " : " F ");
			for (int a = 0; a < 3; a++)
				answer[a]--;
			setCursorPos(25, 2);
			if (cubes[answer[0]][answer[1]][answer[2]] == REAL_CUBE && countTry <= 5) {
				selectScene = SCENE_WIN;
				breakWhile = true;
				loadScene(selectScene);
			}
			else if(cubes[answer[0]][answer[1]][answer[2]] == REAL_CUBE && countTry > 5){
				breakWhile = true;
				loadScene(selectScene);
			}
			else {
				cubes[answer[0]][answer[1]][answer[2]] = SELECTED_CUBE;
				countTry++;
				switch (countTry) {
				case 1:
					setCursorPos(24, 5);
					printf("♥♥♥♥♡");
					break;
				case 2:
					setCursorPos(24, 5);
					printf("♥♥♥♡♡");
					break;
				case 3:
					setCursorPos(24, 5);
					printf("♥♥♡♡♡");
					break;
				case 4:
					setCursorPos(24, 5);
					printf("♥♡♡♡♡");
					break;
				case 5:
					setCursorPos(24, 5);
					printf("♡♡♡♡♡");
					break;
				}
			}
			setCursorVisibility(1, false);
			printFace(face);

			int checkmode = true;
			while (checkmode && !breakWhile) {
				switch (getKeyDown()) {
				case ARROW_UP:
					if (face == FACE_BACK || face > FACE_BACK)
						continue;
					face++;
					printFace(face);
					break;
				case ARROW_DOWN:
					if (face == FACE_DOWN || face > FACE_BACK)
						continue;
					face--;
					printFace(face);
					break;
				case ARROW_LEFT:
					if (face <= FACE_BACK)
						face = FACE_LEFT;
					if (face == FACE_RIGHT)
						face = FACE_FORWARD;
					printFace(face);
					break;
				case ARROW_RIGHT:
					if (face <= FACE_BACK)
						face = FACE_RIGHT;
					if (face == FACE_LEFT)
						face = FACE_FORWARD;
					printFace(face);
					break;
				case SPACE:
					checkmode = false;
					break;
				}
			}
		}
		break;
	case SCENE_WIN:
		printf("You Win!");
		setCursorPos(0, 1);
		for (int a = 0; a < cubeSize; a++) {
			for (int b = 0; b < cubeSize; b++) {
				printf("  ");
			}
			printf("\n");
		}
		setCursorPos(0, 2);
		printf("You tryied %d\n", countTry);
		printf("Press anykey to exit\n");
		_getch();
		break;
	}
}

void printFace(int input_face) {
	switch (input_face) {
	case FACE_FORWARD:
		setCursorPos(0, 1);
		for (int a = 0; a < cubeSize; a++) {
			for (int b = 0; b < cubeSize; b++) {
				switch (cubes[b][a][0]) {
				case FAKE_CUBE:
					printf("□");
					break;
				case REAL_CUBE:
					printf("□");
					break;
				case SELECTED_CUBE:
					printf("■");
				}
			}
			printf("\n");
		}
		setCursorPos(24, 7);
		printf("     □     ");
		setCursorPos(24, 8);
		printf("     □     ");
		setCursorPos(24, 9);
		printf("   □■□   ");
		setCursorPos(24, 10);
		printf("     □     ");
		break;
	case FACE_BACK:
		setCursorPos(0, 1);
		for (int a = 0; a < cubeSize; a++) {
			for (int b = 0; b < cubeSize; b++) {
				switch (cubes[b][a][cubeSize - 1]) {
				case FAKE_CUBE:
					printf("□");
					break;
				case REAL_CUBE:
					printf("□");
					break;
				case SELECTED_CUBE:
					printf("■");
				}
			}
			printf("\n");
		}
		setCursorPos(24, 7);
		printf("     ■     ");
		setCursorPos(24, 8);
		printf("     □     ");
		setCursorPos(24, 9);
		printf("   □□□   ");
		setCursorPos(24, 10);
		printf("     □     ");
		break;
	case FACE_UP:
		setCursorPos(0, 1);
		for (int a = cubeSize - 1; a >= 0; a--) {
			for (int b = 0; b < cubeSize; b++) {
				switch (cubes[b][0][a]) {
				case FAKE_CUBE:
					printf("□");
					break;
				case REAL_CUBE:
					printf("□");
					break;
				case SELECTED_CUBE:
					printf("■");
				}
			}
			printf("\n");
		}
		setCursorPos(24, 7);
		printf("     □     ");
		setCursorPos(24, 8);
		printf("     ■     ");
		setCursorPos(24, 9);
		printf("   □□□   ");
		setCursorPos(24, 10);
		printf("     □     ");
		break;
	case FACE_DOWN:
		setCursorPos(0, 1);
		for (int a = 0; a < cubeSize; a++) {
			for (int b = 0; b < cubeSize; b++) {
				switch (cubes[b][cubeSize - 1][a]) {
				case FAKE_CUBE:
					printf("□");
					break;
				case REAL_CUBE:
					printf("□");
					break;
				case SELECTED_CUBE:
					printf("■");
				}
			}
			printf("\n");
		}
		setCursorPos(24, 7);
		printf("     □     ");
		setCursorPos(24, 8);
		printf("     □     ");
		setCursorPos(24, 9);
		printf("   □□□   ");
		setCursorPos(24, 10);
		printf("     ■     ");
		break;
	case FACE_RIGHT:
		setCursorPos(0, 1);
		for (int a = 0; a < cubeSize; a++) {
			for (int b = 0; b < cubeSize; b++) {
				switch (cubes[cubeSize - 1][a][b]) {
				case FAKE_CUBE:
					printf("□");
					break;
				case REAL_CUBE:
					printf("□");
					break;
				case SELECTED_CUBE:
					printf("■");
				}
			}
			printf("\n");
		}
		setCursorPos(24, 7);
		printf("     □     ");
		setCursorPos(24, 8);
		printf("     □     ");
		setCursorPos(24, 9);
		printf("   □□■   ");
		setCursorPos(24, 10);
		printf("     □     ");
		break;
	case FACE_LEFT:
		setCursorPos(0, 1);
		for (int a = 0; a < cubeSize; a++) {
			for (int b = cubeSize - 1; b >= 0; b--) {
				switch (cubes[0][a][b]) {
				case FAKE_CUBE:
					printf("□");
					break;
				case REAL_CUBE:
					printf("□");
					break;
				case SELECTED_CUBE:
					printf("■");
				}
			}
			printf("\n");
		}
		setCursorPos(24, 7);
		printf("     □     ");
		setCursorPos(24, 8);
		printf("     □     ");
		setCursorPos(24, 9);
		printf("   ■□□   ");
		setCursorPos(24, 10);
		printf("     □     ");
		break;
	}
}