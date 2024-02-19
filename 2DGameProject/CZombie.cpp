#include "CZombie.h"
// >> : GDI+
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
// << :

enum {
	plant = 1, projectile,
	IDLE, Walk, Attack, SlightHurt, BadlyHurt, AttackSlightHurt, AttackBadlyHurt, Die, Delete
};


CZombie::CZombie()
{
	state = Walk;
	beShot = 0;
	changeCOLOR = 0;

	head = FALSE;
	arm = FALSE;

	int yPos = rand() % 5;

	if (yPos == 0) zombiePos.y = 60 + 110;
	else if (yPos == 1)zombiePos.y = 160 + 110;
	else if (yPos == 2)zombiePos.y = 250 + 110;
	else if (yPos == 3)zombiePos.y = 350 + 110;
	else if (yPos == 4)zombiePos.y = 460 + 110;

	zombiePos.x = 1000;

	{// Zombie
		hZombieImage = (HBITMAP)LoadImage(NULL, TEXT("images/Zombie.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hZombieImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("Zombie ÀÌ¹ÌÁö ·Îµå ¿¡·¯"), _T("¿¡·¯¿¡·¯¿¡·¯"), MB_OK);
			return;
		}
		GetObject(hZombieImage, sizeof(BITMAP), &bitZombie);
	}
}

CZombie::~CZombie()
{
	DeleteBitmap();
}

void CZombie::Update(RECT* rectView)
{
	zombieCurframe++;

	switch (state)
	{
	case IDLE:
		if (zombieCurframe > 2) zombieCurframe = 0;
		break;
	case Walk:
		zombiePos.x--;
		if (zombieCurframe > 5) zombieCurframe = 0;
		break;

	case SlightHurt:
		zombiePos.x--;
	case AttackSlightHurt:
		if (zombieCurframe > 5) zombieCurframe = 0;

		if (arm)
		{
			armPos.y += 10;
			if (armPos.y > zombiePos.y - 30) arm = FALSE;
		}
		break;

	case BadlyHurt:
		zombiePos.x--;
	case AttackBadlyHurt:

		if (head)
		{
			cout << "¸Ó¸® ¶³¾îÁü" << endl;
			headPos.x += 5;
			headPos.y += 10;
			if (headPos.y > zombiePos.y - 30) head = FALSE;
		}

		if (zombieCurframe > 11)
		{
			state = Die;
			zombieCurframe = 0;
		}
		break;
	case Die:
		if (zombieCurframe > 5)
		{
			state = Delete;
		}
		break;
	case Attack:
		if (zombieCurframe > 4) zombieCurframe = 0;
		break;
	default:
		break;
	}


}

void CZombie::Draw(HDC hdc, RECT* rectView)
{

	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;
	int xStart;
	int yStart;

	hMemDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL)
	{
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView->right, rectView->bottom);
	}
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

	switch (state)
	{
	case IDLE:
	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hZombieImage);
		bx = bitZombie.bmWidth / 20;
		by = bitZombie.bmHeight / 3.2;

		xStart = zombieCurframe * bx + 1;
		yStart = 5;
	}
	break;
	case Walk:
	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hZombieImage);
		bx = bitZombie.bmWidth / 22;
		by = bitZombie.bmHeight / 3.1;

		xStart = 117 + zombieCurframe * bx;
		yStart = 2;
	}
	break;
	case Attack:
	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hZombieImage);
		bx = bitZombie.bmWidth / 18.1;
		by = bitZombie.bmHeight / 3.2;

		xStart = 302 + zombieCurframe * bx;
		yStart = 5;


	}
	break;
	case AttackSlightHurt: // ÆÈ ¶³¾îÁü
	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hZombieImage);
		bx = bitZombie.bmWidth / 18.2;
		by = bitZombie.bmHeight / 3.2;


		xStart = 296 + zombieCurframe * bx;
		yStart = 52;

		if (zombieCurframe == 5)
		{
			bx = bitZombie.bmWidth / 19;
		}

	}
	break;

	case SlightHurt: // ÆÈ ¶³¾îÁü
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hZombieImage);
		bx = bitZombie.bmWidth / 23;
		by = bitZombie.bmHeight / 3.1;

		xStart = 116 + zombieCurframe * bx;
		yStart = 50;

		if (zombieCurframe == 1) xStart = 117 + zombieCurframe * bx;
		if (zombieCurframe == 5) bx = bitZombie.bmWidth / 21;


		break;
	case AttackBadlyHurt: // ¸Ó¸® ¶³¾îÁü
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hZombieImage);
		bx = bitZombie.bmWidth / 19;
		by = bitZombie.bmHeight / 5;

		xStart = 136 + zombieCurframe % 5 * bx;
		yStart = 100;

		if (zombieCurframe % 5 == 3) bx += 2;
		else if (zombieCurframe % 5 == 4)
		{
			bx++;
			xStart += 2;
		}


		break;
	case BadlyHurt: // ¸Ó¸® ¶³¾îÁü
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hZombieImage);
		bx = bitZombie.bmWidth / 29;
		by = bitZombie.bmHeight / 4.5;

		xStart = 1 + zombieCurframe % 6 * bx;
		yStart = 97;

		if (zombieCurframe % 6 == 4)  bx -= 3;
		else if (zombieCurframe % 6 == 5) xStart -= 3;

		break;
	case Die: // ¾²·¯Áø ÈÄ »ç¶óÁü(Delete)
	{

		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hZombieImage);
		bx = bitZombie.bmWidth / 29;
		by = bitZombie.bmHeight / 4.5;

		xStart = 285 + zombieCurframe * bx;
		yStart = 98;

		switch (zombieCurframe)
		{
		case 1:
			bx += 3;
			break;
		case 2:
			bx += 4;
			xStart += 4;
			break;
		case 3:
			bx += 5;
			xStart += 9;
			break;
		case 4:
			bx += 12;
			xStart += 15;
			break;
		case 5:
			bx += 18;
			xStart += 28;
			break;
		case 6:
			xStart = 285 + 5 * bx + 28;
			bx += 18;
			break;
		default:
			break;
		}

		break;
	}
	default:
		break;
	}




	if (changeCOLOR > 0)
	{
		for (int y = 0; y < by; y++) {
			for (int x = 0; x < bx; x++) {
				COLORREF pixelColor = GetPixel(hMemDC, xStart + x, yStart + y);
				BYTE r = GetRValue(pixelColor);
				BYTE g = GetGValue(pixelColor);
				BYTE b = GetBValue(pixelColor);

				if (pixelColor != RGB(104, 164, 255)) b = min(b + 50, 255);
				SetPixel(hMemDC, xStart + x, yStart + y, RGB(r, g, b));
			}
		}
	}

	TransparentBlt(hdc, zombiePos.x, zombiePos.y - by * 2.4, bx * 2.4, by * 2.4, hMemDC, xStart, yStart, bx, by, RGB(104, 164, 255));


	if (changeCOLOR > 0)
	{
		for (int y = 0; y < by; y++) {
			for (int x = 0; x < bx; x++) {
				COLORREF pixelColor = GetPixel(hMemDC, xStart + x, yStart + y);
				BYTE r = GetRValue(pixelColor);
				BYTE g = GetGValue(pixelColor);
				BYTE b = GetBValue(pixelColor);
				if (pixelColor != RGB(104, 164, 255)) b = max(b - 50, 0);
				SetPixel(hMemDC, xStart + x, yStart + y, RGB(r, g, b));
			}
		}
		if (changeCOLOR >= 2)changeCOLOR = 0;
	}

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);

	if (arm)
	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hZombieImage);
		bx = bitZombie.bmWidth / 79;
		by = bitZombie.bmHeight / 10;

		xStart = bx + 487;
		yStart = 120;
		TransparentBlt(hdc, armPos.x + 28, armPos.y, bx * 2.4, by * 2.4, hMemDC, xStart, yStart, bx, by, RGB(104, 164, 255));
	}
	if (head)
	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hZombieImage);
		bx = bitZombie.bmWidth / 29;
		by = bitZombie.bmHeight / 7;

		xStart = bx + 484;
		yStart = 119;
		TransparentBlt(hdc, headPos.x, headPos.y, bx * 2.4, by * 2.4, hMemDC, xStart, yStart, bx, by, RGB(104, 164, 255));
	}

	// ¹üÀ§
	/*HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, zombiePos.x, zombiePos.y-110, zombiePos.x + 60, zombiePos.y );*/



	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);

}

