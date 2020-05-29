// CrossByKitya.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "CrossByKitya.h"

#define MAX_LOADSTRING 100
#define BTN_MAIN_CROSS  200
#define BTN_MAIN_EXIT 201

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
COLORREF color = RGB(250, 240, 250);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Exit(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CROSSBYKITYA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CROSSBYKITYA));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CROSSBYKITYA));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CROSSBYKITYA);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

HFONT bigButtonFont;
HFONT titleFont;
HBRUSH hBrush;
HFONT textFont;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {

        bigButtonFont = CreateFont(50, 22, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Calibri"));
        HWND button0 = CreateWindow(TEXT("BUTTON"), TEXT("Кроссворды"), WS_VISIBLE | WS_CHILD, 850, 160, 500, 100, hWnd, (HMENU)BTN_MAIN_CROSS, hInst, NULL);
        HWND button1 = CreateWindow(TEXT("BUTTON"), TEXT("Выход"), WS_VISIBLE | WS_CHILD, 850, 300, 500, 100, hWnd, (HMENU)BTN_MAIN_EXIT, hInst, NULL);
        SendMessage(button0, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);
        SendMessage(button1, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);

        titleFont = CreateFont(72, 32, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Calibri"));
        textFont = CreateFont(30, 14, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Calibri"));

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
            // TODO: MainCross button
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

        PAINTSTRUCT ps; //экземпляр структуры рисования
        HDC hdc = BeginPaint(hWnd, &ps); //начали рисование
        hBrush = CreateSolidBrush(color);
        SelectObject(hdc, hBrush);

        SetBkMode(hdc, TRANSPARENT);
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

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

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
