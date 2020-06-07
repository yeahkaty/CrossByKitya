#include "ChooseCrosses.h"
#include "CrossByKitya.h"

HWND backBtn;
LRESULT CALLBACK    ChooseCrossesWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_CREATE:
    {
        backBtn = CreateWindow(TEXT("BUTTON"), TEXT("Back"), (WS_VISIBLE | WS_CHILD), 970, 600, 400, 75, hWnd, (HMENU)BTN_CHOOSE_BACKTOMAIN, hInst, NULL);
        SendMessage(backBtn, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case BTN_CHOOSE_BACKTOMAIN:
        {
            int chooseStyle = GetWindowLong(hWnd, GWL_STYLE);
            SetWindowLong(hWnd, GWL_STYLE, (unsigned int)(chooseStyle & ~(WS_VISIBLE)));
            SendMessage(mainWnd, BackToMainMessage, 0, 0);

        }
        break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps; //экземпляр структуры рисования
        HDC hdc = BeginPaint(chooseCrossesWnd, &ps); //начали рисование
        SelectObject(hdc, hBrush);

        SetBkMode(hdc, OPAQUE);
        SetBkColor(hdc, color);

        
        TCHAR titleText[] = L"Choose crossword";

        SetTextColor(hdc, RGB(255, 170, 220));
        SetBkColor(hdc, RGB(255, 255, 255));
        SelectObject(hdc, titleFont);
        TextOut(hdc, 530, 10, titleText, _ARRAYSIZE(titleText));
        
        EndPaint(hWnd, &ps); //закончили рисование
        break;
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
