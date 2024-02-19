// 2DGameProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "framework.h"
#include "2DGameProject.h"

#include <time.h>
#include <iostream>

#include <wingdi.h>
#include "CObject.h"
#include "CSun.h"
#include "CMap.h"
#include "CSunFlower.h"
#include "CPeashooter.h"
#include "CZombie.h"

using namespace std;

// >> : GDI+
#include <objidl.h>
#include <gdiplus.h> 
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;
ULONG_PTR g_GdiToken;

void Gdi_Init();
void Gdi_End();

// << :

//>> : ani
#pragma comment(lib, "msimg32.lib")


//#ifdef UNICODE
//
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
//
//#else
//
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
//
//#endif

// >> : game control
bool gameStart;
bool gameOn;
int curMode;

// << :


// >> : image variable

HBITMAP hEndingImage;
BITMAP bitEnding;

HBITMAP hTitleImage;
BITMAP bitTitle;

HBITMAP hMainMenuImage;
BITMAP bitMainMenu;

HBITMAP hMainMenuBtnImage;
BITMAP bitMainMenuBtn;

HBITMAP hZombieImage;
BITMAP bitZombie;

HBITMAP hHUDImage;
BITMAP bitHUD;

HBITMAP hStartTextImage;
BITMAP bitStartText;

HBITMAP hBackImage;
BITMAP bitBack;

HBITMAP hSunflowerImage;
BITMAP bitSunflower;

HBITMAP hPeashooterImage;
BITMAP bitPeashooter;

HBITMAP hSunImage;
BITMAP bitSun;

HBITMAP hProgressImage;
BITMAP bitProgress;

HBITMAP hSunUiImage;
BITMAP bitSunUI;

HBITMAP hAniImage;
BITMAP bitAni;

HBITMAP hDoubleBufferImage;

const int SPRITE_SIZE_X = 57;
const int SPRITE_SIZE_Y = 52;

int RUN_FRAME_MAX = 7;
int RUN_FRAME_MIN = 0;

int curframe = RUN_FRAME_MIN;
int curframeWalk = 0;
int curframeAttack = 0;
int sunCurframe = 0;

double progressSize = 10;
int headPos;
double xPos;

int SPRITE_FRAME_COUNT_X = 0;
int SPRITE_FRAME_COUNT_Y = 0;

// << :


// >> : etc variable
RECT rectView;
CObject* map = new CMap();
int sunScore;
POINT btnSize = { 80, 60 };
vector<RECT> btnPos;
vector<BOOL> btnState;

// << :


// >> : func
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
void CreateBitmap();
void DeleteBitmap();
void UpdataFrame(HWND hWnd);
void DrawStartTest(HDC hdc);
void DrawTitle(HDC hdc);
void DrawMainMenu(HDC hdc);
void DrawEnding(HDC hdc);
// << :


#define MAX_LOADSTRING 100

enum State { Update, SunUpdate, SunCreate, Progress, ZombieCreate, ZombieUpdate };
enum btn { sunflower = 0, peashooter };
enum Mode { title, mainmenu, game, ending };

