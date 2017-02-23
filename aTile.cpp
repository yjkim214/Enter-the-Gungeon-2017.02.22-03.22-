#include "stdafx.h"
#include "aTile.h"

HRESULT aTile::init(int idX, int idY, int tileWidth, int tileHeight, int startX, int startY)
{
	_idX = idX;						//Save xIndex
	_idY = idY;						//Save yIndex

	_color = RGB(250, 150, 0);		//tangerine color
	_isOpen = true;					//Set to go once
	_isListOn = false;				//Not on the open list
	_center = PointMake(idX * tileWidth + (tileWidth / 2), idY * tileHeight + (tileHeight / 2));	//Center coordinates to draw tile rectangle
	_rc = RectMakeCenter(_center.x + startX, _center.y + startY, tileWidth, tileHeight);			//Draw with a RectMakeCenter

	return S_OK;
}

void aTile::render()
{
	HBRUSH newBrush, oldBrush;

	newBrush = CreateSolidBrush(_color);
	oldBrush = (HBRUSH)SelectObject(getMemDC(), newBrush);

	RectangleMake(getMemDC(), _rc);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(newBrush);
}
