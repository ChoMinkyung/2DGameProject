#include "CMap.h"
#include "framework.h"

#include <objidl.h>
#include <gdiplus.h> 
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;

CMap::CMap()
{
	map_tile = std::vector<std::vector<MapTile*>>(row, std::vector<MapTile*>(col, nullptr));

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			map_tile[i][j] = new MapTile();
			map_tile[i][j]->rect_size = { 255 + j * 80, 80 + i * 100, 80,100 };
			map_tile[i][j]->plants = FALSE;
			map_tile[i][j]->mouseIn = FALSE;
		}
	}
}

CMap::~CMap()
{
}

void CMap::Update(RECT* rectView)
{
}

void CMap::Draw(HDC hdc, RECT* rectView)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{

			Graphics graphics(hdc);
			SolidBrush brush(Color(100, 255, 255, 255));
			if (map_tile[i][j]->mouseIn && !map_tile[i][j]->plants)
			{
				graphics.FillRectangle(&brush, map_tile[i][j]->rect_size.left, map_tile[i][j]->rect_size.top, 80, 100);

			}

		}
	}
}


BOOL CMap::SetInClick(POINT ptMousePos)
{
	BOOL temp = false;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (ptMousePos.x > map_tile[i][j]->rect_size.left
				&& ptMousePos.x < map_tile[i][j]->rect_size.left + map_tile[i][j]->rect_size.right
				&& ptMousePos.y > map_tile[i][j]->rect_size.top
				&& ptMousePos.y < map_tile[i][j]->rect_size.bottom + map_tile[i][j]->rect_size.top)

			{
				map_tile[i][j]->mouseIn = TRUE;
				temp = true;
			}
			else
			{
				map_tile[i][j]->mouseIn = FALSE;
			}
		}
	}

	if (temp) return true;
	else return false;

}

void CMap::DeleteBitmap()
{

}

POINT CMap::GetPos()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{

			if (map_tile[i][j]->mouseIn)
			{
				if (map_tile[i][j]->plants)
				{
					return{ -1, -1 };
				}
				map_tile[i][j]->plants = TRUE;
				return { map_tile[i][j]->rect_size.left,  map_tile[i][j]->rect_size.top };
			}


		}
	}
}

int CMap::Species()
{
	return 0;
}

int CMap::Count()
{
	return 0;
}

int CMap::Collision(POINT pos)
{
	return 0;
}

int CMap::GetState()
{
	return 0;
}
