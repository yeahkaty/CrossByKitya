#include "ChooseCrosses.h"
#include "CrossByKitya.h"

LRESULT CALLBACK    ChooseCrossesWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_CREATE:
    {

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
        
        TCHAR MainText[] = L"�������� ���������";

        TextOut(hdc, 60, 170, MainText, _ARRAYSIZE(MainText));
        
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