#define timer_ID_UPDATE Update
#define timer_ID_SUN_UPDATE SunUpdate
#define timer_ID_SUN_CREATE SunCreate
#define timer_ID_PROGRESS Progress
#define timer_ID_ZOMBIES_CREATE ZombieCreate
#define timer_ID_ZOMBIES_UPDATE ZombieUpdate


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

	Gdi_Init();
	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		Gdi_End();
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LOGO));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wcex.lpszMenuName = MAKEINTRESOURCEW(NULL); //IDC_MY2DGAMEPROJECT
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_LOGO));

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

	HWND hWnd = CreateWindowW(szWindowClass, _T("Plants vs. Zombies"), WS_OVERLAPPEDWINDOW,
		200, 200, 1030, 650, nullptr, nullptr, hInstance, nullptr); //szTitle , CW_USEDEFAULT, 0, CW_USEDEFAULT, 0


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
	static std::vector<CObject*> suns;
	static std::vector<CObject*> plants;
	static std::vector<CObject*> zombies;
	static CObject* obj;
	static POINT ptMousePos;
	static POINT ptMoveMousePos;
	static RECT btn;
	static int btnClick = -1;

	//AddFontResource("font/휴먼범석체.ttf");

	switch (message)
	{
	case WM_SIZE:
		GetClientRect(hWnd, &rectView);
		break;
	case WM_CREATE:
	{
		curMode = title;
		
		CreateBitmap();
		GetClientRect(hWnd, &rectView);

		btnPos.push_back({ 10, 5, 75, 55 });
		btnPos.push_back({ 5, 65, 75, 105 });

		btnState.push_back(FALSE);
		btnState.push_back(FALSE);

		gameOn = FALSE;
		gameStart = FALSE;
		sunScore = 100;
		headPos = 830;
		xPos = 1000;
		srand(time(NULL));

		break;
	}
	case WM_LBUTTONDOWN:

		ptMousePos.x = LOWORD(lParam);
		ptMousePos.y = HIWORD(lParam);

		if (curMode == game)
		{

			// 해 모으기
			if (ptMousePos.x > 250 && ptMousePos.x < 1000 && ptMousePos.y > 0 && ptMousePos.y < 580)
			{

				for (int i = 0; i < suns.size(); i++)
				{
					if (suns[i]->SetInClick(ptMousePos))
					{
						sunScore += 25;
						break;
					};
				}
			}

			// 식물 심기
			if (btnClick >= 0)
			{
				if (map->SetInClick(ptMousePos))
				{
					POINT pos = map->GetPos();
					if (pos.x != -1)
					{
						switch (btnClick)
						{
						case sunflower:
							obj = new CSunFlower(pos);
							plants.push_back(obj);
							sunScore -= 50;
							break;
						case peashooter:
							obj = new CPeashooter(pos);
							plants.push_back(obj);
							sunScore -= 100;
							break;
						default:
							break;
						}
					}
				}
				btnClick = -1;
			}

			for (int i = 0; i < btnPos.size(); i++)
			{
				if (btnState[i] && ptMousePos.x > btnPos[i].left && ptMousePos.x < btnPos[i].right
					&& ptMousePos.y > btnPos[i].top && ptMousePos.y < btnPos[i].bottom)
				{
					btnClick = i;
				}
			}

		}

		break;
	case WM_MOUSEMOVE:

		if (curMode == game)
		{

			if (btnClick >= 0)
			{
				ptMoveMousePos.x = LOWORD(lParam);
				ptMoveMousePos.y = HIWORD(lParam);
				map->SetInClick(ptMoveMousePos);
			}
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:

			//if (!gameStart && !gameOn)
			//{
			//	cout << "게임 시작" << endl;
			//	SetTimer(hWnd, timer_ID_UPDATE, 150, NULL);
			//	SetTimer(hWnd, timer_ID_SUN_UPDATE, 10, NULL); // 초당 24~30번
			//	SetTimer(hWnd, timer_ID_SUN_CREATE, 5000, NULL);
			//	SetTimer(hWnd, timer_ID_PROGRESS, 1000, NULL);
			//	SetTimer(hWnd, timer_ID_ZOMBIES_CREATE, 10000, NULL); //20000
			//	SetTimer(hWnd, timer_ID_ZOMBIES_UPDATE, 200, NULL);
			//	gameStart = TRUE;
			//	gameOn = TRUE;
			//}

			break;
		default:
			break;
		}
		break;
	case WM_TIMER:

		if (curMode == game)
		{

			switch (wParam)
			{
			case Update:
			{
				int removeIDX = -1;
				for (int i = 0; i < zombies.size(); i++)
				{
					
					if (zombies[i]->GetPos().x < 250)
					{
						curMode = ending;
						InvalidateRect(hWnd, NULL, TRUE);

					};
					
					// 충돌 검사
					int isCollision = 0;
					for (int j = 0; j < plants.size(); j++)
					{
						isCollision = plants[j]->Collision(zombies[i]->GetPos());

						if (isCollision < 0)
						{
							removeIDX = j;
							zombies[i]->Collision({ -1, -1 });
						}

						// 식물과 직접 충돌하면 1 반환
						if (isCollision == 1)
						{
							zombies[i]->Collision({ 1, 1 });
						}

						// 공격물체 충돌하면 2 반환
						if (isCollision == 2)
						{
							zombies[i]->Collision({ 2, 2 });
						}

					}

					

				}

				if (removeIDX >= 0)
				{
					plants.erase(remove(plants.begin() + removeIDX, plants.begin() + removeIDX + 1, plants[removeIDX]));
					removeIDX = -1;
				}

				for (int i = 0; i < plants.size(); i++)
				{
					plants[i]->Update(&rectView);
					if (plants[i]->Species() == sunflower && plants[i]->Count() == 50)
					{
						obj = new CSun(plants[i]->GetPos());
						suns.push_back(obj);
					}
				}



			}
			break;
			case SunUpdate:
				for (int i = 0; i < suns.size(); i++)
				{
					suns[i]->Update(&rectView);
					if (suns[i]->Count() > 100 || suns[i]->GetPos().x <= 100 && suns[i]->GetPos().y <= 15)
					{
						suns.erase(remove(suns.begin() + i, suns.begin() + i + 1, suns[i]));

					}
				}
				break;
			case SunCreate:
				obj = new CSun(&rectView);
				suns.push_back(obj);
				break;

			case ZombieCreate:
				//cout << "좀비 생성" << endl;
				obj = new CZombie();
				zombies.push_back(obj);
				break;
			case ZombieUpdate:
			{
				UpdataFrame(hWnd);

				int removeIDX = -1;
				for (int i = 0; i < zombies.size(); i++)
				{
					zombies[i]->Update(&rectView);
					if (zombies[i]->GetState() < 0) removeIDX = i;

				}

				if (removeIDX >= 0)
				{
					zombies.erase(remove(zombies.begin() + removeIDX, zombies.begin() + removeIDX + 1, zombies[removeIDX]));
					removeIDX = -1;
				}
			}
			break;
			case Progress:
				headPos--;
				progressSize += 0.5;

				if (headPos == 505)
				{
					KillTimer(hWnd, timer_ID_PROGRESS);
					KillTimer(hWnd, timer_ID_ZOMBIES_CREATE);
					gameOn = FALSE;
				}
				break;
			default:
				break;
			}


			break;
		}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
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
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		Graphics graphics(hdc);
		if (curMode == title)
		{
			DrawTitle(hdc);
			Sleep(3000);
			DeleteObject(hTitleImage);
			cout << "cur mode : " << curMode << endl;
			curMode = mainmenu;
			InvalidateRect(hWnd, NULL, false);


		}

		else if (curMode == mainmenu)
		{
			cout << "cur mode : " << curMode << endl;
			DrawMainMenu(hdc);
			Sleep(3000);
			DeleteObject(hMainMenuImage);
			DeleteObject(hMainMenuBtnImage);
			curMode = game;
			InvalidateRect(hWnd, NULL, false);


		}
		else if (curMode == game)
		{
			if (!gameStart && !gameOn)
			{
				cout << "게임 시작" << endl;
				SetTimer(hWnd, timer_ID_UPDATE, 150, NULL);
				SetTimer(hWnd, timer_ID_SUN_UPDATE, 10, NULL); // 초당 24~30번
				SetTimer(hWnd, timer_ID_SUN_CREATE, 5000, NULL);
				SetTimer(hWnd, timer_ID_PROGRESS, 1000, NULL);
				SetTimer(hWnd, timer_ID_ZOMBIES_CREATE, 10000, NULL); //20000
				SetTimer(hWnd, timer_ID_ZOMBIES_UPDATE, 200, NULL);
				gameStart = TRUE;
				gameOn = TRUE;
			}

			DrawBitmapDoubleBuffering(hWnd, hdc);


			for (auto e : zombies)
			{
				e->Draw(hdc, &rectView);
			}
			for (auto e : plants)
			{
				e->Draw(hdc, &rectView);
			}
			for (auto e : suns)
			{
				e->Draw(hdc, &rectView);
			}



			// >> : 버튼 선택
			HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(hdc, pen);
			SelectObject(hdc, GetStockObject(NULL_BRUSH));

			RECT btnSELECT = { 0, 0, 0, 0 };
			if (btnClick == sunflower)
				btnSELECT = btnPos[sunflower];
			else if (btnClick == peashooter)
				btnSELECT = btnPos[peashooter];

			Rectangle(hdc, btnSELECT.left, btnSELECT.top, btnSELECT.right, btnSELECT.bottom);

			// << :


			map->Draw(hdc, &rectView);

			if (gameStart)
			{
				Sleep(1000);
				DrawStartTest(hdc);
				cout << "얼음" << endl;
				Sleep(1000);
				cout << "땡" << endl;
				DeleteObject(hStartTextImage);
				gameStart = FALSE;
			}
		}
		else if (curMode == ending)
		{
			DrawEnding(hdc);
		}

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		DeleteBitmap();
		KillTimer(hWnd, timer_ID_UPDATE);

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
	{//title
		hTitleImage = (HBITMAP)LoadImage(NULL, TEXT("images/title.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hTitleImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("title 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hTitleImage, sizeof(BITMAP), &bitTitle);
	}

	{//ending
		hEndingImage = (HBITMAP)LoadImage(NULL, TEXT("images/ending.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hEndingImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("title 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hEndingImage, sizeof(BITMAP), &bitEnding);
	}


	{//mainmenu
		hMainMenuImage = (HBITMAP)LoadImage(NULL, TEXT("images/mainmenu.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hMainMenuImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("mainmenu 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hMainMenuImage, sizeof(BITMAP), &bitMainMenu);
	}

	{//mainmenu Btn
		hMainMenuBtnImage = (HBITMAP)LoadImage(NULL, TEXT("images/mainmenuBtn.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hMainMenuBtnImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("mainmenuBtn 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hMainMenuBtnImage, sizeof(BITMAP), &bitMainMenuBtn);
	}

	{//background
		hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hBackImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("background 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hBackImage, sizeof(BITMAP), &bitBack);
	}

	{// Sunflower btn
		hSunflowerImage = (HBITMAP)LoadImage(NULL, TEXT("images/Sunflower.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hSunflowerImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("Sunflower 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hSunflowerImage, sizeof(BITMAP), &bitSunflower);

		SPRITE_FRAME_COUNT_X = bitSunflower.bmWidth / 8;
		SPRITE_FRAME_COUNT_Y = bitSunflower.bmHeight / 2;
	}

	{//Progress Bar
		hProgressImage = (HBITMAP)LoadImage(NULL, TEXT("images/progress.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (hProgressImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("Progress Bar 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hProgressImage, sizeof(BITMAP), &bitProgress);

		SPRITE_FRAME_COUNT_X = bitProgress.bmWidth;
		SPRITE_FRAME_COUNT_Y = bitProgress.bmHeight;
	}

	{// Sun UI
		hSunUiImage = (HBITMAP)LoadImage(NULL, TEXT("images/SunUI.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (hSunUiImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("Sun UI 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hSunUiImage, sizeof(BITMAP), &bitSunUI);

		SPRITE_FRAME_COUNT_X = bitSunUI.bmWidth;
		SPRITE_FRAME_COUNT_Y = bitSunUI.bmHeight;
	}

	{// Sun
		hSunImage = (HBITMAP)LoadImage(NULL, TEXT("images/Sun.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (hSunImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("Sun 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hSunImage, sizeof(BITMAP), &bitSun);

		SPRITE_FRAME_COUNT_X = bitSun.bmWidth;
		SPRITE_FRAME_COUNT_Y = bitSun.bmHeight;
	}

	{// Peashooter
		hPeashooterImage = (HBITMAP)LoadImage(NULL, TEXT("images/Peashooter.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hPeashooterImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("Peashooter 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hPeashooterImage, sizeof(BITMAP), &bitPeashooter);

		SPRITE_FRAME_COUNT_X = bitPeashooter.bmWidth / 8;
		SPRITE_FRAME_COUNT_Y = bitPeashooter.bmHeight / 6;
	}

	{// HUD and fonts
		hHUDImage = (HBITMAP)LoadImage(NULL, TEXT("images/HUDandFonts.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hHUDImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("HUDandFonts 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hHUDImage, sizeof(BITMAP), &bitHUD);

	}

	{// Zombie
		hZombieImage = (HBITMAP)LoadImage(NULL, TEXT("images/Zombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hZombieImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("HUDandFonts 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hZombieImage, sizeof(BITMAP), &bitZombie);

	}

	{// StartText
		hStartTextImage = (HBITMAP)LoadImage(NULL, TEXT("images/Start-Text.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hStartTextImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("StartText 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hStartTextImage, sizeof(BITMAP), &bitStartText);

	}

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

		BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);

	}

	{ // Progress bar
		hMemDC2 = CreateCompatibleDC(hMemDC);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hProgressImage);
		bx = bitProgress.bmWidth;
		by = bitProgress.bmHeight;

		int xStart = 0;
		int yStart = 0;

		TransparentBlt(hMemDC, 500, 5, bx * 1.2, by * 2, hMemDC2, xStart, yStart, bx - 62, by, RGB(74, 74, 107));

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);

	}

	{// Progress
		hMemDC2 = CreateCompatibleDC(hMemDC);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hProgressImage);
		bx = bitProgress.bmWidth / 60;
		by = bitProgress.bmHeight / 3.5;

		int xStart = 319;
		int yStart = 20;

		// 제일 오른쪽 830 제일 왼쪽 505 headPos 338
		TransparentBlt(hMemDC, headPos + 30, 24, bx * progressSize, by * 3, hMemDC2, xStart, yStart, bx, by, RGB(74, 74, 107));

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);
	}

	{ // Progress bar head
		hMemDC2 = CreateCompatibleDC(hMemDC);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hProgressImage);
		bx = bitProgress.bmWidth / 10;
		by = bitProgress.bmHeight;

		int xStart = 262;
		int yStart = 0;

		// 제일 오른쪽 830 제일 왼쪽 505 headPos
		TransparentBlt(hMemDC, headPos, 5, bx * 2, by * 2, hMemDC2, xStart, yStart, bx, by, RGB(74, 74, 107));

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);

	}



	{ // Sun UI
		hMemDC2 = CreateCompatibleDC(hMemDC);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hSunUiImage);
		bx = bitSunUI.bmWidth;
		by = bitSunUI.bmHeight;

		int xStart = 0;
		int yStart = 0;

		TransparentBlt(hMemDC, 100, 5, bx / 40, by / 40, hMemDC2, xStart, yStart, bx / 2, by / 2, RGB(51, 0, 255));

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);

	}

	{ // Sun
		hMemDC2 = CreateCompatibleDC(hMemDC);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hSunImage);
		bx = bitSun.bmWidth / 2;
		by = bitSun.bmHeight;

		int xStart = 0;
		int yStart = 0;

		TransparentBlt(hMemDC, 110, 10, bx * 2, by * 2, hMemDC2, xStart, yStart, bx, by, RGB(0, 127, 14));

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);

	}

	{ // Fonts
		hMemDC2 = CreateCompatibleDC(hMemDC);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hHUDImage);
		bx = bitHUD.bmWidth / 57;
		by = bitHUD.bmHeight / 10;
		int singleDigit, xStart, yStart;
		int totalSun = sunScore;
		for (int i = 0; i < 4; i++)
		{
			singleDigit = totalSun % 10;
			totalSun /= 10;
			if (singleDigit == 0) singleDigit = 10;
			xStart = (singleDigit - 1) * 7;
			// 0: 1, 7:2
			yStart = 20;
			// 170
			TransparentBlt(hMemDC, 230 - 20 * i, 20, bx * 3, by * 3, hMemDC2, xStart, yStart, bx, by, RGB(0, 127, 14));
			if (totalSun < 1) break;
		}


		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);

	}

	// Peashooter btn
	{
		hMemDC2 = CreateCompatibleDC(hMemDC);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hPeashooterImage);
		bx = bitPeashooter.bmWidth / 8.3;
		by = bitPeashooter.bmHeight / 6;

		int xStart;
		int yStart = bitPeashooter.bmHeight / 6;
		BOOL state = FALSE;
		if (sunScore >= 100)
		{
			xStart = 113;
			state = TRUE;
		}
		else
		{
			xStart = 138;
			state = FALSE;
		}
		btnState[peashooter] = state;

		TransparentBlt(hMemDC, 0, 50, btnSize.x, btnSize.y, hMemDC2, xStart, yStart, bx, by, RGB(117, 101, 255));


		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);
	}


	// Sunflower btn
	{
		hMemDC2 = CreateCompatibleDC(hMemDC);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hSunflowerImage);
		bx = bitSunflower.bmWidth / 8;
		by = bitSunflower.bmHeight / 2.6;

		int xStart;
		int yStart = 37;
		BOOL state = FALSE;
		if (sunScore >= 50)
		{
			xStart = 30;
			state = TRUE;
		}
		else
		{
			xStart = 58;
			state = FALSE;
		}
		btnState[sunflower] = state;

		TransparentBlt(hMemDC, 0, 0, btnSize.x, btnSize.y, hMemDC2, xStart, yStart, bx, by, RGB(117, 101, 255));

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);
	}

	//{ // Zombie IDLE
	//	hMemDC2 = CreateCompatibleDC(hMemDC);
	//	hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hZombieImage);
	//	bx = bitZombie.bmWidth / 20;
	//	by = bitZombie.bmHeight / 3.2;

	//	int xStart = curframe / 3 * bx + 1;
	//	int yStart = 5;

	//	TransparentBlt(hMemDC, 900, 60, bx * 2.4, by * 2.4, hMemDC2, xStart, yStart, bx, by, RGB(104, 164, 255));

	//	SelectObject(hMemDC2, hOldBitmap2);
	//	DeleteDC(hMemDC2);
	//}

	//{ // Zombie SlightHurt
	//	hMemDC2 = CreateCompatibleDC(hMemDC);
	//	hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hZombieImage);
	//	bx = bitZombie.bmWidth / 29;
	//	by = bitZombie.bmHeight / 4.5;


	//	int xStart = 285+ curframeWalk * bx;
	//	int yStart = 98;


	//	switch (curframeWalk)
	//	{
	//	case 1:
	//		bx += 3;
	//		break;
	//	case 2:
	//		bx += 4;
	//		xStart += 4;
	//		break;
	//	case 3:
	//		bx += 5; 
	//		xStart += 9;
	//		break;
	//	case 4:
	//		bx += 12;
	//		xStart += 15;
	//		break;
	//	case 5:
	//		bx += 18;
	//		xStart += 28; 
	//		break;

	//	default:
	//		break;
	//	}
	//	
	//	TransparentBlt(hMemDC, xPos, 160, bx * 2.4, by * 2.4, hMemDC2, xStart, yStart, bx, by, RGB(104, 164, 255));
	//	SelectObject(hMemDC2, hOldBitmap2);
	//	DeleteDC(hMemDC2);

	//}

	//{ // Zombie Attack
	//	hMemDC2 = CreateCompatibleDC(hMemDC);
	//	hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hZombieImage);
	//	bx = bitZombie.bmWidth / 18.1;
	//	by = bitZombie.bmHeight / 3.2;

	//	int xStart = 302+ curframeAttack/4* bx;
	//	int yStart = 5;

	//	TransparentBlt(hMemDC, 900, 280, bx * 2.4, by * 2.4, hMemDC2, xStart, yStart, bx, by, RGB(104, 164, 255));

	//	SelectObject(hMemDC2, hOldBitmap2);
	//	DeleteDC(hMemDC2);

	//}

	//{ // Zombie WALK
	//	hMemDC2 = CreateCompatibleDC(hMemDC);
	//	hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hZombieImage);
	//	bx = bitZombie.bmWidth / 71;
	//	by = bitZombie.bmHeight / 10;

	//	int xStart = 494 + 0 * bx;
	//	int yStart = 120;

	//	TransparentBlt(hMemDC, xPos+12, 160+25, bx * 2.4, by * 2.4, hMemDC2, xStart, yStart, bx, by, RGB(104, 164, 255));

	//	SelectObject(hMemDC2, hOldBitmap2);
	//	DeleteDC(hMemDC2);

	//}

	//{ // Zombie WALK
	//	hMemDC2 = CreateCompatibleDC(hMemDC);
	//	hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hZombieImage);
	//	bx = bitZombie.bmWidth / 22;
	//	by = bitZombie.bmHeight / 3.1;

	//	int xStart = 117 + curframeWalk / 4 * bx;
	//	int yStart = 2;

	//	TransparentBlt(hMemDC, xPos, 300, bx * 2.4, by * 2.4, hMemDC2, xStart, yStart, bx, by, RGB(104, 164, 255));

	//	SelectObject(hMemDC2, hOldBitmap2);
	//	DeleteDC(hMemDC2);

	//}


	TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, RGB(255, 0, 255));
	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void DrawStartTest(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	int bx, by;
	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hStartTextImage);
	bx = bitStartText.bmWidth;
	by = bitStartText.bmHeight - 20;

	TransparentBlt(hdc, 400, 150, bx, by, hMemDC, 0, 20, bx, by, RGB(255, 255, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);

	//HDC hMemDC;
	//HBITMAP hOldBitmap;
	//int bx, by;

	//hMemDC = CreateCompatibleDC(hdc);
	//if (hDoubleBufferImage == NULL)
	//{
	//	hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
	//}
	//hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

	//{ // 배경
	//	hMemDC = CreateCompatibleDC(hMemDC);
	//	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hStartTextImage);
	//	bx = bitStartText.bmWidth;
	//	by = bitStartText.bmHeight;

	//	BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);

	//	SelectObject(hMemDC, hOldBitmap);
	//	DeleteDC(hMemDC);

	//}
}

