#pragma once
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

#include <objidl.h>
#include <gdiplus.h> 
#pragma comment(lib, "Gdiplus.lib")


enum State { Update, SunUpdate, SunCreate, Progress, ZombieCreate, ZombieUpdate };
enum btn { sunflower = 0, peashooter };
enum Mode { title, mainmenu, game, ending };

#define timer_ID_UPDATE Update
#define timer_ID_SUN_UPDATE SunUpdate
#define timer_ID_SUN_CREATE SunCreate
#define timer_ID_PROGRESS Progress
#define timer_ID_ZOMBIES_CREATE ZombieCreate
#define timer_ID_ZOMBIES_UPDATE ZombieUpdate

using namespace Gdiplus;
void Gdi_Init();
void Gdi_End();

using namespace std;
ULONG_PTR g_GdiToken;

bool gameStart;
bool gameOn;

int curMode;


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

HBITMAP hDoubleBufferImage;
RECT rectView;

void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
void CreateBitmap();
void DeleteBitmap();
void UpdataFrame(HWND hWnd);

void DrawStartTest(HDC hdc);

CObject* map = new CMap();
int sunScore;
POINT btnSize = { 80, 60 };
vector<RECT> btnPos;
vector<BOOL> btnState;