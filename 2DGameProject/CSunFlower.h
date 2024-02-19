#pragma once
#include "CObject.h"

class CSunFlower : public CObject
{
private:
	POINT sunFlowerPos;
	HBITMAP hSunflowerImage;
	BITMAP bitSunflower;
	int sunFlowerCurframe = 0;
	int SPRITE_FRAME_COUNT_X = 0;
	int SPRITE_FRAME_COUNT_Y = 0;
	int plantsSpecies = 0; // sunflower
	int sunCount;
	int beShot;
public:
	CSunFlower(POINT pos);
	~CSunFlower();

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

