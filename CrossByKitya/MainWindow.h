#pragma once
#include "framework.h"

#define BTN_MAIN_CROSS  200
#define BTN_MAIN_EXIT 201
LRESULT CALLBACK    MainWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Exit(HWND, UINT, WPARAM, LPARAM);
