#include "CrossWindow.h"
#include "CrossByKitya.h"
#include "Crossword.h"
#include "TxtConvertor.h"
#include <vector>

HWND backToChooseBtn;
LRESULT CALLBACK CrossWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_CREATE:
    {
        backToChooseBtn = CreateWindow(TEXT("BUTTON"), TEXT("Give up"), (WS_VISIBLE | WS_CHILD), 970, 600, 400, 75, hWnd, (HMENU)BTN_CHOOSE_BACKTOCHOOSE, hInst, NULL);
        SendMessage(backToChooseBtn, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case BTN_CHOOSE_BACKTOCHOOSE:
        {        

            int crossStyle = GetWindowLong(hWnd, GWL_STYLE);
            SetWindowLong(hWnd, GWL_STYLE, (unsigned int)(crossStyle & ~(WS_VISIBLE)));
            int chooseStyle = GetWindowLong(chooseCrossesWnd, GWL_STYLE);
            SetWindowLong(chooseCrossesWnd, GWL_STYLE, (unsigned int)(chooseStyle | (WS_VISIBLE)));
            ShowWindow(mainWnd, 1);
            UpdateWindow(mainWnd);
            RedrawWindow(chooseCrossesWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);


        }
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps; //экземпляр структуры рисования
        HDC hdc = BeginPaint(crossWnd, &ps); //начали рисование


        // Erase BackGround
        SetBkColor(hdc, RGB(255, 255, 255));
        SelectObject(hdc, whitePen);
        RECT rect;
        GetWindowRect(hWnd, &rect);
        LONG width = rect.right - rect.left;
        LONG height = rect.bottom - rect.top;
        Rectangle(hdc, 0, 0, width, height);
        // End of erase

        TCHAR titleText[] = L"Cross";


        SetTextColor(hdc, RGB(255, 170, 220));
        SetBkColor(hdc, RGB(255, 255, 255));
        SelectObject(hdc, titleFont);
        TextOut(hdc, 100, 10, titleText, _ARRAYSIZE(titleText));

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