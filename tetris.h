#pragma once
#ifndef DEF_TETRIS
#define DEF_TETRIS
#include <Windows.h>
#include <time.h>

#define DEF_TIMER1 1

void OnPaint(HDC hDc);
void OnCreate();

void PaintSquare(HDC hMemDC);//showing squares
int CreateRandomSquare();//creating 
void CopySquareToBG();

void OnReturn(HWND hWnd);

//square falling
void SquareFall();
void SquareLeft();
void SquareRight();
//timer function
void OnTimer(HWND hWnd);

void OnLeft(HWND hWnd);
void OnRight(HWND hWnd);
void OnDown(HWND hWnd);
void OnChange(HWND hWnd);

//items stop at the bottom, return 0 for unable to fall
int CanSquareFall();

//stacking items
int CanSquareStack();

int SquareL();
int SquareR();
int SquareLColide();
int SquareRColide();
int CanRotate();
int CanStickRotate();

int GameOver(HWND hWnd);

//alter square value
void ChangeSqrVal();

void ShowSquare2(HDC hMemDC);
void Rotate();
void RotateStick();

void RemoveRow();

void ShowScore(HDC hMemDC);


#endif