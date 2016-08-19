
#include <Windows.h>
#include "tetris.h"
#include <stdlib.h>
char strScore[10] = { 0 };
char g_arrBG[20][10] = { 0 };//use char to save space
char g_arrSquare[2][4] = { 0 };
int g_nSquareID = -1;
int g_nRow = -1;
int g_nCol = -1;
int g_nScore = 0;


void OnPaint(HDC hDc) {

	//creating compatable DC
	HDC hMemDC = CreateCompatibleDC(hDc);

	//creating bitmap
	HBITMAP hBitmapBG = CreateCompatibleBitmap(hDc, 500, 600);//background

															  //connecting them
	SelectObject(hMemDC, hBitmapBG);

	PaintSquare(hMemDC);
	ShowSquare2(hMemDC);

	ShowScore(hMemDC);

	//passing
	BitBlt(hDc, 0, 0, 500, 600, hMemDC, 0, 0, SRCCOPY);


	DeleteObject(hBitmapBG);
	DeleteDC(hMemDC);
}

void ShowScore(HDC hMemDC) {
	Rectangle(hMemDC, 300, 0, 500, 600);
	_itoa_s(g_nScore, strScore, 10 * sizeof(char), 10);
	TextOut(hMemDC, 330, 40, "press ENTER to start", strlen("press ENTER to start"));
	TextOut(hMemDC, 370, 70, "SCORE:", strlen("score:"));
	TextOut(hMemDC, 395, 100, strScore, strlen(strScore));

}

void OnCreate() {
	srand((unsigned int)time(NULL));
	CreateRandomSquare();
	CopySquareToBG();
}

void PaintSquare(HDC hMemDC) {
	int i, j = 0;

	Rectangle(hMemDC, 0, 0, 300, 600);
	//g_arrBG[2][4] = 1;
	//g_arrBG[3][3] = 1;
	//g_arrBG[3][4] = 1;
	//g_arrBG[3][5] = 1;
	//smaller squares 
	HBRUSH hOldBrush;
	HBRUSH hNewBrush = CreateSolidBrush(RGB(160, 160, 160));
	hOldBrush = SelectObject(hMemDC, hNewBrush);
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 10; j++) {
			//drawing
			if (1 == g_arrBG[i][j])
				Rectangle(hMemDC, 30 * j, 30 * i, 30 * j + 30, 30 * i + 30);
		}
	}
	hNewBrush = SelectObject(hMemDC, hOldBrush);
	DeleteObject(hNewBrush);
}

int CreateRandomSquare() {


	int nIndex = rand() % 7;
	//int nIndex = 5;
	switch (nIndex) {

	case 0://z
		g_arrSquare[0][0] = 1;
		g_arrSquare[0][1] = 1;
		g_arrSquare[0][2] = 0;
		g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 0;
		g_arrSquare[1][1] = 1;
		g_arrSquare[1][2] = 1;
		g_arrSquare[1][3] = 0;
		g_nRow = 0;
		g_nCol = 3;
		break;
	case 1://z
		g_arrSquare[0][0] = 0;
		g_arrSquare[0][1] = 1;
		g_arrSquare[0][2] = 1;
		g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 1;
		g_arrSquare[1][1] = 1;
		g_arrSquare[1][2] = 0;
		g_arrSquare[1][3] = 0;
		g_nRow = 0;
		g_nCol = 3;
		break;
	case 2://L
		g_arrSquare[0][0] = 1;
		g_arrSquare[0][1] = 0;
		g_arrSquare[0][2] = 0;
		g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 1;
		g_arrSquare[1][1] = 1;
		g_arrSquare[1][2] = 1;
		g_arrSquare[1][3] = 0;
		g_nRow = 0;
		g_nCol = 3;
		break;
	case 3://L
		g_arrSquare[0][0] = 0;
		g_arrSquare[0][1] = 0;
		g_arrSquare[0][2] = 1;
		g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 1;
		g_arrSquare[1][1] = 1;
		g_arrSquare[1][2] = 1;
		g_arrSquare[1][3] = 0;
		g_nRow = 0;
		g_nCol = 3;
		break;
	case 4://.|.
		g_arrSquare[0][0] = 0;
		g_arrSquare[0][1] = 1;
		g_arrSquare[0][2] = 0;
		g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 1;
		g_arrSquare[1][1] = 1;
		g_arrSquare[1][2] = 1;
		g_arrSquare[1][3] = 0;
		g_nRow = 0;
		g_nCol = 3;
		break;
	case 5://----
		g_arrSquare[0][0] = 1;
		g_arrSquare[0][1] = 1;
		g_arrSquare[0][2] = 1;
		g_arrSquare[0][3] = 1;
		g_arrSquare[1][0] = 0;
		g_arrSquare[1][1] = 0;
		g_arrSquare[1][2] = 0;
		g_arrSquare[1][3] = 0;
		g_nRow = 0;
		g_nCol = 4;
		break;
	case 6://[]
		g_arrSquare[0][0] = 0;
		g_arrSquare[0][1] = 1;
		g_arrSquare[0][2] = 1;
		g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 0;
		g_arrSquare[1][1] = 1;
		g_arrSquare[1][2] = 1;
		g_arrSquare[1][3] = 0;
		g_nRow = 0;
		g_nCol = 4;
		break;
	}
	
	g_nSquareID = nIndex;
	//g_nSquareID = 5;
	return nIndex;
}

