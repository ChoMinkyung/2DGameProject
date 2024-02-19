#pragma once

#include "framework.h"
#include "CObject.h"

class CSun : public CObject
{
private:
	POINT sunPos;
	HBITMAP hSunImage;
	BITMAP bitSun;
	int sunCurframe;
	BOOL inClick;
	int updateY;
	int count;
public:
	CSun(RECT* rectView);
	CSun(POINT pos);
	~CSun();

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

