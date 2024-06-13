// WindowsProject1.cpp : Определяет точку входа для приложения.
//

#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "WindowsProject1.h"
#include <commdlg.h>
#include <locale.h>
#include <cstdio>
#include <cmath>
#include "Graph.h"
#define MAX_LOADSTRING 100

int n;
int Matrix[100][100];
int Path[100];
int lenPath;
TCHAR FileName[200];
int center[100];

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, L"Главное окно", WS_OVERLAPPEDWINDOW,
      500, 100, 700, 700, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

int GetFileNameOpen(char name[200])
{
    OPENFILENAME ofn;
    TCHAR szFilter[100] = L"Текстовые файлы\0*.txt";
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = szFilter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = FileName;
    ofn.nMaxFile = 200;
    ofn.lpstrInitialDir = NULL;
    if (GetOpenFileName(&ofn))
    {
        wcstombs(name, FileName, sizeof(FileName));
        return 1;
    }
    else
        return 0;
}

INT_PTR CALLBACK Dialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    TCHAR bufN[5];
    TCHAR bufMatrix[100];
    int i1 = 0;
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            GetDlgItemText(hDlg, IDC_EDIT1, bufN, 4);
            GetDlgItemText(hDlg, IDC_EDIT2, bufMatrix, 100);
            n = _wtoi(bufN);
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    Matrix[i][j] = (int)bufMatrix[i1] - 48;
                    i1++;
                }
                i1 += 2;
            }
            EndDialog(hDlg, 1);
            break;
        case IDCANCEL:
            EndDialog(hDlg, 0);
            break;
        }
        return (INT_PTR)TRUE;
    }
    return (INT_PTR)FALSE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    setlocale(LC_ALL, "rus");
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            int PrFileName = 0;
            int PrInput = 0;
            double a = 0.0;
            int r = 10;
            int coords[100][2];
            int x, y;
            TCHAR FileName[100];
            TCHAR Buf[10];
            HBRUSH hBrushSol, hBrushBack;
            HPEN hPen, hRedPen;
            HDC hdc;
            PAINTSTRUCT ps;
            RECT WinCoord = {};
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_FAIL:
                char name[200];
                PrFileName = GetFileNameOpen(name);
                if (PrFileName)
                {
                    FILE* file;
                    size_t num;
                    //char name[100];
                    //wcstombs_s(&num, name, (size_t)100, FileName, (size_t)100);
                    file = fopen(name, "rt");
                    fscanf(file, "%d", &n);
                    for (int i = 0; i < n; i++)
                        for (int j = 0; j < n;j++)
                            fscanf(file, "%d", &Matrix[i][j]);
                    fclose(file);
                }
                break;
            case IDM_KLAV:
                PrInput = DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, Dialog1);
                break;
            case IDM_OUTG:
                hdc = GetDC(hWnd);
                hBrushBack = CreateSolidBrush(RGB(255, 255, 255));
                SelectObject(hdc, hBrushBack);
                GetWindowRect(hWnd, &WinCoord);
                Rectangle(hdc, 0, 0, WinCoord.right, WinCoord.bottom);
                DeleteObject(hBrushBack);
                hBrushSol = CreateSolidBrush(RGB(0, 0, 0));
                SelectObject(hdc, hBrushSol);
                for (int i = 0; i < n; i++)
                {
                    a += 3.14 * 2 / n;
                    x = 300 + (int)(150 * cos(a));
                    y = 250 + (int)(150 * sin(a));
                    Ellipse(hdc, x, y, x + r, y + r);
                    _itow(i, Buf, 10);
                    TextOut(hdc, x + r, y + r, Buf, 2);
                    coords[i][0] = x;
                    coords[i][1] = y;
                }
                DeleteObject(hBrushSol);
                hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
                SelectObject(hdc, hPen);
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        if (Matrix[i][j] == 1)
                        {
                            MoveToEx(hdc, coords[i][0] + r/2, coords[i][1] + r/2, NULL);
                            LineTo(hdc, coords[j][0] + r/2, coords[j][1] + r/2);
                        }
                DeleteObject(hPen);
                ReleaseDC(hWnd, hdc);
                break;
            case IDM_FIND:
                FindCircle(Matrix, n, Path, &lenPath, center);
                break;
            case IDM_OUTC:
                hdc = GetDC(hWnd);
                GetWindowRect(hWnd, &WinCoord);
                hBrushBack = CreateSolidBrush(RGB(255, 255, 255));
                SelectObject(hdc, hBrushBack);
                GetWindowRect(hWnd, &WinCoord);
                Rectangle(hdc, 0, 0, WinCoord.right, WinCoord.bottom);
                DeleteObject(hBrushBack);
                TCHAR Buf[10];
                hdc = GetDC(hWnd);
                hBrushSol = CreateSolidBrush(RGB(0, 0, 0));
                SelectObject(hdc, hBrushSol);
                for (int i = 0; i < n; i++)
                {
                    a += 3.14 * 2 / n;
                    x = 300 + (int)(150 * cos(a));
                    y = 250 + (int)(150 * sin(a));
                    Ellipse(hdc, x, y, x + r, y + r);
                    _itow(i, Buf, 10);
                    TextOut(hdc, x + r, y + r, Buf, 2);
                    coords[i][0] = x;
                    coords[i][1] = y;
                }
                DeleteObject(hBrushSol);
                hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
                SelectObject(hdc, hPen);
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        if (Matrix[i][j] == 1)
                        {
                            MoveToEx(hdc, coords[i][0] + r / 2, coords[i][1] + r / 2, NULL);
                            LineTo(hdc, coords[j][0] + r / 2, coords[j][1] + r / 2);
                        }
                DeleteObject(hPen);
                hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
                SelectObject(hdc, hRedPen);
                for (int i = 0; i < lenPath - 1; i++)
                {
                    MoveToEx(hdc, coords[Path[i]][0] + r / 2, coords[Path[i]][1] + r / 2, NULL);
                    LineTo(hdc, coords[Path[i + 1]][0] + r / 2, coords[Path[i + 1]][1] + r / 2);
                }
                DeleteObject(hRedPen);
                hBrushSol = CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc, hBrushSol);
                for (int i = 0; i < n; i++)
                {
                    if (center[i] == -1)
                        break;
                    x = coords[center[i]][0];
                    y = coords[center[i]][1];
                    Ellipse(hdc, x, y, x + r, y + r);
                }
                DeleteObject(hBrushSol);
                ReleaseDC(hWnd, hdc);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
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

// Обработчик сообщений для окна "О программе".
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
