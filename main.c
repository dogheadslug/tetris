#include <Windows.h>
#include <mmsystem.h>
#include <stdbool.h>
#include "resource.h"
#include "tetris.h"
LRESULT CALLBACK P_function(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

bool gameStart = false;

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR LPCmdLine, int nCmdShow) {
    WNDCLASSEX wc;//initialization
    HWND hWnd;
    MSG mSg;


    wc.cbClsExtra = 0;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;//background color
    wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1)); //type of cursor
    wc.hIcon = LoadIcon(NULL, IDI_HAND);//icon on the bottom, MAKEINTRESOURCE(hInstance, IDI_   )
    wc.hIconSm = NULL;  //top left icon
    wc.hInstance = hInstance;
    wc.lpfnWndProc = P_function;// callback address	
    wc.lpszClassName = "tetris";//the unique name for OS's recognition
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;//horizontal | vertical redraw 

                                       //register
    if (0 == RegisterClassEx(&wc)) {
        return 0;
    }

    //creating a window
    hWnd = CreateWindowEx(WS_EX_TOPMOST, "tetris", "tetris ¶íÂÞË¹·½¿é", WS_OVERLAPPEDWINDOW, 100, 100, 500, 650, NULL, NULL, hInstance, NULL);
    if (NULL == hWnd) {
        return 0;
    }

    //showing window
    ShowWindow(hWnd, nCmdShow); //SW_SHOWNORMAL

                                //message loop
    while (GetMessage(&mSg, NULL, 0, 0)) {
        //
        TranslateMessage(&mSg);//traslate message
        DispatchMessage(&mSg);//dispatch message
    }
    return 0;
}

LRESULT CALLBACK P_function(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT pt;
    HDC hDC;//the part paint operation would take place

    switch (nMsg) {
    case WM_CREATE://the creation of window, handles initialization job
        OnCreate();
        break;

    case WM_TIMER:
        OnTimer(hWnd);
        break;

    case WM_PAINT://the main part of the game is here
        hDC = BeginPaint(hWnd, &pt);
        OnPaint(hDC);
        //Rectangle(hDC, 0, 0, 300, 600);
        break;

    case WM_KEYDOWN:
        switch (wParam) {
        case VK_RETURN:
            OnReturn(hWnd);
            break;
        case VK_LEFT:
		case 0x41://A key
            OnLeft(hWnd);
            break;
        case VK_RIGHT:
		case 0x44://D key
            OnRight(hWnd);
            break;
        case VK_UP://changing facing
		case 0x57://W key
            OnChange(hWnd);
            break;
        case VK_DOWN:
		case 0x53://S key
			if (gameStart == false) {
				gameStart = true;
				OnReturn(hWnd);
			}
			else {
                OnDown(hWnd);
			}
            
            break;
		case 0x4D:
			ToggleBGM(hWnd);
			break;
		//case 0x52:
			//Restart(hWnd);//restart
			//break;
        }
        break;

    case WM_DESTROY:
        KillTimer(hWnd, DEF_TIMER1);
        PostQuitMessage(0);//WM_CLOSE, WM_DESTROY, WE_QUIT
        break;
    }

    return DefWindowProc(hWnd, nMsg, wParam, lParam);
}