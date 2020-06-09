// CrossByKitya.cpp : Defines the entry point for the application.
//
#include "Result.h"
#include "Word.h"
#include "Crossword.h"
#include "Place.h"
#include "TxtConvertor.h"
#include <vector>
#include "framework.h"

#include "MainWindow.h"
#include "ChooseCrosses.h"
#include "CrossByKitya.h"
using namespace std;

// Global variables
HFONT bigButtonFont = CreateFont(50, 22, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
    CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Calibri"));
HFONT titleFont = CreateFont(72, 32, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
    CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Calibri"));
HFONT textFont = CreateFont(30, 14, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
    CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Calibri"));
COLORREF color = RGB(250, 240, 250);
HBRUSH hBrush = CreateSolidBrush(color);
HPEN whitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
HPEN blackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szMainWindowClass[MAX_LOADSTRING];
WCHAR szChooseCrossesWindowClass[MAX_LOADSTRING];

HWND mainWnd;








// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);

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
    LoadStringW(hInstance, IDC_CROSSBYKITYA, szMainWindowClass, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_ChooseCrossesClass, szChooseCrossesWindowClass, MAX_LOADSTRING);

    
    MyRegisterClass(hInstance);

    //Result proba = Result("ivqan", "12:01", "109", "01.07");
    //Result proba2 = Result("ivqan", "12:01", "106", "01.07");
   // Result proba3 = Result("ivqan", "12:01", "107", "01.07");
   // vector<Result> probnik;
  // probnik.push_back(proba);
  // probnik.push_back(proba2);
  // probnik.push_back(proba3);
  //  TxtConvertor pr;
  //  pr.WriteResults(probnik);
  //  probnik = pr.ReadResults();
  //  probnik = pr.SortResults(probnik);



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
    WNDCLASSEXW mainWcex;
    WNDCLASSEXW chooseCrossesWcex;

    mainWcex.cbSize = sizeof(WNDCLASSEX);

    mainWcex.style = CS_HREDRAW | CS_VREDRAW;
    mainWcex.lpfnWndProc = MainWndProc;
    mainWcex.cbClsExtra = 0;
    mainWcex.cbWndExtra = 0;
    mainWcex.hInstance = hInstance;
    mainWcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CROSSBYKITYA));
    mainWcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    mainWcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    mainWcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CROSSBYKITYA);
    mainWcex.lpszClassName = szMainWindowClass;
    mainWcex.hIconSm = LoadIcon(mainWcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&mainWcex);

    chooseCrossesWcex.cbSize = sizeof(WNDCLASSEX);
    chooseCrossesWcex.style = 0;
    chooseCrossesWcex.lpfnWndProc = ChooseCrossesWndProc;
    chooseCrossesWcex.cbClsExtra = 0;
    chooseCrossesWcex.cbWndExtra = 0;
    chooseCrossesWcex.hInstance = hInstance;
    chooseCrossesWcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CROSSBYKITYA));
    chooseCrossesWcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    chooseCrossesWcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    chooseCrossesWcex.lpszMenuName = 0;
    chooseCrossesWcex.lpszClassName = szChooseCrossesWindowClass;
    chooseCrossesWcex.hIconSm = LoadIcon(chooseCrossesWcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&chooseCrossesWcex);


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

    mainWnd = CreateWindowW(szMainWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!mainWnd)
    {
        return FALSE;
    }

    ShowWindow(mainWnd, nCmdShow);
    UpdateWindow(mainWnd);

    return TRUE;
}

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