BOOL CZombie::SetInClick(POINT ptMousePos)
{
	return 0;
}

void CZombie::DeleteBitmap()
{
	DeleteObject(hZombieImage);
}

POINT CZombie::GetPos()
{
	return zombiePos;
}

int CZombie::Species()
{
	return 0;
}

int CZombie::Count()
{
	return 0;
}


int CZombie::Collision(POINT pos)
{
	if (pos.x == -1)
	{
		if (state == Attack) state = Walk;
		else if (state == AttackSlightHurt) state = SlightHurt;
		else if (state == AttackBadlyHurt) state = BadlyHurt;
	}
	else if (pos.x == 1)
	{
		if (state == Walk) state = Attack;
		else if (state == SlightHurt) state = AttackSlightHurt;
		else if (state == BadlyHurt) state = AttackBadlyHurt;
	}
	else if (pos.x == 2)
	{
		beShot++;

		if (beShot % 3 != 0)
		{
			changeCOLOR++;
		}

		if (beShot == 12)
		{
			arm = TRUE;
			armPos = zombiePos;
			armPos.y -= 60;

			if (state == Walk) state = SlightHurt;
			else if (state == Attack) state = AttackSlightHurt;

		}
		else if (beShot == 18)
		{
			head = TRUE;
			headPos = zombiePos;
			headPos.y -= 110;

			if (state == SlightHurt) state = BadlyHurt;
			else if (state == AttackSlightHurt) state = AttackBadlyHurt;

		}
		else if (beShot == 21)
		{
			zombieCurframe = 0;
			state = Die;
		}



	}
	return 0;
}

int CZombie::GetState()
{
	if (state == Delete)
	{
		changeCOLOR = 0;
		return -1;
	}
	return 0;
}

