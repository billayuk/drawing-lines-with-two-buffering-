// lines without buffering.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "lines without buffering.h"
#include "vector"
#include "points_To_Use.h"

using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


vector<points_To_Use>points;
bool draw = false;
bool newline = false;


//to make the program to stop buffering, i need to create a bitmap 
HBITMAP        hBitmap = 0;
HBITMAP        storeBitmap = 0;
HDC            hmemDC = 0;
unsigned int   width = 0;
unsigned int   height = 0;

bool bitmapCreate(HWND hWnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LINESWITHOUTBUFFERING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LINESWITHOUTBUFFERING));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LINESWITHOUTBUFFERING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LINESWITHOUTBUFFERING);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   //now create you bitmap of the same size or client area of you window and display it
   RECT mainArea;
   GetClientRect(hWnd, &mainArea);
   width = mainArea.right - mainArea.left;
   height = mainArea.bottom - mainArea.top;
   bitmapCreate(hWnd);


   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
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
            PAINTSTRUCT ps;
           /* HDC hdc = BeginPaint(hWnd, &ps);*/
            
            if (points.size() > 0)
            {
                if (points.size() ==1)
                {
                    SetPixel(hmemDC, points[0].getX(), points[0].getY(), RGB(0, 0, 255));

                }
                else
                {
                    HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
                    HGDIOBJ oldpen = SelectObject(hmemDC, pen);

                    for (size_t i = 0; i < points.size(); i++)
                    {
                        if (points[i].islineBegins())
                        {
                            MoveToEx(hmemDC, points[i].getX(), points[i].getY(), NULL);
                        }
                        else
                        {
                            LineTo(hmemDC, points[i].getX(), points[i].getY());
                        }

                  
                    }
                    SelectObject(hmemDC, oldpen);
                    DeleteObject(pen);
                }
            }

            // add the next two lines to your paint
            HDC hdc = BeginPaint(hWnd, &ps);
            BitBlt(hdc, 0, 0, width, height, hmemDC, 0, 0, SRCCOPY);
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_LBUTTONDOWN:
        draw = true;
        newline = true;
        break;

    case WM_LBUTTONUP:
        draw = false;
        newline = false;
        break;


    case WM_MOUSEMOVE:
        if (draw)
        {
            POINTS clickPoint = MAKEPOINTS(lParam);
            points.push_back(points_To_Use(clickPoint.x, clickPoint.y, newline));
            newline = false;
            InvalidateRect(hWnd, NULL, true);
        }
        break;

        //now create the size with lparam
    case WM_SIZE:
        width = LOWORD(lParam);
        height = HIWORD(lParam);
        bitmapCreate(hWnd);
        InvalidateRect(hWnd, NULL, FALSE);


    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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

//select and delete bitmap
// remember to delete any extisting bitmap
void bitmapDelete()
{
    if (storeBitmap != 0 && hmemDC != 0)
    {
        SelectObject(hmemDC, storeBitmap);
        storeBitmap = 0;
    }
    if (hBitmap !=0)
    {
        DeleteObject(hBitmap);
        hBitmap = 0;
    }
    if (hmemDC !=0)
    {
        DeleteDC(hmemDC);
        hmemDC = 0;
    }
}


bool bitmapCreate(HWND hWnd)
{
    bool state = false;
    HDC hdc;

    //to delete object
    bitmapDelete();

    //create a context compatible with the window
    hdc = ::GetDC(hWnd);
    hmemDC = CreateCompatibleDC(hdc);
    if (hmemDC !=0)
    {
        //create a bitmap compatible with your windows
        hBitmap = CreateCompatibleBitmap(hdc, width, height);
        if (hBitmap != 0)
        {
          /*  SaveToFile(hBitmap2, "c:\\t.bmp"); you can save your bitmap to a file with this code */
            storeBitmap = (HBITMAP)SelectObject(hmemDC, hBitmap);
            state = true;
        }
    }
    ReleaseDC(hWnd, hdc);
    RECT bill;

    bill.left = 0;
    bill.right = width;
    bill.top = 0;
    bill.bottom = height;
    FillRect(hmemDC, &bill, (HBRUSH)(COLOR_WINDOW + 1));
    return state;

}
