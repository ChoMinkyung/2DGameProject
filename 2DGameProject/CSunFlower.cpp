#include "CSunFlower.h"
#include "CSun.h"

CSunFlower::CSunFlower(POINT pos)
{
	sunFlowerPos = pos;
	sunCount = 0;
	beShot = 0;
	{//Sunflower
		hSunflowerImage = (HBITMAP)LoadImage(NULL, TEXT("images/Sunflower.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hSunflowerImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("Sunflower 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hSunflowerImage, sizeof(BITMAP), &bitSunflower);

		SPRITE_FRAME_COUNT_X = bitSunflower.bmWidth / 8;
		SPRITE_FRAME_COUNT_Y = bitSunflower.bmHeight / 2.2;
	}

}

CSunFlower::~CSunFlower()
{
}

void CSunFlower::Update(RECT* rectView)
{
	sunFlowerCurframe++;
	if (sunFlowerCurframe > 7) sunFlowerCurframe = 0;
	sunCount++;
	if (sunCount > 50)
	{
		sunFlowerCurframe = 0;
		sunCount = 0;
	}
}

void CSunFlower::Draw(HDC hdc, RECT* rectView)
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

	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hSunflowerImage);
		bx = SPRITE_FRAME_COUNT_X;
		by = SPRITE_FRAME_COUNT_Y;

		int xStart = sunFlowerCurframe * bx + 2;
		int yStart = 5;

		if (sunCount > 45)
		{
			xStart = 2;
			yStart = 36;
		}

		TransparentBlt(hdc, sunFlowerPos.x, sunFlowerPos.y + 5, bx * 2.5, by * 2.5, hMemDC, xStart, yStart, bx, by, RGB(117, 101, 255));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}


}


BOOL CSunFlower::SetInClick(POINT ptMousePos)
{
	return 0;
}

void CSunFlower::DeleteBitmap()
{
}

POINT CSunFlower::GetPos()
{
	return sunFlowerPos;
}

int CSunFlower::Species()
{
	return plantsSpecies;
}

int CSunFlower::Count()
{
	return sunCount;
}

int CSunFlower::Collision(POINT pos)
{
	if (sunFlowerPos.x + 75 > pos.x && sunFlowerPos.y > pos.y - 110 && sunFlowerPos.y < pos.y)
	{
		beShot++;
		if (beShot > 80) return -1;
		return 1;
	}
}

int CSunFlower::GetState()
{
	//if (beShot > 20) return -1;
	return 0;
}
