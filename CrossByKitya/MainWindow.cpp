// Message handler for about box.
#include "CrossByKitya.h"


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

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {

        
        HWND button0 = CreateWindow(TEXT("BUTTON"), TEXT("����������"), WS_VISIBLE | WS_CHILD, 850, 160, 500, 100, hWnd, (HMENU)BTN_MAIN_CROSS, hInst, NULL);
        HWND button1 = CreateWindow(TEXT("BUTTON"), TEXT("�����"), WS_VISIBLE | WS_CHILD, 850, 300, 500, 100, hWnd, (HMENU)BTN_MAIN_EXIT, hInst, NULL);
        SendMessage(button0, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);
        SendMessage(button1, WM_SETFONT, (WPARAM)bigButtonFont, TRUE);

        

        /*
        HFONT CreateFont(
            int nHeight,               // ������ ������
            int nWidth,                // ������� ������ �������
            int nEscapement,           // ���� �������
            int nOrientation,          // ���� ���������� �������� �����
            int fnWeight,              // ������� ������
            DWORD fdwItalic,           // ��������� ��������� ���������� ������
            DWORD fdwUnderline,        // ��������� ��������� �������������
            DWORD fdwStrikeOut,        // ��������� ��������� ������������
            DWORD fdwCharSet,          // ������������� ������ ��������
            DWORD fdwOutputPrecision,  // �������� ������
            DWORD fdwClipPrecision,    // �������� ���������
            DWORD fdwQuality,          // �������� ������
            DWORD fdwPitchAndFamily,   // ��� ����� ��������� ������ � ���������
            LPCTSTR lpszFace           // ��� ��������� ������
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

        PAINTSTRUCT ps; //��������� ��������� ���������
        HDC hdc = BeginPaint(hWnd, &ps); //������ ���������
        SelectObject(hdc, hBrush);

        SetBkMode(hdc, TRANSPARENT);
        SetBkColor(hdc, color);
        Rectangle(hdc, 50, 160, 800, 600);

        SetTextColor(hdc, RGB(200, 100, 165));
        SelectObject(hdc, textFont);
        TCHAR MainText[] = L"����� ���������� � ���� CrossByKitya!";
        TCHAR MainText1[] = L"��� �� ������ ���� ������� �� ������ ����������.";
        TCHAR MainText2[] = L"���� �� ������ �������� ����, ������� �� ������ �����.";
        TextOut(hdc, 60, 170, MainText, _ARRAYSIZE(MainText));
        TextOut(hdc, 60, 210, MainText1, _ARRAYSIZE(MainText1));
        TextOut(hdc, 60, 250, MainText2, _ARRAYSIZE(MainText2));

        TCHAR titleText[] = L"CrossByKitya";

        SetTextColor(hdc, RGB(255, 170, 220));
        SetBkColor(hdc, RGB(255, 255, 255));
        SelectObject(hdc, titleFont);
        TextOut(hdc, 530, 10, titleText, _ARRAYSIZE(titleText));

        EndPaint(hWnd, &ps); //��������� ���������
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

