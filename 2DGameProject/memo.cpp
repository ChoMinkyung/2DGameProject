// JM_WINPROJ_Game.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "2DGameProject.h"
#include "framework.h"
#include <stdio.h>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib,"msimg32.lib")
#define timer_ID_1 123

#include <iostream>
using namespace std;

#ifdef UNICODE

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 

#else

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 

#endif

using namespace Gdiplus;
static POINT ptMousePos;

int RUN_FRAME_MAX = 0;
int RUN_FRAME_MIN = 0;

const int SPRITE_SIZE_X = 4;//57;
const int SPRITE_SIZE_Y = 6;//52;

int SPRITE_FRAME_COUNT_X = 0;
int SPRITE_FRAME_COUNT_Y = 0;

BITMAP bitAni;

int curframe = RUN_FRAME_MIN;

RECT rectView;


HBITMAP hBackImage;
BITMAP bitBack;

HBITMAP hOrangeMushroomImage;
BITMAP bitOrangeMushroom;

HBITMAP hDoubleBufferImage;

void CreateBitmap();
void DrawBitmap(HWND hWnd, HDC hdc);
void DeleteBitmap();

void UpdataFrame(HWND hWnd);

void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY2DGAMEPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);


    //Gdi_Init();
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2DGAMEPROJECT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MY2DGAMEPROJECT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY2DGAMEPROJECT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        100, 100, 1660, 780, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    static POINT ptMousePos;
    //RECT rectView;
   
    //HDC hdc;

    switch (message)
    {
    case WM_CREATE: // 윈도우가 생성될 때 한번 호출
        ptMousePos.x = 0;
        ptMousePos.y = 0;
        CreateBitmap();
        //SetTimer(hWnd, timer_ID_2, 20, AniProc);
        SetTimer(hWnd, timer_ID_1, 30, AniProc);
        GetClientRect(hWnd, &rectView);
        break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmld = HIWORD(wParam);


        // 메뉴 선택을 구문 분석합니다:
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

    case WM_TIMER: // 타이머 이벤트, 타이머는 일이 바쁘지 않을때만 잘 작동됨
    {
        if (wParam == timer_ID_1)
        {
            ptMousePos.x += 20;
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
    break;

    case WM_LBUTTONDOWN:
        /*ptMousePos.x = LOWORD(lParam);
        ptMousePos.y = HIWORD(lParam);
        InvalidateRect(hWnd, NULL, TRUE);*/
        break;
    case WM_LBUTTONUP:
        //DrawMushroom(hWnd,hdc);
        //InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawBitmapDoubleBuffering(hWnd, hdc);
      
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        DeleteBitmap();
        KillTimer(hWnd, timer_ID_1);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



// 정보 대화 상자의 메시지 처리기입니다.
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


void CreateBitmap()
{
    // >> 배경
    hBackImage = (HBITMAP)LoadImage(nullptr, TEXT("images/background.bmp")
        , IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    if (hBackImage == NULL)
    {
        DWORD dwError = GetLastError();
        MessageBox(NULL, _T("배경 이미지 로드 에러"), _T("에러"), MB_OK);
        return;
    }
    GetObject(hBackImage, sizeof(BITMAP), &bitBack);


    {
        hOrangeMushroomImage = (HBITMAP)LoadImage(nullptr, TEXT("images/주황버섯.bmp")
            , IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hOrangeMushroomImage == NULL)
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("버섯이미지 로드 에러"), _T("에러"), MB_OK);
            return;
        }
        GetObject(hOrangeMushroomImage, sizeof(BITMAP), &bitOrangeMushroom);

        RUN_FRAME_MAX = bitAni.bmWidth / SPRITE_SIZE_X - 1;
        RUN_FRAME_MIN = 2;
        curframe = RUN_FRAME_MIN;

        SPRITE_FRAME_COUNT_X = bitAni.bmWidth / SPRITE_SIZE_X;
        SPRITE_FRAME_COUNT_Y = bitAni.bmHeight / SPRITE_SIZE_Y;
    }


}
void DrawBitmap(HWND hWnd, HDC hdc)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;
    int bx;
    int by;

    {
        hMemDC = CreateCompatibleDC(hdc);
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
        bx = bitBack.bmWidth;
        by = bitBack.bmHeight;

        BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);

        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }

    {
        hMemDC = CreateCompatibleDC(hdc);
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hOrangeMushroomImage);
        bx = bitOrangeMushroom.bmWidth / SPRITE_FRAME_COUNT_X;;
        by = bitOrangeMushroom.bmHeight / SPRITE_FRAME_COUNT_Y;

        //BitBlt(hdc, 150, 150, bx, by, hMemDC, 0, 0, SRCCOPY);

        //색 빼기. (255 , 0 ,255 ) 는 분홍색.
        TransparentBlt(hdc, 100, 100, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));


        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }

}

