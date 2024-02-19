#include "CSun.h"
#include <math.h>
#include <iostream>

CSun::CSun(RECT* rectView)
{
	count = 0;
	updateY = 1;

	sunPos.x = rand() % (rectView->right - rectView->left - 400) + 300;
	//cout << "생성된 해 위치 : " << sunPos.x << endl;
	sunPos.y = 0;
	sunCurframe = 0;

	{//Sun
		hSunImage = (HBITMAP)LoadImage(NULL, TEXT("images/Sun.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hSunImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("Sun 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hSunImage, sizeof(BITMAP), &bitSun);
	}
}

CSun::CSun(POINT pos)
{
	count = 0;
	updateY = 0;
	sunPos.x = pos.x + 50;
	sunPos.y = pos.y + 50;

	//cout << "생성된 해 위치 : " << sunPos.x << endl;
	sunCurframe = 0;

	{//Sun
		hSunImage = (HBITMAP)LoadImage(NULL, TEXT("images/Sun.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hSunImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("Sun 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hSunImage, sizeof(BITMAP), &bitSun);
	}
}

CSun::~CSun()
{

}

void CSun::Update(RECT* rectView)
{
	
	if (!inClick)
	{
		sunCurframe++;
		if (sunCurframe > 1) sunCurframe = 0;

		if (updateY == 1)
			if (sunPos.y < (rectView->bottom - rectView->top) - 100)sunPos.y += 1;
			else count++;

		if (updateY == 0)
			count++;
	}
	else
	{
		float direction_x = sunPos.x - 100;
		float direction_y = sunPos.y - 15;

		direction_x = direction_x / sqrt(pow(sunPos.x, 2) + pow(sunPos.y, 2)) * 2;
		direction_y = direction_y / sqrt(pow(sunPos.x, 2) + pow(sunPos.y, 2));

		if (direction_x < 1) direction_x = 1;
		if (direction_y < 1 && direction_y > 0) direction_y = 1;

		direction_x *= -1;
		direction_y *= -1;


		for (int i = 0; i < 20; i++)
		{
			if (sunPos.x > 100) sunPos.x += direction_x;
			if (sunPos.y > 15) sunPos.y += direction_y;

			if (sunPos.x <= 100 && sunPos.y <= 15)
			{
				break;
			}
		}


	}
}

void CSun::Draw(HDC hdc, RECT* rectView)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;

	hMemDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL)
	{
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView->right, rectView->bottom);
	}
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

	{ // Sun
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hSunImage);
		bx = bitSun.bmWidth / 2;
		by = bitSun.bmHeight;

		int xStart = sunCurframe * bx;
		int yStart = 0;

		TransparentBlt(hdc, sunPos.x, sunPos.y, bx * 2, by * 2, hMemDC, xStart, yStart, bx, by, RGB(0, 127, 14));

		// 클릭 범위
		//Ellipse(hdc, sunPos.x, sunPos.y, sunPos.x + 50, sunPos.y + 50);

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);

	}


}

BOOL CSun::SetInClick(POINT ptMousePos)
{

	if (pow(ptMousePos.x - (sunPos.x + 25), 2)
		+ pow(ptMousePos.x - (sunPos.x + 25), 2) < pow(25, 2)
		&& pow(ptMousePos.y - (sunPos.y + 25), 2)
		+ pow(ptMousePos.y - (sunPos.y + 25), 2) < pow(25, 2))
	{
		inClick = TRUE;
	}

	if (inClick) return TRUE;
	else return FALSE;
}

void CSun::DeleteBitmap()
{
	DeleteObject(hSunImage);
}

POINT CSun::GetPos()
{
	return sunPos;
}

int CSun::Species()
{
	return 0;
}

int CSun::Count()
{
	return count;
}

int CSun::Collision(POINT pos)
{
	return 0;
}

int CSun::GetState()
{
	return 0;
}

