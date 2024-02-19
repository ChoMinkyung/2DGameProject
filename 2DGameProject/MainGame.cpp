#include "MainGame.h"

void CreateBitmap()
{
	{//title
		hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/title.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hBackImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("title 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hBackImage, sizeof(BITMAP), &bitBack);
	}

	{//mainmenu
		hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/mainmenu.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hBackImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("title 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hBackImage, sizeof(BITMAP), &bitBack);
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
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hStartTextImage);
	bx = bitStartText.bmWidth;
	by = bitStartText.bmHeight - 20;

	TransparentBlt(hdc, 400, 150, bx, by, hMemDC, 0, 20, bx, by, RGB(255, 255, 255));

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