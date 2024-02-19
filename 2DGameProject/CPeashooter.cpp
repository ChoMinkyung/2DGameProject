#include "CPeashooter.h"

CPeashooter::CPeashooter(POINT pos)
{
	peashooterPos = pos;

	peaPos.x = pos.x + 55;
	peaPos.y = pos.y + 15,
		peaCount = 0;
	beShot = 0;

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

	{// Peashooter
		hPeaImage = (HBITMAP)LoadImage(NULL, TEXT("images/Peashooter.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hPeaImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("Peashooter 이미지 로드 에러"), _T("에러에러에러"), MB_OK);
			return;
		}
		GetObject(hPeaImage, sizeof(BITMAP), &bitPea);

		SPRITE_FRAME_COUNT_X = bitPea.bmWidth / 8;
		SPRITE_FRAME_COUNT_Y = bitPea.bmHeight / 6;
	}
}



CPeashooter::~CPeashooter()
{
}

void CPeashooter::Update(RECT* rectView)
{
	peashooterCurframe++;
	if (peashooterCurframe > 7) peashooterCurframe = 0;

	if (peaState == wait)
	{
		peaCurframe = 0;
		peaCount++;
		if (peaCount == 30)
		{
			peaPos.x = peashooterPos.x + 55;
			peaState = shoot;
		}
	}
	else if (peaState == shoot)
	{
		peaPos.x += 15;

		if (peaPos.x > rectView->right)
		{
			peaPos.x = peashooterPos.x + 55;
			peaState = wait;
			//DeleteBitmap();
		}

	}
	else if (peaState == attack)
	{
		peaCurframe++;
		if (peaCurframe > 2)
		{
			peaPos.x = peashooterPos.x + 55;
			peaCurframe = 0;
			peaState = wait;

		}
	}

}

void CPeashooter::Draw(HDC hdc, RECT* rectView)
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
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hPeashooterImage);
		bx = SPRITE_FRAME_COUNT_X;
		by = SPRITE_FRAME_COUNT_Y;

		int xStart;
		int yStart;

		if (peaCount > 27)
		{
			bx -= 2;
			xStart = (peaCount - 28) * bx;
			yStart = SPRITE_FRAME_COUNT_Y;
			if (peaCount == 30) peaCount = 0;
		}
		else
		{
			xStart = peashooterCurframe * bx;
			yStart = 0;
		}


		TransparentBlt(hdc, peashooterPos.x + 5, peashooterPos.y + 5, bx * 2.5, by * 2.5, hMemDC, xStart, yStart, bx, by, RGB(117, 101, 255));

		// 범위
		/*HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, peashooterPos.x, peashooterPos.y, peashooterPos.x + 70, peashooterPos.y + 90);
*/

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}

	if (peaState != wait)
	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hPeaImage);
		bx = bitPea.bmWidth / 19;
		by = bitPea.bmHeight / 15;

		int xStart = 77 + peaCurframe * 12;
		int yStart = 43;

		if (peaCurframe == 2)
			TransparentBlt(hdc, peaPos.x, peaPos.y, bx * 2.5, by * 2.5, hMemDC, xStart - 1, yStart - 3, bx + 2, by + 2, RGB(117, 101, 255));
		else
			TransparentBlt(hdc, peaPos.x, peaPos.y, bx * 2.5, by * 2.5, hMemDC, xStart, yStart, bx, by, RGB(117, 101, 255));

		// 범위

		/*HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
		if(peaState==attack)pen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));

		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, peaPos.x, peaPos.y, peaPos.x + 30, peaPos.y + 30);*/



		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}

}

BOOL CPeashooter::SetInClick(POINT ptMousePos)
{
	return 0;
}

void CPeashooter::DeleteBitmap()
{
	DeleteObject(hPeaImage);
}

POINT CPeashooter::GetPos()
{
	return POINT();
}

int CPeashooter::Species()
{
	return 0;
}

int CPeashooter::Count()
{
	return 0;
}

int CPeashooter::Collision(POINT pos)
{
	if (peaPos.x + 10 > pos.x && peaPos.y > pos.y - 110 && peaPos.y < pos.y)
	{
		peaState = attack;
		return pea;
	}

	if (peashooterPos.x + 80 > pos.x && peashooterPos.y > pos.y - 110 && peashooterPos.y < pos.y)
	{
		beShot++;
		if (beShot > 80) return -1;
		return plant;
	}

	return 0;
}

int CPeashooter::GetState()
{
	//if (beShot > 10) return -1;
	return 0;
}
