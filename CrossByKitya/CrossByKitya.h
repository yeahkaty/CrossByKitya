#pragma once

#include "resource.h"
#include "framework.h"
#include "Result.h"
#include "Word.h"
#include "Crossword.h"
#include "Place.h"
#include "TxtConvertor.h"
#include <vector>
#define MAX_LOADSTRING 100

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Global Variables:
extern HINSTANCE hInst;                                // current instance
extern WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
extern vector<Crossword> crosswords;
extern vector<Result> results;
extern TxtConvertor txtParser;

extern WCHAR szMainWindowClass[MAX_LOADSTRING];            // the main window class name
extern WCHAR szChooseCrossesWindowClass[MAX_LOADSTRING];
extern WCHAR szCrossWindowClass[MAX_LOADSTRING];
extern WCHAR szResultsWindowClass[MAX_LOADSTRING];

extern HWND mainWnd;
extern HWND chooseCrossesWnd;
extern HWND crossWnd;
extern HWND resultsWnd;

extern COLORREF color;
extern HFONT bigButtonFont;
extern HFONT titleFont;
extern HBRUSH hBrush;
extern HFONT textFont;
extern HPEN whitePen;
extern HPEN blackPen;


#define BackToMainMessage WM_USER+1