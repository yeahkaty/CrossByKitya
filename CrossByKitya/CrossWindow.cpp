#define _CRT_SECURE_NO_WARNINGS

#include "CrossWindow.h"
#include "CrossByKitya.h"
#include "Crossword.h"
#include "TxtConvertor.h"
#include <vector>
#include <chrono>
#include <ctime>
#include <time.h>

class CrossCheckResult {
public:
    vector<int> idsToGreen;
    vector<int> idsToRed;
    CrossCheckResult(vector<int>greenIds, vector<int> redIds) {
        idsToGreen = greenIds;
        idsToRed = redIds;
    }
    CrossCheckResult() {

    }
};

auto start = std::chrono::system_clock::now();
void DrawCrossword(HWND hWnd);
CrossCheckResult checkCross(Crossword cross);
#define testTextBox 999
HWND backToChooseBtn;
int crosswordFieldWidth;
int crosswordFieldHeight;
int descStartX;
int descStartY;
CrossCheckResult checkRes;
map<int, HWND> crossOnField;
Crossword cross;
int sumLength;
HWND nameTextBox;

LRESULT CALLBACK CrossWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    HDC hdcEdit = (HDC)wParam;

    switch (message)
    {
    case WM_CREATE:
    {
        backToChooseBtn = CreateWindow(TEXT("BUTTON"), TEXT("Give up"), (WS_VISIBLE | WS_CHILD), 970, 600, 400, 75, hWnd, (HMENU)BTN_CHOOSE_BACKTOCHOOSE, hInst, NULL);
        SendMessage(backToChooseBtn, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);
        nameTextBox = CreateWindow(TEXT("Edit"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 580, 30, 400, 40, hWnd, (HMENU)testTextBox, hInst, NULL);
        SendMessage(nameTextBox, WM_SETFONT, (WPARAM)textFont, TRUE);
    }
    break;
    case WM_CTLCOLOREDIT: 
    {
        HWND editControlNow = (HWND)lParam;
        HMENU menuNow = GetMenu(editControlNow);
        int menuNowId = int(menuNow);
        if (find(checkRes.idsToGreen.begin(), checkRes.idsToGreen.end(), menuNowId) != checkRes.idsToGreen.end()) {
            SetTextColor(hdcEdit, RGB(0, 255, 0));
        }
        else if (find(checkRes.idsToRed.begin(), checkRes.idsToRed.end(), menuNowId) != checkRes.idsToRed.end()) {
            SetTextColor(hdcEdit, RGB(255, 0, 0));
        }
        else {
            SetTextColor(hdcEdit, RGB(0, 0, 0));
        }
        SelectObject(hdcEdit, CreateSolidBrush(RGB(255, 255, 255)));
        
        return 0;
    }
    break;
    case Cross1Message: 
    {
        if (crossOnField.size() != 0) {
            for (map<int, HWND>::iterator it = crossOnField.begin(); it != crossOnField.end(); ++it) {
                DestroyWindow(it->second);
            };
            crossOnField.clear();
        }
        cross = crosswords[0];
        sumLength = 0;
        for (map<Word, Place>::iterator it = (*cross.getMap()).begin(); it != (*cross.getMap()).end(); ++it) {
            sumLength += it->first.length;
        }
        ShowWindow(hWnd, 1);
        RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
        DrawCrossword(hWnd); 

        
    }
    break;
    case Cross2Message: 
    {
        if (crossOnField.size() != 0) {
            for (map<int, HWND>::iterator it = crossOnField.begin(); it != crossOnField.end(); ++it) {
                DestroyWindow(it->second);
            };
            crossOnField.clear();
        }
        cross = crosswords[1];
        sumLength = 0;
        for (map<Word, Place>::iterator it = (*cross.getMap()).begin(); it != (*cross.getMap()).end(); ++it) {
            sumLength += it->first.length;
        }
        ShowWindow(hWnd, 1);
        RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
        DrawCrossword(hWnd);

    }
    break;
    case Cross3Message: 
    {
        if (crossOnField.size() != 0) {
            for (map<int, HWND>::iterator it = crossOnField.begin(); it != crossOnField.end(); ++it) {
                DestroyWindow(it->second);
            };
            crossOnField.clear();
        }
        cross = crosswords[2];
        sumLength = 0;
        for (map<Word, Place>::iterator it = (*cross.getMap()).begin(); it != (*cross.getMap()).end(); ++it) {
            sumLength += it->first.length;
        }
        ShowWindow(hWnd, 1);
        RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
        DrawCrossword(hWnd);

    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        if(crossOnField.find(wmId) != crossOnField.end())
        {
            if (HIWORD(wParam) == EN_CHANGE)
            {
                checkRes = checkCross(cross);
                if (checkRes.idsToGreen.size() == sumLength) {
                    auto end = std::chrono::system_clock::now();
                    std::chrono::duration<double> elapsed_seconds = end - start;
                    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
                    
                    TCHAR buff[12];
                    GetWindowText(nameTextBox, buff, 12);
                    string time = to_string((int)floor(elapsed_seconds.count()/60))+":";
                    int secs = floor(elapsed_seconds.count());
                    secs %= 60;
                    if (secs < 10) {
                        time += "0";
                    }
                    time += to_string(secs);
                    wstring wName = wstring(&buff[0]);
                    string name = string(wName.begin(), wName.end());
                    string scores = to_string((int)((1500 / elapsed_seconds.count()) * cross.getLevel()));


                    std::time_t t = std::time(nullptr);
                    char mbstr[100];
                    std::strftime(mbstr, sizeof(mbstr), "%F", std::localtime(&t));

                    string date = string(mbstr);



                    results.push_back(Result(name,time,scores,date));
                    results=txtParser.SortResults(results);
                    txtParser.WriteResults(results);


                    int crossStyle = GetWindowLong(hWnd, GWL_STYLE);
                    SetWindowLong(hWnd, GWL_STYLE, (unsigned int)(crossStyle & ~(WS_VISIBLE)));
                    int chooseStyle = GetWindowLong(chooseCrossesWnd, GWL_STYLE);
                    SetWindowLong(chooseCrossesWnd, GWL_STYLE, (unsigned int)(chooseStyle | (WS_VISIBLE)));
                    ShowWindow(mainWnd, 1);
                    UpdateWindow(mainWnd);
                    RedrawWindow(chooseCrossesWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
                    //std::cout << "finished computation at " << std::ctime(&end_time)
                        //std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
                }
                else {
                    ShowWindow(hWnd, 1);
                    RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
                    DrawCrossword(hWnd);
                    for (map<int, HWND>::iterator it = crossOnField.begin(); it != crossOnField.end(); ++it) {
                        /*if (find(checkRes.idsToGreen.begin(), checkRes.idsToGreen.end(), it->first) != checkRes.idsToGreen.end()) {
                            SetTextColor(hdcEdit, RGB(0, 255, 0));
                            SendMessage(hWnd, WM_CTLCOLOREDIT, (WPARAM)hdcEdit, (LPARAM)it->first);

                        }
                        else if (find(checkRes.idsToRed.begin(), checkRes.idsToRed.end(), it->first) != checkRes.idsToRed.end()) {
                            SetTextColor(hdcEdit, RGB(255, 0, 0));
                            SendMessage(hWnd, WM_CTLCOLOREDIT, (WPARAM)hdcEdit, (LPARAM)it->first);

                        }
                        else {
                            SetTextColor(hdcEdit, RGB(0, 0, 0));
                            SendMessage(hWnd, WM_CTLCOLOREDIT, (WPARAM)hdcEdit, (LPARAM)it->first);

                        }*/
                        SendMessage(hWnd, WM_CTLCOLOREDIT, (WPARAM)hdcEdit, (LPARAM)it->first);
                    }
                }
            }
            break;
        }
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
        
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps; //��������� ��������� ���������
        HDC hdc = BeginPaint(crossWnd, &ps); //������ ���������


        // Erase BackGround
        
        SetBkColor(hdc, RGB(255, 255, 255));
        SelectObject(hdc, whitePen);
        RECT rect;
        GetWindowRect(hWnd, &rect);
        LONG width = rect.right - rect.left;
        LONG height = rect.bottom - rect.top;
        Rectangle(hdc, 0, 0, width, height);
        // End of erase
        
        TCHAR titleText[] = L"Cross is puzzled by";
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




        EndPaint(crossWnd, &ps); //��������� ���������

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
void DrawCrossword(HWND hWnd)
{
    HDC hdc = GetDC(hWnd);
    SetTextColor(hdc, RGB(65, 45, 58));
    SetBkColor(hdc, color);
    SetBkMode(hdc, TRANSPARENT);
    SelectObject(hdc, textFont);
   
    int wId = 1;
    int hStep = (crosswordFieldWidth - 90) / cross.getSize_horizontal();
    int vStep = (crosswordFieldHeight - 90) / cross.getSize_vertical();
    int startX = 85;
    int startY = 130;
    int additionalLines = 0;
    map<Word, Place> displacement = *cross.getMap();
    for (map<Word, Place>::iterator it = displacement.begin(); it != displacement.end(); ++it) {
        Word wordNow = it->first;
        Place place = it->second;
        int editIdNow = 0;
        //Draw textboxes
        HFONT tempFont = CreateFont(vStep-10, hStep-16, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, MONO_FONT, TEXT("Courier"));
        for (int i = 0; i < wordNow.getLength(); i++) {
            if (place.getIsHorizontal()) {
                editIdNow = stoi(to_string(place.getXPlace()+i)+to_string(place.getYPlace()));
                if (crossOnField.find(editIdNow) == crossOnField.end())
                {
                    crossOnField.insert(pair<int, HWND>(editIdNow, CreateWindow(TEXT("Edit"), TEXT(""), WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER, startX + (place.getXPlace() + i) * hStep, startY + place.getYPlace() * vStep, hStep, vStep, crossWnd, (HMENU)editIdNow, hInst, NULL)));
                    SendMessage(crossOnField[editIdNow], WM_SETFONT, (WPARAM)tempFont, TRUE);
                }  
            }
            else {
                editIdNow = stoi(to_string(place.getXPlace()) + to_string(place.getYPlace()+i));

                if (crossOnField.find(editIdNow) == crossOnField.end())
                {
                    crossOnField.insert(pair<int, HWND>(editIdNow, CreateWindow(TEXT("Edit"), TEXT(""), WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER, startX + place.getXPlace() * hStep, startY + (place.getYPlace() + i) * vStep, hStep, vStep, crossWnd, (HMENU)editIdNow, hInst, NULL)));
                    SendMessage(crossOnField[editIdNow], WM_SETFONT, (WPARAM)tempFont, TRUE);
                }
            }
        }
        //Draw id's
        SelectObject(hdc, textFont);
        if (place.getIsHorizontal()) {
            if (wId < 10) {
                TextOut(hdc, (startX + place.getXPlace() * hStep) - hStep * 0.4, startY + place.getYPlace() * vStep + vStep * 0.25, to_wstring(wId).c_str(), 1);
            }
            else {
                TextOut(hdc, (startX + place.getXPlace() * hStep) - hStep * 0.8, startY + place.getYPlace() * vStep + vStep * 0.25, to_wstring(wId).c_str(), 2);
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
CrossCheckResult checkCross(Crossword cross){
    vector<int> greenIds;
    vector<int> redIds;
    map<Word, Place> displacement = *cross.getMap();
    for (map<Word, Place>::iterator it = displacement.begin(); it != displacement.end(); ++it) {
        Word wordNow = it->first;
        Place placeNow = it->second;
        bool areAllLetters = true;
        for (int i = 0; i < wordNow.getWord().length(); i++) {
            if (placeNow.getIsHorizontal()) {
                TCHAR buff[2];
                GetWindowText(crossOnField[stoi(to_string(placeNow.getXPlace()+i)+to_string(placeNow.getYPlace()))], buff, 2);
                if (wcslen(buff) == 0) {
                    areAllLetters = false;
                    break;
                }
            }
            else {
                TCHAR buff[2];
                GetWindowText(crossOnField[stoi(to_string(placeNow.getXPlace()) + to_string(placeNow.getYPlace()+i))], buff, 2);
                if (wcslen(buff) == 0) {
                    areAllLetters = false;
                    break;
                }
            }
        }
        if (areAllLetters) 
        {
            bool makeGreen = true;
            for (int i = 0; i < wordNow.getWord().length(); i++) {
                if (placeNow.getIsHorizontal()) {
                    TCHAR buff[2];
                    GetWindowText(crossOnField[stoi(to_string(placeNow.getXPlace() + i) + to_string(placeNow.getYPlace()))], buff, 2);
                    if (buff[0] != wordNow.getWord()[i]) {
                        makeGreen = false;
                        break;
                    }
                }
                else {
                    TCHAR buff[2];
                    GetWindowText(crossOnField[stoi(to_string(placeNow.getXPlace()) + to_string(placeNow.getYPlace() + i))], buff, 2);
                    if (buff[0] != wordNow.getWord()[i]) {
                        makeGreen = false;
                        break;
                    }
                }
            }
            if (makeGreen) {
                for (int i = 0; i < wordNow.getWord().length(); i++) {
                    
                    if (placeNow.getIsHorizontal()) {
                        greenIds.push_back(stoi(to_string(placeNow.getXPlace() + i) + to_string(placeNow.getYPlace())));
                    }
                    else {
                        greenIds.push_back(stoi(to_string(placeNow.getXPlace()) + to_string(placeNow.getYPlace() + i)));
                    }
                }
            }
            else {
                for (int i = 0; i < wordNow.getWord().length(); i++) {
                    if (placeNow.getIsHorizontal()) {
                        redIds.push_back(stoi(to_string(placeNow.getXPlace() + i) + to_string(placeNow.getYPlace())));
                    }
                    else {
                        redIds.push_back(stoi(to_string(placeNow.getXPlace()) + to_string(placeNow.getYPlace() + i)));
                    }
                }
            }
        }
    }
    return CrossCheckResult(greenIds, redIds);
}