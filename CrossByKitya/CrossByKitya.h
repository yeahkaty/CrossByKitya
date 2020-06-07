#pragma once

#include "resource.h"
#include "framework.h"

#define MAX_LOADSTRING 100

// Global Variables:
extern HINSTANCE hInst;                                // current instance
extern WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
extern WCHAR szMainWindowClass[MAX_LOADSTRING];            // the main window class name
extern WCHAR szChooseCrossesWindowClass[MAX_LOADSTRING];
extern COLORREF color;
extern HFONT bigButtonFont;
extern HFONT titleFont;
extern HBRUSH hBrush;
extern HFONT textFont;