//void DrawMushroom(HWND hWnd, HDC hdc)
//{
//
//    HDC hMemDC;
//    HBITMAP hOldBitmap;
//    int bx, by;
//    
//
//    hMemDC = CreateCompatibleDC(hdc);
//    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hOrangeMushroomImage);
//    bx = bitOrangeMushroom.bmWidth;
//    by = bitOrangeMushroom.bmHeight;
//
//    //BitBlt(hdc, 150, 150, bx, by, hMemDC, 0, 0, SRCCOPY);
//
//    //색 빼기. (255 , 0 ,255 ) 는 분홍색.
//    TransparentBlt(hdc, ptMousePos.x, ptMousePos.y, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));
//
//    SelectObject(hMemDC, hOldBitmap);
//    DeleteDC(hMemDC);
//}

void DeleteBitmap()
{
    DeleteObject(hBackImage);
    DeleteObject(hOrangeMushroomImage);
}


void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;
    int bx, by;

    HDC hMemDC2;
    HBITMAP hOldBitmap2;

    hMemDC = CreateCompatibleDC(hdc);
    if (hDoubleBufferImage == NULL)
    {
        hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
    }
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

    { // 배경
        hMemDC2 = CreateCompatibleDC(hMemDC);
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);
        bx = bitBack.bmWidth;
        by = bitBack.bmHeight;

        cout << rectView.right << ", " << rectView.bottom << endl;
        BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);


        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);

    }

    //TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, RGB(255, 0, 255));
    BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, SRCCOPY);
    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);

    //HDC hMemDC;
    //HBITMAP hOldBitmap;
    //int bx, by;

    //HDC hMemDC2;
    //HBITMAP hOldBitmap2;


    //hMemDC = CreateCompatibleDC(hdc);

    //if (hDoubleBufferImage == NULL)
    //{
    //    hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
    //}
    //hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

    //{ // 배경 
    //    hMemDC2 = CreateCompatibleDC(hMemDC);
    //    hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);
    //    bx = bitBack.bmWidth;
    //    by = bitBack.bmHeight;

    //    BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);

    //    SelectObject(hMemDC2, hOldBitmap2);
    //    DeleteDC(hMemDC2);
    //}

    //{ // 주황버섯
    //    hMemDC2 = CreateCompatibleDC(hMemDC);
    //    hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hOrangeMushroomImage);
    //    bx = bitOrangeMushroom.bmWidth;// , SPRITE_FRAME_COUNT_X;
    //    by = bitOrangeMushroom.bmHeight;// , SPRITE_FRAME_COUNT_Y;

    //    int xStart = curframe * bx;
    //    int yStart = 0;

    //   // static int xPos = 0;

    //    TransparentBlt(hMemDC, 0, 0, bx, by, hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255));

    //    SelectObject(hMemDC2, hOldBitmap2);
    //    DeleteDC(hMemDC2);

    //}

    //BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, SRCCOPY);
    //SelectObject(hMemDC, hOldBitmap);
    //DeleteDC(hMemDC);// 잠시만 기다려바
}

void UpdataFrame(HWND hWnd)
{
    curframe++;
    if (curframe > RUN_FRAME_MAX)
        curframe = RUN_FRAME_MIN;

    InvalidateRect(hWnd, NULL, false);

}

static int yPos = 0;

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    UpdataFrame(hWnd);
    yPos += 5;
    if (yPos > rectView.bottom) yPos = 0;
}

