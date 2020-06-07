#pragma once

#include "resource.h"
#include "framework.h"

#define MAX_LOADSTRING 100
#define BTN_MAIN_CROSS  200
#define BTN_MAIN_EXIT 201

// Global Variables:
extern HINSTANCE hInst;                                // current instance
extern WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
extern WCHAR szMainWindowClass[MAX_LOADSTRING];            // the main window class name
extern COLORREF color;
extern HFONT bigButtonFont;
extern HFONT titleFont;
extern HBRUSH hBrush;
extern HFONT textFont;