void CopySquareToBG() {
	int i = 0;
	int j = 0;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) {
			g_arrBG[i][j + 3] = g_arrSquare[i][j];
		}
	}
}

void OnReturn(HWND hWnd) {
	SetTimer(hWnd, DEF_TIMER1, 500, NULL);

}

void SquareFall() {
	for (int i = 19; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (1 == g_arrBG[i][j]) {
				g_arrBG[i + 1][j] = g_arrBG[i][j];
				g_arrBG[i][j] = 0;
			}
		}
	}
}

void OnTimer(HWND hWnd) {
	HDC hDc = GetDC(hWnd);

	if (1 == CanSquareFall() && 1 == CanSquareStack()) {
		SquareFall();
		g_nRow++;
	}
	else {
		//alter the value of square if the item can not fall
		ChangeSqrVal();
		RemoveRow();
		if (0 == GameOver(hWnd)) {
			KillTimer(hWnd, DEF_TIMER1);
			//return 0;
		}
		CreateRandomSquare();
		CopySquareToBG();
	}

	OnPaint(hDc);

	ReleaseDC(hWnd, hDc);
}

int GameOver(HWND hWnd) {
	int i = 0;
	for (i = 0; i < 10; i++) {
		if (g_arrBG[0][i] == 2) {
			//game over, pop up a window
			int GameoverInfo = MessageBox(hWnd, "gameover", "Message", MB_RETRYCANCEL);
			//return 0;
			//retry function
			switch (GameoverInfo) {
			case IDRETRY:
				OnReturn(hWnd);//restart
				g_nScore = 0;
				//clear the game area
				for (int i = 0; i < 20; i++) {
					for (int j = 0; j < 10; j++) {
						g_arrBG[i][j] = 0;
					}
				}
				return 1;
				break;
			case IDCANCEL:
				KillTimer(hWnd, DEF_TIMER1);
				PostQuitMessage(0);//WM_CLOSE, WM_DESTROY, WE_QUIT
				return 0;
				break;
			}
		}
	}
	return 1;
}

int CanSquareFall() {
	for (int i = 0; i < 10; i++) {
		if (1 == g_arrBG[19][i])
			return 0;
	}
	return 1;
}

void ChangeSqrVal() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (1 == g_arrBG[i][j])
				g_arrBG[i][j] = 2;
		}
	}
}

void ShowSquare2(HDC hMemDC) {
	HBRUSH hOldBrush;
	HBRUSH hNewBrush = CreateSolidBrush(RGB(120, 120, 120));
	hOldBrush = SelectObject(hMemDC, hNewBrush);
	SelectObject(hMemDC, hNewBrush);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (2 == g_arrBG[i][j])
				Rectangle(hMemDC, 30 * j, 30 * i, 30 * j + 30, 30 * i + 30);
		}
	}
	hNewBrush = SelectObject(hMemDC, hOldBrush);
	DeleteObject(hNewBrush);
}

