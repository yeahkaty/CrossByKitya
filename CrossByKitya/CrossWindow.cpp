#include "CrossWindow.h"
#include "CrossByKitya.h"
#include "Crossword.h"
#include "TxtConvertor.h"
#include <vector>

void DrawCrossword(int num, HWND hWnd);
//#define testTextBox 500
HWND backToChooseBtn;
int crosswordFieldWidth;
int crosswordFieldHeight;
int descStartX;
int descStartY;
map<int, HWND> crossOnField;
//HWND TextBox;
LRESULT CALLBACK CrossWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    HDC hdcEdit = (HDC)wParam;

    switch (message)
    {
    case WM_CREATE:
    {
        backToChooseBtn = CreateWindow(TEXT("BUTTON"), TEXT("Give up"), (WS_VISIBLE | WS_CHILD), 970, 600, 400, 75, hWnd, (HMENU)BTN_CHOOSE_BACKTOCHOOSE, hInst, NULL);
        SendMessage(backToChooseBtn, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);
        //TextBox = CreateWindow(TEXT("Edit"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 200, 20, 20, hWnd, (HMENU)testTextBox, hInst, NULL);
    }
    break;
    /*case WM_CTLCOLOREDIT: {
        SetTextColor(hdcEdit, RGB(255, 255, 255));
        SetBkColor(hdcEdit, RGB(0, 0, 0));
        return (INT_PTR)CreateSolidBrush(RGB(109, 194, 222));
    }
        break;*/
    case Cross1Message: 
    {
        ShowWindow(hWnd, 1);
        RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
        DrawCrossword(0, hWnd); 

        
    }
    break;
    case Cross2Message: 
    {
        ShowWindow(hWnd, 1);
        RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
        DrawCrossword(1, hWnd);

    }
    break;
    case Cross3Message: 
    {
        ShowWindow(hWnd, 1);
        RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
        DrawCrossword(2, hWnd);

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
        break;
        /*case testTextBox:
        {
            TCHAR buff[1];
            GetWindowText(TextBox, buff, 1);
            if (HIWORD(wParam) == EN_CHANGE) 
            {
                SendMessage(backToChooseBtn, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);
                SendMessage(hWnd, WM_CTLCOLOREDIT, (WPARAM)hdcEdit, (LPARAM)testTextBox);

                int x = 0;
            }
        }
        break;*/
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

        SelectObject(hdc, hBrush);
        SelectObject(hdc, blackPen);
        SetBkColor(hdc, color);
        Rectangle(hdc, 40, 85, width * 0.45, 670);
        crosswordFieldWidth = width * 0.45 - 40;
        crosswordFieldHeight = 670 - 85;
        descStartX = width * 0.46 + 10;
        descStartY = 90;
        Rectangle(hdc, descStartX - 10, descStartY - 5, 1370, 570);
        EndPaint(crossWnd, &ps); //закончили рисование

    }
    break;
    case WM_DESTROY:
        //PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
void DrawCrossword(int num, HWND hWnd)
{
    HDC hdc = GetDC(hWnd);
    SetTextColor(hdc, RGB(65, 45, 58));
    SetBkColor(hdc, color);
    SetBkMode(hdc, TRANSPARENT);
    SelectObject(hdc, textFont);

    if (crossOnField.size() != 0) {
        for (map<int, HWND>::iterator it = crossOnField.begin(); it != crossOnField.end(); ++it) {
            DestroyWindow(it->second);
        };
        crossOnField.clear();
    }
    int wId = 1;
    int id = 0;
    Crossword cross = crosswords[num];
    int hStep = (crosswordFieldWidth - 90) / cross.getSize_horizontal();
    int vStep = (crosswordFieldHeight - 90) / cross.getSize_vertical();
    int startX = 85;
    int startY = 130;
    int additionalLines = 0;
    map<Word, Place> displacement = *cross.getMap();
    for (map<Word, Place>::iterator it = displacement.begin(); it != displacement.end(); ++it) {
        Word wordNow = it->first;
        Place place = it->second;
       
        //Draw textboxes
        HFONT tempFont = CreateFont(vStep-10, hStep-16, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, MONO_FONT, TEXT("Courier"));
        for (int i = 0; i < wordNow.getLength(); i++) {
            if (place.getIsHorizontal()) {
                crossOnField.insert(pair<int, HWND>(id + 900, CreateWindow(TEXT("Edit"), TEXT(""), WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER, startX + (place.getXPlace() + i) * hStep, startY + place.getYPlace() * vStep, hStep, vStep, crossWnd, (HMENU)id + 900, hInst, NULL)));
                SendMessage(crossOnField[id+900], WM_SETFONT, (WPARAM)tempFont, TRUE);
            }
            else {
                crossOnField.insert(pair<int, HWND>(id + 900, CreateWindow(TEXT("Edit"), TEXT(""), WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER, startX + place.getXPlace() * hStep, startY + (place.getYPlace() + i) * vStep, hStep, vStep, crossWnd, (HMENU)id + 900, hInst, NULL)));
                SendMessage(crossOnField[id+900], WM_SETFONT, (WPARAM)tempFont, TRUE);

            }
            id++;
        }
        SelectObject(hdc, textFont);
        //Draw id's
        if (place.getIsHorizontal()) {
            if (wId < 10) {
                TextOut(hdc, (startX + place.getXPlace() * hStep) - hStep * 0.35, startY + place.getYPlace() * vStep + vStep * 0.25, to_wstring(wId).c_str(), 1);
            }
            else {
                TextOut(hdc, (startX + place.getXPlace() * hStep) - hStep * 0.7, startY + place.getYPlace() * vStep + vStep * 0.25, to_wstring(wId).c_str(), 2);
            }
        }
        else {
            if (wId < 10) {
                TextOut(hdc, startX + place.getXPlace() * hStep + hStep * 0.25, (startY + place.getYPlace() * vStep) - vStep * 0.7, to_wstring(wId).c_str(), 1);
            }
            else {
                TextOut(hdc, startX + place.getXPlace() * hStep + hStep * 0.25, (startY + place.getYPlace() * vStep) - vStep * 0.7, to_wstring(wId).c_str(), 2);
            }
        }

        //Draw description
        HFONT descFont = CreateFont(16, 10, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, MONO_FONT, TEXT("Courier"));
        SelectObject(hdc, descFont);
        string desc = to_string(wId)+". ";
        desc += wordNow.getDescription();
        
        wstring wDesc = wstring(desc.begin(), desc.end());

        vector<wstring> descriptionLines;
        int pointer = 0;
        while (pointer < wDesc.length()) {
            int newPointer = 0;
            if (pointer + 66 > wDesc.length()) {
                newPointer = wDesc.length();
            }
            else {
                newPointer = pointer + 66;
            }
            descriptionLines.push_back(wDesc.substr(pointer, newPointer - pointer));
            pointer = newPointer;
        }

        for (int j = 0; j < descriptionLines.size(); j++) {
            if (descriptionLines.size()!=1 && j!=0) {
                additionalLines++;
                TextOut(hdc, descStartX, descStartY + 17*(wId - 1) + 17 * (additionalLines), descriptionLines[j].c_str(), descriptionLines[j].length());
            }
            else {
                TextOut(hdc, descStartX, descStartY + 17*(wId - 1) + 17 * (additionalLines), descriptionLines[j].c_str(), descriptionLines[j].length());
            }
        }
        wId++;
    }
}