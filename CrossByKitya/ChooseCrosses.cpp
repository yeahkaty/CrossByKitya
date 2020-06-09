#include "ChooseCrosses.h"
#include "CrossByKitya.h"
#include "Crossword.h"
#include "TxtConvertor.h"
#include <vector>


HWND backBtn;
HWND firstCrossBtn;
HWND secondCrossBtn;
HWND thirdCrossBtn;

HWND crossWnd;

LRESULT CALLBACK    ChooseCrossesWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_CREATE:
    {
        backBtn = CreateWindow(TEXT("BUTTON"), TEXT("Back"), (WS_VISIBLE | WS_CHILD), 970, 600, 400, 75, hWnd, (HMENU)BTN_CHOOSE_BACKTOMAIN, hInst, NULL);
        SendMessage(backBtn, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);
        firstCrossBtn = CreateWindow(TEXT("BUTTON"), TEXT("Play"), (WS_VISIBLE | WS_CHILD), 540, 220, 200, 45, hWnd, (HMENU)BTN_FIRSTCROSS, hInst, NULL);
        SendMessage(backBtn, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);
        secondCrossBtn = CreateWindow(TEXT("BUTTON"), TEXT("Play"), (WS_VISIBLE | WS_CHILD), 540, 405, 200, 45, hWnd, (HMENU)BTN_SECONDCROSS, hInst, NULL);
        SendMessage(backBtn, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);
        thirdCrossBtn = CreateWindow(TEXT("BUTTON"), TEXT("Play"), (WS_VISIBLE | WS_CHILD), 540, 590, 200, 45, hWnd, (HMENU)BTN_THIRDCROSS, hInst, NULL);
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
            RedrawWindow(mainWnd, NULL, NULL, RDW_INTERNALPAINT|RDW_INVALIDATE| RDW_UPDATENOW);


        }
        break;
        case BTN_FIRSTCROSS:
        {
            int chooseStyle = GetWindowLong(hWnd, GWL_STYLE);
            SetWindowLong(hWnd, GWL_STYLE, (unsigned int)(chooseStyle & ~(WS_VISIBLE)));

            if (crossWnd == NULL) {
                crossWnd = CreateWindowW(szCrossWindowClass, szTitle, WS_OVERLAPPED | WS_CLIPCHILDREN,
                    0, 0, CW_USEDEFAULT, CW_USEDEFAULT, mainWnd, nullptr, hInst, nullptr);
                SetParent(crossWnd, mainWnd);
                int style = GetWindowLong(crossWnd, GWL_STYLE); //gets current style
                SetWindowLong(crossWnd, GWL_STYLE, (unsigned int)(style & ~(WS_CAPTION | WS_SIZEBOX)));
                SetWindowPos(crossWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                if (!crossWnd)
                {
                    return FALSE;
                }
            }

            SendMessage(crossWnd, Cross1Message, 0, 0);
            ShowWindow(crossWnd, 1);
            UpdateWindow(crossWnd);

        }
        break;
        case BTN_SECONDCROSS:
        {
            int chooseStyle = GetWindowLong(hWnd, GWL_STYLE);
            SetWindowLong(hWnd, GWL_STYLE, (unsigned int)(chooseStyle & ~(WS_VISIBLE)));

            if (crossWnd == NULL) {
                crossWnd = CreateWindowW(szCrossWindowClass, szTitle, WS_OVERLAPPED | WS_CLIPCHILDREN,
                    0, 0, CW_USEDEFAULT, CW_USEDEFAULT, mainWnd, nullptr, hInst, nullptr);
                SetParent(crossWnd, mainWnd);
                int style = GetWindowLong(crossWnd, GWL_STYLE); //gets current style
                SetWindowLong(crossWnd, GWL_STYLE, (unsigned int)(style & ~(WS_CAPTION | WS_SIZEBOX)));
                SetWindowPos(crossWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                if (!crossWnd)
                {
                    return FALSE;
                }
            }

            SendMessage(crossWnd, Cross2Message, 0, 0);
            ShowWindow(crossWnd, 1);
            UpdateWindow(crossWnd);
        }
        break;
        case BTN_THIRDCROSS:
        {
            int chooseStyle = GetWindowLong(hWnd, GWL_STYLE);
            SetWindowLong(hWnd, GWL_STYLE, (unsigned int)(chooseStyle & ~(WS_VISIBLE)));

            if (crossWnd == NULL) {
                crossWnd = CreateWindowW(szCrossWindowClass, szTitle, WS_OVERLAPPED | WS_CLIPCHILDREN,
                    0, 0, CW_USEDEFAULT, CW_USEDEFAULT, mainWnd, nullptr, hInst, nullptr);
                SetParent(crossWnd, mainWnd);
                int style = GetWindowLong(crossWnd, GWL_STYLE); //gets current style
                SetWindowLong(crossWnd, GWL_STYLE, (unsigned int)(style & ~(WS_CAPTION | WS_SIZEBOX)));
                SetWindowPos(crossWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                if (!crossWnd)
                {
                    return FALSE;
                }
            }

            SendMessage(crossWnd, Cross3Message, 0, 0);
            ShowWindow(crossWnd, 1);
            UpdateWindow(crossWnd);
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

        SetBkMode(hdc, TRANSPARENT);
        SetBkColor(hdc, color);

        // Crosswords drawing
        for (int i = 0; i < crosswords.size(); i++) {
            Rectangle(hdc, 25, 100 +(185 *i), 750, 100 + (170 * (i+1) + 15*i));
            SetTextColor(hdc, RGB(0, 0, 0));
            SelectObject(hdc, bigButtonFont);
            string crossName = crosswords[i].getName();
            wstring wCrossName = wstring(crossName.begin(), crossName.end());
            TextOut(hdc, 40, 102 + (185 * i), wCrossName.c_str(), crossName.length());
            SelectObject(hdc, textFont);
            SetTextColor(hdc, RGB(100, 65, 90));
            string crossDescription = crosswords[i].getDescription();
            wstring wCrossDescription = wstring(crossDescription.begin(), crossDescription.end());
            vector<wstring> descriptionLines;
            int pointer = 0;
            while (pointer < wCrossDescription.length()) {
                int newPointer = 0;
                if (pointer + 66 > wCrossDescription.length()) {
                    newPointer = wCrossDescription.length();
                }
                else {
                    newPointer = pointer + 66;
                }
                descriptionLines.push_back(wCrossDescription.substr(pointer, newPointer - pointer));
                pointer = newPointer;
            }
            for (int j = 0; j < descriptionLines.size(); j++) {
                if (j == 0) {
                    TextOut(hdc, 45, 145 + (185 * i) + (22 * j), descriptionLines[j].c_str(), descriptionLines[j].length());
                }
                else {
                    TextOut(hdc, 30, 145 + (185 * i) + (22 * j), descriptionLines[j].c_str(), descriptionLines[j].length());
                }
            }

            SetTextColor(hdc, RGB(65, 45, 58));
            string authorName = "Author: " + crosswords[i].getAuthor();
            wstring wAuthorName = wstring(authorName.begin(), authorName.end());
            TextOut(hdc, 40, 230 + (185 * i), wAuthorName.c_str(), wAuthorName.length());

            SetTextColor(hdc, RGB(255, 255, 255));
            SelectObject(hdc, titleFont);
            TextOut(hdc, 240, 205 + (185 * i), L"★ ★ ★", 5);
            SetTextColor(hdc, RGB(255, 215, 0));
            int level = crosswords[i].getLevel();
            if (level < 2) {
                TextOut(hdc, 240, 205 + (185 * i), L"★ ☆ ☆", 5);
            }
            else if (level == 2) {
                TextOut(hdc, 240, 205 + (185 * i), L"★ ★ ☆", 5);
            }
            else {
                TextOut(hdc, 240, 205 + (185 * i), L"★ ★ ★", 5);
            }
        }

        // Results drawing
        SetBkMode(hdc, TRANSPARENT);
        SetBkColor(hdc, color);
        Rectangle(hdc, 775, 100, 1400, 570);
        SetTextColor(hdc, RGB(65, 45, 58));
        SelectObject(hdc, textFont);

        TextOut(hdc, 780, 105, L"Nickname", 8);
        TextOut(hdc, 980, 105, L"Scores", 5);
        TextOut(hdc, 1080, 105, L"Time", 4);
        TextOut(hdc, 1180, 105, L"Date", 4);

        for (int i = 0; i < results.size(); i++) {
            string rsName = results[i].getName();
            string rsScores = results[i].getScores();
            string rsData = results[i].getData();
            string rsTime = results[i].getTime();

            wstring wRsName = wstring(rsName.begin(), rsName.end());
            wstring wRsScores = wstring(rsScores.begin(), rsScores.end());
            wstring wRsData = wstring(rsData.begin(), rsData.end());
            wstring wRsTime = wstring(rsTime.begin(), rsTime.end());

            TextOut(hdc, 780, 115 + (i + 1) * 20, wRsName.c_str(), wRsName.length());
            TextOut(hdc, 980, 115 + (i + 1) * 20, wRsScores.c_str(), wRsScores.length());
            TextOut(hdc, 1080, 115 + (i + 1) * 20, wRsData.c_str(), wRsData.length());
            TextOut(hdc, 1180, 115 + (i + 1) * 20, wRsTime.c_str(), wRsTime.length());
        }


        
        TCHAR titleText[] = L"Choose crossword";
        TCHAR rateText[] = L"Rating table";


        SetTextColor(hdc, RGB(255, 170, 220));
        SetBkColor(hdc, RGB(255, 255, 255));
        SelectObject(hdc, titleFont);
        TextOut(hdc, 100, 10, titleText, _ARRAYSIZE(titleText));
        TextOut(hdc, 950, 10, rateText, _ARRAYSIZE(rateText));

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
