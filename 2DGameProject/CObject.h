#pragma once
#include "framework.h"
#include <time.h>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;



struct Map
{
	POINT pos;
};

class CObject
{
protected:
	HBITMAP hDoubleBufferImage;
public:
	virtual void Update(RECT* rectView) = 0;
	virtual void Draw(HDC hdc, RECT* rectView) = 0;
	virtual void DeleteBitmap() = 0;
	virtual POINT GetPos() = 0;
	virtual int Collision(POINT pos) = 0;

	virtual BOOL SetInClick(POINT ptMousePos) = 0;
	virtual int Species() = 0;
	virtual int Count() = 0;
	virtual int GetState() = 0;
};