int CanSquareStack() {
	for (int i = 19; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (1 == g_arrBG[i][j]) {
				if (2 == g_arrBG[i + 1][j])
					return 0;//return 0, fall disabled
			}
		}
	}
	return 1;
}

void OnLeft(HWND hWnd) {
	HDC hDc = GetDC(hWnd);
	if (1 == SquareL() && 1 == SquareLColide()) {
		SquareLeft();//moving item
		g_nCol--;
		OnPaint(hDc);
		ReleaseDC(hWnd, hDc);
	}
}

void SquareLeft() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (1 == g_arrBG[i][j]) {
				g_arrBG[i][j - 1] = g_arrBG[i][j];
				g_arrBG[i][j] = 0;

			}
		}
	}
}

int SquareL() {//left boarder
	for (int i = 0; i < 20; i++) {
		if (1 == g_arrBG[i][0])return 0;
	}
	return 1;
}

int SquareLColide() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (1 == g_arrBG[i][j]) {
				if (2 == g_arrBG[i][j - 1]) {
					return 0;
				}
			}
		}
	}
	return 1;
}

void OnRight(HWND hWnd) {
	HDC hDc = GetDC(hWnd);
	if (1 == SquareR() && 1 == SquareRColide()) {
		SquareRight();//moving item
		g_nCol++;
		OnPaint(hDc);
		ReleaseDC(hWnd, hDc);
	}
}

void SquareRight() {
	for (int i = 0; i < 20; i++) {
		for (int j = 9; j >= 0; j--) {
			if (1 == g_arrBG[i][j]) {
				g_arrBG[i][j + 1] = g_arrBG[i][j];
				g_arrBG[i][j] = 0;

			}
		}
	}
}

int SquareR() {//right boarder
	for (int i = 0; i < 20; i++) {
		if (1 == g_arrBG[i][9])return 0;
	}
	return 1;
}

int SquareRColide() {
	for (int i = 0; i < 20; i++) {
		for (int j = 9; j >= 0; j--) {
			if (1 == g_arrBG[i][j]) {
				if (2 == g_arrBG[i][j + 1]) {
					return 0;
				}
			}
		}
	}
	return 1;
}

void OnDown(HWND hWnd) {//accelrate falling
	OnTimer(hWnd);
}

void OnChange(HWND hWnd) {
	
	HDC hDc = GetDC(hWnd);
	//MessageBox(hWnd, "gameover", "Message", MB_RETRYCANCEL);
	//TextOut(hDc, 395, 200, "up", strlen("up"));
	switch (g_nSquareID) {
	case -1:
		MessageBox(hWnd, "gameover", "Message", MB_RETRYCANCEL);
		break;

	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		
		if (1 == CanRotate()) {
			Rotate();
			//MessageBox(hWnd, "gameover", "Message", MB_RETRYCANCEL);
		}
		break;
	case 5:
		if (1 == CanStickRotate()) {
			//MessageBox(hWnd, "gameover", "Message", MB_RETRYCANCEL);
			RotateStick();
		}
		break;
	case 6:
		return;

	}
	OnPaint(hDc);
	ReleaseDC(hWnd, hDc);
}

void Rotate() {

	int nTemp = 2;
	char arrSquare[3][3] = { 0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arrSquare[i][j] = g_arrBG[g_nRow + i][g_nCol + j];
		}
	}

	for (int i = 0; i < 3; i++) {//tutorial 33
		for (int j = 0; j < 3; j++) {
			g_arrBG[g_nRow + i][g_nCol + j] = arrSquare[nTemp][i];
			nTemp--;
		}
		nTemp = 2;
	}

}

int CanRotate() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (2 == g_arrBG[g_nRow + i][g_nCol + j])return 0;
		}
	}


	if (g_nCol < 0) {
		g_nCol = 0;
		
	}
	else if (g_nCol > 7) {
		g_nCol = 7;
	}

	return 1;
}