void DrawTitle(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	int bx, by;
	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hTitleImage);
	bx = rectView.right - rectView.left;
	by = rectView.bottom - rectView.top;

	
	TransparentBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, bitTitle.bmWidth, bitTitle.bmHeight, NULL);

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void DrawMainMenu(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	int bx, by;

	// screen
	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hMainMenuImage);
	bx = rectView.right - rectView.left;
	by = rectView.bottom - rectView.top;


	TransparentBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, bitMainMenu.bmWidth/3, bitMainMenu.bmHeight, NULL);

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);

	// btn
	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hMainMenuBtnImage);
	bx = bitMainMenuBtn.bmWidth / 12;
	by = bitMainMenuBtn.bmHeight / 5;

	int xStart = 660;
	int yStart = 30;

	TransparentBlt(hdc, 500, 130, bx * 2.5, by * 2.5, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 214));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void DrawEnding(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	int bx, by;
	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hEndingImage);
	bx = bitEnding.bmWidth;
	by = bitEnding.bmHeight;


	TransparentBlt(hdc, 250, 80, bx, by, hMemDC, 0, 0, bx, by, NULL);

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}


void DeleteBitmap()
{
	DeleteObject(hAniImage);
	DeleteObject(hBackImage);
}

void UpdataFrame(HWND hWnd)
{
	curframe++;
	if (curframe > 9) curframe = RUN_FRAME_MIN;

	curframeWalk++;
	if (curframeWalk > 5) curframeWalk = 0;

	curframeAttack++;
	if (curframeAttack > 19) curframeAttack = 0;

	xPos -= 0.5;
	InvalidateRect(hWnd, NULL, false);

}

void Gdi_Init()
{
	GdiplusStartupInput gpsi;
	GdiplusStartup(&g_GdiToken, &gpsi, NULL);
}

void Gdi_End()
{
	GdiplusShutdown(g_GdiToken);
}

