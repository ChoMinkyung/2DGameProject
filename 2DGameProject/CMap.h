#pragma once

#include "CObject.h"
#include <vector>
struct MapTile
{
	RECT rect_size;
	BOOL plants;
	BOOL mouseIn;
};

class CMap : public CObject
{
private:
	std::vector<vector<MapTile*>> map_tile;
	int row = 5;
	int col = 9;
	ULONG_PTR g_GdiToken;

public:
	CMap();
	~CMap();
	void Update(RECT* rectView) override;
	void Draw(HDC hdc, RECT* rectView) override;
	BOOL SetInClick(POINT ptMousePos) override;
	void DeleteBitmap() override;
	POINT GetPos()override;
	int Species() override;
	int Count() override;
	int Collision(POINT pos) override;
	int GetState() override;

};