void RotateStick() {
	if (1 == g_arrBG[g_nRow][g_nCol - 1]) {//horizontal
		//clear
		g_arrBG[g_nRow][g_nCol - 1] = 0;
		g_arrBG[g_nRow][g_nCol + 1] = 0;
		g_arrBG[g_nRow][g_nCol + 2] = 0;
		if (2 == g_arrBG[g_nRow + 1][g_nCol]) {
			//rebuild
			g_arrBG[g_nRow - 1][g_nCol] = 1;
			g_arrBG[g_nRow - 2][g_nCol] = 1;
			g_arrBG[g_nRow - 3][g_nCol] = 1;

		}
		else if (2 == g_arrBG[g_nRow + 2][g_nCol]) {
			g_arrBG[g_nRow - 1][g_nCol] = 1;
			g_arrBG[g_nRow - 2][g_nCol] = 1;
			g_arrBG[g_nRow + 1][g_nCol] = 1;

		}
		else {
			//rebuild
			g_arrBG[g_nRow - 1][g_nCol] = 1;
			g_arrBG[g_nRow + 1][g_nCol] = 1;
			g_arrBG[g_nRow + 2][g_nCol] = 1;
		}

	}
	else {//vertical
		  //clear
		g_arrBG[g_nRow - 1][g_nCol] = 0;
		g_arrBG[g_nRow + 1][g_nCol] = 0;
		g_arrBG[g_nRow + 2][g_nCol] = 0;

		if (2 == g_arrBG[g_nRow][g_nCol + 1] || 9 == g_nCol) {
			g_arrBG[g_nRow][g_nCol - 1] = 1;
			g_arrBG[g_nRow][g_nCol - 2] = 1;
			g_arrBG[g_nRow][g_nCol - 3] = 1;

			g_nCol = g_nCol - 2;

		}
		else if (2 == g_arrBG[g_nRow][g_nCol + 2] || 8 == g_nCol) {
			g_arrBG[g_nRow][g_nCol + 1] = 1;
			g_arrBG[g_nRow][g_nCol - 1] = 1;
			g_arrBG[g_nRow][g_nCol - 2] = 1;

			g_nCol = g_nCol - 1;
		}
		else if (2 == g_arrBG[g_nRow][g_nCol - 1] || 0 == g_nCol) {
			g_arrBG[g_nRow][g_nCol + 1] = 1;
			g_arrBG[g_nRow][g_nCol + 2] = 1;
			g_arrBG[g_nRow][g_nCol + 3] = 1;

			g_nCol = g_nCol + 1;
		}

		else {
			//rebuild
			g_arrBG[g_nRow][g_nCol - 1] = 1;
			g_arrBG[g_nRow][g_nCol + 1] = 1;
			g_arrBG[g_nRow][g_nCol + 2] = 1;
		}
	}
}

int CanStickRotate() {
	int i, j = 0;
	for (i = 1; i < 4; i++) {//left and right boarder
		if (2 == g_arrBG[g_nRow][g_nCol + i] || g_nCol + i > 9) {
			break;
		}
	}
	for (j = 1; j < 4; j++) {
		if (2 == g_arrBG[g_nRow][g_nCol - j] || g_nCol - j < 0) {
			break;
		}
	}
	if (i - 1 + j - 1 < 3) {
		return 0;
	}

	if (g_nRow < 1)return 0;//the stick can not rotate when at the very top of the game area
	return 1;
}

void RemoveRow() {
	int nTempi = 0;
	int i = 0;
	int j = 0;
	for (i = 19; i >= 0; i--) {
		int nSum = 0;
		for (j = 0; j < 10; j++) {
			nSum += g_arrBG[i][j];
		}
		if (20 == nSum) {//remove Row
			for (nTempi = i; nTempi >= 0; nTempi--) {
				for (j = 0; j < 10; j++) {
					g_arrBG[nTempi][j] = g_arrBG[nTempi - 1][j];
				}
			}
			g_nScore++;
			i = 20;
		}
	}
}