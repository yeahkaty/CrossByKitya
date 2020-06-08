// Message handler for about box.
#include "CrossByKitya.h"
#include "MainWindow.h"

HWND chooseCrossesWnd;

HWND button0;
HWND button1;

void RepaintMe(HWND hWnd);

INT_PTR CALLBACK Exit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        if (LOWORD(wParam) == AcceptExit || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == RegretExit) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)FALSE;
        }
    }

    break;
    }
    return (INT_PTR)FALSE;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {

        
        button0 = CreateWindow(TEXT("BUTTON"), TEXT("Кроссворды"), WS_VISIBLE | WS_CHILD, 850, 160, 500, 100, hWnd, (HMENU)BTN_MAIN_CROSS, hInst, NULL);
        button1 = CreateWindow(TEXT("BUTTON"), TEXT("Выход"), WS_VISIBLE | WS_CHILD, 850, 300, 500, 100, hWnd, (HMENU)BTN_MAIN_EXIT, hInst, NULL);
        SendMessage(button0, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);
        SendMessage(button1, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);


        

        /*
        HFONT CreateFont(
            int nHeight,               // высота шрифта
            int nWidth,                // средняя ширина символа
            int nEscapement,           // угол наклона
            int nOrientation,          // угол ориентации базисной линии
            int fnWeight,              // толщина шрифта
            DWORD fdwItalic,           // описатель параметра курсивного шрифта
            DWORD fdwUnderline,        // описатель параметра подчеркивания
            DWORD fdwStrikeOut,        // описатель параметра зачеркивания
            DWORD fdwCharSet,          // идентификатор набора символов
            DWORD fdwOutputPrecision,  // точность вывода
            DWORD fdwClipPrecision,    // точность отсечения
            DWORD fdwQuality,          // качество вывода
            DWORD fdwPitchAndFamily,   // шаг между символами шрифта и семейство
            LPCTSTR lpszFace           // имя гарнитуры шрифта
        );*/
    }
    break;
    case BackToMainMessage: {
        int b0style = GetWindowLong(button0, GWL_STYLE);
        int b1style = GetWindowLong(button1, GWL_STYLE);
        SetWindowLong(button0, GWL_STYLE, (unsigned int)(b0style | (WS_VISIBLE)));
        SetWindowLong(button1, GWL_STYLE, (unsigned int)(b1style | (WS_VISIBLE)));
        RepaintMe(hWnd);
        ShowWindow(mainWnd, 1);
        UpdateWindow(mainWnd);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case BTN_MAIN_CROSS:
        {
            int b0style = GetWindowLong(button0, GWL_STYLE);
            int b1style = GetWindowLong(button1, GWL_STYLE);
            SetWindowLong(button0, GWL_STYLE, (unsigned int)(b0style & ~(WS_VISIBLE)));
            SetWindowLong(button1, GWL_STYLE, (unsigned int)(b1style & ~(WS_VISIBLE)));

            if (chooseCrossesWnd == NULL) {
                chooseCrossesWnd = CreateWindowW(szChooseCrossesWindowClass, szTitle, WS_OVERLAPPED | WS_CLIPCHILDREN,
                    0, 0, CW_USEDEFAULT, CW_USEDEFAULT, mainWnd, nullptr, hInst, nullptr);
                SetParent(chooseCrossesWnd, hWnd);
                int style = GetWindowLong(chooseCrossesWnd, GWL_STYLE); //gets current style
                SetWindowLong(chooseCrossesWnd, GWL_STYLE, (unsigned int)(style & ~(WS_CAPTION | WS_SIZEBOX)));
                SetWindowPos(chooseCrossesWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                if (!chooseCrossesWnd)
                {
                    return FALSE;
                }
            }
            

            ShowWindow(chooseCrossesWnd, 1);
            UpdateWindow(chooseCrossesWnd);
            

            return TRUE;
        }
        break;
        case BTN_MAIN_EXIT:
        {
            if (DialogBox(hInst, MAKEINTRESOURCE(IDD_EXIT), hWnd, Exit) == AcceptExit) {
                DestroyWindow(hWnd);
            }
        }
        break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        RepaintMe(hWnd);
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
void RepaintMe(HWND hWnd) {
    PAINTSTRUCT ps; //экземпляр структуры рисования
    HDC hdc = BeginPaint(hWnd, &ps); //начали рисование
    
    // Erase BackGround
    SetBkColor(hdc, RGB(255, 255, 255));
    SelectObject(hdc, whitePen);
    RECT rect;
    GetWindowRect(hWnd, &rect);
    LONG width = rect.right - rect.left;
    LONG height = rect.bottom - rect.top;
    Rectangle(hdc, 0, 0, width, height);
    // End of erase
    SelectObject(hdc, blackPen);

    SelectObject(hdc, hBrush);
    SetBkMode(hdc, OPAQUE);
    SetBkColor(hdc, color);
    Rectangle(hdc, 50, 160, 800, 600);

    SetTextColor(hdc, RGB(200, 100, 165));
    SelectObject(hdc, textFont);
    TCHAR MainText[] = L"Добро пожаловать в игру CrossByKitya!";
    TCHAR MainText1[] = L"Что бы начать игру нажмите на кнопку КРОССВОРДЫ.";
    TCHAR MainText2[] = L"Если вы хотите покинуть игру, нажмите на кнопку ВЫХОД.";
    TextOut(hdc, 60, 170, MainText, _ARRAYSIZE(MainText));
    TextOut(hdc, 60, 210, MainText1, _ARRAYSIZE(MainText1));
    TextOut(hdc, 60, 250, MainText2, _ARRAYSIZE(MainText2));

    TCHAR titleText[] = L"CrossByKitya";

    SetTextColor(hdc, RGB(255, 170, 220));
    SetBkColor(hdc, RGB(255, 255, 255));
    SelectObject(hdc, titleFont);
    TextOut(hdc, 530, 10, titleText, _ARRAYSIZE(titleText));

    EndPaint(hWnd, &ps); //закончили рисование
}

