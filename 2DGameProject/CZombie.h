#pragma once
#include "CObject.h"

class CZombie : public CObject
{
private:
	POINT zombiePos;
	HBITMAP hZombieImage;
	BITMAP bitZombie;
	int zombieCurframe = 0;
	int state; // 0:IDLE 1:Walk 2:Attack 3:Die
	int beShot;
	int changeCOLOR;
	int blueFrame;

	BOOL arm;
	BOOL head;

	POINT armPos;
	POINT headPos;
public:
	CZombie();
	~CZombie();

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

