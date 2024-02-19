#pragma once
#include "CObject.h"

enum { plant = 1, pea, wait, shoot, attack };

class CPeashooter : public CObject
{
private:
	POINT peashooterPos;
	POINT peaPos;
	HBITMAP hPeashooterImage;
	HBITMAP hPeaImage;
	BITMAP bitPeashooter;
	BITMAP bitPea;

	int beShot;
	int peashooterCurframe = 1;
	int peaCurframe = 0;
	int SPRITE_FRAME_COUNT_X = 0;
	int SPRITE_FRAME_COUNT_Y = 0;
	int plantsSpecies = 1; // peashooter
	int peaCount; // wait
	int peaState = wait; // 
public:
	CPeashooter(POINT pos);
	~CPeashooter();

	void Update(RECT* rectView)override;
	void Draw(HDC hdc, RECT* rectView) override;
	BOOL SetInClick(POINT ptMousePos) override;
	void DeleteBitmap() override;
	POINT GetPos()override;
	int Species() override;
	int Count() override;
	int Collision(POINT pos) override;
	int GetState() override;

};

